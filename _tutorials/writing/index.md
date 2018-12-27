
### Thank you

First, let me (mshafer1 - site Curator) say "Thank you." for being willing to share your knowledge with the rest of the FRC community.
I am posting this article for new writers to have an easy reference on how to format their pages and submit them.

### Creating the html file

One can use 
[Notepad++](https://notepad-plus-plus.org/) or 
[Visual Studio Code](https://code.visualstudio.com/)
 to create a basic html file (and open it in any web browser to check it).
<br/>
 Another option is to use an online html editor like [this free one](http://www.html.am/html-editors/online-html-editor.cfm) and download the resulting source (If using this method, please adjust the image and file links before sending it to me - see section below.)


### Formatting Specs


	<ul>
		<li>
			<p>Please put a written by [Team Number] with a logo or something on the bottom.

		<li>
			Please put a written by [Team Number] with a logo or something on the bottom.
		</li>
		<li>
			<p>Header 1 and 2 are used in the setup for the page, <br/>
			so use Header 3 and smaller for section labels within the document.<br/> (I will replace these with PHP function calls that generate the table of contents).</p>
		</li>
		<li>
			Don't worry about the exact path to the css file or the menu or other header items - when I move it into a php script (like the rest of the site), the header I have built will take care of those things.
		</li>
		<li>
			To keep architecture consistent, please put any and all images in a folder named images next to your html file (i.e. paths should look like src="images/example.jpeg"), and downloadable files should be linked with href="files/example.vi" (which means that any attached vi's and the like should be put in a folder named files next to the html file). You will need to zip and include these files in your email to me.
		</li>
	
### Couple of final notes

If you want to see what the page will look like once it it styled,
 you can copy the contents of the css file (it's a text file that can be opened in notepad[++]) into the &lt;head&gt;...&lt;/head&gt; section in between &lt;style&gt; and &lt;/style&gt; tags to see what result will look like;
 or, place this: <br/>
<code>
&lt;link rel="stylesheet" type="text/css" href="http://frclabviewtutorials.com/css/styles.css"&gt;
</code>
<br/>
in the head section of your document to load the style sheet dynamically



Email me your drafts for review at [admin@frclabviewtutorials.com](mailto:admin@frclabviewtutorials.com). Once I have what I need to format your page, I will post it for peer review to the admin group.

