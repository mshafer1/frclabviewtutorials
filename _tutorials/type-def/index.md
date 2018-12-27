---
layout: basic
title: TypeDef
---


You are actually already using these whether you realize it or not - you'll be able to recognize them in some of the standard code once we are through.

A Type Def is a custom control that has all the instances linked so that one can change the original and immediately have the changes reflected throughout the project.&nbsp;([NI Documentation here](http://zone.ni.com/reference/en-XX/help/371361H-01/lvhowto/creating_type_defs/))

For this example, we will be creating and modifying a Type Def for a [state machine](/state-machine/)

### Initialization

Just a formality, but we will open several devices in Begin.vi

{% include downloadableImage.html path='images/StateMachineOpenActuator.png' alt='Initialization' height=415 width=220 %}

### Teleop

Due to the constructs of this data structure, it can be implemented in Periodic Tasks or in Teleop, because our state machine tutorial already shows a similar one in Periodic Tasks.vi, we will implement this one in Teleop.

To start, create a enum control on the front panel, and right click on it. From the menu, select "Make Type Def."

{% include zoomableImage.html path='images/StateMachineCreateTypeDef.png' alt='create the Type Def.' scaler='' height=761 width=504 %}

<img alt="" src="examples\typedef\StateMachineCreateTypeDef.png" style="height: 415px; width: 275px;" />

Right click again and select "Open Type Def"

{% include zoomableImage.html path='images/StateMachineOpenTypeDef.png' alt='Open the typedef' scaler='' height=754 width=632 %}

<img alt="StateMachineOpenTypeDef.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

Once the Type Def is open, we can set the items of the enum. For this example the Up, Down, and Initialize, have been entered.

{% include zoomableImage.html path='images/modes.png' alt='The initial configuration of a couple of modes' scaler='' height=499 width=515 %}

<img alt="modes.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

Back in Teleop.vi, we will use a feedback node to keep track of the current state.

{% include downloadableImage.html path='images/feedback.Oops.png' alt='initial setup conditions' height=393 width=593 %}

[<img alt="feedback.Oops.png" style="height: 358px; width: 300px;" src="examples\typedef\ />](https://docs.google.com/uc?export=download&id=0BwEBnEBtHotGaExHUDl0RTNENm8)

Here we realize that a mistake was made - we want to have a state for getting the user input.

If we right click on the constant that was made from our original control, we can reopen the typedef.

{% include zoomableImage.html path='images/reopenedTypedef.png' alt='Re-opening the typedef' scaler='' height=514 width=764 %}

<img alt="reopenedTypedef.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

And we just add the get user input case to the values,

{% include zoomableImage.html path='images/addedOption.png' alt='Adding another option' scaler='' height=499 width=515 %}

<img alt="addedOption.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

We also need to tell LabVIEW to apply the changes

{% include zoomableImage.html path='images/applyChanges.png' alt='Applying the change' scaler='' height=539 width=327 %}

<img alt="applyChanges.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

Back in teleop, notice that both instances of the Type Def have updated.

{% include zoomableImage.html path='images/teleopUpdated.png' alt='it updated inside Teleo too.' scaler='' height=349 width=231 %}

<img alt="teleopUpdated.png" style="height: 358px; width: 300px;" src="examples\typedef\ />

And we finish out (most of this is implemented in our State Machines tutorial, so for details on that, [click here](/state-machine/))

{% include downloadableImage.html path='images/finished.png' alt='finishing up' height=425 width=886 %}

[<img alt="finished.png" style="width: 600px; height: auto;" src="examples\typedef\ />](https://docs.google.com/uc?export=download&id=0BwEBnEBtHotGQ1JRbVppYW9OVUU)

#### This tutorial is meant to be suggestive of how one might use a Type Def in the FIRST Robotics Competition. It will likely need to be modified to fit your specific application.

While this is a short example, the power of the Type Def grows exponentially. This last year our team had to add a case to a state machine that already had eleven (or so) cases, in the past, that would have meant deleting all the next case constants, modifying the case structure to take the new one, . . . Fortunately we had implemented a Type Def for our possible modes, and adding that case became as simple as the above example.

#### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/1IFFYDrJ7nq8cMuUK5Py9xQ8ztbp9hwLU4hM5a1MSkvs/viewform?usp=send_form)
