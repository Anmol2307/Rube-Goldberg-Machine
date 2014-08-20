/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  
  //! Constructor for dominos_t class which sets up the initial positions of the elements of the Rube Goldberg Simulation
  {
  	//! x is a variable that decides the shifting of the entire deisgn. This is added to the x co-ordinate of the positions set to all the objects. 
  	float x = -7;
	float ry = 2.0;		
    //Ground
    //!1<b> GROUND </b>
     /*!A b2Body object is initiased for representing Ground. This object is pointed by the b2Body* pointer variable b1. A variable of the type b2EdgeSgape shape is declared and set to be the line segment whose end points are (-90.0f, 0.0f) & (90.0f, 0.0f) of the type b2Vec2. This is done by calling the  Set method of b2EdgeShape class. A b2BodyDef variable bd is defined for creating the b1 body object using the class method of world CreateBody. Fixture is assigned to the body using the shape vaariable and  density as parameters to the b2Body method Create Fixture .
     */
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
      

    //Top horizontal shelf
    //!<b>2 HORIZONTAL SHELF </b>
    /*! A b2PolygonShape type object/variable shape is declared as set as a box of 3 * 0.25 for representing the dimensions of the horizontal shelf. A b2BodyDef object bd is declared for the shelf. The position of the body(shelf) is set to (-40.0f + x, 30.0f). Then a b2Body object is created using the method CreateBody by passing bd. This is pointed by the b2Body pointer ground. Then b2Body method CreateFixture is called to set the fixtures: Shape and Density = 0.0f.
    
    This is the platform on which the balls at the start of the simulation
    
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-40.0f + x, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    // Moving Ball
    
    //!<b> 3 THE BIG SPHERE </b>
    /*! 
    This block generates the big sphere that lands on the horizontal platform initially.
    
    Start by Declaring a b2Body * variable sbody to store reference of a sphere body. circle is the b2CircleShape object to store its radius = 1.0 . ballfd object stores the fixtures, like shape,density = 55,friction = 0 ,restitution = 0 which are float32 variables.<p>
    Bodydef ballbd object type is set to to dynamic & its position is set to (-40.0f + x, 140.0f). The velocity of the Bodydef object is assigned (0.50,0.0), which is only in the x direction. A b2Body object is initialised using bd and method CreateBody, assigned fixture using CreateFixture and is pointed to by sbody & fixture is assigned to it.<p>
    
    */
    {
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 25.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-40.0f + x, 140.0f);
      ballbd.linearVelocity.Set(0.50f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
		}
		/*! <b> 4 PULLEY </b>
		 
		This block generates the first pulley which contains a box on one side and a horizontal bar at the other. This Pully System consists of the three components : The open box, the horizontal bar and pulley joint.
    
    A new b2BodyDef object pointed by bd is created. This Bodydef object is set the fixtures and properties of the open box on the left side of the pulley. The position is set to (-35+ x,25), type to dynamicBody and fixedRotation is set true.For the open box,three b2PolygonShape and b2FixtureDef variables representing three small boxes for the sides. They are set as boxes of dimesion 2 * 0.2 , 2 *0.2 , 0.2 * 2.Thus the shape fixture is assigned.The other fixtures (density= 10,friction= 0.5,restitution= 0) are assigned the same values. Then the open box is created by using bd and fd1, fd2, fd3. This is pointed to by box.<p>
    For the bar, bd is set to the required position (-30 + x,25). fd1 is modified with density value(34) for the bar. And box2 points to the b2Bodybox object created using body definition bd and fixture f1.<p>
    For the pulley joint , b2PulleyJointDef object is created, which is pointed to by myjoint. Four b2vec2 type anchors(on body 1(-35+x, 30), body 2(-30+x, 20), ground1 (-35+x, 40) , ground2(-30+x, 40)) are also required for defining the joint. The pulley ratio is defined = 1. and then myjoint is initialised by giving the box1 , box2 ,their centres & anchors for ground 1& 2. myjoint represents the entire pulley system.<p> 
    
    */
		
		{
			{
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-35+ x,25);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.0,0.2, b2Vec2(0.f,-1.9f), 0);
      //bs1.SetAsBox(2,0.2);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2.0, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;

      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2.0, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The other end
      bd->position.Set(-30 + x,25);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-35+x, 30); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(-30+x, 20); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-35+x, 40); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-30+x, 40); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
	}
	
 // Horizontal Rotating bar to push the cart
 
