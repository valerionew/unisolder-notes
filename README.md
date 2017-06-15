# unisolder-notes
Just a set of notes for anyone who is trying to build his unisolder controller.
It is intented to be a personal recap of the original topic on dangerousprototypes.com forum.  
If you are reading this after i finished my project (so you are in the future, WOAH!), probably i'm not updating this document anymore. If it was useful to you, please help to keep it updated, by modifying the document and making a Pull Request. The community will thank you.  
**I'm currently building this project, and this page is a work in progress, so the info may be unaccurate and untested. No warranty is given.**

## General notes

### Soldering and mounting
No hot air or reflow oven si required, it can be soldered by hand and soldering iron.  
Sparkybg reccomends BGA no-clean flux.

### Configuration resistors
There are some configuration resistors, please make sure to pick the correct values for your application. Those are listed in the *Equivalent parts in bom* section of this document.

### Power supply
The controller can be powered anywere from 9V to 26V, AC or DC. However, since the iron current is limited to 6Arms, more voltage means more power to the iron.  
A **toroidal** transformer is recommended: **24V 120VA.**  
Although this is not fully recommended you can use a 24V DC supply, because of grounding difficulties in switching PSUs. There are two power input ports on the *"back"* pcb. One is for AC, the other is for DC.

### OLED display configuration
The project is capable of using either a 7 segment display or an oled display.  
If you want to use the oled display, there are some components that you can remove from the BOM and some pads to short.
* Ensure to get a SSD1306 128x64 oled. 
* Q15, Q17 and UL2003N are not needed.
* Ra to Rg are shorted 
* Ja to Jg are shorted  
* Short, on the back side of the front pcb, the pins that have some soldermask free pads arround, with the pads.

### Buzzer
Q20 and D17 are needed only if a DC active buzzer (internal oscillator) is used. The one provided in BOM, however, needs them.

### Sleep sensor  
The author of the project has provided also a sensor module, based on an IR system, to detect whether the iron is in its holder.  
You can use whatever system you want: a mechaincal switch, a reed switch, an hall sensor... You can use any switch or any other device that shorts SLEEP to GND when the tool is in the holder. SLEEP is connected to a 3.3v pullup resistor.

### Calibration 
The author of the project recommens, if needed, to calibrate the temperature of the iron with Sn63/Pb37 solder, which melts at 183°C. 
You shouldn't need to calibrate your iron, do it only if it's needed.

### Iron ID resistors
The station can automatically recognise the instrument you attach to it. To do this, you will need a resistor in the iron connector, so that the system can read it when a new instrument is plugged. If you don't want to switch between instruments, you can simply connect the resistor to the station connector instead of the iron connector. 
ID resistors must be not less than 1% tolerance

| ID resistor table is not | ready yet |
|--------------------------|-----------|
|                          |           |
|                          |           |

## Software, programming the PIC
There are two alternatives for the PIC32 firmware
* Using the firmware without bootloader, loading it directly with a PicKit
* Using the firmware with bootloader, loading the bootloader with the PicKit and the firmware via usb and UniSolder's PC software.
To me is unclear what are the advantages of picking one choice over the other, i have to ask the author to clarify.

If you don't have a pickit and don't want to get one, you can use an arduino as here http://www.microchip.com/forums/m653443.aspx. I've not tried this solution personally, so i don't know if it works. Let me know if you try this.

To load the firmware with a PicKit you will have to use MPLAB X, microchip's software


## Equivalent parts in bom
Some parts are not really easy to find. Some of them can be substituted easily

### Rs1 shunt resistor, R37, R42
0.003 or 0.004 ohm resistor can be used as a shunt.  
If you use **0.003** ohm shunt, R37 and R42 have to be both **1.5k** 0.1%.  
If you use **0.004** ohm shunt, R37 and R42 have to be both **2.0k** 0.1%.  

### Ra to Rg 47ohm
Those resistors are not needed if you are going to use the OLED screen. You will need to short their pads with solder or use 0ohm resistors.

### 3v and 3.0v zener diodes
Despite the different name in the BOM, the same part can be used for both.

