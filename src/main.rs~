use rodio::{source::Source, Decoder, OutputStream, Sink};
use serde_json::Result;
use std::collections::HashMap;
use std::fs::File;
use std::io::BufReader;
use std::sync::{Arc, Mutex};

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

    let starting_volume: f32 = 1.0;
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

    // ###### SET VOLUMES #######
    std::thread::spawn(move || {
        let mut is_loud = true;

        loop {
            println!("loud state -> {is_loud}");

            match thread_volume.lock() {
                Ok(mut v_hash) => {
                    let mut updated_hash: HashMap<u8, f32> = HashMap::new();

                    if is_loud {
                        for (k, _v) in v_hash.clone().into_iter() {
                            updated_hash.insert(k, 2.0);
                        }
                    } else {
                        for (k, _v) in v_hash.clone().into_iter() {
                            updated_hash.insert(k, 0.4);
                        }
                    }

                    *v_hash = updated_hash;

                    is_loud = !is_loud;
                    std::thread::sleep(std::time::Duration::from_secs_f32(7.5));
                }
                Err(_) => {
                    std::thread::sleep(std::time::Duration::from_millis(1));
                }
            }
        }
    });

    // ###### UPDATE VOLUMES #######
    loop {
        match volume_arc.lock() {
            Ok(v_hash) => {
                for (k, v) in v_hash.clone().into_iter() {
                    let s = sinks.get(&k).unwrap();
                    s.set_volume(v);
                }
            }
            Err(_) => {}
        };

        std::thread::sleep(std::time::Duration::from_millis(2));
    }
}

fn read_zone_data() -> Result<Vec<Zone>> {
    let zone_data =
        std::fs::read_to_string("data/zones.json").expect("Failed to read zone data file");
    let zones: Vec<Zone> = serde_json::from_str(&zone_data)?;

    Ok(zones)
}
