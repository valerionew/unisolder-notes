# unisolder-notes
Just a set of notes for anyone who is trying to build his own unisolder controller.
It is intented to be a personal recap of the [original topic on dangerousprototypes.com forum](http://dangerousprototypes.com/forum/viewtopic.php?t=7218).  
If you are reading this after i finished my project (so you are in the future, WOAH!), probably i'm not updating this document anymore. If it was useful to you, please help to keep it updated, by modifying the document and making a Pull Request. The community will thank you.  
**I'm currently building this project, and this page is a work in progress, so the info may be unaccurate and untested. No warranty is given. Please refer to [LICENSE.md file](https://github.com/5N44P/unisolder-notes/blob/master/LICENSE.md) for all the conditions.**

## General notes

### Soldering and mounting
No hot air or reflow oven si required, the board can be mounted with a regular soldering iron.  
Sparkybg reccomends BGA no-clean flux. I personally use a felt tip regular flux and it works well for me.  
**ATTENTION** there are some resistor pairs that can be mounted in the wrong direction. All the mentioned couples have to be mounted with the long side according to the long side of the front board. Those are the couples that require special attention during the mounting:
* R27 and R28
* R63 and R65, double and triple check this pair, it's very common to have these wrong. If you do probably you will get error 13.
* R30 and R31
* R35 and R39
* R25 and R26
* C60 and R46

Please check <a href="http://dangerousprototypes.com/forum/download/file.php?id=11712&mode=view" target="_blank">the image provided by the author </a> if you have any doubt about mounting or component orientation.


### Configuration resistors
There are some configuration resistors, please make sure to pick the correct values for your application. Those are listed in the [*Equivalent parts in bom*](#equivalent-parts-in-bom) section of this document.

### Power supply
The controller can be powered anywere from 9V to 26V, AC or DC. However, since the iron current is limited to 6Arms, more voltage means more power delivered to the iron.  
A **toroidal** transformer is recommended: **24V 120VA.**  
Although this is not fully recommended (because of grounding difficulties in switching PSUs) you can use a 24V DC supply.  
There are two power input ports on the *"back"* pcb. One is for AC, the other is for DC.

### OLED display configuration
At an early stage of the project the author was planning to implement both the 7 segment display and the OLED display. The 7 segment option was never implemented, and the compatibility was removed. 
There are some components that you'll have to remove from the BOM and some pads to short.
* Ensure to get a SSD1306 128x64 oled. 
* Q15, Q17 and U9 (UL2003N) are not needed.
* Ra to Rg are shorted 
* Ja to Jg are shorted  
* Short, on the back side of the front pcb, the pins that have some soldermask free pads arround, with the pads.
* See the [U19 FAN5331 section](#u19-fan5331-r68) in this document, for picking the correct boost feedback resistor. 

### Buzzer
Q20 and D17 are needed only if a DC active buzzer (internal oscillator) is used. The one specified in BOM, however, does not need them.
Unfortunately for now the DC buzzers are not supported by the firmware.

### Sleep sensor  
The author of the project has provided also a sensor module, based on an IR system, to detect whether the iron is in its holder.  
You can use whatever system you want: a mechaincal switch, a reed switch, an hall sensor... You can use any switch or any other device that shorts SLEEP to GND when the tool is in the holder. SLEEP is connected to a 3.3v pullup resistor.

### Calibration 
The author of the project recommens, if needed, to calibrate the temperature of the iron with Sn63/Pb37 solder, which melts at 183°C. 
You shouldn't need to calibrate your iron, do it only if it's needed.

### Iron ID resistors
The station can automatically recognise the instrument you attach to it. To do this, you will need a resistor pair in the iron connector, so that the system can read it when a new instrument is plugged. If you don't want to switch between instruments, you can simply connect the resistor to the station connector instead of the iron connector. 
ID resistors must be not less than 1% tolerance.
We will call Rid1 the resistor that goes between ID and Vout1-, and Rid2 the resistor that goes between ID and Vout2-

|    Soldering iron model  |   Rid1  |   Rid2  |
|--------------------------|---------|---------|
|     HAKKO T12            |   1k    |  5.6k   |
| HAKKO FX8801, HAKKO 907  |   1k    |  820    |
| JBC C245                 |   150   |  5.6k   |
| JBC C210                 |   3k    |  5.6k   |
| JBC Microtweezers        |   1k    |   //    |
| WELLER WSP80             |   120   |  5.6k   |
| ERSA RT80                |   300   |  110    |

## Software, programming the PIC
There are two alternatives for the PIC32 firmware:
* Using the firmware without bootloader, loading it directly with a PicKit
* Using the firmware with bootloader, loading the bootloader with the PicKit and the firmware via usb and UniSolder's PC software.

To me is unclear what are the advantages of picking one choice over the other, i have to ask the author to clarify.

If you don't have a pickit and don't want to get one, you can use an arduino as here http://www.microchip.com/forums/m653443.aspx. I've not tried this solution personally, so i don't know if it works. Let me know if you try this.  
You can also use [pic32prog](https://github.com/sergev/pic32prog) from sergev, if you have a pickit 2 and want to program the microcontroller.  
To load the firmware with a PicKit you will have to use MPLAB X, microchip's software.  
As zed65 stated in the forum: "You can NOT program the PIC via the PicKit2/3 standalone programming software. You have to put the programmer into MPLab mode in the standalone software then program it via MPLab."

#### Modify the software
If you want to modify the software you'll have to compile it with XC32 v1.33 compiler (**paid**), adding the "s" option to the optimization.

## Equivalent parts in bom
Some parts are not really easy to find. Some of them can be easily substituted with equivalent parts.

### Rs1 shunt resistor, R37, R42
0.003 or 0.004 ohm resistor can be used as a shunt. **WSL3637** from Vishay is used. I wasn't able to find an equivalent part that would have a similar package.
If you use **0.003** ohm shunt, R37 and R42 have to be both **1.5k** 0.1%.  
If you use **0.004** ohm shunt, R37 and R42 have to be both **2.0k** 0.1%.  


### Ra to Rg 47ohm
Those resistors are not needed. You will need to short their pads with solder or use zero ohm resistors.

### 3v and 3.0v zener diodes
Despite the different name in the BOM, the same part can be used for both.

### Rgnd1
This resistor is in a 2512 format, 10M, it is there to prevent huge electrical potentials between the computer's ground when it's connected and the station's ground.  
You can use any value between 1M and 10M, or leave it disconnected if you feel safe, anyway this isn't recommended.

### Capacitors
For the ceramic capacitors insulator type, C0G is the best, X7R is also good. X5R is not as good as X7R. If it's possible avoid Y5V. 
Where voltage is not specified you can pick any voltage. 50V rating is better than higher.  A contributed list of which capacitors need higher voltages than the logic 3.3V would be appreciated. 

### Diodes
Please note that many times with diodes there is the same part from a different manifacturer listed with the first two letters.  

### D1, D2, D3, D4 SR580
SR580 means "Schottky rectifier, 5A, 80V". There's nothing special about these diodes. Just use 5A 80V Schottky in a DO-201 package.  
This part can be substituted with SB5100 or other Schottky Rectifiers with at least 5A current capability and at least 80V forward voltage. However the 80V part is still preferable, because it will have less forward drop.  

### Rc2 Bourns trimmer
In BOM it's indicated as Bourns 3362, this part is a THT trimmer from a previous version, correct part number is **Bourns 3364X-1-202E.**  
I'm using a **Bourns 3314J-1-202E** which also fits well. 


### Q10, Q11: IPD053N08
If you want to change this part, pick a part which has same: package, Rds(on), Vds, and gate threshold voltage.

### U1 LM2675, R3 and R4
Either the LM2675M-3.3 and the LM2675M-ADJ version can be used.   
If **LM2675M-3.3** is used, R3 has to be 0 (shorted) and R4 has to be 1.5k.  
If **LM2675M-ADJ** is used, R3 has to be 3k and R4 has to be 1.8k.  
LM2674 can be used too.

### U9 ULN2003L
You don't need this IC, this was only for the 7-seg version. 

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

### U19 FAN5331, R68
This part can be substituted with LM2731, FAN5333A or FAN5333B. Please note that either version of FAN5333 have a different feedback voltage from each other and from the FAN5331. LM2731 has the same feedback voltage. This part is the boost converter for the OLED display. Different OLED displays need different voltages. Usually they can be either 9V or 12V. Check the voltage of your OLED and select R68 accordingly. R68 should be at least 1%.

Follows a table with values that should suit. These values are not tested (FAN5333B with 9V display is tested by me and working), proceed with caution and check the voltage prior to soldering the OLED.

| IC                | R68 for 9V display | R68 for 12V display |
|-------------------|--------------------|---------------------|
| FAN5331 (1.230V)  | 4.7k               | 3k                  |
| FAN5333A (0.110V) | 340                | 249                 |
| FAN5333B (0.315V) | 1k                 | 732                 |

### Q2 SUD50P10
Can be substituted with SQD50P08

### Q10, Q11 IPD053N08
To substitute this part the important parameters are: 
* Vds(max) should be at least 75V. 
* Rds(on) should be no more than 0.01ohm.

AUIRFR3607 or IPD12CN10NGATMA1 can do the job.

### Q15 IRLML6401
This part should not be installed when using the OLED display

### Q17 IRLML2502
This part should not be installed when using the OLED display

## Packages compatibility

### SOD123 diodes
SOD123 diodes can be used also in miniMELF packages. Check in the document to see which parameters are important, to find a substitute.  
If you can't find the part you are looking for, ask in the thread and please open an issue/pull request to update the document. 

### SOT223 
Footprints for the SOT223 components are also compatible with DPAK packages.

## Connectors
These are the part numbers for the connectors i've used. I was able to crimp all of them with a single tool: **NEWBRAND NB-8160-04**

### J1, J7 
Cable connector: MOLEX 039013022 555702R1  
Crimp pin: MOLEX 39-00-0039  
PCB connector: MOLEX 5566-02A-210  

### J2, J3, J9  
Cable connector: MOLEX 5557-04R  
Crimp pin: MOLEX 39-00-0039  
PCB connector: MOLEX 039288040 5566-04A-210  

### J4, J8  
Cable connector: 3M 89110-0101HA  
PCB connector: 3M N2510-6002RB  

### J6
Cable connector: MOLEX 022013037 2695-03RP  
Crimp pin: MOLEX 008550102 2759-(555)L  
PCB connector: MOLEX 022292031 AE-6410-03A(241)  

### J5 RJ11v  
This is just an RJ11 vertical connector. I found that Molex 95522-2667 fits perfectly.  



### JBC T245
The matching socket for this iron, if you want to keep the original plug, is the Hirose RPC1-12RB-6P(71)

### Iron connector
If you don't want to keep the orignal connector from your iron, i've used and i suggest:  
Socket: **LUMBERG KFV 81**  
Plug: **LUMBERG 0332 08-1**  





~~Currently i'm on page 60 of the topic. This is just a reminder for myself, ignore it~~
