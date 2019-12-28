---
layout: basic
title: FGV
---

### What is a Functional Global Variable(FGV)?

An FGV is a [standard LabVIEW data structure](https://decibel.ni.com/content/docs/DOC-2143){:target="_blank"} that implements data storage in a globally accessible way.
	Every time you call the FGV (which is a vi), the block diagram runs exactly once - either updating the data or reading it.

### FGV vs. Global Variable

The FGV is a data structure designed to help prevent  [race conditions](http://zone.ni.com/reference/en-XX/help/371361J-01/lvconcepts/using_local_and_global/#Race_Conditions){:target="_blank"}.
However, if you are writing to your variable in one loop (for example, in Teleop), and reading from it in another (for example, periodic tasks), this will not cause a race condition.

There are three criteria that should be considered when choosing to implement an FGV or a simple Global

* Performance
If you know that race conditions will not occur (you only write to it in one place), then a Global wins. [Globals offer a significant speed performance over FGVs](http://vishots.com/wp-content/uploads/2013/12/ts2147hollenback.pdf#page=25){:target="_blank"}
	* See also [team 358's documentation for how to create globals](http://www.team358.org/files/programming/ControlSystem2015-2019/labview/CreateGlobal.pdf){:target="_blank"} and [the WPI documentation on global and local variables](https://wpilib.screenstepslive.com/s/currentCS/m/labview/l/696737-local-and-global-variables-in-labview-for-frc){:target="_blank"}.

* Custom Boundaries
	Here an FGV wins. If you want your shooter wheel speed (or whatever the data represents) to have certain boundaries on it (i.e. from 0 to 0.5), than an FGV can allow you to enforce this whenever setting the value. So an FGV wins in this case.

* Race Conditions
	This one is the trump card, if one loop (for example, Teleop) needs to increment whatever is currently in the variable, and another occasionally needs to decrement it, use an fgv

		
### Always consider which is the better data structure for the particular scenario.



### How to make an FGV

For this example, we will make an FGV that contains the speed for the a shooter motor, and will briefly discuss how to use it

### Create a new VI

This vi will be the FGV, so it needs a couple of controls.
* An Enum - use an enum to determine if initializing, setting, or reading the data
* Motor In - use a numeric input to allow for the data to be set
* Motor Out - use a numeric indicator for passing the data out to the calling code


{% include zoomableImage.html path='images/frontPanel.png' alt='Adding the controls and indicator' height=503 width=785 %}

These controls and the indicator need to be accessible via the connector pane.
<br/>
To connect a control or indicator to the connector pane, select the desired terminal.


{% include zoomableImage.html path='images/terminal1.png' alt='select a terminal' height=171 width=202 %}


Then select the control or indicator to connect it to.


{% include zoomableImage.html path='images/terminal2.png' alt='select the corresponding control/indicator' height=460 width=800 %}

### Block Diagram


The basis of the FGV is a while loop that has two things:
* A constant so it <u>only runs once</u>
* An <u>uninitialized</u> shift register to hold the data



Add a shift register to the while loop


{% include zoomableImage.html path='images/AddShiftRegister.png' alt='Add a shift register to the while loop' height=720 width=510 %}


Put a case structure inside the while loop and connect it the enum to the selector.
Notice that not all of the enum values are setup as cases initially, so right click on the case structure and select "Add case for every value".



For the initialize case, put a default value in.


{% include zoomableImage.html path='images/Init.png' alt='Put a default value in the initialize case' height=480 width=510 %}


In the set case, this is where we can enforce the valid range of values. We take the input and run it through a coerce block and store the coerced value in the shift register.


{% include downloadableImage.html path='images/set.png' alt='Coerce the value and put it int eh shift register' height=218 width=385 %}


In the read case, we take the value from the shift register and report it to the indicator.


{% include zoomableImage.html path='images/Read.png' alt='Pass the shift register out to the indicator' height=441 width=511 %}


We are now faced with a decision of what to do in the other cases where the output is not needed. 
<br/>
Two options present themselves:
1. Move it to the output of the shift register so it is always updated
1. Configure the output to be the default for a number (which is zero) if the selected Mode is not Read.
<br/>
This example implements a default.


{% include zoomableImage.html path='images/useDefault.png' alt='Use the default value when not reading' height=608 width=510 %}

And we are Done. <a href="files/fgv.vi" download>Click here to download the finished version</a>

{% include downloadableImage.html path='images/finished.png' alt='Final version' height=218 width=385 %}

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/1k0Ud3et2y2xGKg-mLIG5weMitF4ETSYoHUwcaLNoGAw/viewform?usp=send_form){:target="_blank"}
