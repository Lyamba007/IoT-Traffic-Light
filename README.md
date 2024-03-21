# IoT-Traffic-Light
The intelligent traffic control device prototype with a support of the "Green Wave" mode was developed. 
The "Green Wave" mode is implemented with a smartphone, simulating an on-board computer for a special service vehicle.

The algorithm of the intelligent traffic light (ITL) is represented in the form of a temporal graph with the transitions of the control automaton. 
The control unit is based on the microcontroller with the Wi-Fi module (ESP8266).
The Arduino IDE was used.

The traffic light model is realized on the colored LEDs basis: red - R314D-L, yellow - LY 2040, green - FYL-5013 UGD.
_________________________________________________________________________________________________________________________________
# Branch content
The control device has been refactored:
- Async Web Server instead of Web Server.
- Timer instead of delays in automaton template
- Server realization on HTML+CSS+JS instead of Xamarin. 
- WiFi internal connection instead of Access Point.
- Code refactor (see detailed with the main branch comparing).
_________________________________________________________________________________________________________________________________
#Additional information

See the main branch to discover the idea of the ITL.
Useful materials: Presentation notes, Demo Video, Comments to Demo Video.
_________________________________________________________________________________________________________________________________