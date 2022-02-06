# wxPanGrid
Sample to Pan / manipulate scrollbars in a wxWindow with a mouse click and drag

  This is a sample for how I managed to solve a photoshop sytle pan in a wxWidgets scrolled window. I wanted to be able to click on the grid and drag/pan it in any direction on the users screen, I wanted a 1:1 ratio so if the mouse traveled 20pixels so would the grid. This was particularly challenging because in wxWidgets the scroll bar positions are in logical scroll units, not pixels, and the mouse dragging across the screen would be calculated in pixels. 
  
This also includes code for drawing a grid with their device context.
  
## Example
![Animation1](https://user-images.githubusercontent.com/7757495/152697846-0d96c857-f169-4ff2-8325-1c2fb349f8f5.gif)

## Windows building
1. Requires [wxWidgets](https://www.wxwidgets.org/downloads/) GUI library. You will probably need to download and build the library from source. I used wxWidgets-3.1.5 for wxPanGrid.

2. Make sure the compiler knows where to look for the header file(s) for the library. Open the .sln and navigate to **Project > Properties > Configuration Properties > C/C++ > General**. Then under **Additional Include Directories** add the location for the header files:
    -  `...\wxWidgets-3.1.5\include`
    -  `...\wxWidgets-3.1.5\include\msvc`

3. Tell the linker where to look for the library file(s). Open the .sln and navigate to **Project > Properties > Configuration Properties > Linker > General**. Then under **Additional Library Directories** add path for library files. 
    - `...\wxWidgets-3.1.5\lib\vc_lib`

