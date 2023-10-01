use crate::models::zone::Zone;

#[derive(Clone)]
pub struct Space {
    pub id: u8,
    x: f32,
    y: f32,
    z: f32,
    diameter: f32,
    max_fill_pct: f32,
    pub fill: f32,
}

impl Space {
    pub fn build_from_zone(zone: &Zone) -> Space {
        Space {
            id: zone.id,
            x: zone.position[0],
            y: zone.position[1],
            z: zone.position[2],
            diameter: zone.diameter,
            max_fill_pct: zone.max_fill_pct,
            fill: 0.0,
        }
    }
    pub fn get_id(&self) -> u8 {
        self.id
    }

    fn set_fill(&mut self, fill: f32) {
        self.fill = fill;
    }

    pub fn tick(&mut self) {
        self.set_fill(self.fill + 1.0);
    }

    pub fn reset(&mut self) {
        self.set_fill(0.0)
    }

    pub fn is_in_space(&self, point: (f32, f32, f32)) -> bool {
        let distance = get_distance((self.x, self.y, self.z), point);
        // if point.0 == 360.0 && point.1 == 202.0 {
        //     println!("distance: {distance}");
        // } else {
        //     ();
        // }

        distance * 2.0 <= self.diameter
    }

    fn get_fill_pct(&self) -> f32 {
        let radius = self.diameter * 0.5;
        let total_space = std::f32::consts::PI * radius.powi(2);

        self.fill / total_space
    }

    pub fn get_adjusted_fill_pct(&self) -> f32 {
        let base_pct = self.get_fill_pct();
        let adj_pct = base_pct / self.max_fill_pct;

        if adj_pct > 2.0 {
            2.0
        } else {
            adj_pct
        }
    }
}

fn get_distance(pt_a: (f32, f32, f32), pt_b: (f32, f32, f32)) -> f32 {
    let (x_a, y_a, z_a) = pt_a;
    let (x_b, y_b, z_b) = pt_b;

    // if x_b == 360.0 && y_b == 202.0 {
    //     println!("space x: {x_a}, point x: {x_b}");
    //     println!("space y: {y_a}, point y: {y_b}");
    //     println!("space z: {z_a}, point z: {z_b}");
    // } else {
    //     ()
    // }

    ((x_a - x_b).powi(2) + (y_a - y_b).powi(2) + (z_a - z_b).powi(2)).sqrt()
}
