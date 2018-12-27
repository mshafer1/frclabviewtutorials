---
layout: basic
title: Cameras - Switching
---


### Note

This tutorial was written in the 2015-16 FRC season Stronghold.<br/>
**The shipping vision code has changed so much since then that this method is obsolete**.

### Background

A common desire among FRC teams has been to have multiple cameras on a robot that can easily be switched between, however coding a solution has not been trivial.  As a result, my teammate James and I (Dillon), from FRC team 3061, Huskie Robotics, came up with this relatively simple solution.

### OverView

The basic concept is that we are modifying two WPI camera VIs that handle sending a camera image to the PC.  The modification involves changing the VIs to accept multiple camera Device Refs and then iterating the necessary code over the camera Device Reference whose image is needed at that time.

### Initialize

Begin by making a personal and renamed copy of two WPI libraries, which can be found by searching in the LabVIEW project window.

Make a copy of **WPI_CameraBackground Loop.vi** and call it **WPI_*Dual*CameraBackground Loop.vi**.  Also, make a copy of **WPI_CameraSend Images To PC Loop.vi** and call it **WPI_*Dual*CameraSend Images To PC Loop.vi**

Save these somewhere convenient and accessible.

### Vision Processing.vi

Here is the original Vision Processing.vi for reference:

{% include downloadableImage.html path='images/Vision Processing.png' alt='original Vision Processing.vi' height=539 width=1440 %}

And now the modified version:

{% include downloadableImage.html path='images/New Vision Processing.png' alt='modified Vision Processing.vi' height=512 width=1518 %}

As you can see, several changes were made:
<br/>
* Duplicate the generic camera set-up code for "USB 0" and "USB 1"
* Run **both** Device References through the **WPI_CameraUpdate Camera Status.vi** (This step is critical, otherwise the camera feed will appear to try and change, but it will revert to the same camera)
* The while loop can be left alone and used for actual processing of images
* Call the custom made **WPI_DualCameraBackground Loop.vi**. Note that creating the second camera Device Reference input for this VI is part of the next step.



### WPI_DualCameraBackground Loop.vi

Very little needs to be modified in this VI, as the cameras are always USB and therefore no modification of the case structure is required.  Simply add a second Device Reference for your new camera and pass both these Device References to **WPI_DualCamerSend Images To PC Loop.vi**. Note that creating the second camera Device Reference input for this VI is part of the next step.

Relevant part of original VI:

{% include downloadableImage.html path='images/CameraBkgLoop.png' alt='original WPI_CameraBackgroundLoop.vi' height=101 width=174 %}

Modified Portion:

{% include downloadableImage.html path='images/New CameraBkgLoop.png' alt='new WPI_DualCameraBackgroundLoop.vi' height=116 width=200 %}

### WPI_DualCameraSend Images To PC Loop.vi

This VI is the most change-heavy, although it is still not very complex. Simply follow the instructions and utilize the snippets to prevent bugs:

First for reference, the original VI:

{% include downloadableImage.html path='images/Camera Send Loop.png' alt='original WPI_CameraSend Images To PC Loop.vi' height=529 width=1352 %}

And the modified version we will achieve:

{% include downloadableImage.html path='images/New Camera Send Loop.png' alt='original WPI_CameraSend Images To PC Loop.vi' height=604 width=1828 %}

The list of changes should be easy to follow, but if you are unsure, you can always refer to the snippets above for visual comparisons.

* Add input for second camera Device Reference
* Create an array from the two Device References
* Remove case structure in center of diagram (keeping the True case), you should be left with the while loop containing a single case structure
* Wrap **WPI_CameraSet Frame Rate.vi** through to **WPI_CameraOpenAndSetVideoMode.vi** in a for loop that indexes the array of camera Device References
* In the pre-existing while loop:
	* Open the array up with Index Array
	* Pass the two Device References into a Select with a boolean (easy if using a global variable) that gives T/F for switching cameras and gives output Device Reference to the inner case structure
	* In the inner case structure:
		* Keep the same code but draw a case structure around **Safe Image Get Image.vi**'s "Image Out" output.  This case structure can be used to rotate an image, if necessary, and then pass output to **IMAQ Flatten Image To String.vi** like normal
		
### Some important notes:

* Because only one camera is ever active at a time, this method will still use the same bandwidth as a Robot with only 1 camera attached.
* No changes need to be made to the Dashboard. Simply make sure to change the "Camera Off" Drop down menu to "USB Camera SW".  If you have an active and working camera feed, then when the appropriate trigger is set to switch cameras, the display on the Dashboard will automatically update to reflect the change.


And that is all, you can now easily switch between two camera inputs.  In addition, this method should be extendable to even more cameras, and with more effort possibly IP Cameras as well.

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/1sQwJFJFLU3ba5wuePyZgG3o_NjIneZ9Z5VDUgXnpDS8/viewform?usp=send_form){:target="_blank"}
