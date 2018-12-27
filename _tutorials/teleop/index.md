---
layout: basic
title: Teleop
---


### Background

When the authors of this website first started programming for FRC, we would get the 'Robot Drive Not Running Fast Enough' error frequently. After speaking with several teams at regionals, we came up with a solution. The following optimization has been used by the teams that we are alumni of and mentors of, and none of the teams have had that error since.

-- note --

In the summer of 2016, we were able to actually do a performance test on this that showed that the following method significantly outperformed the DevRef get/set method. We gave our results to the people at NI that work on this, and they said the reason was the DevRef get allocated memory every time and they fixed that for the 2017 season (and presumabley onwards).<br/>
For that reason, the following moves from being an optimization to reduce lag to being an optimization for the developer (by not causing him/her to type out a case sensitive name multiple and related less than great development methods).

### Initialize

Begin by opening the devices in Begin.vi, notice that we even skip setting the refnum, and just bundle everything.

{% include downloadableImage.html path='images/init.png' alt='Setup' height=224 width=330 %}


Now, place an indicator on the front panel, here is another place where the [TypeDef](/type-def/) can be extremely useful, so we'll take a moment to set one up, notice that we also take this opportunity to rename each element in the cluster to something meaningful (drive joystick, rather than JoystickDevRef)

{% include zoomableImage.html path='images/devRef.png' alt='Indicator' scaler='' height=768 width=1024 %}


We can use these names in the Begin.vi block diagram as well - by switching the bundle for a bundle by name - this also bears other advantages like what is demonstrated in the [TypeDef tutorial](/type-def/)

{% include downloadableImage.html path='images/beginWithTypeDef.png' alt='setting up the TypeDef' height=273 width=380 %}


For now, we copy the indicator from Begin, to Teleop and paste it on the front panel (and switch it to a control).

{% include zoomableImage.html path='images/Teleop.png' alt='Teleop' scaler='' height=768 width=1304 %}

We can connect both the control and the indicator to the terminal block, and connect the two in main.vi

Inside Teleop we can unbundle the DevRefs and use them.

{% include downloadableImage.html path='images/TeleopUnbundle.png' alt='Undbundled TypeDef\'s' height=94 width=215 %}

This wire allows us to skip the getDevRef for every device every time through the loop. Giving us the performance boost we were after.

Notice that the wire in main will not break thanks to the typedef.

This minor change to the architecture can permit Teleop to complete just a little faster, which can remove the error message, and using a typedef, can save a lot of time during development too.

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/a/harding.edu/forms/d/1ZDh67B3i0bncr6dbTfLuGpHzn4Qwmzl5LdpjiVPbpcw/viewform?usp=send_form){:target="_blank"}