### Rgnd1
This resistor is in a 2512 format, 10M, it is there to prevent huge electrical potentials between the computer's ground and the station's ground.  
You can use any value between 1M and 10M, or leave it disconnected if you feel safe, anyway this isn't recommended.

### Q10, Q11: IPD053N08
If you want to change this part, pick a part which has same: package, Rds(on), Vds, and gate threshold voltage.

### Rc2 Bourns trimmer
In BOM it's indicated as Bourns 3362, this part is a THT trimmer from a previous version, correct part number is Bourns 3364X-1-202E.  
I've ordered 3314J-1-202E, not mounted yet. It seems it can fit, but i'm not sure yet. 

### U1 LM2675, R3 and R4
Either the LM2675M-3.3 and the LM2675M-ADJ version can be used.  
If **LM2675M-3.3** is used, R3 has to be 0 (shorted) and R4 has to be 1.5k.  
If **LM2675M-ADJ** is used, R3 has to be 3k and R4 has to be 1.8k. 
LM2674 can be used too.

### U9 ULN2003L
You don't need this IC if you are going to use the OLED display.

### U10 MCP4651-503 (50k)
This part seems hard to find. You can replace it with the MCP4651-104 (100k) version. You can **NOT** use the 103 (10k) version.  
**Beware that this part is different from U15 below**, they have a similar code but with the 5 and the 6 switched. 

### U15 MCP4561-503 (50k)
This part (as before) seems hard to find. You can replace it with the MCP4651-104 (100k) version. You can **NOT** use the 103 (10k) version.  
**Beware that this part is different from U10 above**, they have a similar code but with the 5 and the 6 switched.

### U6 REF303
This part seems harder to find than the others. 
* MAX6035AAUR30 may work, not personally tested

### U14 LM4041CIM3-1.2
Can be substituted with LM4051AEM3-1.2

### U12, U13, U18 MCP6V27
This part can be substituted with:
* MCP6V02
* MCP6V07

### U17 MCP6V03
This part can be substituted with:
* MCP6V01
* MCP6V06
* MCP6V08
* MCP6V26
* MCP6V28


### Q2 SUD50P10
Can be substituted with SQD50P08

### Q10, Q11 IPD053N08
To substitute this part the important parameters are: 
Vds(max) should be at least 75V. 
Rds(on) should be no more than 0.01ohm.
AUIRFR3607 or IPD12CN10NGATMA1 can do the job.

### Q15 IRLML6401
This part should not be installed when using the OLED display

### Q17 IRLML2502
This part should not be installed when using the OLED display



### SOD123 diodes
SOD123 diodes can be used also in miniMELF packages. Check in the document to see which parameters are important, to find a substitute.  
If you can't find the part you are looking for, just ask in the thread and please open an issue/pull request to update the document. 

### SOT223 
Footprints for the SOT223 components are also compatible with DPAK packages.

### SR580 
SR580 means "Schottky rectifier, 5A, 80V". There's nothing special about these diodes. Just use 5A 80V Schottky.

## Connectors
I'm not sure of this parts, i've bought them, please wait until i can confirm.  

* **J1, J7**  
Cable connector: MOLEX 039013022 555702R1  
Crimp pin: MOLEX 39-00-0039  
PCB connector: MOLEX 5566-02A-210  

* **J2, J3, J9**   
Cable connector: MOLEX 5557-04R  
Crimp pin: MOLEX 5556-T2  
PCB connector: MOLEX 039288040 5566-04A-210  

* **J4, J8**   
Cable connector: 3M 89110-0101HA  
PCB connector: 3M N2510-6002RB  

* **J6**  
Cable connector: MOLEX 022013037 2695-03RP  
Crimp pin: MOLEX 008550102 2759-(555)L  
PCB connector: MOLEX 022292031 AE-6410-03A(241)  

* **J5** RJ11v  
This is just an RJ11 vertical connector. I found that Molex 95522-2667 fits perfectly.  



### JBC T245
The matching socket for this iron, if you want to keep the original plug, is the Hirose RPC1-12RB-6P(71)








~~Currently i'm on page 32 of the topic. This is just a reminder for myself, ignore it~~
