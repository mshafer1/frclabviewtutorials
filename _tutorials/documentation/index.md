---
layout: basic
title: Documentation
---

### Purpose

The purpose of documentation is twofold:
1. Others can look at your code and know what you are doing (ranging from mentors, to the next primary programmer, to someone you're trying to help)
1. You can remember what that piece does (or which loop was the ___ in?)


Documentation is very important, and with a few built in tools, your LabVIEW code can be much easier to read.

### Simplest - comments

These allow you to put text anywhere in the code to explain what is going on. They can be used to label which motor is which, etc., but it is better to use labels for that.

{% include zoomableImage.html path='images/comments.png' alt='Adding a comment' height=302 width=300 %}

### Hidden, but useful - labels

Labels are on everything in LabVIEW and (with a few exceptions) you can change them to say what you want. Use them to name your controls and indicators to what they actually represent.

{% include zoomableImage.html path='images/controlLabel.png' alt='Using labels to document controls and indicators' height=355 width=292 %}

You can also use them to help keep track of which wire is which.

{% include zoomableImage.html path='images/wireLabel.png' alt='Using labels to document wires' height=516 width=906 %}

### Harder to find, but extremely useful - Subdiagram labels

Some items in LabVIEW have subdiagram labels (case structures, loops, etc.) - allowing you to put a nice looking comment inside them. 
{% include zoomableImage.html path='images/subLabels.png' alt='Adding a sublabel to a while loop' height=757 width=906 %}

### If uncertain how or when to use one of these, or would like to suggest another option, please fill out this form.

[Google Form](https://docs.google.com/forms/d/1aP5jeNJFZRcKiqmr3Z6ehcJrC1ZHHpNzLFEKMgkqdqs/viewform?usp=send_form){:target="_blank"}
