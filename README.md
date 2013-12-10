STM32F4DiscoveryBidirectionalHID
================================

This project is a fully functional project for the Coocox IDE for the STM32F4Discovery board.

It provides an easy to use 'base' any project you can imagine that needs bidirectional HID USB capabilities.

In addition, I have provided two python programs(one for windows, one for linux) which seemlessly communicate with the STM32F4Discovery board, after having been programmed with these project files.

As a demonstration of the capabilities of this project, I have implemented two simple command/response sequences.

1. Sending the string 'test' to the STM32F4Discovery from the included python program, you will get a response from the STM32F4Discovery stating 'Testing 1 2 3 . . .'

2. Sending the string 'led' plus a number '3', '4', '5', or '6', the corresponding LED3/4/5/6 on the STM32F4Discovery will toggle and the STM32F4Discovery will also respond with text indicating such.

In addition, I have included a simple function to allow sending text via the HID protocol: void SendStrToUSB(uint8_t* str);

Everything is easily understood by looking at the main while loop in main.c, as changing the code to your desire is made as seemless and simple as possible. It should be rather self-explanatory.

Coocox IDE setup
================

Download and install the [CooCox IDE](http://www.coocox.org/index.html) and [GNU Tools for Arm](https://launchpad.net/gcc-arm-embedded). Merely point the Coocox IDE at the GNU Tools bin folder.

STM32F4Discovery ST-Link setup
==============================

You will also want to get the [ST-LINK/V2 in-circuit debugger/programmer](http://www.st.com/web/catalog/tools/FM146/CL1984/SC724/SS1677/PF251168) for debugging and programming.

Python setup
============

Merely install python, and the pyusb module, there are tons of tutorials online for both windows and linux installations.

When you are done installing python you merely have to type these commands to talk to your STM32F4Discovery after you have programmed it from the included project filees via Coocox:

at the command line type:

stm32f4usb-(windows or linux).py test

The response should be: Testing 1 2 3 . . .

or

stm32f4usb-(windows or linux).py led3

The response should be: LED3(Orange) has been toggled!

or

stm32f4usb-(windows or linux).py led4

The response should be: LED4(Green) has been toggled!

or

stm32f4usb-(windows or linux).py led5

The response should be: LED5(Red) has been toggled!

or

stm32f4usb-(windows or linux).py led6

The response should be: LED6(Blue) has been toggled!

Enjoy!
======
