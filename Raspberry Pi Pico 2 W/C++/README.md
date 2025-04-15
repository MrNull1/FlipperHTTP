## Raspberry Pi Pico 2 W Installation (C++)

There are two installation methods. Choose whichever is the most convenient for you. The first method only works if you have the complete wiring, including the optional pins.

### Method 1
1. Install the Video Game Module Tool app on your Flipper Zero from the Apps catalog: [Video Game Module Tool](https://lab.flipper.net/apps/video_game_module_tool).
2. Download the `flipper_http_pico_2w_c++.uf2` file.
3. Disconnect your Raspberry Pi Pico W from your Flipper and connect your Flipper to your computer.
4. Open qFlipper.
5. Click on the `File manager`.
6. Navigate to `SD Card/apps_data/pico/`. If the folder doesn’t exist, create it yourself. Inside that folder, create a folder called `FlipperHTTP`.
7. Drag the `flipper_http_pico_2w_c++.uf2` file you downloaded earlier into the directory.
8. Disconnect your Flipper from your computer, then turn off your Flipper.
9. Connect your Raspberry Pi Pico W to the Flipper, then turn on your Flipper.
10. Open the Video Game Module Tool app on your Flipper. It should be located in the `Apps->GPIO` folder from the main menu.
11. In the Video Game Module Tool app, select `Install Firmware from File`, then `apps_data`.
12. Scroll down and click on the `pico` folder, then `FlipperHTTP`, and then `flipper_http_pico_2w_c++.uf2`.
13. The app will begin flashing the firmware to your Raspberry Pi Pico W. Wait until the process is complete.

### Method 2
1. Download the `flipper_http_pico_2w_c++.uf2` file.
2. Press and hold the `BOOT` button on your Raspberry Pi Pico W for 2 seconds.
3. While holding the `BOOT` button, connect the Raspberry Pi Pico W to your computer using a USB cable.
4. Drag and drop the downloaded file onto the device. It will automatically reboot and begin running the FlipperHTTP firmware.

Here's a video tutorial: https://www.youtube.com/watch?v=rdzKDCjbZ4k

## Raspberry Pi Pico 2 W Build Instructions (C++)

  This is only if you want to build and/or modify the firmware for yourself, only recommended for experienced developers.

### Prerequisites

1. Download the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open the Arduino IDE, go to `File -> Preferences`, then put this link in the `Additional Boards Manager URLs` section:
```
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
3. Click `ok`, then click on the `Boards Manager`. (The second button down on the left sidebar).
4. Search for `Pico`, then click install under `Raspberry Pi Pico/RP2040/RP2350`
5. Now click on the `Library Manager` (One under the `Boards Manager` section), and search for `JSON`.
6. Click install under `ArduinoJson`, **NOT** `Arduino_JSON`.
7. Clone the github repository using:
```
git clone https://github.com/jblanked/FlipperHTTP
```
8. Rename the `src` folder to `flipper-http`.

### Setup

1. Open the file `flipper-http/flipper-http.ino` in the Arduino IDE.
2. Make desired modifications (or not).
3. Plug the Pico 2 W into your computer.
4. Under the `Select Board` dropdown, choose your serial port, then search for `Raspberry Pi Pico 2 W`, and select.
5. Now go to `Tools -> Flash Size`, and select the option that says `4MB (Sketch: 4032KB, FS: 64KB)`
6. Now open the boards.h file, and uncomment this line (remove the `//`):
```
16: // #define BOARD_PICO_2W 7      // Raspberry Pi Pico 2W          Raspberry Pi Pico/RP2040/RP2350 by Earl Philhower
```

### Compilation

1. Click the right facing arrow in the top left corner, to compile and upload.
2. That's it! The compilation might take a minute, especially your first time. The onboard LED should hopefully flash three times when a successful upload has occured.
