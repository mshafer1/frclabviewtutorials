
### Intro

Over the years, several of the mentors and students involved in writing the 
content of this website have found themselves designing a manipulator and trying to 
decide between an encoder and a potentiometer for the feedback in the system.

Several reasons that have been considered for the encoder are:

	- Easier to swap out - since it doesn't matter how the encoder shaft is rotated when it is attached,  just that the manipulator is in a known state (i.e. down) when the robot is turned on.
	- Harder to break - since they have an infinite number of rotations (within the lifespan of the sensor that is . . .)

Several reasons that have been considered for the potentiometer are:

	- It does not matter where it is when the robot is turned on (since the physical setup of the potentiometer always corresponds to the actual)

The purpose of this tutorial is to show how to have the software on the robot allow for a potentiometer to account for this.

Because potentiometers "know" where they are at startup, it doesn't matter where the actuator is, the set points (min, max, and others) are still correct.

### Setup

First, we must setup a potentiometer. 

{% include zoomableImage.html path='images/soldering.jpg' alt='Soldering the potentiometer' scaler='' height=816 width=612 %}

We attached a knob to our potentiometer for testing purposes, 
	but it would likely be attached to a motor or gear shaft in mechanics of the 
	manipulator to be controlled.

{% include zoomableImage.html path='images/knob.jpg' alt='Soldering the potentiometer' scaler='' height=816 width=612 %}

We also need to open the potentiometer in Begin.vi

{% include downloadableImage.html path='images/setup.png' alt='Soldering the potentiometer' height=95 width=146 %}

### Basic Read

We start by putting the logic in Teleop.vi to decide what the target setpoint of a PID is and reading the potentiometer for the process variable.

{% include downloadableImage.html path='images/reading_basic.png' alt='Soldering the potentiometer' height=324 width=657 %}

We can improve this by moving the potentiometer code into a sub-vi.

{% include zoomableImage.html path='images/makeSubVI.png' alt='create sub-VI' scaler='' height=900 width=1024 %}

We will use a while loop to remember whether or not the values have been initialized

{% include zoomableImage.html path='images/while_loop.png' alt='add a while loop' scaler='' height=537 width=777 %}

Add a case structure to the loop and a shift register

{% include zoomableImage.html path='images/shift_register.png' alt='add a shift register to it' scaler='' height=537 width=777 %}

Wire from the inside of the selector terminal to the right shift register (in the True case)

{% include zoomableImage.html path='images/wire_shift_regiser.png' alt='wire the selector to the shift register' scaler='' height=537 width=777 %}

Create a True constant in the False case and connect it to the tunnel. 
This will cause the input of the shift register to default to False, 
but to remember the True after that. 
We can use this to decide when to initialize the values.

We now want to move the GetDevRef VI into the false case.

{% include zoomableImage.html path='images/getDevRef.png' alt='move the get devRef' scaler='' height=537 width=777 %}

We now need to wire the DevRef to the while loop.

{% include zoomableImage.html path='images/wireDevRef.png' alt='Connect it to the While Loop' scaler='' height=537 width=777 %}

And create a shift register for it.

{% include zoomableImage.html path='images/new_shift_register.png' alt='Replace the tunnel with a Shift Register' scaler='' height=537 width=777 %}

Move the Potentiometer Get VI after the case structure the True case and 
	connect it's DevRef terminals to the shift registers and the output to the indicator.

{% include zoomableImage.html path='images/potentiometer_get.png' alt='Connect the get to the shift registers' scaler='' height=537 width=777 %}

Create a constant on the while loop's control terminal and set it to True (to make it run only once).

{% include zoomableImage.html path='images/while_constant.png' alt='Create a constant on the control terminal' scaler='' height=537 width=777 %}

On the output wire, insert a subtract node.

{% include zoomableImage.html path='images/insert_subtraction.png' alt='Insert Subtract node' scaler='' height=537 width=777 %}

And create a constant. This can be used as the expected offset - 
so that when the manipulator is in a known state (i.e. against a hard stop) 
the VI can read 0 (if the known state is with the arm at the top of the potentiometer range,
 make it an add so that the sensor reads 1 at that point). <u>
 If the potentiometer is adjusted, only this constant needs to be changed to keep all 
 the set points the same</u>.

{% include zoomableImage.html path='images/offset_constant.png' alt='Create constant for offset.' scaler='' height=537 width=777 %}

### Reading offset from a file on load

