# ESP32Doorbell
ESP32 Doorbell made by a ChatGPT (Code for the ESP32) and the wiring is done by [Random Making Encounters](https://www.youtube.com/watch?v=44uBA2G4OIQ&t=416s) Thanks to him for the wonderful setup. This would be ALOT different if i didnt discover his video.

**Materials**
-  2x ESP32 WROOM 32 DevKitC
-  1x DFPlayer
-  1x 4Ω 3 Watt Speaker
-  1x SD card (Micro SD or TF Card, 32GB max storage)
-  1x 100 µF Electrolytic Capacitor
-  1x 10  µF Electorlytic Capacitor
-  2x 0.1 µF Capacitor (104 Ceramic Capacitor)
-  1x 330Ω Resistor (Optional
-  1x LED (Light Emitting Diodes) (Optional)
-  1x PAM8403 with Volume Control (Optional)
-  1x SSD1306 0.96in OLED Display (Optional

-------------------------------------------------------------------------------------------

# Important!
-  The ESP32 requires a "middleman" for both the Sender and Receiver to communicate, use either your home network or a dedicated router for this.
-  The sound quality of the speaker may have a humming noise when setting the volume from the PAM8403 to max.
-  When playing the ringtone on max volume, you may experience cracking noises from the speaker use a film capacitor instead of an electrolytic one on the PAM8403 Input.
-  If the doorbell is connected to the WiFi and no output it means that it had trouble sending data to the network, find a place with less obstacles to avoid signal degradation.
-  Make sure both ESP32s and the doorbell module are connected to a stable 5V power source.

-------------------------------------------------------------------------------------------

# Image of the complete build 

***Prototyping Phase***

![image](https://github.com/user-attachments/assets/1e092382-ff64-4710-b704-97ecce082e1b)

-------------------------------------------------------------------------------------------
