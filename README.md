# wxPanGrid
Sample to Pan / manipulate scrollbars in a wxWindow with a mouse click and drag

  This is a sample for how I managed to solve a photoshop sytle pan in a wxWidgets scrolled window. I wanted to be able to click on the grid and drag/pan it in any direction on the users screen, I wanted a 1:1 ratio so if the mouse traveled 20pixels so would the grid. This was particularly challenging because in wxWidgets the scroll bar positions are in logical scroll units, not pixels, and the mouse dragging across the screen would be calculated in pixels. 
  
  ![Animation1](https://user-images.githubusercontent.com/7757495/152697846-0d96c857-f169-4ff2-8325-1c2fb349f8f5.gif)
