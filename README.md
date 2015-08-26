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
<h2>Screenshots:</h2>
<strong>Basic Models:</strong>
![Basic Models](/screenshots/basic-models.png?raw=true)
<br><br>
<strong>Multiple Models:</strong>
![Multiple Models](/screenshots/multiple-models.png?raw=true)
