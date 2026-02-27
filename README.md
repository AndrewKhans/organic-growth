# organic-growth
A game made in C with Raylib

## Compile
cc main.c -o game \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lraylib \
  -framework OpenGL \
  -framework Cocoa \
  -framework IOKit \
  -framework CoreVideo

## What does it have?
1. 2D Physics
2. Evolving
3. Plants
4. Silliness


- A map you can navigate
- A procedural adventure where you are on an oragnic ship that grows and mutates like a plant, with a strange algorithm
- you tend to it and chop off pieces so it grows in a desirable shape
- you place goods on it and they fit on it nicely since they fall downwards. you also might want to hollow out an inside so that you can store stuff inside. then the ship grows to fill its insides
- flowers grow on the edges and top, more flowers bring you more speed. flowers are very random in shape and color
    - the shapes can look totally fucked, barely even flower-like


