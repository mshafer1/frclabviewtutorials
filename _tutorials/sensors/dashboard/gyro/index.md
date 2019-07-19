---
layout: basic
title: Gyro - Dashboard
---

### To Display a Gyro on the Dashboard

The default dashboard does not read anything, so the first step is to add a read into the dashboard code. To do this, open an FRC Dashboard Project.

{% include zoomableImage.html path='images/createDashboardProject.png' alt='open dashboard project' height=957 width=1116 %}

Open Dashboard Main.vi. If you right click on the Gyro indicator and select find terminal, LabVIEW will point you here.

{% include zoomableImage.html path='images/gyroterminal.png' alt='Gyro indicator in block diagram' height=654 width=1516 %}

<img alt="" src="examples\gyro\gyroterminal.png" style="width: 601px; height: 259px;" />

Notice that there is nothing wired into it. To adjust this, use a dashboard read to get the gyro value that you will now send from either Teleop or timed tasks.

It should look something like this.

{% include downloadableImage.html path='images/gyroRead.png' alt='Using a dashboard read to set the indicator' height=107 width=336 %}

[<img alt="" src="examples\gyro\gyroRead.png" style="width: 336px; height: 107px;" />](https://docs.google.com/uc?export=download&id=0BwEBnEBtHotGUmhKLV8zZ0dZYkU)

Save the vi, and build the executable in the project. When the build is complete, explore the build and note where it is (personally I put a shortcut to it on the desktop). Once that is complete, close out of that project and open your robot project.

At this point, you need to decide whether to put the update code in Teleop or timed tasks, personally I prefer to put it in Periodic Tasks, but some might say to put everything in Teleop and get rid of all the other parallel loops in the architecture. For this example, I will put it in Periodic Tasks, but to put it in Teleop only requires taking what is inside the loop presented here and putting it in Teleop.

To read the gyro and send it to the dashboard, could look something like this (notice: constantly doing the DevRef get is time consuming, consider putting that outside the loop and passing the resulting DevRef into the loop)

{% include downloadableImage.html path='images/gyroLoop.png' alt='reading the gyro' height=244 width=408 %}

[<img alt="" src="examples\gyro\gyroLoop.png" style="width: 250px; height: 199px;" />](https://docs.google.com/uc?export=download&id=0BwEBnEBtHotGVEplV3hVM2dXWVk)

Finally, the gyro does need to be wired (There are plenty of documentation on that, like [this one](http://team358.org/files/programming/ControlSystem2015-2019/#gyro)) and opened in the begin.vi like so.

{% include downloadableImage.html path='images/gyroOpen.png' alt='opening the gyro in begin.vi' height=105 width=208 %}

[<img alt="" src="examples\gyro\gyroOpen.png" style="width: 208px; height: 105px;" />](https://docs.google.com/uc?export=download&id=0BwEBnEBtHotGUWdmOE5zcXFHRms)

### To use the dashboard you just created

Easiest way, open it, then open the Driver Station. The DS should recognize that a dashboard is already open and just work with it.

#### Some things to consider for improvement

1. Inserting a division with remainder in between the gyro read and dashboard write so that it is divided by 360 and the remainder is written (this will make the gyro display on the dashboard always point the correct direction).

2. Also writing the value to a global variable to be read in Teleop or Autonomous and used.

#### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/a/harding.edu/forms/d/1CVKshcWipp6sm_QeKU9u_3dJnu0uTtFmsTgOA1soPP0/viewform?usp=send_form){:target="_blank"}
