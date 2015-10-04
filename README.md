<h1>OpenGL 3D Engine</h1>

<p>A basic 3D engine to render a model into an openGL context. This engine is capable of reading both OBJ files and a plain MODEL file which only contains sets of vertices.</p>

<h2>Libraries:</h2>

<p>This project uses openGl 3.3 along side some other libraries to help create the window and reduce the amount of mathematical work:</p>

<ul>
    <li>Glew - This is the openGL functionality in an extension format. The library can be found <a href="http://glew.sourceforge.net/">here</a>.</li>
    <li>Glfw - This is the window handler for the openGL context. It is used to open a basic window so that the models can be rendered inside. The library can be found <a href="http://www.glfw.org/">here</a>.</li>
    <li>Glm - This is the mathematical library so that we don't have to write classes for vectors and matrices, along with the mathematical operations for them. The library can be found <a href="http://glm.g-truc.net/0.9.7/index.html">here</a>.</li>
</ul>

<p>In order to use the source files and Visual Studio solution, make sure that the libraries are linked correctly.</p>

<h2>Example:</h2>

<h3>Setup steps:</h3>

<p>In order to use an example of the program that is shown in the screenshots below follow these steps:</p>

<ol>
    <li>Download the zip file from the download link</li>
    <li>Unzip the file to any convenient directory</li>
    <li>Locate and open the Debug folder from the main directory</li>
    <li>Run the ALL.exe file (This should open in a fullscreen window)</li>
</ol>

<h3>Controls:</h3>

<ul>
    <li>Camera (Look around) - Mouse movement</li>
    <li>Move forward (In the direction the camera is facing) - 'w' key</li>
    <li>Move backwards - 's' key</li>
    <li>Move left - 'a' key</li>
    <li>Move right - 'd' key</li>
    <li>Menu - 'Esc' key</li>
</ul>

<p>Note: In order to close the program either open the menu and click on the Exit button or press 'Alt' + 'F4'.

<h2>Screenshots:</h2>

<strong>Basic Models:</strong>
![Basic Models](/Screenshots/basic-models.png?raw=true)
<br><br>
<strong>Multiple Models:</strong>
![Multiple Models](/Screenshots/multiple-models.png?raw=true)
