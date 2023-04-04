use serde::Deserialize;

#[derive(Deserialize, Clone)]
pub struct Zone {
    pub id: u8,
    pub diameter: f32,
    pub max_fill_pct: f32,
    pub position: [f32; 3],
    pub sample_path: String,
}

impl Zone {
    pub fn sample_path(&self) -> String {
        self.sample_path.to_string()
    }
}
