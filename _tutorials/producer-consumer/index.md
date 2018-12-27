
### What is it?

The producer consumer is a <a href="http://www.ni.com/white-paper/3023/en/" target="_blank">
	standard LabVIEW architecture</a> which allows for the separation of the code that is creating data or instruction from the code that is logging that data or putting those instructions to action.

Its primary use is for large scale applications where recording every bit of data is important, but in FRC we often times care more about the most current data or instructions, so while a true producer consumer is implemented using a queue, it is advisable to use an fgv or global variable.

### Why use this architecture?


		One reason to use this is to separate the code that is deciding what needs to be done (reading the joysticks) and implementing (setting the actuators).
		<br/>
		**Why not put it all in one place?**
		<br/>
		The more code there is in a single vi, the harder it is to maintain (correct an issue, update, or add to).
		<br/>
		**Don't parallel loops cause lag?**
		They can, if not implemented correctly. It is worth noting that the standard architecture utilizes several parallel loops. (The main loop running Teleop, the loop in the vision code, the loops in periodic tasks, ... etc.).
		To avoid having one loop hog the cpu, put a wait in it (wait (ms).vi). Even a wait of 0 milliseconds will free the cpu to perform other tasks (like running other loops).
	

### Example


		For this example, we will implement a robot that has a linear actuator using a PID and encoder.
	

#### Begin.vi


		Initializing the necessary items.
		<ul>
			- Joysticks
			- Motor - the linear actuator
			- Encoder
		</ul>
	

{% include downloadableImage.html path='images/init.png' alt='Setting things up' height=430 width=304 %}

#### Teleop.vi


		Here, the joystick is read, and depending on which button is pushed (if any), the value in the global variable is updated.
	

{% include downloadableImage.html path='images/selectState.png' alt='Reading joystick to set the state the elevator should be in' height=186 width=544 %}

#### Periodic Tasks


		Here the state is read from the global variable and used to create an encoder set point. Based on that set point and what the encoder currently reads, the motor is set.
	

{% include zoomableImage.html path='images/timedTasks.png' alt='Updating the motor in timed tasks' scaler='' height=725 width=1360 %}

### Summary


		This tutorial shows how just a little bit of separating code can make all of the pieces seem simpler and much easier to understand. Also, if the actuator needed to go through sequences, it could do so without affecting how often the joysticks values are read or affecting the drive loop. For an additional architecture to consider for sequences, look at our [state machine tutorial](/state-machine/). These two pieces work well together, allowing the driver to update the instructions at any instant, and when the sequence is ready, it can check for the latest update in the variable.
	

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/1Ss-2aGj6CvNpmaQoAonbolDKR5M341OyFYC3bJ5d5jo/viewform?usp=send_form)
