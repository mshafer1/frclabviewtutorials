---
layout: basic
title: File Based Autonomous (an easy way)
description: A methodology for storing Autonomous configuration in the Autonomous.vi Front Panel to allow for multiple runs with tweaks without re-deploying code.
---

### Clarification

This optimization is not for the robot, rather it is for the developer. What is presented below is a methodology that - when combined with certain architectures, can minimize the amount of code necessary - thereby reducing the time to write it and the effort to debug/enhance it.

### Setup

For the duration of this tutorial, it is assumed that the motors and joysticks have already been opened in Begin.vi, and that this robot has a wheeled shooter.

### Architecture

This configuration utilizes the [producer-consumer architecture](/tutorials/producer-consumer).
This allows the code for controlling the actuators to be in one single place (periodic tasks) and the code to control it to be in either 
Teleop or Autonomous - depending on which mode the robot is in.


### Caveat

This setup has both a major advantage and disadvantage. The advantage is that the code for moving is reused, and does not need to be repeated in addition to the fact that if a control is changed in autonomous, the robot only needs to be re-enabled to use the updated variation.
<br/>
The disadvantage is because the movements are stored in a control, one must go to edit > make current values default in order to make the changes be saved to the vi.


{% include zoomableImage.html path='images/currentValues.png' alt='Setting the current values' height=667 width=773 %}

### Autonomous.vi


We start by adding a shooter speed to the default array of motor movements.

{% include zoomableImage.html path='images/addingSpeed.png' alt='Adding the shooter speed to the array' height=358 width=773 %}


In the block diagram, we enable the for loop that uses the array, and update the current movement indicator (delete and recreate).


{% include downloadableImage.html path='images/enableForLoop.png' alt='enable the for loop to use the array.' height=378 width=709 %}

This loop will perform each instruction for the specified amount of time, then move onto the next instruction in the array. 
By adding what the shooter's speed should be, it now controls the whole robot with this set of instructions.

Using an [fgv](/tutorials/fgv/) to pass the shooter speed to periodic tasks, the autonomous.vi is finished.

{% include downloadableImage.html path='images/auto.png' alt='finishing up' height=423 width=709 %}

### Periodic Tasks.vi

In periodic tasks, the fgv is read and the motor is set.

{% include downloadableImage.html path='images/periodic.png' alt='setting the motor' height=486 width=700 %}

### Summary

By using the array of movements and the fgv, no code is unnecessarily repeated (assuming that the drive code used in teleop is slightly different),
and by using the [fgv](/tutorials/fgv/), data checking can be performed that values that are input for the shooter speed are valid.


### Possible Improvements

- One could use encoders and a PID to make the movements instead of time
- One could change the loop so that it remains there until the motors are done moving (if using previous improvement)

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/1UbODQWDz7NuqA-_Bt2zzXWO6hTLlmWoB5HwroNHUtl4/viewform?usp=send_form){:target="_blank"}
