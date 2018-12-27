
### Using Limit Switches

It is often advantageous to use limit switches to set how far an actuator can go. It is possible to [configure hardware using limit switches and Talons](http://crosstheroadelectronics.com/Talon%20SRX%20User%27s%20Guide.pdf#page=20), so that the limit switch directly inputs to the Talon, but presented here is a software solution.

### Insertable VI

For the sake of this tutorial, we will construct a VI that takes in the DevRef's for each piece of hardware associated with this example, and performs the logic to set the motor. This will allow this VI to be used in Autonomous and/or Teleop, or if it needs to be run all the time, can be placed in Periodic Tasks.

### Begin.vi

Just a formality, but we will start by opening the necessary hardware in Begin.vi. For this example, we will use two limit switches, a joystick, and a motor.

{% include downloadableImage.html path='images/LimitSwitch_Begin.png' alt='Opening the limit switch in begin.vi' height=507 width=220 %}

[<img alt="" src="examples\limitswitch\LimitSwitch_Begin.png" />](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGLXI4VDdjaUVIZUk)

### Actuator.vi

In this example, we are constructing a vi, that can be called frequently to set the values of the motor based on joystick input, and we will add front panel controls in to allow for running this VI in Autonomous and passing in constants to control the motor.

For an example on having a motor remain in a state until a new input, we will refer you to our [State Machine Tutorial](/state-machine/)

### Block Diagram

We are assuming that the hardware has already been opened. To allow this VI to execute as quickly as possible, we will rely on the calling VI to provide the DevRef's as opposed to Refnums.

Let's start simple and use two buttons and some selects to set the motor.

{% include downloadableImage.html path='images/LimitSwitch_Basic.png' alt='Using Joystick values to set motor' height=225 width=372 %}

[<img alt="" src="examples\limitswitch\LimitSwitch_Basic.png" />](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGRWxWQm9jTGJQbWs)

Now, this is good, but we wanted the limit switches to turn off the motor at its limits, so let's add that in. One way to do this is to use more selects such that when a limit switch is pressed, it allows the value to be anywhere within a range that is either stopped or goes the other way. Like below.

{% include downloadableImage.html path='images/LimitSwitch_BasicWLimits.png' alt='Basic use of limit switch' height=321 width=650 %}

[<img alt="" src="examples\limitswitch\LimitSwitch_BasicWLimits.png" />](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGdVk1Wm9mUFVyZGs)

**NOTE: This is configured for the limit switch to report true when pressed, depending on how it is wired, this may be backwards, if this is the case, merely insert a not gate in between the read and the select.**

At this point, the wiring is becoming a little chaotic, but we want to keep our constants so that this vi is generic and can be used year after year and by multiple teams, so we will switch to using multiple nested case structures.

{% include downloadableImage.html path='images/LimitSwitch_CaseWLimit.png' alt='Using case switches for limit switch' height=363 width=603 %}

[<img alt="" src="examples\limitswitch\LimitSwitch_CaseWLimit.png" />](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGeWxMRVVNdF9uclU)

This is good, we have the motor set by the joystick buttons and using the limit switch to not allow the motor to continue past the limit switches.

Now we want to add some Boolean controls in that will allow us to call this VI in Auto and ignore the joystick input.

[<img alt="" src="examples\limitswitch\limitSwitch_Auto.png" />](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGekNCZDlyUlRSN0k)

Now we will go to the front panel and clean it up a little bit.

### Front Panel

At this point, we just want to tidy up a bit by doing some alignments and fitting horizontally and vertically by aligning the tops of the clusters and one of the buttons, then a horizontal gap between them and finally the second button was aligned left and vertically compressed.

{% include zoomableImage.html path='images/LimitSwitch_FrontPanel.png' alt='Tyding up the front panel' scaler='' height=712 width=1210 %}

<img alt="" src="examples\limitswitch\LimitSwitch_FrontPanel.png" height="200px"; width="auto";/>

For this VI to truly be universal, we need to set the buttons to latch mode allowing the VI to be called once, setting them to true in autonomous, then called again without passing anything so it reads the joystick.

{% include zoomableImage.html path='images/LimitSwitch_FrontPanelButtons.png' alt='Setting button action mode' scaler='' height=1178 width=2033 %}

<img alt="" src="examples\limitswitch\LimitSwitch_FrontPanelButtons.png" height="200px"; width="auto";/>

### Connector Pane

By convention, inputs are on the left so we wire the DevRef's and buttons to terminals on the left.

1- Select appropriate Terminal,

{% include zoomableImage.html path='images/LimitSwitch_FrontPanelTerminal1.png' alt='Setting the terminal' scaler='' height=241 width=500 %}

<img alt="" height="100px"; width="auto"; src="examples\limitswitch\LimitSwitch_FrontPanelTerminal1.png" />

2 - Select Control or Indicator

{% include zoomableImage.html path='images/LimitSwitch_FrontPanelTerminal2.png' alt='Setting the control for that terminal' scaler='' height=856 width=1472 %}

<img alt="" height="200px"; width="auto"; src="examples\limitswitch\LimitSwitch_FrontPanelTerminal2.png" />

### Finished

And with that, this vi is ready to be brought into the robot project and called to set the actuator motor from anywhere. - Auto, Teleop, or Timed Tasks.

[click here to download finished version](https://drive.google.com/uc?export=download&amp;id=0BwEBnEBtHotGaTNxLWltc09XNHM)

**WARNING - reading joysticks in multiple locations tends to cause lag, if you need more controls than you wish to put in here, move the joystick code outside and pass in the button values.**

### Some Possible Improvements

One could configure this vi with memory so the motor continues on its path until it reaches a limit switch or the command is changed, please see our tutorial on state machines.

One could set the DevRef input [terminals to required](http://zone.ni.com/reference/en-XX/help/371361H-01/lvconcepts/building_connector_pane/) so that they cannot be left un-wired on accident.

One could configure it using [Functional Global Variable architecture](https://decibel.ni.com/content/docs/DOC-2143) to open the devices itself on the first run, then remember the DevRefs

### Request More Details

[click here to request a clarification](https://docs.google.com/a/harding.edu/forms/d/1zihjhp8RryXq4o2vR1oDJK2dUg86iPsCx60G7NpEkFA/viewform?usp=send_form)
