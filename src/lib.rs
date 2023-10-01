use bindgen::Builder;

pub mod models;

pub mod mock_zed;

pub mod draw;

fn main() {
    let mut builder = Builder::new();

    builder.header("sl/Camera.hpp");

    builder.generate().expect("Unable to generate bindings");
}
