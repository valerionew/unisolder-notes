# unisolder-notes
Just a set of notes for anyone who is trying to build his unisolder controller.
It is intented to be a personal recap of the original topic on dangerousprototypes.com forum.  
**I'm currently building this project, and this page is a work in progress, so the info may not be 100% accurate and tested. No warranty is given.**

### Power supply
A **toroidal** transformer is recommended: **24V 120VA.**  
Although this is not fully recommended you can use a 24V DC supply. There are two power input ports on the *"back"* pcb. One is for AC, the other is for DC.

### OLED display configuration
The project is capable of using either a 7 segment display or an oled display.  
If you want to use the oled display, there are some components that you can remove from the BOM and some pads to short.
* Ensure to get a SSD1306 128x64 oled. 
* Q15, Q17 and UL2003N are not needed.
* Ra to Rg are shorted 
* Ja to Jg are shorted  
* Short, on the back side of the front pcb, the pins that have some soldermask free pads arround, with the pads.




~~Currently i'm on page 6 of the topic. This is just a reminder for myself, ignore it~~
