---
layout: basic
title: Auto Selecting
---

### Adding options to the defualt autonomous

The default dashboard uses a variable that is set in the Begin VI to decide what options to display, so we'll start by adding options to the default there.

{% include zoomableImage.html path='images/editingAutoList.png' alt='The auto list on the dashboard is set in Begin.vi' scaler='' height=859 width=1438 %}

If you deploy this code and open connect the dashboard, you can click the drop down to see the updated options list.

It is also possible to **type** the desired option - but when doing this (with the default dashboard) you have to click out of the box to apply the value

### Adding options to auto code


Right click on the case structure in Autonomous


{% include zoomableImage.html path='images/addingOptionsToAuto.png' alt='Right click the case structure' scaler='' height=1009 width=1678 %}


You see all of the cases that are currently there. You also have the option to delete the case that is shown when you right click.



Delete all cases you don't plan to use (keep anything you are planning to copy and paste later)



Add a case for every value that you would like to select (I encourage you to keep the blank, default case) and edit the code.
<br/>
You can change the label by double clicking and editing between the quote marks.


{% include zoomableImage.html path='images/forward.png' alt='Editing case values by double clicking header and changing string' scaler='' height=1009 width=1678 %}

While this does allow for as many options as you desire, you have to type out the names for them multiple times (in auto and either in the Begin so they show in the list, or when you use them).


### Creating an Enum

We first change the Dashboard Read to reading a number

{% include zoomableImage.html path='images/dashboardReadNunber.png' alt='Change dashboard read to number' scaler='1.5' height=1009 width=1678 %}

We then create an enum (from the numerics palette) and make it a [Type Def](/type-def)

{% include zoomableImage.html path='images/makeTypeDef.png' alt='Make an enum and create a Tpe Def from it' scaler='1.5' height=1009 width=1678 %}

Once opened, we can edit the items and add all the options we desire.

Once that is finished, we Apply Changes (under File) and Save it (save it somewhere easily accessible - like the desktop)

Back in Autonomous, use a Type Cast vi (use quick search - hit ctrl + space - or find it under the Numeric -> Data Manipulation pallette) to convert the number that is read to the enum

{% include zoomableImage.html path='images/typeCast.png' alt='Make an enum and create a Tpe Def from it' scaler='1.5' height=1009 width=1678 %}

You can right click and select "Add case for every value" to populate the entire list

{% include zoomableImage.html path='images/addCaseForEveryValue.png' alt='Right click and select add case for every value' scaler='' height=805 width=1329 %}

### Customizing dashboard

To use this value (or rather - have it sent . . .), we need to create a custom dashboard (more details on setting this up under our [gyro](/gyro/) tutorial).

We replace the default combo box with our enum by selecting "choose a control" and navigating to where we saved it.

{% include zoomableImage.html path='images/replaceComboBox.png' alt='Replace the combobox with our enum' scaler='1.5' height=1009 width=1678 %}

This will break the dashboard because the are several vi's on the block diagram expecting a string, so we will go update those now.

First, we replace the Write String with a NT Write Number

{% include zoomableImage.html path='images/writeNumber.png' alt='Replace the write string with Write Number' scaler='' height=1009 width=1678 %}

We also remove the code that updated the options (since we now know these from the enum)

{% include zoomableImage.html path='images/removeOptionsSetter.png' alt='Remove the code to update the options' scaler='' height=1009 width=1678 %}

And change the "Select Auto"; Value Change case to writing a number (this is the case that sends the update whenever you change it)

{% include zoomableImage.html path='images/updateSetValue.png' alt='Update the set value to set a number' scaler='' height=1009 width=1678 %}

Now all you need to do to add or remove (or rename) auto modes is open the type def and change it's items, then rebuild both the dashboard and the robot project.

#### Some things to consider for improvement

1. Build the dashboard and copy it over the default one so (in Program Files) so when Driver station opens it will use your updated version (otherwise you need to have your updated version running first)

2. Extending the array of movements (provided in the default auto) to include manipulator movements

3. Use encoders and/or a gyro for more accurate movements (than time will consistently produce).

#### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/e/1FAIpQLSfiym4KdDe-SOvNmLLPcQIK47748i-zQprWFll1v58B0t5Rag/viewform?usp=sf_link)
