use serde::Deserialize;

#[derive(Deserialize, Clone)]
pub struct Zone {
    pub id: u8,
    diameter: f32,
    max_fill_pct: f32,
    position: [f32; 3],
    pub sample_path: String,
}

impl Zone {
    pub fn sample_path(&self) -> String {
        self.sample_path.to_string()
    }
}
