use serde_json::Result;
use std::collections::HashMap;

use crate::models::space::Space;
use crate::models::zed_data::ZedData;

const WIDTH: f32 = 1280.0;
const _HEIGHT: f32 = 1080.0;

pub struct ZedProcessor {
    x_res: f32,
}

impl ZedProcessor {
    pub fn new() -> Self {
        Self { x_res: WIDTH }
    }

    // ## call ZED.retreiveMeasure
    fn get_point_cloud(&self) -> Vec<f32> {
        let ctx = zmq::Context::new();
        let request = ctx.socket(zmq::REQ).unwrap();

        request.connect("tcp://127.0.0.1:5555").unwrap();

        println!("Requesting point cloud data...");
        request.send("1", 0).unwrap();

        let msg = request.recv_bytes(0).unwrap();
        println!("Received data!");
        let _zed_data: ZedData = read_zed_data(&msg).unwrap();
        println!("ZED data deserialized!");

        vec![0.0, 0.2, 0.04, 0.8, 0.1, 0.4, 0.4, 0.4, 0.5, 0.0, 0.95]
    }

    // IN: index and value
    // OUT: (x, y, z) point
    fn normalize_pt(&self, idx: u32, val: f32) -> (f32, f32, f32) {
        let x = idx as f32 % self.x_res;
        let y = (idx as f32 / self.x_res).floor();
        let z = val;

        (x, y, z)
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
                let n_p = self.normalize_pt(idx as u32, *p);

                if n_space.is_in_space(n_p) {
                    n_space.tick();
                } else {
                    ()
                }
            }

            println!("points in zone {:?}", n_space.get_adjusted_fill_pct());

            acc.insert(n_space.id, n_space.get_adjusted_fill_pct());
            acc
        })
    }
}

fn read_zed_data(zed_bytes: &Vec<u8>) -> Result<ZedData> {
    let slice_end: usize = zed_bytes.iter().len();
    let d: ZedData = serde_json::from_slice(&zed_bytes[0..slice_end]).expect("Failed to deserialize");

    d.show_res();

    let z = d.get_z("360", "202");
    println!("x: 360, y: 202, z: {:?}", z);

    Ok(d)  
}
