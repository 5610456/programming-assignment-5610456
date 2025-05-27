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

  Defined by a computer scientist within the 1980s, Craig Reynolds who developed the algorithm.

    They follow three rules:
     - 1) Cohesion- Moving towards a large population of other boids, keeping within the crowd.
     - 2) Separation- Avoid colliding with other boids, keeping to a clear path.
     - 3) Alignment- Maintain the same direction as the rest of the boids.


# Design and Structure
  - Within my program the classes are as follows:
    - Boid
    - Flock
    - NGLScene
    - MainWindow


# Project Progression
- ![Screenshot from 2025-05-24 16-45-27](https://github.com/user-attachments/assets/5e9e954f-ad1d-4047-b10c-9401d521bdbd)
- (Screenshot displaying inital screen)
- All of the information and functions required to describe a single Boid using NGL's ngl::Vec3 for location, velocity, and acceleration are stored in the boid class in boid.h. The class has methods for drawing the Boid in three dimensions, simulating flocking behaviours, applying forces, and updating the Boid's movement.
- I created the constructor in boid.cpp to establish the Boid's initial position and to reset its acceleration and velocity to zero. By adding acceleration to velocity, restricting speed, updating location, and finally deleting acceleration to prevent buildup, the update function advances the Boid with each frame.
- To keep the flock together, the Boid moves toward the average position of its neighbors using the seek function. Each behavior—cohesion, separation, and alignment—is weighted and added to the acceleration with applyForce. The draw function renders the Boid using NGL’s built-in "boid" shape, applying the proper transformation and shaders.

![Screenshot from 2025-05-27 09-16-01](https://github.com/user-attachments/assets/b344e2c8-b5ed-4972-91ec-4db19fa12315)
-(Screenshot displaying final image I got to)
- After finishing the Boid class, I created the Flock class to manage a group of Boids. It begins with an initial set of Boids and records their size, colour, life, position, and orientation. Each Boid’s movement and flocking behaviour is handled by the update method. The flock generates new Boids if there aren't enough active ones. It also applies gravity, gradually increases Boid size, reduces their lifespan, and marks them as dead when their life ends or they fall too low.
- To keep the flock growing, the birthParticles function resets dead Boids to bring them back. I also wrote utility functions to reset Boid attributes and assign random movement directions. The render method draws each Boid individually using its own draw function.
- The class also allows moving the whole flock, adjusting alignment behaviour, changing how spread out the Boids are, and adding new Boids at any time. This setup makes it simple to control a large number of Boids and results in realistic 3D flocking behaviour.

# Project Evaluation
- 

# Ref:
- Using John Macey ParticleQt as a reference, replacing 'Particle' with 'Boid' and 'Emitter' with 'Flock' (https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt) [Last Accessed 27 May 2025]

- Taking inspo off: Coding Adventure: Boids (https://youtu.be/bqtqltqcQhw?si=F-BrRPD3BPAI0X3d) [Last Accessed 27 May 2025]

- Nature of Code Chapter 5: Autonomous Agents (https://natureofcode.com/autonomous-agents/) [Last Accessed 27 May 2025]

- NGL Graphics Libary (http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/index.html) [Last Accessed 27 May 2025]

