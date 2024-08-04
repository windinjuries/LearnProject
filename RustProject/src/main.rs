use std::os::fd::RawFd;

use linux::syscall::*;
fn main() {
    let result: Result<i32, nix::Error>;
    let fd:RawFd;
    let num:i32 = 1;
    result = openat("/sys/class/leds/green_led/brightness", OFlag::O_RDWR, Mode::S_IRWXO);
    match result {
        Ok(n)  => {
            fd = n;
            println!("fd is {}", fd);
        },
        Err(e) => {
            println!("Error: {}", e); 
            return; 
        }
    }
    result = fc(fd, 1, 1);
    match result {
        Ok(n)  => {
            fd = n;
            println!("fd is {}", fd);
        },
        Err(e) => {
            println!("Error: {}", e); 
            return; 
        }
    }
    
}



