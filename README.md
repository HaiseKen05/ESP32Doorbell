# ESP32Doorbell
ESP32 Doorbell made by a ChatGPT (Code for the ESP32) and the wiring is done by [Random Making Encounters](https://www.youtube.com/watch?v=44uBA2G4OIQ&t=416s) Thanks to him for the wonderful setup. This would be ALOT different if i didnt discover his video.

**Materials**
-  2x ESP32 WROOM 32 DevKitC
-  1x DFPlayer
-  1x 4Ω 3 Watt Speaker
-  1x SD card (Micro SD or TF Card, 32GB max storage)
-  1x 100µF Electrolytic Capacitor
-  2x 10µF Electorlytic Capacitor
-  1x 0.1µF Capacitor (104 Ceramic Capacitor)
-  1x MB-102
-  1x Push Button
-  1x 330Ω Resistor (Optional
-  1x LED (Light Emitting Diodes) (Optional)
-  1x PAM8403 with Volume Control (Optional)
-  1x SSD1306 0.96in OLED Display (Optional)

-------------------------------------------------------------------------------------------

# Important!
-  Place 100µF Capacitor and 0.1µF Ceramic Capacitor in parallel with the MB-102 5V and GND to smooth out power fluctuations.
-  DFPlayer Mini Module is sensitive to power fluctuations.
-  Both ESP32s must connect to the same Wi-Fi router for both the Sender and Receiver to communicate, use either your home network or a dedicated router for this.
-  The sound quality of the speaker may have a humming noise when setting the volume from the PAM8403 to max.
-  Connect a 10µF Capacitor (or a film capacitor) in series with each of the DAC_R and DAC_L to the R and L input pins of the PAM8403. ( Capacitor ( + ) connects to DAC_R, Capacitor ( - ) to R input of the PAM8403, DO THE SAME FOR THE OTHER DAC_L and L Input (This is only applicable to electrolytic capacitor)
-  When playing the ringtone on max volume, you may experience cracking noises from the speaker use a film capacitor instead of an electrolytic one on the PAM8403 Input.
-  If the doorbell is connected to the WiFi and no output it means that it had trouble sending data to the network, find a place with less obstacles to avoid signal degradation.
-  Make sure both ESP32s and the doorbell module are connected to a stable 5V power source.
-  Make sure that the Receiver ESP32 has all common GND, specifically on GPIO18, if not the ringtone will not work.
-  The whole thing will not work if the WiFi network is not connected to the internet. 

-------------------------------------------------------------------------------------------

# Image of the complete build 

***Prototyping Phase***

![image](https://github.com/user-attachments/assets/1e092382-ff64-4710-b704-97ecce082e1b)

-------------------------------------------------------------------------------------------

# Pin Assignments

**ESP32 (Receiver)**
| DFPLayer Mini Mp3-TF-16P | Pins |
|:------------------------:|:----:|
| **VCC** | 5V (MB-102) |
| **GND** | GND (MB-102) |
| DAC_R | R (PAM8403) |
| DAC_L | L (PAM8403 |
| IO_2 | GPIO 18 (ESP32) | 

| PAM8403 | Pins |
|:-------:|:----:|
| R | DAC_R (DFPlayer Mini) |
| L | DAC_L (DFPlayer Mini) |
| G | GND (MB-102) |
| **VCC** | 5V (MB-102) | 
| **GND** | GND (MB-102) | 
| L OUT + | Red Wire Speaker | 
| L OUT - | Black Wire Speaker | 

| ESP32 | Pins |
|:-----:|:----:|
| **VIN** | 5V (MB-102) |
| **GND** | GND (MB-102) | 
| LED | GPIO 4 |
| SIGNAL PIN | GPIO 18 |

| Speaker | Pins |
|:-------:|:----:|
| Red Wire | L OUT + (PAM8403) | 
| Black Wire | L OUT - (PAM8403) | 

**ESP32 (Sender)**
| ESP32 | Pins |
|:-----:|:----:|
| LED | GPIO 2 (Built-in) |
| Button | GPIO 4 |

| SSD1306 | Pins |
|:-------:|:----:|
| **GND** | GND |
| **VCC** | VIN | 
| SCK/SCL | GPIO 22 (ESP32) | 
| SDA | GPI0 21 (ESP32) | 

| Button | Pins |
|:------:|:----:|
| 1st Leg | GPIO 4 (ESP32) | 
| 2nd Leg | GND | 


-------------------------------------------------------------------------------------------
🚀 Getting Started
Follow these steps to set up your ESP32 Doorbell system:

1. Install Arduino IDE & ESP32 Board Support
Install the Arduino IDE.

Go to File > Preferences, add the following to Additional Board URLs:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Then, go to Tools > Board > Board Manager, search for ESP32, and install it.

2. Download the Project Code
Open the [Doorbell](https://github.com/HaiseKen05/ESP32Doorbell/tree/main/Doorbell) folder in the repository.

Download or clone the repo using:

```bash
https://github.com/HaiseKen05/ESP32Doorbell.git
```
locate: 
**InsideUnit.ino (for the receiver ESP32)**

**OutsideUnit.ino (for the sender ESP32)**

3. Connect & Identify COM Ports
Connect both ESP32 DevKit boards to your PC.

In Arduino IDE, go to Tools > Port and find which COM port corresponds to each ESP32.
⚠️ Upload code to one board at a time!

4. Configure Wi-Fi Credentials
Edit both sketches to include your local Wi-Fi SSID and password:
```bash
// Wi-Fi Credentials
const char* ssid = ""; // WiFi Name
const char* password = ""; // WiFi Password
```
6. Set Receiver IP in Sender Sketch
Upload the Receiver sketch first.

Open the Serial Monitor at 115200 baud to find its IP address once connected.

Update the Sender code with that IP:
```bash
const char* receiverIP = ""; // Receiver IP Address 
```
-------------------------------------------------------------------------------------------
# NOTES

You dont need to worry about having to install libraries for the DFPlayer module as the ESP32 (The Receiver unit) will emulate a button press on one of its GPIO pins (in this case i used GPIO 18 but you can change it to what ever pin you want) other than that everything is working perfectly fine.

-------------------------------------------------------------------------------------------

# Video links 

Wiring Configuration

Final build and Test 