//!<b>5 BIG  REVOLVING HORIZONTAL PLATFORM </b>
    /*!
    This block is for the generation of the horizontal bar that is hinged and rotates about its center of mass. In the design another ball is set on it initially. 
    
    A b2PolygonShape object shape is set as box of dimensions (6.2f, 0.2f). A b2BodyDef bd is declared for the horizontal bar, whose position is set to (-27, 5.5) and type assigned to b2_dynamicBody. Fixture for the body is declared fd. Shape is assigned to the fd, density is set to 1. Then a body object b2 is initialsed and pointed to by body.<p>
    
    Another body body2 is defined with position (-27+x, 7.5) (for the hinge) and box dimensions (0.2f, 6.0f) using bd2.
    
    Then b2RevoluteJointDef object jointDef is declared to represent the revolving platform. jointDef.bodyA & jointDef.bodyA are initialized to body1 and body2,localAnchor A & B members are set to (0,0), collideConnected is set false. CreateJoint is called by the world object to initialise the joint and rotating platform.
    */ 
{
      b2PolygonShape shape;
      shape.SetAsBox(6.2f, 0.2f);
      //b2PolygonShape sh;
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
      b2BodyDef bd;
      bd.position.Set(-27, 5.5);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
      //b2FixtureDef *fd1 = new b2FixtureDef;
      //fd->density = 1.f;
      //fd->shape = new b2PolygonShape;
      //fd->shape = &sh;
      //body->CreateFixture(fd1);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 6.0f);
      b2BodyDef bd2;
      bd2.position.Set(-27+x, 7.5);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

   }

// Cart
//!<b>6 THE CAR</b>
    /*!
    This block generates the car that is triggered by the rotation of the large horizontal bar. 
    
    Three b2Body* objects cartbox , cartwheel1 and cartwheel2 are used. Bodydef bd is set to cartbox whose position is set to (-24+x, 1). Fixture fd1 is associated with the bd. The shape  is set as box (6.0,0.8). 
    
    Two sphere bodies are creates like in component 3. Their radius is 1 and density is 0.5. They formthe wheels of the car.
    
    The cartbox, cartwheel1 and cartwheel2 are joined by RevoluteJoint and  the endpoint of the cartbox.
    */ 
	{
		//b2Body* cartbox = createBox(400, 30, 100, 10);
		//b2Body* cartwheel1 = createCircle(300, 30, 20);
		//b2Body* cartwheel2 = createCircle(300, 30, 20);

		//b2PolygonShape shape;
      		//shape.SetAsBox(6.0f, 0.8f);
      		//b2PolygonShape sh;
      		//sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
		      b2BodyDef bd;
		      bd.position.Set(-24+x, 1);
		      bd.type = b2_dynamicBody;
		      b2Body* cartbox = m_world->CreateBody(&bd);
		      //b2FixtureDef *fd = new b2FixtureDef;
		      //fd->density = 1.f;
		      //fd->shape = new b2PolygonShape;
		      //fd->shape = &shape;
		      //cartbox->CreateFixture(fd);

            //////////////////////

	b2FixtureDef *fd1 = new b2FixtureDef;// Declaring a new FixtureDef pointer
      fd1->density = 1.5;	// Assigning the members of the FixtureDef appropriately
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;//assigning the shape member to a PolygonShape pointer
      b2PolygonShape bs1;	// declaring a polygon shape pointer 
      bs1.SetAsBox(6.0,0.8, b2Vec2(0.f,0.0f), 0);	// Assigning the pointer to a box with appropriate agruements 
      fd1->shape = &bs1; // Assigning the new Reference
     
      
      b2FixtureDef *fd2 = new b2FixtureDef; // Declaring a new FixtureDef pointer
      fd2->density = 1; // Assigning the members of the FixtureDef object pointer appropriately
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;	// assigning the shape member to a PolygonShape pointer
      b2PolygonShape bs2;								// declaring a polygon shape pointer 
      bs2.SetAsBox(0.2,2.0, b2Vec2(-6.0f,1.5f), 0); // Assigning the pointer to a box with appropriate agruements
      fd2->shape = &bs2; // Assigning the new Reference
      
      b2FixtureDef *fd3 = new b2FixtureDef; // Declaring a new FixtureDef pointer
      fd3->density = 1; // Assigning the members of the FixtureDef* object pointer appropriately
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape; // assigning the shape member to a new PolygonShape pointer
      b2PolygonShape bs3; // declaring a polygon shape pointer 
      bs3.SetAsBox(0.2,2.0, b2Vec2(+6.0f,1.5f), 0); // Assigning the pointer to a box with appropriate agruements
      fd3->shape = &bs3; // Assigning the new Reference
      
      cartbox->CreateFixture(fd1);
      //cartbox->CreateFixture(fd2);
      //cartbox->CreateFixture(fd3);





	   //////////////////////		





	      b2Body* cartwheel1;
	      b2CircleShape circle1;
	      circle1.m_radius = 1.0;
	
	      b2FixtureDef ballfd1;
	      ballfd1.shape = &circle1;
	      ballfd1.density = 0.5f;
	      ballfd1.friction = 0.1f;
	      ballfd1.restitution = 0.0f;
	      b2BodyDef ballbd1;
	      ballbd1.type = b2_dynamicBody;
	      ballbd1.position.Set(-27.0f + x, 0.0f);
	      //ballbd.linearVelocity.Set(0.50f,0.0f);
	      cartwheel1 = m_world->CreateBody(&ballbd1);
	      cartwheel1->CreateFixture(&ballfd1);

		b2Body* cartwheel2;
	      b2CircleShape circle2;
	      circle2.m_radius = 1.0;
	
	      b2FixtureDef ballfd2;
	      ballfd2.shape = &circle2;
	      ballfd2.density = 0.5f;
	      ballfd2.friction = 0.1f;
	      ballfd2.restitution = 0.0f;
	      b2BodyDef ballbd2;
	      ballbd2.type = b2_dynamicBody;
	      ballbd2.position.Set(-21.0f + x, 0.0f);
	      //ballbd.linearVelocity.Set(0.50f,0.0f);
	      cartwheel2 = m_world->CreateBody(&ballbd2);
	      cartwheel2->CreateFixture(&ballfd2);
	
		b2RevoluteJointDef* firstWheelRevoluteJointDef = new b2RevoluteJointDef();
		firstWheelRevoluteJointDef->Initialize(cartwheel1, cartbox, cartwheel1->GetWorldCenter());
		m_world->CreateJoint(firstWheelRevoluteJointDef);

		b2RevoluteJointDef* secondWheelRevoluteJointDef = new b2RevoluteJointDef();
		secondWheelRevoluteJointDef->Initialize(cartwheel2, cartbox, cartwheel2->GetWorldCenter());
		m_world->CreateJoint(secondWheelRevoluteJointDef);
		
	}



