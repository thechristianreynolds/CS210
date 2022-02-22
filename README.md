# Corner Grocer Shopping Cart Application

### Project Summary
This application combines C++ and Python. It uses C++ to get user input from the keyboard and Python to get cart items from a text file. It allows the user to view the quantity of each item in his/her cart, the quantity of a specific item, and a histogram of the entire cart.

### What Went Well
The problem as a whole was solved. Minimal code was used, and everything functions as it should. This includes error checking and exception handling.

### What Could Be Better
In the future I would like to break the main Source.cpp file into a few classes. One class to handle the Python calling functions and one class to handle the C++ functions. Currently many functions are defined in the Source.cpp file and it appears very cluttered.

### What Was Challenging
The biggest challenged I faced when coding this project was deciding if certain code should be included in main or if it should be defined as a separate function. I'm not completely certain how closing a file happens in C++ so I was hesitant to put this operation in a function. In the end I think bringing it into its own function helped the readability of the code.

### Maintainable? Readable? What Did I Learn?
I am pleased with the readability of my code. As stated before, it may appear cluttered, however, every function is commented with its purpose. Along with the comments and appropriately named variables, I believe this is my most readable code to date. Any developer can grab this code and read it and know exactly what is going on and where. This is my biggest takeaway from the project. Commenting and appropriate variable naming seem tedious at times but overall they make the code more readable and help anyone who is new to the code base gain an understanding quickly. 