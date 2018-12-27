---
layout: basic
title: Arduino on the Dashboard
---

### Background

Many of the years that the authors have been involved with FRC, we wanted to collect I/O on the Driver Station. Sometimes it was an abort button, other times a potentiometer to select an auto program, and still others we wanted to put LED's on the Driver Station that would light up to alert the drivers/coach to something (game piece acquired, aligned for shot, etc.)

The TI Launchpad allows for the input to the driverstation by acting as an extra Joystick but  requires a bit of setup and is only an input.

Below is presented a setup that allows for an Arduino to be used for generic I/O on the Driver Station through the LabVIEW Interface for Arduino (now, [LINX](https://www.labviewmakerhub.com/doku.php?id=libraries:linx:start)).

For this tutorial, we will implement reading a potentiometer and displaying it on the Dashboard. The setup presented below can be used to read or write to/from any of the pins on the Arduino (including writing PWM out).

### Setup

First, we wire a potentiometer so that it can act as an Analog Input to the Arduino.

We wire 5V and Ground from the Arduino to the two outer pins of the potentiometer and connect the wiper pin to A0.

{% include zoomableImage.html path='images/wire_potentiometer.jpg' alt='Wire the potentiometer to A0' scaler='' height=612 width=816 %}

The library we will use to interact with the Arduino from LabVIEW is called the LabVIEW Interface for Arduino (now, [LINX](https://www.labviewhacker.com/doku.php?id=libraries:linx:start)) which we need to download and install to LabVIEW.

{% include zoomableImage.html path='images/labVIEWMakerHubDownloadLinx.png' alt='On labviewmakerhub.com select download now' scaler='' height=728 width=1366 %}

If prompted, select to open in Package Manager.

{% include zoomableImage.html path='images/OpenInPackageManager.png' alt='open in VI Package Manager' scaler='' height=728 width=1366 %}

Select Install

{% include zoomableImage.html path='images/vipmInstall.png' alt='Select install' scaler='' height=544 width=783 %}

Follow prompts

{% include zoomableImage.html path='images/vipmFollowPrmopts.png' alt='Follow prompts' scaler='' height=544 width=783 %}

To see where the installed library is in the palette, select 'Show in Palettes'

{% include zoomableImage.html path='images/vipmShowInPalettes.png' alt='Show in palettes' scaler='' height=544 width=783 %}

Connect the Arduino to the computer and open LabVIEW 
	(Note: The Arduino driver is needed for this step - 
	you can download and install it with the default IDE at 
	[Arduino.cc](http://arduino.cc))


From the launch screen (or any screen actually) select Tools -> MakerHub -> LINX -> 
	LINX Firmware Wizard...


{% include zoomableImage.html path='images/lvOpenFirmwareWizard.png' alt='Open Firmware wizard' scaler='' height=602 width=700 %}

Select the correct type of Arduino firmware to use and click next.

{% include zoomableImage.html path='images/lvSelectType.png' alt='Select the correct type of Arduino' scaler='' height=509 width=642 %}

Select the port that the Arduino is connected to (See Arduino getting started info for help) and click next to download firmware.

This firmware implements a communication interface that allows for the VIs we installed earlier to control the I/O on the Arduino.

{% include zoomableImage.html path='images/linxSelectPort.png' alt='Select Port' scaler='' height=509 width=642 %}

Click next to download the default firmware image

{% include zoomableImage.html path='images/confirm.png' alt='click next' scaler='' height=509 width=642 %}

### Create custom dashboard

Once the download finishes, press "Finish" to return to the LabVIEW welcome screen.

Select a New -> FRC Dashboard Project.

In the configuration dialogue choose what you would like to name the project and where to save it and click next.

{% include zoomableImage.html path='images/lvConfigProject.png' alt='Select the correct type of Arduino' scaler='' height=449 width=613 %}

In the Project Explorer window, select and open "Dashboard Main.vi"


	This is a source code version of the default dashboard. 
	Go to the block diagram (press CTRL + e or select Window -> Show Block Diagram).


Scroll to the top (the region that is expected to be edited), and add a While Loop.

{% include zoomableImage.html path='images/lvDefaultBlockDiagram.png' alt='View the block diagram' scaler='' height=728 width=1366 %}

Open the palette (right click if it is not already open) and select MakerHub -> LINX -> Open

This VI creates the communication link to the Arduino for us.

Place it to the left of the new While Loop

{% include zoomableImage.html path='images/lvLinxOpen.png' alt='Get the LINX Open vi' scaler='' height=728 width=1366 %}

Right click on the top left terminal of the Open.vi and select Create -> Constant

Select the port the Arduino is connected to.

{% include zoomableImage.html path='images/lvSelectPort.png' alt='Create port constant' scaler='' height=496 width=1304 %}

Wire the top right terminal (LINX Resource) to the While Loop and set it to a Shift Register

{% include zoomableImage.html path='images/lvLinxShiftRegister.png' alt='Wire resource to loop' scaler='' height=496 width=1304 %}

Wire the error out from the Open to the While Loop.

Get a Close.vi from the LINX palette and place it to 
	the right of the while Loop - this VI will unreserve the port.


Wire the error from the left of the While Loop to the close vi

{% include zoomableImage.html path='images/lvWireErrorToClose.png' alt='Wire LINX close VI' scaler='' height=496 width=1304 %}

Branch the error wire and connect it to the stop terminal for the loop.

From the MakerHub -> LINX -> Peripherals -> Analog palette Select the Analog Read.vi

{% include zoomableImage.html path='images/lvGetAI.png' alt='Get Analog Read vi' scaler='' height=728 width=1366 %}

And set the Analog channel and pass the reference and the error through the read vi

{% include downloadableImage.html path='images/basicRead.png' alt='Set the analog channel to read' height=162 width=995 %}

Unfortunately, if we abort the VI, the port to the Arduino is not properly closed.

The port will remain reserved (but unavailable to the Open.vi) 
	until the owning process (right now, LabVIEW) is completely shut down.


This does not create an issue for the built version of the dashboard as that is an executable of its own
	and releases the port when it is closed.

To make this easier to deal with while in development in LabVIEW, we will create a stop button in a new VI. Create a new VI.

Place a stop button and an round LED (or some other form of both a Boolean control and indicator) on the front panel.

{% include zoomableImage.html path='images/stopFP.png' alt='Stop vi front panel' scaler='' height=503 width=785 %}

Connect the output to a terminal on the VI by clicking on the terminal first, then the indicator

{% include zoomableImage.html path='images/connectToTerminal.png' alt='Connect the output to the terminal' scaler='' height=503 width=785 %}

On the block diagram, simply connect the control to the indicator.

This will allow you to press the button to send a True out to the calling VI.

Save this vi as stop_button.vi

{% include downloadableImage.html path='images/connectControlToIndicator.png' alt='connect the control to the indicator.' height=98 width=320 %}

Drag the VI just created (by the icon) to the block diagram of the Dashboard Main.vi

{% include zoomableImage.html path='images/dragStopVI.png' alt='Drag the Stop VI in' scaler='' height=768 width=1366 %}

Insert an OR on the Error wire going to the stop terminal and connect the output of the Stop VI to the OR

{% include zoomableImage.html path='images/connectStopVI.png' alt='Connect the Stop VI to the or' scaler='' height=728 width=1366 %}

The finished product

{% include downloadableImage.html path='images/finishedArduinoLoop.png' alt='The finished Arduino Loop' height=162 width=995 %}

### Test

For the sake of testing it, we will replace the numeric indicator with a Horizontal Progress bar.

{% include zoomableImage.html path='images/lvProgressBar.png' alt='replace the numeric indicator with a Horizontal Progress bar' scaler='' height=505 width=1061 %}

Open Properties on the bar.

{% include zoomableImage.html path='images/lvBarOpenProperties.png' alt='Open the properties' scaler='' height=728 width=1366 %}

On the scale tab set the Maximum to 5 (the Arduino will read an AI from 0V to 5V).

{% include zoomableImage.html path='images/lvBarPropMax.png' alt='Set the max to 5' scaler='' height=499 width=515 %}

Run the Dashboard VI. After a few seconds, the connection with the Arduino 
	will be established and the progress bar will update as you move the potentiometer.

{% include zoomableImage.html path='images/lvBarUpdates.png' alt='Watch the bar update' scaler='' height=442 width=1044 %}

To stop running, first open stop_button.vi and press the stop button the front panel

This will cause the Arduino loop to stop executing allowing the Close.vi to close the port to it.

{% include zoomableImage.html path='images/lvPressStop.png' alt='Press the Stop Button' scaler='' height=503 width=785 %}

(How can I know if it worked?, the stop_button vi will stop executing because it is no longer getting called).

You can then abort the dashboard VI from the block diagram.

See our tutorial on [Connecting a Gyro to the dashboard](/gyro/#sec_To_use_the_dashboard_you_just_created) for more information on using this custom dashboard with the Driver Station and running it.

### Sending data to the robot

To send this value to the robot, use the Dashboard Write vi and name the variable.

{% include zoomableImage.html path='images/lvSendToRobot.png' alt='Send to robot' scaler='' height=433 width=1026 %}

The Dashboard VI's can be used to write data on the robot and read it on the dashboard, or vice versa.

Use the write vi to send the data and the read vi to receive it. Make sure to use the same data type on each end and the same (case-sensitive) name.

{% include downloadableImage.html path='images/lvDashboardReadWrite.png' alt='Read and write vi\'s' height=130 width=346 %}

You can use the data sent from the robot to control the Arduino as well.

{% include downloadableImage.html path='images/lvSmartDashboardRead.png' alt='Read data from the robot' height=103 width=285 %}

### To use the dashboard you just created

Easiest way, build it, open it, then open the Driver Station. The DS should recognize that a dashboard is already open and just work with it.

### Some possible improvements

	- Use binary switches (connected to the DI/O pins) for selecting an Auto.
	- Create an abort button to stop a sequence.
	- Connect LEDs to the Arduino and turn them on when the robot detects something.

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/e/1FAIpQLScoNTU1fMBIMOPEjr39TV6-f26npH6rwBOyiETmzymyWFKAjA/viewform)