// Block to generate the curve
//!<b>7 GENERATION OF THE CURVES </b>
     /*!
     This block generates the two curves in the simulation. A curve is generated by connecting small lines. Any curve can broken down angularly in smaller parts and the x and y coordinates can be approximated to r*cos(angle) and r* sin(angle) where r is the radius of curvature at that point.
     
     Both the curves we generated here are parts of the circle. One of radius 3.5 and other of radius 15. The first one is 3/4th part of the circle while the secon one is the quarter of the circle. In first part we are iterating over angles of pi/24 and in the second part we are iterating over the angle pi/40.
     */	
{	
	{
		b2Body * curve;
        	b2EdgeShape shape[40];
        	b2BodyDef shapebd;
        	b2FixtureDef shapefd;
        	float32 x = -14.0;
       	 	float32 y = 11.5f;
        	float32 radius = 3.5;
        	//float32 mult = -1;
        	curve = m_world->CreateBody(&shapebd);
        	int i = 0;
        	for(i = 1; i < 32 ; i++){
          shape[i].Set(b2Vec2( x+radius*sin(b2_pi/24+b2_pi/3.f+i*b2_pi/24.0) , y + radius*cos(b2_pi/24+b2_pi/3.f+i*b2_pi/24.0)) , b2Vec2( x+radius*sin(b2_pi/24+b2_pi/3.f+(i+1)*b2_pi/20.0) , y + radius*cos(b2_pi/24+b2_pi/3.f+(i+1)*b2_pi/20.0)));
          shapefd.friction = 0;
          shapefd.shape = &shape[i];
          curve->CreateFixture(&shapefd);
        }

	

}
/////////////////////////////////////////////////////////////////////
{
			b2Body * curve;
			b2EdgeShape curves[20];
			b2BodyDef curvebd[20];
			float32 x = 1;
			float32 y = 22;
			float32 radius = 15;
			for(int i = 10 ;i < 20 ; i++){
				curves[i].Set(b2Vec2(x+radius*sin(3.0f/4.0f*b2_pi+i*b2_pi/40.0) , y+radius*cos(3.0f/4.0f*b2_pi+i*b2_pi/40.0)) , b2Vec2(x+radius*sin(3.0f/4.0f*b2_pi+(i+1)*b2_pi/40.0) , y+radius*cos(3.0f/4.0f*b2_pi+(i+1)*b2_pi/40.0)));
				curve = m_world->CreateBody(&curvebd[i]);
				curve->CreateFixture(&curves[i] , 0);
			}
			
			}

}

// Block to generate the horizontal part of the curve and 10 balls on it.
//!<b>8 HORIZONTAL PART OF THE CURVE WITH 10 BALLS ON IT </b>
     /*!
     This block generates the horizontal part of the curve and places 10 balls on it. For this a horizontal line similar to component 1 is defind at points (b2Vec2(0.0f, 7.0f), b2Vec2(22.0f, 7.0f)).
     
     For the spherical body the declaration is similar to that of component 3 but with radius 0.45 with centres separated by 1f. 
     */

