const GRAYSCALE_ARR: [char; 10] = [' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'];

pub fn draw(min: f32, max: f32, vals: Vec<f32>) {
    let range: f32 = max - min;
    let line = vals.iter().fold(String::new(), move |mut acc, v| {
        let mut idx = GRAYSCALE_ARR.len() as f32 - ((v - min) * GRAYSCALE_ARR.len() as f32 / range).floor();
        idx = idx - 1.0;
        acc.push(GRAYSCALE_ARR[idx as usize]);
        acc
    });

    println!("{line}\n");
}
