---
layout: basic
title: Using an Enum for the autonomous multi-select
description: The built-in selector setup uses case-sensitive, space-conscience strings. Yuck. Here's how to use a type-def'd enum to populate the strings, and the case structure.
---

### Background

With the default code, there is a Dashboard Write in begin that takes an array of strings:

{% include downloadableImage.html path='images/initial_begin_setup.png' alt='default strings sent to dashboard' %}

This is then read back in the beginning of the provided auto-code template for a case structure.

{% include downloadableImage.html path='images/initial_auto_setup.png' alt='default strings read from dashboard into case structure' width=700 %}

These strings are case-sensitive, space-conscience strings - requiring you to type the **exact** same value into the string array in Begin and into the case structure in Auto. Yuck.

### Let's use an enum

For the sake of simplicity, let's use a typedef'd enum to provide the strings to the dashboard and to populate our case structure.

In Begin.vi, create an enum **control** (we need to access the strings from the enum via properties, which are not available on a constant).

{% include zoomableImage.html path='images/create_enum.png' alt='Create an enum in begin.vi' width=100 scaler=.5 %}
<br/>
{% include zoomableImage.html path='images/make_control.png' alt='Change it to an enum control' height=400 %}

Right click on the control, and select:
    Create -> Property Node -> Strings[]

{% include zoomableImage.html path='images/create_strings_property.png' alt='Create an enum in begin.vi' width=100 scaler=.5 %}

Then, connect the strings array to the dashboard.

{% include downloadableImage.html path='images/use_enum_to_populate.png' alt='Use the enum strings to populate the dashboard' %}

We may want to update the values later (either adding, or substituting), so let's take a moment to make this enum a TypeDef ([docs here](/tutorials/type-def/))

### Back in Auto

The value coming back from the dashboard is still a string, but we can convert it to the enum.

Place a copy of the typedef'd enum on the diagram connected to a "Scan from String" as the default value.

{% include downloadableImage.html path='images/cast_back_to_enum.png' alt='Use the enum as the default value into the ScanFromString' %}

The "Scan from String" will identify the value of the enum that matches the passed string (while one can do this with arbitrary strings, it is best to do it only when the strings are guaranteed to be equivalent to one of the enum value names).

Connect the output from the "Scan from String" to a new case structure.


{% include downloadableImage.html path='images/connect_to_case_structure.png' alt='Connect to a new case structure' %}

Open the typedef and provide the desired possible modes (make sure to include a do-nothing).

{% include zoomableImage.html path='images/set_enum_options.png' alt='Set the typedef to the desired values' height=400 %}
<br/>
Apply changes:

{% include zoomableImage.html path='images/apply_changes.png' alt='Apply the changes' height=400 %}

(save and close the TypeDef)

Right click on the case structure, and select "Add case for every value"

{% include zoomableImage.html path='images/make_case_for_every_value.png' alt='Change it to an enum control' %}

### Conclusion

You now have an enum that (if edited) will update both in Begin - where it's strings are sent to the dashboard to select an auto, and in auto - where it is used to parse the returned string and manage possible case structure values.

### Possible Improvements

* Handling errors (indicated on the error-out of the Scan From String) if the driver decides to type a value in.
* See also [autonomous](/tutorials/autonomous/)

