# DIN Slot Information Display
This project is for those with an extra DIN slot (used for radios and cd changers).
## Usage
### Case
Included in this repository is the STL files required to make the case.

However, becuase the screws I am using were used, you may need to edit the sizes of the holes in order to assemble the case.

Freecad was used to create the models if editing the models is required.

### Code
This project was mainly created for cars using the k-line protocal for communication.

**THIS MEANS UNLESS YOUR CAR USES K-LINE, THE CODE WILL NOT WORK.**

The Arduino Nano is being used and pin numbers may have to edited if a different microcontroller is used.

#### Dependances
This project requires the fallowing liberaries to be installed from Arduino IDE liberary manager:
|Liberary name|  Auther  |   Version  |
|      ---    |     ---  |    ---     |
|  OBD2_KLine |   Muki01 |    1.0.1   |
| LiquidCrystal I2C  |  Marco Schwarts | 1.1.2|
