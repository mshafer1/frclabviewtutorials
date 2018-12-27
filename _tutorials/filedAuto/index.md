---
layout: basic
title: File-based Auto
---

### Clarification

What is presented below is a method for defining the autonomous period of the robot in XML that is stored on the roboRIO. The XML file should be included in your version control as it is part of your source. However, because it does not need to be compiled, can be modified between runs without redeploying all of the code. This works well when coupled with the types of architecture laid out in the [Autonomous](/tutorials/autonomous/) tutorial with the results from the XML file taking the place of the controls.

### Setup

In the project explorer (the window that opens after you finish going through the create project dialogue), right click on **Target (roboRIO-XXYY-frc.local)** and select New -> Control


{% include zoomableImage.html path='images/newControl.png' alt='Create a new control to define auto moves' scaler='' height=561 width=392 %}

We will use this control to define what an auto move looks like (i.e. how far to move, what direction to turn, whether or not the claw is open, what angle the arm should be at, etc.), but controls are only allowed to have one item in them, so we first add a cluster control.


{% include zoomableImage.html path='images/addCluster.png' alt='Create a new control cluster to hold definition' scaler='' height=503 width=785 %}


We then add controls to it for each of the parameters that we want to use to define the movement (in this example, we will specify how far in feet -the auto code will translate that to encoder clicks, what direction in degrees, the minimum number of seconds, and whether or not the  claw should be open - boolean.)

{% include zoomableImage.html path='images/addControls.png' alt='Add controls to cluster' scaler='' height=503 width=785 %}

We can set the cluster to arrange them horizontally or vertically, because this definition will be used to display them in the editor and we want it to be a series of steps from left to right, we will choose to 'array vertically'


{% include zoomableImage.html path='images/arrangeVertically.png' alt='Arrange cluster vertically' scaler='' height=503 width=785 %}

So we can easily add or remove items from this later, we will set this as a type def (see also [TypeDef tutorial](/tutorials/type-def) for more info on why TypeDef's should be used often)


{% include zoomableImage.html path='images/makeTypeDef.png' alt='Make TypeDef' scaler='' height=503 width=785 %}

Save the control


### Getting the editing tool


<a href="files/files/autoProfiling.zip" download>Download autoProfiling.zip</a>



Extract the files to where you want to store them. This should be with the rest of your source because EditMoves.vi uses its location to determine where to store the xml file (which you should include in your source control) and where to get the FTP (File Transfer Protocol) program it uses (WinSCP).


{% include zoomableImage.html path='images/extractZip.png' alt='Extract the tool to your source location' scaler='' height=434 width=648 %}


Back in the project explorer, expand and then right click on "My Computer" and select "Add" -> "File . . ."
<br/>
This will open a file dialogue. Use it to select the EditMoves.vi that you just extracted.


{% include zoomableImage.html path='images/openEditMoves.png' alt='Select EditMoves.vi' scaler='' height=480 width=683 %}


By putting this vi under "My Computer", you are telling LabVIEW that you want this vi to run locally.


EditMoves.vi is a utility VI that allows for you to put in your own definition of what an autonomous move looks like and build an array of such moves for an auton program. EditMoves will extract xml from the array and store it locally (when save is hit) and put it on the robot for recallMovesOnRobot.vi to load when your autonomous code calls it.


Also add recallMovesOnRobot.vi under the Target (maybe even under "Support Code" or under "Team Code" - it's up to you).

{% include zoomableImage.html path='images/add_recallMovesOnRobot.png' alt='Add recallMoves.vi' scaler='' height=768 width=1366 %}

### Configure tool VIs for your auto


Open EditMoves.vi and put the typedef (that defines an auto move) into the array control


{% include zoomableImage.html path='images/editMovesSetTypeDef.png' alt='put typedef in edit moves' scaler='' height=768 width=1366 %}


Set your team number in the numeric control (this is used for determining the IP address of the rio to send the xml file to).



Go to "Edit" -> "Make Current Value Default" to store these settings (team number in particular).
<br/>
Save the vi.



Open recallMovesOnRobot.vi and add your typedef to this array as well.
	


{% include zoomableImage.html path='images/loadMovesSetTypeDef.png' alt='put typedef in load moves' scaler='' height=768 width=1366 %}


(likely this will still result in a broken VI - right click on the vi and select "change to indicator to fix" if it is broken)


{% include zoomableImage.html path='images/setIndicator.png' alt='set array as indicator again' scaler='' height=724 width=917 %}


Save the vi.


### Final settings and first test


The roboRIO has a unique ssh key that WinSCP (the FTP client that EditMoves uses) will want to store before allowing for automatic transfer.
<br/>
Under the "upload tool" folder we extracted earlier, open WinSCP\WinSCP-5.11.3-Portable\WinSCP.exe


{% include zoomableImage.html path='images/openWinSCP.png' alt='Open WinSCP to store ssh key' scaler='' height=434 width=648 %}


Put "roborio-XXYY-frc.local" (where XXYY is your team number) in the host name.
<br/>
Put "lvuser" (the user that the program runs as) in the user name (there is no password on this account).
<br/>
And press Login


{% include zoomableImage.html path='images/WinSCPlogin.png' alt='WinSCP login to roborio' scaler='' height=430 width=640 %}


When the warning that WinSCP does not recognize the SSH key from the host (unknown host) pops up, select yes (this will continue with the connection and store the SSH key for future connections).


{% include zoomableImage.html path='images/WinSCPwarning.png' alt='WinSCP login to roborio' scaler='' height=286 width=476 %}


Once connected, right click and select "New" -> "Directory".


{% include zoomableImage.html path='images/WinSCPnewDir.png' alt='WinSCP new directory' scaler='' height=688 width=961 %}


Name it "config" (case sensitive - without the quotes). This is where the xml file will be stored.


{% include zoomableImage.html path='images/WinSCPconfig.png' alt='WinSCP name the folder ' scaler='config' height=291 width=353 %}


Back in EditMoves.vi, run the vi and set some moves. In our example, we'll configure the robot to go forward 10 feet, turn right 90&deg;, and open the arm (for 1 second).


{% include zoomableImage.html path='images/editMoves.png' alt='Configure the movements' scaler='' height=724 width=681 %}


When we press "Save and send to robot", the array of movements is parsed to xml, stored locally, and copied to the config folder on the roborio. To see the file on the roborio, go back to WinSCP (you may need to refresh it to see the file).


{% include zoomableImage.html path='images/WinSCPconfirmFile.png' alt='Confirm the file is there' scaler='' height=630 width=961 %}


Lastly, we check that we are successfully able to have the robot read it back out of the file.
<br/>
Go back to recallMovesOnRobot.vi and run it (since it is under the Target in the project, it will deploy and run on the roborio)
<br/>
If everything worked, you will see the same moves you just stored in EditMoves.vi read back out.


{% include zoomableImage.html path='images/recallMovesWorking.png' alt='Confirm recalling movements is working' scaler='' height=724 width=917 %}

### Some possible improvements

* Add multiple option support by
	* Changing roboRIO file path to a control in both the editor and the loader (pass it in from dashboard to select an auto file) -- OR --
	* Changing the data type to an array of arrays of movements and use dashboard to select which array of movements to use
		
### If this tutorial inadvertently leaves some details out, please tell us about it and we will update it.

[Google Form to request details](https://docs.google.com/forms/d/e/1FAIpQLSeLtDSjCaUwpZxXjxakH__im3VBRPbOiAhKlZXcwuE78g5HLg/viewform?usp=sf_link){:target="_blank"}
