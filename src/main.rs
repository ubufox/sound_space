use rodio::{source::Source, Decoder, OutputStream, Sink};
use serde_json::Result;
use std::collections::HashMap;
use std::fs::File;
use std::io::BufReader;
use std::sync::{Arc, Mutex};

use sound_space::mock_zed::ZedProcessor;
use sound_space::models::space::Space;
use sound_space::models::zone::Zone;

fn main() {
    let (_stream, stream_handle) = OutputStream::try_default().unwrap();

    let zones: Vec<Zone> = read_zone_data().unwrap();

    let sinks: HashMap<u8, Sink> = zones.clone().iter().fold(HashMap::new(), |mut acc, z| {
        let sink = Sink::try_new(&stream_handle).unwrap();
        let file = BufReader::new(File::open(z.sample_path()).unwrap());
        let source = Decoder::new(file).unwrap();

        sink.append(source.repeat_infinite());

        acc.insert(z.id, sink);
        acc
    });

    let starting_volume: f32 = 0.0;
    let keys: Vec<u8> = zones.clone().iter().fold(vec![], |mut acc, z| {
        acc.push(z.id);
        acc
    });

    let volumes: HashMap<u8, f32> = keys.iter().fold(HashMap::new(), |mut acc, k| {
        acc.insert(k.clone(), starting_volume);
        acc
    });

    let volume_arc = Arc::new(Mutex::new(volumes));
    let thread_volume = volume_arc.clone();

    let interactive_spaces: Vec<Space> = zones
        .clone()
        .iter()
        .map(|z| Space::build_from_zone(z))
        .collect();

    // ###### SET VOLUMES #######
    // IN: Vec<Spaces>
    // OUT: Recurring updates to a fill_data RwLock<HashMap<u8, f32>>
    std::thread::spawn(move || {
        let zed = ZedProcessor::new();

        loop {
            match thread_volume.lock() {
                Ok(mut v_hash) => {
                    *v_hash = zed.get_fills(interactive_spaces.clone());
                    drop(v_hash);
                    std::thread::sleep(std::time::Duration::from_millis(5));
                }
                Err(_) => {
                    std::thread::sleep(std::time::Duration::from_millis(1));
                }
            }
        }
    });

    // ###### UPDATE VOLUMES #######
    std::thread::spawn(move || loop {
        match volume_arc.lock() {
            Ok(v_hash) => {
                for (k, v) in v_hash.clone().into_iter() {
                    let s = sinks.get(&k).unwrap();

                    s.set_volume(v);
                }

                drop(v_hash);
            }
            Err(_) => {}
        };

        std::thread::sleep(std::time::Duration::from_millis(5));
    });

    loop {}
}

fn read_zone_data() -> Result<Vec<Zone>> {
    let zone_data =
        std::fs::read_to_string("data/zones.json").expect("Failed to read zone data file");
    let zones: Vec<Zone> = serde_json::from_str(&zone_data)?;

    Ok(zones)
}