To move the offset value to being stored in a file 
(this will enable use to later update it programmatically, but have it remembered across reboots),
 open a PuTTY session and enter a host name of RoboRIO-XXYY-FRC.local 
 -- where XXYY is your team number, as configured on the RoboRIO -- 
 (if using ethernet, you could also enter the RoboRIO's IP address. 
 Tools like [Advanced IP Scanner](http://www.advanced-ip-scanner.com/) 
 can help you find this if you don't know it.)
 {% include zoomableImage.html path='images/open_putty.png' alt='Open PuTTY' scaler='' height=448 width=466 %}

PuTTY will prompt you for a username and password. This is the same as you use on the web interface (default to admin, blank).

{% include zoomableImage.html path='images/PuTTY_username.png' alt='Enter username (admin)' scaler='' height=117 width=675 %}

Nothing will be displayed (echoed) as you enter the password. To enter a blank password (the default), just press enter.

{% include zoomableImage.html path='images/PuTTY_password.png' alt='Enter password (hit enter for blank)' scaler='' height=424 width=675 %}

If login is successful, a prompt will be displayed (most likely admin@{the host name you used}:~#). 
The first two values tell us what machine we are logged into 
(logged in as admin on roboRIO-3937-FRC in this case).
After the colon, the current file path is displayed 
(~ means home, similar to the user's directory on Windows). Finally, a pound sine indicates the end of the prompt.
 (because the prompt [is configurable in Linux](https://www.cyberciti.biz/tips/howto-linux-unix-bash-shell-setup-prompt.html),
 this can be changed).
 <br/>
We can find the absolute path by entering the command `pwd`.

{% include zoomableImage.html path='images/PuTTY_pwd.png' alt='Enter pwd to find absolute path' scaler='' height=424 width=675 %}

Create a folder to hold any and all settings files.

{% include zoomableImage.html path='images/PuTTY_mkdir.png' alt='Create a directory with mkdir settings' scaler='' height=424 width=675 %}

To see the permissions (who can read or write to files in this directory), enter the command `ls -l` (ListSubdirectory -Longformat)

{% include zoomableImage.html path='images/PuTTY_ls-l.png' alt='List subdirectory in long format (ls -l)' scaler='' height=424 width=675 %}

The `total 0` in the output means that there are no files in the current directory.

The second lines gives us information about the settings directory.

We gather from this that the directory (by default) can be [R]ead from, [W]ritten to, and e[X]ecuted 
(or rather, the programs in side it can be) by the owner (who is admin).
<br/>
Only read and executed by other members of the group, and the world.


So that we don't have to care what user our LabVIEW program is executing as, 
we will change the permissions so that anyone can read or write to the this directory 
by running the command `chmod 777 settings` (this will also make it executable, 
to remove that access for the group and world, use 766).
{% include zoomableImage.html path='images/PuTTY_chmod.png' alt='use the chmod command to change the access permissions' scaler='' height=424 width=675 %}

If you run `ls -l` now, 
you will see that the dashes have been replaced with w's - signifying that the write permission is now granted.

You can use a text editor like [vi](http://www.howtogeek.com/102468/a-beginners-guide-to-editing-text-files-with-vi/) to create the file, but we will show how to have 
LabVIEW create it with a default value (this allows for less setup when moving between controllers).

<p>First, move the offset constant into the False case of the Case Structure and reconnect it to the subtraction node. Then, also connect it to the while loop and create a shift register.

{% include zoomableImage.html path='images/moving_const.png' alt='move the constant inside the False case.' scaler='' height=537 width=777 %}

Connect the left shift register to the tunnel in the True case to make this value remembered after the initialization.

{% include zoomableImage.html path='images/remember_offset.png' alt='Connect the shift register in the True case.' scaler='' height=537 width=777 %}

In the False case, you can press the Control key while clicking and moving the mouse to create some more space.

{% include zoomableImage.html path='images/create_space.png' alt='Click and control drag to expand the diagram.' scaler='' height=537 width=777 %}

Get an Open/Create/... VI from the File I/O palette.

{% include zoomableImage.html path='images/open_file.png' alt='Get an Open File VI.' scaler='' height=537 width=777 %}

Right click on the "file path" terminal

{% include zoomableImage.html path='images/select_path_terminal.png' alt='Right click on path terminal' scaler='' height=537 width=777 %}

and create a constant.

{% include zoomableImage.html path='images/path_constant.png' alt='Create a constant' scaler='' height=537 width=777 %}

Also create a constant for the operation terminal and set it to open.

{% include zoomableImage.html path='images/operation_open.png' alt='Create an Open constant for the operation' scaler='' height=537 width=777 %}

Finally, set the access terminal to read only

{% include zoomableImage.html path='images/access_read.png' alt='Create a Read-only constant for the access' scaler='' height=537 width=777 %}

If we highlight the VI and it's constants, we can use the diagram cleanup button to cleanup just the selection.

{% include zoomableImage.html path='images/cleanup_selection.png' alt='Cleanup the selection' scaler='' height=537 width=777 %}

We'll need to create some more space to handle if the file does not exist yet.

{% include zoomableImage.html path='images/create_space_2.png' alt='Click and control drag to expand the diagram.' scaler='' height=403 width=583 %}

We then add a Case Structure and connect the File Open's error out terminal to it.

{% include zoomableImage.html path='images/case_structure.png' alt='Click and control drag to expand the diagram.' scaler='' height=537 width=777 %}

 In the No Error case, we add a Read Text File VI (we set it to read 1 character, but later changed our minds on that.)

{% include zoomableImage.html path='images/read_file_1.png' alt='Create a read Text File in the No Error Case.' scaler='' height=696 width=844 %}

From the String Palette -> Number/String Conversion, we get the Frac/Exp String to Number VI (this allows for decimal values).

{% include zoomableImage.html path='images/get_converter.png' alt='Get a Frc/Exp String to Number VI' scaler='' height=792 width=1176 %}

We place this after the case structure and wire the output from the read to it.

{% include zoomableImage.html path='images/convert_file.png' alt='Use it to convert the file' scaler='' height=489 width=974 %}

And use the number it returns as the default value.

{% include zoomableImage.html path='images/use_as_default.png' alt='Number becomes the default' scaler='' height=489 width=974 %}

In the Error case (this will be triggered if the file does not exist yet), we use another File Open VI, but set this one to Create Mode and Write-Only access.

{% include zoomableImage.html path='images/open_write.png' alt='Create the file in the error case' scaler='' height=489 width=974 %}

We add a Write Text File VI and connect it to the Open VI. We then create a constant for the text to write
that we will set to the desired default value.

{% include zoomableImage.html path='images/write_file.png' alt='Create the file in the error case' scaler='' height=489 width=974 %}

Now close the file.

{% include zoomableImage.html path='images/close_file_creation.png' alt='Create the file in the error case' scaler='' height=489 width=974 %}

We then re-open the file with read access.

{% include zoomableImage.html path='images/open_read.png' alt='Re-open the file with read access.' scaler='' height=489 width=974 %}

At this point, we realized we wanted to read the file in either case, 
so we move it to being after the Case Structure and rewire the error and refnum values through the No Error case.

{% include zoomableImage.html path='images/move_read.png' alt='Move the read after the case structure' scaler='' height=489 width=974 %}

We then wire the refnum from re-opening the file in the error case to the read VI via the tunnel.

{% include zoomableImage.html path='images/re-open_and_read.png' alt='Move the read after the case structure' scaler='' height=489 width=974 %}

We also connect the error wire to the read, and the output of the read to the convert VI and cleanup the diagram.

{% include zoomableImage.html path='images/cleanup_diagram.png' alt='Move the read after the case structure' scaler='' height=489 width=974 %}

### Programmatically updating configuration file

To allow us to programmatically update the file (and zero point)
 we insert a Compound Arithmetic into the wire control the main case structure.

{% include zoomableImage.html path='images/insert_compound.png' alt='Insert compound arithmetic' scaler='' height=694 width=974 %}

First, we invert the input that is not used

{% include zoomableImage.html path='images/invert_input.png' alt='Invert unused input' scaler='' height=694 width=974 %}

Then, we change the mode to And

{% include zoomableImage.html path='images/change_mode.png' alt='Invert unused input' scaler='' height=694 width=974 %}

Finally, we create a control on the inverted input. And name it Set.

{% include zoomableImage.html path='images/create_control.png' alt='Create a control on the inverted input' scaler='' height=694 width=974 %}

We now add a case structure inside the false case, around the logic to read the file.

{% include zoomableImage.html path='images/add_case_structure.png' alt='Add another case structure' scaler='' height=694 width=974 %}

Move the convert inside the new structure and reconnect it.

{% include zoomableImage.html path='images/move_convert.png' alt='Move the convert inside' scaler='' height=694 width=974 %}

Connect the Set control to the new case structures control terminal.

{% include zoomableImage.html path='images/connect_set.png' alt='Connect the set control' scaler='' height=694 width=974 %}

Swap the case structure's False case.

{% include zoomableImage.html path='images/change_to_false_case.png' alt='Change the case structure to being the false case.' scaler='' height=694 width=974 %}

Move the path constant outside the case structures and reconnect it.

{% include zoomableImage.html path='images/move_path.png' alt='Move the path constant.' scaler='' height=694 width=974 %}

In the outer False Case, inner True case, add an Open File VI set to replace or create and write only

Add a Write Text File VI.

From the String Palette, get a Number to Fractional String VI

Connect it to the write and create a control for the zero point.

Wire the path constant to the Open VI

{% include zoomableImage.html path='images/setup_replace.png' alt='Create control for zero point.' scaler='' height=694 width=974 %}

Wire the zero point to the tunnel so that it can start being used.

{% include zoomableImage.html path='images/wire_zero_point.png' alt='Connect the zero point to the tunel.' scaler='' height=694 width=974 %}

At this point, we we add some comments, and do a diagram cleanup.

{% include downloadableImage.html path='images/finished.png' alt='Finished VI.' height=407 width=1637 %}

### Summary

This method allows a potentiometer's read to be quickly adjusted 
- removing the disadvantage of having to get the shaft just right when making adjustments, 
but keeping the advantage of a known position at startup (without always starting in the same spot).


**Always make sure the manipulator is not going to move based on an old config!** 
If this is in Periodic tasks, the code will run and can have the set point update without enabling 
the robot; however, if this is implemented in Teleop, <u>pull the breakers to the actuator **before**
 enabling to call the set</u>

### Possible Improvements

	- Change the create file case to make the necessary system execution calls to create the directory
	- Customize the dashboard to have a button for the set position

### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/e/1FAIpQLSeFfwmdTzcfjmf0jIidE-USjnL4z8DJTGH18JgZJCPMjnrEFw/viewform)
