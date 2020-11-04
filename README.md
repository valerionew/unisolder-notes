# unisolder-notes
![License CC-BY-4.0](https://img.shields.io/badge/License-CC--BY--4.0-green.svg)
<img align="right" src="/img/writing-01.png" width=250 />

Just a set of notes for anyone who is trying to build his own unisolder controller.
It is intented to be a personal recap of the [original topic on dangerousprototypes.com forum](http://dangerousprototypes.com/forum/viewtopic.php?t=7218).  

If you are reading this after i finished my project (so you are in the future, WOAH!), probably i'm not updating this document anymore. If it was useful to you, please help to keep it updated, by modifying the document and making a Pull Request. The community will thank you. Please see the [Contributing](#contributing) section of this document.  

**I'm currently building this project, and this page is a work in progress, so the info may be unaccurate and untested. No warranty is given. Please refer to [LICENSE.md file](https://github.com/5N44P/unisolder-notes/blob/master/LICENSE.md) for all the conditions.**

<!-- TOC depthFrom:2 depthTo:3 withLinks:1 updateOnSave:1 orderedList:0 -->

- [General notes](#general-notes)
	- [Sources](#sources)
	- [Soldering and mounting](#soldering-and-mounting)
	- [Interactive PCB map](#interactive-pcb-map)
	- [Configuration resistors](#configuration-resistors)
	- [Power supply](#power-supply)
	- [Earthing](#earthing)
	- [OLED display configuration](#oled-display-configuration)
	- [Buzzer](#buzzer)
	- [Sleep sensor](#sleep-sensor)
	- [Calibration](#calibration)
	- [Iron ID resistors](#iron-id-resistors)
- [Software and programming the PIC](#software-and-programming-the-pic)
- [Equivalent parts in BOM](#equivalent-parts-in-bom)
	- [Resistors](#resistors)
	- [Capacitors](#capacitors)
	- [Diodes](#diodes)
	- [Transistors](#transistors)
	- [Packages compatibility](#packages-compatibility)
	- [Connectors](#connectors)
	- [Iron connector](#iron-connector)
- [Contributing](#contributing)

<!-- /TOC -->


## General notes

### Sources
Original sources from Sparkybg are available as a submodule in this repository. Check out the sources on GitHub: [sparkybg/UniSolder-5.2](https://github.com/sparkybg/UniSolder-5.2)

### Soldering and mounting
No hot air or reflow oven is required, the board can be mounted with a regular soldering iron.  
Sparkybg recommends BGA no-clean flux. I personally use a felt tip regular flux and it works well for me.  
**ATTENTION**: there are some resistor pairs that can be mounted in the wrong direction. All the mentioned couples have to be mounted with the long side according to the long side of the front board. Those are the couples that require special attention during the mounting:
* R27 and R28
* R63 and R65, double and triple check this pair, it's very common to have these wrong. If you do probably you will get error 13.
* R30 and R31
* R35 and R39
* R25 and R26
* C60 and R46

Please check <a href="http://dangerousprototypes.com/forum/download/file.php?id=11712&mode=view">the image provided by the author</a> if you have any doubt about mounting or component orientation.

### Interactive PCB map

I'm currently hosting on my GitHub pages this very useful interactive pcb map by Bug82: [unisolder-chips](https://valerionew.github.io/unisolder-chips/)

Original post [here](http://dangerousprototypes.com/forum/download/file.php?id=12034), I'm hosting it with the author's permission after his hosting went down.


### Configuration resistors
There are some configuration resistors, please make sure to pick the correct values for your application. Those are listed in the [*Equivalent parts in BOM*](#equivalent-parts-in-BOM) section of this document.

### Power supply
The controller can be powered anywhere from 9V to 26V, AC or DC. However, since the iron current is limited to 6A RMS, more voltage means more power delivered to the iron.
A **toroidal** transformer is recommended: **24V 120VA**.
Although this is not fully recommended (because of grounding difficulties in switching PSUs) you can use a 24V DC supply.
There are two power input ports on the *"back"* pcb. One is for AC, the other is for DC.

### Earthing
The controller should not be earthed in any way, except for the iron tip. In many cases the earth of the tip differs from the ground of the controller. For this reason, is not possible to use the tip earth connection to send the sleep/stand signal (see [Sleep sensor](#sleep-sensor) section of this document). SLEEP pin should never be connected directly to the iron tip.
Also, proceed with caution with the ground clip lead if troubleshooting the board with an oscilloscope. Disconnect the system from main's earth before attaching the clip to board ground.


### OLED display configuration
At an early stage of the project the author was planning to implement both the 7 segment display and the OLED display. The 7 segment option was never implemented, and the compatibility was removed.
There are some components that you'll have to remove from the BOM and some pads to short.
* Ensure to get a SSD1306 128x64 oled. It is mainly available in a 0.96" size. I've used this part with success: **DD-12864WE-4A**. However, user SZ64 from the forum was able to get a 1.3" display (**UG-2864KSWLG01**) and confirmed that it is pin to pin compatible, and needs 12V. Users NECHTO and afedorov patched the firmware to work with SH1106 displays, patches can be found in this [forum post](http://dangerousprototypes.com/forum/viewtopic.php?f=56&t=7218&p=67042&hilit=display+SH1106#p67042) and recompiled firmware in this [other post](http://dangerousprototypes.com/forum/viewtopic.php?f=56&t=7218&start=1665#p67047).
* Q15, Q17 and U9 (UL2003N) are not needed.
* Ra to Rg are shorted
* Ja to Jg are shorted  
* Short, on the back side of the front pcb, the pins that have some soldermask free pads around, with the pads.
* See the [U19 FAN5331 section](#u19-fan5331-r68) in this document, for picking the correct boost feedback resistor.

### Buzzer
Q20 and D17 are needed only if a DC active buzzer (internal oscillator) is used. The one specified in BOM, however, does not need them.
Unfortunately for now the DC buzzers are not supported by the firmware.

### Sleep sensor  
The author of the project has provided also a sensor module, based on an IR system, to detect whether the iron is in its holder.  
You can use whatever system you want: a mechanical switch, a reed switch, an hall sensor... You can use any switch or any other device that shorts SLEEP to GND when the tool is in the holder. SLEEP is connected to a 3.3v pullup resistor.

### Calibration
You'll need to calibrate the controller by connecting a very precise 10 ohm resistor (0.1% is recommended) between SENSEA and Vout1-.  
Go to the Calibration submenu and turn the trimmer until R shows as close as possible to 100 times the resistor. If the trimmer doesn't get you to the value, try replacing R57 and R59 (one by one) with next higher and next lower value (1.8k, 1.3k).

### Iron ID resistors
The station can automatically recognize the instrument you attach to it. To do this, you will need a resistor pair in the iron connector, so that the system can read it when a new instrument is plugged. If you don't want to switch between instruments, you can simply connect the resistor to the station connector instead of the iron connector.
ID resistors must be not less than 1% tolerance.
We will call Rid1 the resistor that goes between ID and Vout1-, and Rid2 the resistor that goes between ID and Vout2-

| Soldering iron model    | Rid1 | Rid2 |
|:------------------------|:-----|:-----|
| HAKKO T12/T15           | 1k   | 5.6k |
| HAKKO FX8801, HAKKO 907 | 1k   | 820  |
| JBC C245                | 150  | 5.6k |
| JBC C210                | 3k   | 5.6k |
| JBC C105/C115           | 3k   | 1k   |
| JBC Microtweezers       | 1k   | //   |
| JBC Nanotweezers        | 1.5k | //   |
| WELLER WSP80            | 120  | 5.6k |
| WELLER WMRT             | 680  | //   |
| ERSA RT80               | 300  | 110  |
| PACE TD100 Black        | 680  | 560  |
| PACE TD200 Blue         | 680  | 470  |

## Software and programming the PIC
There are two alternatives for the PIC32 firmware:
* Using the firmware without bootloader, loading it directly with a PicKit
* Using the firmware with bootloader, loading the bootloader with the PicKit and the firmware via usb and UniSolder's PC software.

To me it's unclear what are the advantages of picking one choice over the other, I have to ask the author to clarify.

If you don't have a pickit and don't want to get one, you can use an Arduino as [here](http://www.microchip.com/forums/m653443.aspx). I've not tried this solution personally, so i don't know if it works. Let me know if you try this.  
You can also use [pic32prog](https://github.com/sergev/pic32prog) from sergev, if you have a pickit 2 and want to program the microcontroller.  
To load the firmware with a PicKit you will have to use MPLAB X, Microchip's software.  
As zed65 stated in the forum: "You can NOT program the PIC via the PicKit2/3 standalone programming software. You have to put the programmer into MPLab mode in the standalone software then program it via MPLab."  

To attach the PicKit3 to the unisolder board check on the PicKit for the little arrow pointing to pin 1. Connect that pin to the square pad on the unisolder board, and the rest of the pins in order. Pin 6 of the PicKit stays disconnected.  

#### Modify the software
If you want to modify the software you'll have to compile it with XC32 v1.33 compiler (**paid**), adding the "s" option to the optimization.

#### Testing the bootloader
To test if the bootloader loading went ok, hold down keys "+" and "-" during power up. If some moving squares appear on the screen, the bootloader is working.

## Equivalent parts in BOM
Some parts are not really easy to find. Some of them can be easily substituted with equivalent parts.

### Resistors

#### Rs1 shunt resistor, R37, R42
0.003 or 0.004 ohm resistor can be used as a shunt. **WSL3637** from Vishay is used. I wasn't able to find an equivalent part that would have a similar package.
If you use **0.003** ohm shunt, R37 and R42 have to be both **1.5k** 0.1%.  
If you use **0.004** ohm shunt, R37 and R42 have to be both **2.0k** 0.1%.  

#### Ra to Rg 47ohm
Those resistors are not needed. You will need to short their pads with solder or use zero ohm resistors.

#### 3v and 3.0v zener diodes
Despite the different name in the BOM, the same part can be used for both.

#### Rgnd1
This resistor is in a 2512 format, 10M, it is there to prevent huge electrical potentials between the computer's ground when it's connected and the station's ground.  
You can use any value between 1M and 10M, or leave it disconnected if you feel safe, anyway this isn't recommended.

#### Rc2 Bourns trimmer
In BOM it's indicated as Bourns 3362, this part is a THT trimmer from a previous version, correct part number is **Bourns 3364X-1-202E.**  
I'm using a **Bourns 3314J-1-202E** which also fits well.

### Capacitors
For the ceramic capacitors insulator type, C0G is the best, X7R is also good. X5R is not as good as X7R. If it's possible avoid Y5V.
Where voltage is not specified you can pick any voltage. 50V rating is better than higher.  A contributed list of which capacitors need higher voltages than the logic 3.3V would be appreciated.

### Diodes
Please note that many times with diodes there is the same part from a different manufacturer listed with the first two letters.  

#### D1, D2, D3, D4 SR580
SR580 means "Schottky rectifier, 5A, 80V". There's nothing special about these diodes. Just use 5A 80V Schottky in a DO-201 package.  
This part can be substituted with SB5100 or other Schottky Rectifiers with at least 5A current capability and at least 80V forward voltage. However the 80V part is still preferable, because it will have less forward drop.  

#### D5, D8, D10, D14, D15	BAT46WH
Alternative parts:
* BAT46WH

#### D6, D7, D12	SS310A
SS310A means 3A, 100V schottky. Any Schottky with the same ratings will do. For example:
* SK310SMA

#### D9, D11, D13	1N4007
Alternative parts:
* GF1M

#### D18, D19	MMBD1505A
If replacing this part, beware that the reverse leakage current is very important and should be as low as possible.

#### D22	SS34A
SS34A means 3A, 40V schottky. Any Schottky with the same ratings will do. For example:
* SK34SMA
* SS34FA

#### D16, D17, D20, D21	BAV199
This part is common with a suffix, such as "BAV199,215". It is the same part.

#### TVS1 60V TVS
60V TVS is just a 60V TVS. Any 60V TVS or close to this will do. For example:
* 1.5KE62A

#ICs

#### U1 LM2675, R3 and R4
Either the LM2675M-3.3 and the LM2675M-ADJ version can be used.   
If **LM2675M-3.3** is used, R3 has to be 0 (shorted) and R4 has to be 1.5k.  
If **LM2675M-ADJ** is used, R3 has to be 3k and R4 has to be 1.8k.  
LM2674 can be used too.

#### U9 ULN2003L
You don't need this IC, this was only for the 7-seg version.

#### U10 MCP4651-503 (50k)
This part seems hard to find. You can replace it with the MCP4651-104 (100k) version. You can **NOT** use the 103 (10k) version.  
**Beware that this part is different from U15 below**, they have a similar code but with the 5 and the 6 switched.

#### U15 MCP4561-503 (50k)
This part (as before) seems hard to find. You can replace it with the MCP4561-104 (100k) version. You can **NOT** use the 103 (10k) version.  
**Beware that this part is different from U10 above**, they have a similar code but with the 5 and the 6 switched.

#### U6 REF3030
This part seems harder to find than the others. These are some of the possible alternatives:
* MAX6010AEUR
* MAX6063AEUR
* ISL21010CFH330Z
* MAX6035AAUR30 may work, not personally tested.
* LM4120AIM5-3.0 may work, not personally tested.

#### U14 LM4041CIM3-1.2
Can be substituted with **LM4051AEM3-1.2**

#### U12, U13, U18 MCP6V27
This part can be substituted with:
* MCP6V02
* MCP6V07
* AD8629

#### U17 MCP6V03
This part can be substituted with:
* MCP6V01
* MCP6V06
* MCP6V08
* MCP6V26
* MCP6V28
* AD8628

#### U19 FAN5331, R68
This part can be substituted with LM2731, FAN5333A or FAN5333B. Please note that either version of FAN5333 have a different feedback voltage from each other and from the FAN5331. LM2731 has the same feedback voltage. This part is the boost converter for the OLED display. Different OLED displays need different voltages. Usually they can be either 9V or 12V. Check the voltage of your OLED and select R68 accordingly. R68 should be at least 1%.

Follows a table with values that should suit. These values are not tested (FAN5333B with 9V display is tested by me and working), proceed with caution and check the voltage prior to soldering the OLED.

| IC                | R68 for 9V display | R68 for 12V display |
|:------------------|:-------------------|:--------------------|
| FAN5331 (1.230V)  | 4.7k               | 3k                  |
| FAN5333A (0.110V) | 340                | 249                 |
| FAN5333B (0.315V) | 1k                 | 732                 |

### Transistors

#### Q10, Q11: IPD053N08
If you want to change this part, pick a part which has same: package, Rds(on), Vds, and gate threshold voltage.

#### Q2, Q8 SUD50P10
Can be substituted with **SQD50P08**

#### Q10, Q11 IPD053N08
**AUIRFR3607** or **IPD12CN10NGATMA1** can do the job.

To substitute this part the important parameters are:
* Vds(max) should be at least 75V.
* Rds(on) should be no more than 0.01ohm.

#### Q14, Q15, Q16, Q18, Q19, Q21, Q22 IRLML6401
This part can be substituted with VISHAY SI2315BDS-T1-E3 (@Tony, pg 113 unisolder forum)
#### Q15 IRLML6401
This part should not be installed when using the OLED display.

#### Q17 IRLML2502
This part should not be installed when using the OLED display.

### Packages compatibility

#### SOD123 diodes
SOD123 diodes can be used also in miniMELF packages. Check in the document to see which parameters are important, to find a substitute.  
If you can't find the part you are looking for, ask in the thread and please open an issue/pull request to update the document.

#### SOT223
Footprints for the SOT223 components are also compatible with DPAK packages.

### Connectors
These are the part numbers for the connectors I've used. I was able to crimp all of them with a single tool: **NEWBRAND NB-8160-04**

#### J1, J7
Cable connector: MOLEX 039013022 555702R1  
Crimp pin: MOLEX 39-00-0039  
PCB connector: MOLEX 5566-02A-210  

#### J2, J3, J9  
Cable connector: MOLEX 5557-04R  
Crimp pin: MOLEX 39-00-0039  
PCB connector: MOLEX 039288040 5566-04A-210  

#### J4, J8  
Cable connector: 3M 89110-0101HA  
PCB connector: 3M N2510-6002RB  

#### J6
Cable connector: MOLEX 022013037 2695-03RP  
Crimp pin: MOLEX 008550102 2759-(555)L  
PCB connector: MOLEX 022292031 AE-6410-03A(241)  

#### J5 RJ11v  
This is just an RJ11 vertical connector. I found that Molex 95522-2667 fits perfectly.

### Iron connector
If you don't want to keep the original connector from your iron, I've used and I suggest:  
Socket: **LUMBERG KFV 81**  
Plug: **LUMBERG 0332 08-1**  

#### JBC T245
The matching socket for this iron, if you want to keep the original plug, is the Hirose RPC1-12RB-6P(71)

## Contributing
Contributing to this repo is very welcome, feel free to add any information.  
The information on this repo are gathered all around the internet, especially from the Dangerous Proto forum, and not only by first-hand experience. Please specify if what you're adding is tested by you personally or mention the source.  
Please pay attention to not add copyright-protected material to the repo. Photos you're not the author have to be considered under full copyright by the author, unless otherwise explicitly stated.

Many thanks to the contributors @rsre and @lauer2356/EricLau


~~Currently I'm on page 100 of the topic. This is just a reminder for myself, ignore it~~