{
    {
      b2Body* b1;
      b2EdgeShape shape;
      shape.Set(b2Vec2(0.0f, 7.0f), b2Vec2(22.0f, 7.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }


for (int i = 0; i < 10 ; i++) {
	{
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.45;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.1f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(1.0 + i, 8.0);
      //ballbd.linearVelocity.Set(0.50f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
		}
	}
}

	float y = 2.5;
	//The revolving horizontal platform
	//!<b>9.1 REVOLVING HORIZONTAL PLATFORM </b>
    /*!
    This block is for the generation of the horizontal bar that is hinged and rotates about its center of mass. In the design another ball is set on it initially. 
    
    A b2PolygonShape object shape is set as box of dimensions (2.2f, 0.2f). A b2BodyDef bd is declared for the horizontal bar, whose position is set to (-27+x, 25 + y) (where y is the variable set for adjusting the height of some components) and type assigned to b2_dynamicBody. Fixture for the body is declared fd. Shape is assigned to the fd, density is set to 1. Then a body object b2 is initialsed and pointed to by body.<p>
    
    Another body body2 is defined with position (-27+x, 25 + y+ ry) (for the hinge) and box dimensions (0.2f, 2.0f) using bd2.
    
    Then b2RevoluteJointDef object jointDef is declared to represent the revolving platform. jointDef.bodyA & jointDef.bodyA are initialized to body1 and body2,localAnchor A & B members are set to (0,0), collideConnected is set false. CreateJoint is called by the world object to initialise the joint and rotating platform.
    */
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
      //b2PolygonShape sh;
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
      b2BodyDef bd;
      bd.position.Set(-27+x, 25 + y+ ry);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
     
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f + y);
      b2BodyDef bd2;
      bd2.position.Set(-27+x, 27 + y+ ry);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

    }

		// Moving Ball
		//! <b>9.2 SPHERE ON HORIZONTAL BAR </b>
    /*! 
    This block generates the sphere that is kept on the horizontal rotatable bar (5th component).
    
    Start by Declaring a b2Body * variable sbody to store reference of a sphere body. circle is the b2CircleShape object to store its radius = 0.70 . ballfd object stores the fixtures, like shape,density = 2.5,friction = 0.0 ,restitution = 0.0 which are float32 variables.<p>
    Bodydef ballbd object type is set to dynamic & its position is set to (-27.0f+x, 28.0f + y+ ry). The velocity of the Bodydef object is assigned (0.0,0.0). A b2Body object is initialised using bd and method CreateBody, assigned fixture using CreateFixture and is pointed to by sbody & fixture is assigned to it.<p>
    
    */
    {
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.70;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 2.5f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-27.0f+x, 28.0f + y+ ry);
      ballbd.linearVelocity.Set(0.0f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
		}
		
		// Ramp Component
		//! <b>10 THE RAMP </b>
		/*! 
				This block generates the ramp on which the ball(component 6) would travel. It consists of 2 vertical bars, 1 horizontal bars and 3 bars at some angle with the horizontal bars. All the bars are fixed.
				
		The vertical bars are set are boxes of dimensions (0.25f, 8.0f) and (0.25f, 5.0f) respectively. Their Bodydef members positions are set to (-24.0f+x, 20.0f+y + ry) and (-14.0f+x, 20.0f+y+1.5+ ry).
		
		The three bars which are not horizontal have the same dimensions (3.5f, 0.25f) but two of them are at angle 5*pi/6 with horizontal and one of the is  at pi/6. Their positions are (-21.0f+x, 25.0f+ y +ry) , (-21.0f+x, 15.0f+ y+ry) and (-17.0f+x, 20.0f + y + ry) respectively. The horizontal bar has dimensions (5, 0.25).
		
		
		
		*/


		{
			//Vertical Bars		
			{
      b2PolygonShape shape;
      shape.SetAsBox(0.25f, 8.0f);
	
      b2BodyDef bd;
      bd.position.Set(-24.0f+x, 20.0f+y + ry);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    	}
    
			{
      b2PolygonShape shape;
      shape.SetAsBox(0.25f, 5.0f);
	
      b2BodyDef bd;
      bd.position.Set(-14.0f+x, 20.0f+y+1.5+ ry);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    	}
    
    // Horizontal Bars
    	{
      b2PolygonShape shape;
      shape.SetAsBox(3.5f, 0.25f,b2Vec2(0,0),5*3.14/6);
	
      b2BodyDef bd;
      //bd.friction = 0.3f;
      bd.position.Set(-21.0f+x, 25.0f+ y+ ry);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.3f);
    	}
    
    	{
      b2PolygonShape shape;
      shape.SetAsBox(3.5f, 0.25f,b2Vec2(0,0),3.14/6 );
	
      b2BodyDef bd;
      
      bd.position.Set(-17.0f+x, 20.0f + y+ ry);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.3f);
    	}
    
    	{
      b2PolygonShape shape;
      shape.SetAsBox(3.5f, 0.25f,b2Vec2(0,0),5*3.14/6);
	
      b2BodyDef bd;
      
      bd.position.Set(-21.0f+x, 15.0f + y+ ry);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.3f);
    	}
    
    	{
    	  b2PolygonShape shape;
    	  shape.SetAsBox(5.0f, 0.25f);
	
    	  b2BodyDef bd;	
      
	      bd.position.Set(-17.0f+x, 15.0f + y - 1.5+ ry);
	      b2Body* ground = m_world->CreateBody(&bd);
      	ground->CreateFixture(&shape, 0.3f);
    	}
    }
    
    
    
    
    
		//Ball on the curve
		/*! <b>11 LIGHT BALL ON THE CURVE </b>
		 
		This block generates a ball on the curve. This ball collides with the ball on the pulley and triggers collision with the system of rotatable bars. 
    
    Start by Declaring a b2Body * variable sbody to store reference of a sphere body. circle is the b2CircleShape object to store its radius = 0.40 . ballfd object stores the fixtures, like shape,density = 0.1 ,friction = 0.0 ,restitution = 1.0 which are float32 variables.<p>
    Bodydef ballbd object type is set to dynamic & its position is set to (-14.0, 11.0f). The velocity of the Bodydef object is assigned (0.0,0.0). A b2Body object is initialised using bd and method CreateBody, assigned fixture using CreateFixture and is pointed to by sbody & fixture is assigned to it.<p>
     
    
    */
    {
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.40;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.10f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.1f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(-14.0, 11.0f );
      ballbd.linearVelocity.Set(0.0f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
			}
    
    
		
		// Revolving Platforms
		//!<b>12 THREE REVOLVING PLATFORMS </b>
    /*!
    This block is for the generation of 3 bars that and hinged and rotate about their center of mass.
    
    A b2PolygonShape object shape is set as box of dimensions (2.2f, 0.2f),(0.2,2.0),(2.2f,0.2f). A b2BodyDef bd is declared for the horizontal bar, whose position is set to (-3.1+x, 13.4),(-3.5+x, 17.1) , (-0.2+x, 19.1) in the three cases and type assigned to b2_dynamicBody. Fixture for the body is declared fd. Shape is assigned to the fd, density is set to 0.1 , 0.1 , 0.01. Then a body object b2 is initialsed and pointed to by body.<p>
    
    Another body body2 is defined with position (-3.1+x, 15.4), (-3.5+x, 19.1), (-0.2+x, 21.1) in the three cases (for the hinge) and box dimensions (0.2f, 2.0f), (2.0f,0.2f),(0.2f,2.0f) using bd2.<p>
    
    Then b2RevoluteJointDef object jointDef is declared to represent the revolving platform. jointDef.bodyA & jointDef.bodyA are initialized to body1 and body2,localAnchor A & B members are set to (0,0), collideConnected is set false. CreateJoint is called by the world object to initialise the joint and rotating platform.<p>
    */
	{
		//The revolving horizontal platform leftmost
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
      //b2PolygonShape sh;
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
      b2BodyDef bd;
      bd.position.Set(-3.1+x, 13.4);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.02f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
      //b2FixtureDef *fd1 = new b2FixtureDef;
      //fd->density = 1.f;
      //fd->shape = new b2PolygonShape;
      //fd->shape = &sh;
      //body->CreateFixture(fd1);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-3.1+x, 15.4);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    
   
	
//The revolving horizontal platform second	
		{
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 2.2f);
      //b2PolygonShape sh;
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
      b2BodyDef bd;
      bd.position.Set(-3.5+x, 17.1);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.02f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
      //b2FixtureDef *fd1 = new b2FixtureDef;
      //fd->density = 1.f;
      //fd->shape = new b2PolygonShape;
      //fd->shape = &sh;
      //body->CreateFixture(fd1);

      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(-3.5+x, 19.1);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
	
	//The revolving horizontal platform rightmost
	
		{
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
      //b2PolygonShape sh;
	
      b2BodyDef bd;
      bd.position.Set(-0.2+x, 19.1);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 0.001f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
      //b2FixtureDef *fd1 = new b2FixtureDef;
      //fd->density = 1.f;
      //fd->shape = new b2PolygonShape;
      //fd->shape = &sh;
      //body->CreateFixture(fd1);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-0.2+x, 21.1);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
 	} 
    
    // Horizontal Fixed Platform
    //!<b>13 HORIZONTAL SHELF FOR DOMINOS </b>
    /*! 
    This block generates the left horizontal platform on which dominos will be kept initially. 
    
    A b2PolygonShape type object/variable shape is declared as set as a box of (6.0f, 0.25f) for representing the dimensions of the horizontal shelf. A b2BodyDef object bd is declared for the shelf. The position of the body(shelf) is set to (6.5f+x, 22.5f). Then a b2Body object is created using the method CreateBody by passing bd. This is pointed by the b2Body pointer ground. Then b2Body method CreateFixture is called to set the fixtures: Shape and Density = 0.02f and Friction = 0.1f.
    
    
    
    */
    {
      b2PolygonShape shape;  // Declaring a Polygon Shape object for Horizontal Shelf
      shape.SetAsBox(6.0f, 0.25f); // Set the Shape as a  box
	
      b2BodyDef bd; // Declaring Body Declaration object
      bd.position.Set(6.5f+x, 22.0f); // Setting the position for shelf
      b2Body* ground = m_world->CreateBody(&bd); // Initialising the ground object with the required definition
      ground->CreateFixture(&shape, 0.0f); // Set fixture to the shape
    }
    
    //Dominos on the left horizontal platform
    //!<b>14 DOMINOS </b>
    /*!
    A b2PolygonShape type object/variable shape is declared. This object is then set as a box of (0.1f, 1.0f) for representing the shape of a domino. A b2FixtureDef object fd is defined to store the fixtures: shape , density=0.001f and friction =0.1f. Then FOR EACH  of the ten dominos, a b2BodyDef object bd is defined and the type and position of bd are set appropriately (0.69f+x + 1.0f * i, 23.0f) for values of i in [0,10], A b2Body object is created using bd and method CreateBody and is pointed to by body , fixture is assigned using fd.
    
    */
    
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f); // Setting Shape of Dominos
	
      b2FixtureDef fd; 
      fd.shape = &shape;
      fd.density = 0.001f;
      fd.friction = 0.1f;   // Assigning Fixture objects,required parameters  
		
      for (int i = 0; i < 10; ++i)    // Creating 10 domino body objects
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;					// Dynamic type objects are required for motion	
	  bd.position.Set(0.69f+x + 1.0f * i, 23.0f); 
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);					// Assigning Fixtures
	}
    }
    
   //The pendulums
    //!<b>15 SYSTEM OF PENDULUMS </b>
    /*!
     This block generates the system of 10 pendulums which are supported from a horizontal plank. 
    
    A b2Body variable pointed by b2 is created. A horizontal plank is to be created. For this a b2PolygonShape type object/variable shape is declared. Shape is then set as box(4.25f, 1.5f). b2BodyDef bd is declared and set position for the plank (-36.5f, 28.0f) . b2 is assigned usind the definition bd. Then , fixture and density= 1.0f is assigned to b2(plank).
    
    	The bobs are generated by doing the following in a loop 10 times.
    	
    	b2Body *b4 is created for the bob of the pendulum using body definitons , fixtures and polygon shapes. The difference is that the bob is a dynamic body and density = 0.0005 and at position(11.0f + 2+x, 31.5f) (for i in [0,4]) with dimensions 0.25 * 0.25 and coefficient of restitution = 1.0f. Then a b2RevoluteJointDef object jd for joining the two b2Body objects and form the pendulum system. A b2Vec2 object anchor is the fixed position (11.0f + i+x, 32.0f) about which the pendulum oscillates. anchor , b2 & b4 are used to initialise the joint jd , which represents the pendulum.
    */
   
    
   for (int i = 0; i < 5 ; i++) { 
    
    {
      b2Body* b2;
      {

	b2PolygonShape shape;
	shape.SetAsBox(4.25f, 1.5f);
	  
	b2BodyDef bd;

	bd.position.Set(11.0f + 2+x, 31.5f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 1.0f);
      }

	

      b2Body* b4;

      {

				b2PolygonShape shape;
	
				shape.SetAsBox(0.25f, 0.25f);

	  

				b2BodyDef bd;

				bd.type = b2_dynamicBody;
				//bd.restitution = 1.0f;
				

				bd.position.Set(11.0f+x + i, 24.0f);
				b4 = m_world->CreateBody(&bd);
				
				b2FixtureDef ballfd;
      	ballfd.shape = &shape;
     		ballfd.density = 0.00050f;
      	ballfd.friction = 0.3f;
      	ballfd.restitution = 1.0f;
				
				
				b4->CreateFixture(&ballfd);

      }

	

      b2RevoluteJointDef jd;

      b2Vec2 anchor;

      anchor.Set(11.0f + i+x, 32.0f);

      jd.Initialize(b2, b4, anchor);

      m_world->CreateJoint(&jd);

    }

  }
  
  // Horizontal Fixed Platform
    //!<b>16 OTHER HORIZONTAL SHELF FOR DOMINOS </b>
    /*! 
    This block generates the right horizontal platform on which dominos will be kept initially. The rightmost pendulum will trigger collisions among the dominos set on this. 
    
    A b2PolygonShape type object/variable shape is declared as set as a box of (6.0f, 0.25f) for representing the dimensions of the horizontal shelf. A b2BodyDef object bd is declared for the shelf. The position of the body(shelf) is set to (22.5f+x, 22.5f). Then a b2Body object is created using the method CreateBody by passing bd. This is pointed by the b2Body pointer ground. Then b2Body method CreateFixture is called to set the fixtures: Shape and Density = 0.0f and Friction = 0.0f.
    
    
    
    */
    {
      b2PolygonShape shape;  // Declaring a Polygon Shape object for Horizontal Shelf
      shape.SetAsBox(6.0f, 0.25f); // Set the Shape as a  box
	
      b2BodyDef bd; // Declaring Body Declaration object
      bd.position.Set(22.5f+x, 22.5f); // Setting the position for shelf
      b2Body* ground = m_world->CreateBody(&bd); // Initialising the ground object with the required definition
      ground->CreateFixture(&shape, 0.0f); // Set fixture to the shape
    }
   
   //Dominos on  the other horizontal platfrom
   //!<b>17 DOMINOS ON OTHER SHELF</b>
    /*!
    A b2PolygonShape type object/variable shape is declared. This object is then set as a box of (0.1f, 1.0f) for representing the shape of a domino. A b2FixtureDef object fd is defined to store the fixtures: shape , density=0.001f and friction =0.1f. Then FOR EACH  of the ten dominos, a b2BodyDef object bd is defined and the type and position of bd are set appropriately (16.69f+x + 1.0f * i, 23.5f) for values of i in [0,10], A b2Body object is created using bd and method CreateBody and is pointed to by body , fixture is assigned using fd.
    
    */
   {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f); // Setting Shape of Dominos
	
      b2FixtureDef fd; 
      fd.shape = &shape;
      fd.density = 0.001f;
      fd.friction = 0.1f;   // Assigning Fixture objects,required parameters  
		
      for (int i = 0; i < 10; ++i)    // Creating 10 domino body objects
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;					// Dynamic type objects are required for motion	
	  bd.position.Set(16.69f+x + 1.0f * i, 23.5f); 
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);					// Assigning Fixtures
	}
    } 
    
    // Ball on second horizontal platform
     //! <b> 18 SPHERE ON HORIZONTAL BAR </b>
    /*! 

    This block generates the ball that is kept adjacent to the dominos on the right platform (13th component).

    

    Start by Declaring a b2Body * variable sbody to store reference of a sphere body. circle is the b2CircleShape object to store its radius = 0.40 . ballfd object stores the fixtures, like shape,density = 0.01,friction = 0.3 ,restitution = 0.0 which are float32 variables.<p>
    Bodydef ballbd object type is set to to dynamic & its position is set to(27.8f+x, 23.5). The velocity of the Bodydef object is assigned (0.0,0.0). A b2Body object is initialised using bd and method CreateBody, assigned fixture using CreateFixture and is pointed to by sbody & fixture is assigned to it.<p>

    
    */
    {
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.40;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.01f;
      ballfd.friction = 0.3f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(27.8f+x, 23.5);
      ballbd.linearVelocity.Set(0.0f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
		}
		
		//The see-saw system at the bottom
		//!<b>19 SEE-SAW SYSTEM </b>
    /*! The see-saw system consists of two components:The triangle wedge, the plank which contains two rods at one end for collecting ball and and one rodon thee other for triggering collision with horizontal platform.
    
    For generating the triangle wedge, a b2PolygonShape poly is defined which is initiaised to triangle by three b2vec2 vertices stored in the array. They are (-1,0) , (1,0), (0,3). A fixture definition wedgefd is defined and its shape is assigned to poly, density = 10.0, friction = 0.0f , restitution = 0.0f. A body definition wedgebd is defined and its position set to b2vec2(35.0f+x, 0.0f). sbody is then initialized using CreateBody & CreateFixture.
    
    For generating the plank on top of the wedge, a b2PolygonShape shape is defined which is set as box with b2vec(15.0f, 0.2f).Four fixture objects are declared fd1,fd2,fd3,fd4 and their shapes are assigned to boxes (6.0,0.2),(0.2,2.0),(0.2,2.0),(0.2,10.0) and their densities are 1.0, 1.0,1.0, and 0.28 respectively, friction = 0.0,0.5,0.5,0.5, restitution = 0.0f for all. A body definition bd2 is defined and its position set to b2vec2(30.0f, 1.50f) and type to b2_dynamicBody. body is then initialized using CreateBody & CreateFixture.
    
    Now, there is a need to join the two b2Body sbody and body using a joint. jd is defined to be of type b2RevoluteJointDef and requires an anchor/fixed point which is initialised to (35.0f+x, 3.0f). jd is initialised with sbody,body & anchor and CreateJoint function.
    
      
    */
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,3.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;

      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(35.0f+x, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
     	
     	b2BodyDef *bd = new b2BodyDef;	// Declaring a new BodyDef pointer
      bd->type = b2_dynamicBody;	// Assigning its member type to dynamic , as it is subject to change state on applying force
      bd->position.Set(35.0f+x,3.0f);	// Set the position member of the BodyDef* object 
      //bd->fixedRotation = true;	// Assign the fixedRotation member to true 
      
      //The left bar
      b2FixtureDef *fd1 = new b2FixtureDef;// Declaring a new FixtureDef pointer
      fd1->density = 1.0;	// Assigning the members of the FixtureDef appropriately
      fd1->friction = 0.0;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;//assigning the shape member to a PolygonShape pointer
      b2PolygonShape bs1;	// declaring a polygon shape pointer 
      bs1.SetAsBox(6.0,0.2, b2Vec2(0.f,0.0f), 0);	// Assigning the pointer to a box with appropriate agruements 
      fd1->shape = &bs1; // Assigning the new Reference
     
      
      b2FixtureDef *fd2 = new b2FixtureDef; // Declaring a new FixtureDef pointer
      fd2->density = 1; // Assigning the members of the FixtureDef object pointer appropriately
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;	// assigning the shape member to a PolygonShape pointer
      b2PolygonShape bs2;								// declaring a polygon shape pointer 
      bs2.SetAsBox(0.2,2.0, b2Vec2(-6.0f,1.5f), 0); // Assigning the pointer to a box with appropriate agruements
      fd2->shape = &bs2; // Assigning the new Reference
      
      b2FixtureDef *fd3 = new b2FixtureDef; // Declaring a new FixtureDef pointer
      fd3->density = 1; // Assigning the members of the FixtureDef* object pointer appropriately
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape; // assigning the shape member to a new PolygonShape pointer
      b2PolygonShape bs3; // declaring a polygon shape pointer 
      bs3.SetAsBox(0.2,2.0, b2Vec2(-2.5f,1.5f), 0); // Assigning the pointer to a box with appropriate agruements
      fd3->shape = &bs3; // Assigning the new Reference
      
      b2FixtureDef *fd4 = new b2FixtureDef; // Declaring a new FixtureDef pointer
      fd4->density = 0.28; // Assigning the members of the FixtureDef* object pointer appropriately
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape; // assigning the shape member to a new PolygonShape pointer
      b2PolygonShape bs4; // declaring a polygon shape pointer 
      bs4.SetAsBox(0.2,10.0, b2Vec2(6.0f,10.0f), 0); // Assigning the pointer to a box with appropriate agruements
      fd4->shape = &bs4; // Assigning the new Reference
      
       
       
      b2Body* box1 = m_world->CreateBody(bd); // Declaring & Assigning a Body* Object pointer with BodyDef bd arguement 
      box1->CreateFixture(fd1);	// Adding the previously declared three FixtureDef pointers in the box1 object
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
    
    
      
      
      
      

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(35.0f+x, 3.0f);
      jd.Initialize(sbody, box1, anchor);
      m_world->CreateJoint(&jd);

    }
    
    //!
    /*!<b>20 REVOLVING HORIZONTAL PLATFORM </b> <br>
    This block is for the generation of another horizontal bar that is hinged and rotates about its center of mass. In the design another ball is set on it initially. This is similar to the component 5
    
    A b2PolygonShape object shape is set as box of dimensions (2.2f, 0.2f). A b2BodyDef bd is declared for the horizontal bar, whose position is set to (39+x, 22) (where y is the variable set for adjusting the height of some components) and type assigned to b2_dynamicBody. Fixture for the body is declared fd. Shape is assigned to the fd, density is set to 100.1f. Then a body object b2 is initialsed and pointed to by body.<p>
    
    Another body body2 is defined with position (39+x, 24) (for the hinge) and box dimensions (0.2f, 2.0f) using bd2.
    
    Then b2RevoluteJointDef object jointDef is declared to represent the revolving platform. jointDef.bodyA & jointDef.bodyA are initialized to body1 and body2,localAnchor A & B members are set to (0,0), collideConnected is set false. CreateJoint is called by the world object to initialise the joint and rotating platform.
    */
    
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
      //b2PolygonShape sh;
      //sh.SetAsBox(0.2,1.1,b2Vec2(-1.1,0.5),0);
	
      b2BodyDef bd;
      bd.position.Set(39+x, 22);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 100.1f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
      
      //b2FixtureDef *fd1 = new b2FixtureDef;
      //fd->density = 1.f;
      //fd->shape = new b2PolygonShape;
      //fd->shape = &sh;
      //body->CreateFixture(fd1);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(39+x, 24);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    
    //!
    /*!<b>21 ANOTHER SPHERE ON THE ROTATING PLATFORM </b> <br>
    This block generates a sphere. Similar to initial component 3 but with radius 0.7 and density = 0.5.
    
    */
    
    {
    	b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 0.70;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.5f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.5f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(38.9f+x, 25.5f);
      ballbd.linearVelocity.Set(0.0f,0.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    	
		}
    
    //!
    /*!<b>22 ANOTHER PULLEY </b> <br>
    This block generates a pulley. Similar to initial component 4.
    
    */
    
	  
	{
			{
	//Box createbox(b2World* m_world);
     
	b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(44+ x,15);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2.0,0.2, b2Vec2(0.f,-1.9f), 0);
      //bs1.SetAsBox(2,0.2);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2.0, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;

      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2.0, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       

      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The other end
      bd->position.Set(52 + x,5);	
      //fd1->density = 30.0;	  
      b2FixtureDef *fd13 = new b2FixtureDef;
      fd13->density = 2.01;
      fd13->friction = 0.5;
      fd13->restitution = 0.f;
      fd13->shape = new b2PolygonShape;

      b2PolygonShape bs13;
      bs13.SetAsBox(3.0,2.0, b2Vec2(-1.0f,0.f), 0);
      fd13->shape = &bs13;
      
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd13);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(44+x, 10); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(52+x, 10); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(44+x, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(52+x, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);  
}	
	}
    
   //!
    /*!<b>23 VERTICAL BAR </b> <br>
    This block generates a vertical bar. Similar to component 1 but with different dimensions (0.5f, 10.0f). 
    
    */  
    
	
	 //Box *createbox = new Box(m_world) ; 
		
	{
	
	b2PolygonShape shape;
      shape.SetAsBox(0.5f, 10.0f);
	
      b2BodyDef bd;
      bd.position.Set(48.25 + x, 10.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
