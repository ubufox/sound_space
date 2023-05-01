use serde_json::Result;
use std::collections::HashMap;

use crate::models::space::Space;
use crate::models::zed_data::ZedData;

const WIDTH: f32 = 720.0;
const Z_MAX: f32 = 3.0;
const Z_MIN: f32 = 0.5;
const Z_PEAK: f32 = 1000.0;

pub struct ZedProcessor {
    width: f32,
}

impl ZedProcessor {
    pub fn new() -> Self {
        Self { width: WIDTH }
    }

    // ## call ZED.retreiveMeasure
    fn get_point_cloud(&self) -> Vec<String> {
        let ctx = zmq::Context::new();
        let request = ctx.socket(zmq::REQ).unwrap();

        request.connect("tcp://127.0.0.1:5555").unwrap();
        request.send("1", 0).unwrap();

        let msg = request.recv_bytes(0).unwrap();
        let zed_data: ZedData = read_zed_data(&msg).unwrap();

        zed_data.data         
    }

    // IN: index and value
    // OUT: (x, y, z) point
    fn normalize_pt(&self, idx: u32, val: f32) -> (f32, f32, f32) {
        let x = idx as f32 % self.width;
        let y = (idx as f32 / self.width).floor();

        let range = Z_MAX - Z_MIN;
        let z = (val - Z_MIN) / range * Z_PEAK;

        if x == 359.0 && y == 202.0 {
            println!("point -> {x}, {y}, {z}");
        } else {
            ();
        }
        (x, y, z)
    }

    fn get_z_f32(&self, val: &String) -> Option<f32> {
        match val.trim().parse::<f32>() {
            Ok(f) => {
                if f.is_nan() || f.is_infinite() {
                    None
                } else {
                    Some(f)
                }
            },
            Err(_) => None,
        }
    }

    pub fn get_fills(&self, spaces: Vec<Space>) -> HashMap<u8, f32> {
        // get point cloud from ZED sensor
        let pts = self.get_point_cloud();

        // update spaces
        spaces.iter().fold(HashMap::new(), |mut acc, s| {
            let mut n_space = s.clone();

            // reset fill value to 0.0
            // may be unnecessary if the Vec is fresh when passed in
            n_space.reset();

            for (idx, p) in pts.iter().enumerate() {
                // get a 3D point (f32, f32, f32)
                let pz = match self.get_z_f32(p) {
                    Some(v) => v,
                    None => 1000000.0,
                };
                let n_p = self.normalize_pt(idx as u32, pz);

                if n_space.is_in_space(n_p) {
                    n_space.tick();
                } else {
                    ()
                }
            }

            println!("space {:?} has -> {:?} points filled", n_space.id, n_space.fill);
            acc.insert(n_space.id, n_space.get_adjusted_fill_pct());
            acc
        })
    }
}

fn read_zed_data(zed_bytes: &Vec<u8>) -> Result<ZedData> {
    let slice_end: usize = zed_bytes.iter().len();
    let d: ZedData = serde_json::from_slice(&zed_bytes[0..slice_end]).expect("Failed to deserialize");

    d.show_res();

    let z_a = d.get_z("360", "202");
//     let z_b = d.get_z("0", "0");
//     let z_c = d.get_z("719", "0");
//     let z_d = d.get_z("0", "403");
//     let z_e = d.get_z("719", "403");
// 
    println!("x: 360, y: 202, z: {:?}", z_a);
//     println!("x: 0, y: 0, z: {:?}", z_b);
//     println!("x: 719, y: 0, z: {:?}", z_c);
//     println!("x: 0, y: 403, z: {:?}", z_d);
//     println!("x: 719, y: 403, z: {:?}", z_e);

    Ok(d)  
}
