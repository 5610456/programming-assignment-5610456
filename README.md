[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/hhQzWvz6)


# Project: Craig Boids Flocking System in 3D

# Project Aims
- This project aims to simulate flocking behaviours as seen in real life (such as birds, crowds or schools of fish) by using simple 3D shapes to mimic these behaviours.

# File Excution
- Download all files
- Run within C Lion
- Buid
- Run using 'play' button

# Background Research
- About Boids:

  Defined by a computer scientist within the 1980s, Craig Reynolds, who developed the algorith to mimic the natural movement of flocks. These 'boids' as he puts it follows 3 rules that imitate complex crowd behavior. 

    The rules are as follows:
     - 1) Cohesion- Moving towards a large population of other boids, keeping within the crowd.
     - 2) Separation- Avoid colliding with other boids, keeping to a clear path.
     - 3) Alignment- Maintain the same direction as the rest of the boids.
      
      These create believable group movement without requiring a leader.


# Design and Structure
  - Within my program the classes are as follows:
    - Boid
    - Flock
    - NGLScene
    - MainWindow


# Project Progression
- ![Screenshot from 2025-05-24 16-45-27](https://github.com/user-attachments/assets/5e9e954f-ad1d-4047-b10c-9401d521bdbd)
- (Screenshot displaying inital screen)
- All the data and functions required to define a single Boid are stored in the Boid class, located in boid.h. This includes the Boid's position, velocity, and acceleration using NGL’s ngl::Vec3. The class also contains methods to draw the Boid in 3D, simulate flocking behaviour, apply forces, and update its movement over time.
- I implemented the constructor in boid.cpp to set the Boid’s initial position and reset its velocity and acceleration to zero. The update() function advances the Boid each frame by adding acceleration to velocity, limiting the speed, updating the position, and resetting the acceleration to prevent it from accumulating.
- To maintain flocking behaviour, each Boid steers toward the average position of its neighbours using the seek() function. The main behaviours—cohesion, separation, and alignment—are each weighted and applied through the applyForce() method. The draw() method renders each Boid using NGL’s built-in "boid" primitive, applying appropriate transformations and shaders.
- After completing the Boid class, I created the Flock class to manage a group of Boids. It initializes with a set number of Boids and stores their position, orientation, size, colour, and lifespan. The update() method handles each Boid’s behaviour and spawns new ones if not enough are active. Gravity is applied, Boid size gradually increases, lifespan decreases, and Boids are marked dead if they fall below a threshold or their life ends.
- To keep the flock growing, birthParticles() resets dead Boids and reuses them. I also created helper functions to randomise initial directions and reset attributes. The render() method iterates over the Boids and draws each one using its individual draw() call. The class also supports flock translation, adjusting alignment and spread, and dynamically adding new Boids, making it easier to simulate and control realistic 3D flocking behaviour.
- The NGLScene class sets up, animates, and renders the entire Boids system using OpenGL and the NGL library. In initializeGL(), OpenGL primitives

![Screenshot from 2025-05-27 09-16-01](https://github.com/user-attachments/assets/b344e2c8-b5ed-4972-91ec-4db19fa12315)
- (Screenshot displaying final image I got to)
- To troubleshoot the issue, I first attempted to merge and repurpose the original particle system logic into the Boid implementation. Despite integrating the logic from the particle files, there was no visual improvement.
- Suspecting the shaders might be the problem, I simplified both BoidFragment.glsl and BoidVertex.glsl by replacing their contents with a basic solid yellow RGBA colour. However, this still did not render the Boids on screen.
- As a further test, I moved the RGBA colour assignment into the NGLScene.cpp file to bypass potential shader issues entirely, but the Boids still failed to appear.
- 
- Debugging Summarised:
- Replaced shaders with solid color: still failed
- Attempted direct color in C++: no result
- Checked draw calls and confirmed draw() was called


# Project Evaluation
- I would have liked to add some additional features besides to the initial goal of making the Boids render correctly.
- One idea was to incorporate obstacles that the Boids would have to avoid, like skyscrapers or blocks.
- I also thought about including hoops in the scene for the Boids to fly through.
- Adding user interaction was another possible enhancement. The mouse pointer, for instance, could either attract Boids and cause them to follow it, or it could serve as an obstacle that the Boids would have to avoid in real time.

# References:
- Using John Macey ParticleQt as a reference, replacing 'Particle' with 'Boid' and 'Emitter' with 'Flock' (https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt) [Last Accessed 27 May 2025]

- Taking inspo off: Coding Adventure: Boids (https://youtu.be/bqtqltqcQhw?si=F-BrRPD3BPAI0X3d) [Last Accessed 27 May 2025]

- Nature of Code Chapter 5: Autonomous Agents (https://natureofcode.com/autonomous-agents/) [Last Accessed 26 May 2025]

- NGL Graphics Libary (http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/index.html) [Last Accessed 26 May 2025]

-Flocks, Herds, and Schools: A Distributed Behavioral Model  (https://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/) [Last Accessed 27 May 2025]

