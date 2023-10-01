extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn main() {
    let libdir_path = PathBuf::from("/usr/local/zed")
        .canonicalize()
        .expect("cannot canonicalize path");

    let camera_headers_path = libdir_path.join("include/sl/Camera.h");
    let fusion_headers_path = libdir_path.join("include/sl/Fusion.h");
    let camera_headers_path_str = camera_headers_path.to_str().expect("Camera path is not a valid string");
    let fusion_headers_path_str = fusion_headers_path.to_str().expect("Fusion path is not a valid string");

    let ai_obj_path = libdir_path.join("lib/libsl_ai.so")
    let zed_obj_path = libdir_path.join("lib/libsl_zed.so")
    let lib_path = libdir_path.join("/lib/libsl_zed_static.a")


    println!("cargo:rustc-link-search={}", libdir_path.to_str().unwrap());

    println!("cargo:rustc-link-lib=sl_zed");

    println!("cargo:rerun-if-changed={}", camera_headers_path_str);
    println!("cargo:rerun-if-changed={}", fusion_headers_path_str);

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
