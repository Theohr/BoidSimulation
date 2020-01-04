# Boid Simulation

## 10578755

### Brief evaluation 

   This software attempts to simulate the behavior of a flock of boids. The Boids are rendered in the scene and function through the three basic rules Separation which will keeps them away from colliding with each other, Alignment which will make them move with the same speed and Cohesion making them moving with the average position of the local flock and maintain in a group. 
  
   The tasks achieved in this simulation except the movement based on the 3 rules is the flock being able to follow a Leader Boid, a Predator pursuing the Boids and them fleeing from it and avoiding obstacles found in their way. Also, the way user can interact with the simulation on button click.
  
   There issues on this software is the trade-off the amount of flocks and boids for the performance. Trying to add more flocks and boids managed to make the performance pure and run slow. Also, it doesn’t run much as it stops after the boids cover a certain amount of distance.
  
   What I would do differently is to add more flocks and boids in the scene and make them run freely and change flocks according to each boids velocity. Also, creating a 3-D scene and drawing actual Birds flying in the sky or fishes swimming in the water would be extra if I had more time.
  
### User Interactions

  User has to run the solution first then the simulation will start on its own. Some functions were implemented so the user can use the buttons from the keyboard to interact and make changes to the executable such as:
  
          1) Esc Key  = Breaks the program
          2) p  = Pause the Simulation
          3) b  = Predator chases Boids
          4) r = Removes a Boid on click from the flock  
          5) x = Zoom in 
          6) X = Zoom out
          7) v = Flock changes direction
          
### How does code fit together

   The code is very simple to understand. First, we created 6 classes in the solution for Boids, Vector, Flock, Obstacles, Movement and Main. 
  
#### Vector Class

  We start off with the Vector class where we will fit our math functions like Addition, Difference, Multiplication, Dot and Cross product, Magnitude, Normalization, Distance and a Null/New Vector, which will contain our mathematical expressions. ]

#### Boids Class

  We go and create the Boids Class where we will declare what kind of boids we have, their position, velocity and id of each boid and some getters and setters for their identity and also some functions to draw them and also make them move.  The constructor of the class sets each boid’s position velocity and id using the new Vector we created in the Vector class, the draw function using the position each boid has and the move function getting the id for the 3 type of boids we have and feeding them values based on that using the Movement functions we will implement in the Movement class later. 

#### Flock Class

  On the Flock Class we will implement the Boids list where we will have a flock of some Boids, their leader and a predator. Our flock will have a calculated centroid and the radius of the flock where it will use the null Vector, the Distance and Multiplication functions of Vector class to not include boids that aren’t in the distance calculated aren’t in the flock. We also implement the drawBoids Function where we draw the Leader, Normal and Predator boids and also the moveBoids where we take the function move, we created in Boids class and based on the type of boid we use the Magnitude and Difference function from Vector to make them move in the scene. Extra functions are the addBoid and removeBoid where the user on button click can actually add boids in the flock. 

#### Movement Class

  Moving on with the Movement class where we will basically implement every movement function our boids will follow. Based on the Reynolds boid simulation boids should follow 3 basic rules mentioned in the evaluation, Separation, Cohesion and Alignment. All of the 3 functions above implemented by using the Vector class functions and the flock of the boids apply the rules a basic Boid Simulation should have. We also have the DrawBoids function where we use OpenGL for the drawing of each boid represented as a Green Triangle, Leader Boid represented as a Yellow Triangle and Predator Boid represented as a Red Triangle. Some extra functions are followLeader where our flock follows a Boid called the Leader, avoidObstacles where by using the Vector class we calculate our Boids to detect the obstacle and move accordingly so they don’t hit it, pursueBoids where our predator pursuing the boids, fleePredator where our Boids flee from the predator so they don’t get caught and drawObstacles where we draw cubes as obstacles in the scene using the Obstacle class.

#### Obstacles Class

   Here we basically set the location, radius and the angle our obstacles will have and draw them on the scene using OpenGL as Cubes.
  
#### Main Class

   Where we get the rest of the above classes implemented and by using OpenGL we create our scene, set the camera how the user will view the scene, create the init function where we create the environment and render the obstacles in the scene, the display function which gets the functions created to draw the obstacles, set the camera and draw the boids, the handleKeyboard function with the keys the user can press to interact with the Simulation, the update which will update the animations so our program doesn’t stuck anywhere getting the functions from the other classes and our main where the list of each key will be printed for the user to interact to the simulation and create the window for the scene getting the functions above.
  
### Program Uniqueness

   Program renders a flock of boids following some basic rules and moving through the scene according to the Leader of the flock. Not that impressive but it gets better as boids are being pursued by their predator which they manage to avoid and not collide with it but also avoiding obstacles coming their way and managing to regroup after getting separated.
  
#### Idea

   I always wanted to get deeper into game and simulation creations and when I searched for this simulation It actually was appealing more than the other options trying to implement such a thing. 
  
#### What I started with

   I started with the creation and rendering of the Boids, Predator, Leader and actually making them move in the scene then added some extra things such as Predator pursuing boids, boids fleeing, boids avoiding random obstacles in their way etc. 
  
#### Started with a given project?

   How I got things done is with the research on the specific topic on the internet and viewing other simulations found in YouTube or Websites. A lot of help was the Boids Pseudocode I found online. Other than that, I researched well most of the Simulations found online and by getting ideas on how each one implemented theirs I tried implementing mine with some additional tweaks. 

## YouTube Video Link
https://www.youtube.com/watch?v=c2MvHWHUhJU
