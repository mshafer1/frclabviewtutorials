---
layout: basic
title: Memory Libray
---

### What is this

The memory library is a VI package of low level Boolean memory vi's that are built to allow for better code re-usability.

### Why is this published

Pursuant with FRC Rule R13, FRC Team# 3937 has chosen this as their outlet to release code that is intended for reuse.

### Detailed descriptions

Below is an inclusive list of the vi's included in the library and their function. All vi's are configured so <u>each instance</u> has its own memory (if used multiple times, each time is completely independent of the others).
<br/>

* Edge Detector**
	<br/>
	This vi can be used to detect the first time a signal becomes true, or false, or both. Its primary use is in conjunction with a joystick button and can be used to trigger an event on when the button is first pressed or similar using another mode.

* SR Flip Flop
	<br/>
	This vi implements a software version of the hardware [JK Latch](https://en.wikipedia.org/wiki/Flip-flop_(electronics)#JK_latch){:target="_blank"} with an enable bit.
	<br/>
	In short,

	|Summary of SR Flip Flop Operation|
	| Set 	 |	Reset	|	Enable	| Output |
	| ---	 |	---		|	---		|	---	 |
	| False  | 	False 	|	Either	| Previous Value (defaults to false, memory is retained) |
	| Either | 	Either 	|	False	| Previous Value (defaults to false, memory is retained) |
	| True 	 | 	False 	|	True	| True |
	| False  | 	True 	|	True	| False |
	| True	 |  True	|	True	| The opposite of the previous value |
			

### Example Usages

Once Per Press:
{% include downloadableImage.html path='images/risingEdge.png' alt='Rising edge example' height=126 width=378 %}

{% include downloadableImage.html path='images/fallingEdge.png' alt='Falling edge example' height=126 width=378 %}

{% include downloadableImage.html path='images/buttonOnDifferentButtonOff.png' alt='SR separate' height=150 width=457 %}

{% include downloadableImage.html path='images/buttonOnButtonOff.png' alt='Rising edge example' height=132 width=671 %}

### Download


<a href="files/memory_library-1.0.1.2.vip" download>Click here</a> to download the latest version (we recommend uninstalling older versions before installing updates).
<br/> 
[VI Package Manager](http://www.ni.com/tutorial/12397/en/) required (likely already installed){:target="_blank"}.
    


**Changelog**
* <a href="files/memory_library-1.0.0.1.vip" download>1.0.0.1</a> - initial release (2015)
* <a href="files/memory_library-1.0.1.2.vip" download>1.0.1.2</a> - update context help on VIs (2018)
