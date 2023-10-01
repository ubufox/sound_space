use serde::Deserialize;
use std::collections::HashMap;

#[derive(Deserialize, Clone)]
pub struct ZedData {
    pub resolution: HashMap<String, u32>,
    pub data: Vec<f32>,
}

impl ZedData {
    pub fn show_res(&self) {
        println!("width: {:?}, height: {:?}",
            self.resolution.get("width"),
            self.resolution.get("height"),
        );
    }

    pub fn get_z(&self, x: &str, y: &str) -> f32 {
        let idx: usize = self.get_idx(x.trim().parse().unwrap(), y.trim().parse().unwrap()) as usize;
        self.data[idx]
    }

    fn get_idx(&self, x: u32, y: u32) -> u32 {
        y * self.resolution.get("width").unwrap() + x
    }
}
