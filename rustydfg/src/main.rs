use std::io::prelude::*;
use std::io::BufReader;
use std::fs::File;
use std::path::Path;

struct Machine_Code{
	absolute_address: &'static str,
	relative_address: &'static str,
	macro_op: &'static str,
	micro_instr: &'static str,
	micro_op:  &'static str
}

fn lines_from_file<P>(filename: P) -> Vec<String>
    where P: AsRef<Path>,
{
    let file = File::open(filename).expect("no such file");
    let buf = BufReader::new(file);
    buf.lines().map(|l| l.expect("Could not parse line")).collect()
}

// ---

fn main() {

    let lines = lines_from_file("Shashank25_output");
    for line in lines {
		for word in line.split(":"){
			let name = word.trim();
			let line_locater = &line;
			print!(" '{}' ", line_locater[0]);

		}
        println!("\n");
    }
}
