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


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <string>
#include <iostream>

#define	RAND_LIMIT 32767
extern "C"
{
#include<pthread.h>
}

namespace cs296
{


class Box
{
	private:
		bool m_contact	;
		b2World* my_world;
		std::thread musicThread;
		pthread_t t1;
		bool calledOnce;
	public:


  Box(b2World* m_world){
	float x = -7;      
	m_contact = false;	
	calledOnce=false;
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
      box1->SetUserData(this);
      box2->SetUserData(this);    
}			
		

	//static void* play(void*){/home/anmol/cs296/g25_project/cs296_base_code
		//std::cout<<"threading is working";
		////usleep(1000000);
		////play your song here
		////int status = system ("play ./doc/sound.wav");
		////std::cout<<status;		
		//return NULL;
	//}
	
	
	
	//void startContact() { 
			//std::cout<<"Detected\n";
			//m_contact = true;
   			
			//this->render();	}
  	//void endContact() { m_contact = false;
   			//pthread_detach(t1);	}
	//void render(){
		//if(1){
			//if(calledOnce){
				
				
			//pthread_cancel(t1);
			//}
			//calledOnce=true;
			
			//int result = pthread_create(&t1,0,Box::play,this);	
			//std::cout << "result\n";
			//std::string msg1 ("hello");
			
			////std::thread thr(&Ball::play1, this,10);
			////std::swap(thr,musicThread);
			
			//std::cout<<"here\n";
		//}
			///*	int a=1;
			//std::cout<<"Called me\n";	
			//int create1 = pthread_create( &t1, NULL,cs296::Ball::play1,reinterpret_cast<void*>(&msg1));
		//*/
			////	}
			
		//return;
	//}

	//void musicThreadjoin(){
	////	musicThread.join();	
		////system("pkill mpg123");	
	//}


	

};

//class MyContactListener : public b2ContactListener
  //{
    	////std::cout << "Check20\n";
	//void BeginContact(b2Contact* contact) {
	  
      //void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      //if ( bodyUserData ){
        //static_cast<Box*>( bodyUserData )->startContact();
	////std::cout << "Check1\n";
	
	  //}
      ////check if fixture B was a ball
     
	//bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      //if ( bodyUserData ){
        //static_cast<Box*>( bodyUserData )->startContact(); 
	//std::cout<< "Check2\n" ;
    
	  //}

//}
  
    //void EndContact(b2Contact* contact) {
  
      ////check if fixture A was a ball
      //void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	  ////std::cout<<"Here inside end\n";
	  //if ( bodyUserData ){
        //static_cast<Box*>( bodyUserData )->endContact();
		//static_cast<Box*>( bodyUserData )->musicThreadjoin();
 	////	system("pkill mpg123");
	  //}
      ////check if fixture B was a ball
      //bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      //if ( bodyUserData ){
        //static_cast<Box*>( bodyUserData )->endContact();
 	////	system("pkill mpg123");
		//static_cast<Box*>( bodyUserData )->musicThreadjoin();
    //}
	//}
 
//};

  //! Declaring class base_sim_t and struct settings_t
  /*! 
  	The members and base classes of a struct are public by default, But this is not so in classes which contains public, private and protected members struct and class are otherwise functionally equivalent.
  */
  class base_sim_t; //!< Declaring class base_sim_t
  struct settings_t; //!< Declaring struct settings_t
  
  /*!
  	 The purpose of typedef is to assign alternative names to existing types. This make the code look cleaner and easier to understand. Now we can declare objetc references of settings_t by sim_create_fcn() 
  */
  typedef base_sim_t* sim_create_fcn(); 

  //! Struct to store & modify the Simulation settings. Some can be controlled in the GUI.
  /*!
  A Struct setting_t is defined to store the important parameters and attributes associated with the simulation of the Rube Goldberg Machine/Physics Engine
  
  */
  struct settings_t
  {
    //! Constructor function for the initialization of the struct members
    /*! The only  difference between class & struct is that the members of struct are public.
    	So there exists a constructor function for structs to initialize the some default values. Some of these values can be changed in the GUI.
    	
    	By default, View_center will be initialised to b2vec2(0.0f,20.0f)
    	hz of float type is assigned 60 & stores the frequency of the iteration in the simulation, 
    	All the other variables are of int32 type and are initialized as follows: velocity_iterations=8, position_iterations=3,draw_shapes=1,draw_joints=1,draw_AABBs=0,draw_pair=0,draw_contact_points=0,draw_contact_normals=0,
    	draw_contact_forces=0,draw_friction_forces=0,draw_COMs=0,draw_stats=0,draw_profile=0,enable_warm_starting=1,enable_continuous=1,
    	enable_sub_stepping=0,pause=0, single_step=0 
    */
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;   //!< Defines a b2Vec2 type variable to store coordinates of center of GUI
    float32 hz;		//!< A box2D float32 variable to store the frequency in terms of fps
    int32 velocity_iterations;	//!< A Box2D int32 variable to store the the number of velocity_iterations
    int32 position_iterations;	//!< A Box2D int32 variable to store the the number of position_iterations
    int32 draw_shapes; //!< A Box2D int32 variable to check if shapes are drawn (boolean in nature)
    int32 draw_joints; //!< A Box2D int32 variable to  check if  joints are draawn (boolean in nature)
    int32 draw_AABBs; //!< A Box2D int32 variable to  check if  AABB are draawn (boolean in nature)
    int32 draw_pairs; //!< A Box2D int32 variable to check if  pairs are draawn
    int32 draw_contact_points; //!< A Box2D int32 variable to check if contact points are draawn
    int32 draw_contact_normals; //!< A Box2D int32 variable to check if normals are drawn
    int32 draw_contact_forces; //!< A Box2D int32 variable to check if contact forces are applied
    int32 draw_friction_forces; //!< A Box2D int32 variable to check if friction forces are applied
    int32 draw_COMs; //!< A Box2D int32 variable to check if COMs of bodies are drawn
    int32 draw_stats; //!< A Box2D int32 variable to check if normals are drawn
    int32 draw_profile; //!< A Box2D int32 variable to check if statistics are shown
    int32 enable_warm_starting; //!< A Box2D int32 variable to check if warm is enabled
    int32 enable_continuous; //!< A Box2D int32 variable to check continuity of variable
    int32 enable_sub_stepping; //!< A Box2D int32 variable to check if stepping is enabled
    int32 pause; //!< A Box2D int32 variable to check if system is paused
    int32 single_step; //!< A Box2D int32 variable to step to the end of the simulation
  };
  
  //! Struct sim_t to store the reference to base_sim_t struct and an identifier string for the simulation
  struct sim_t
  {
    const char *name;  //!< This char variable stores the identifier/name of the system 
    sim_create_fcn *create_fcn; //!< This variable stores the reference to base_sim_t object

		//! Constructor for sim_t
		
		/*! 
			This function Initialzes the name and create_fcn members of the struct 
		*/
    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  //! Setting maximum contact points to 2048
  const int32 k_max_contact_points = 2048;  
  
  //!Struct contact_point_t to store the variables/parameters for contact of bodies
  /*!
  	The contact_point_t struct consists of fixtures (reference) of the two bodies whose contact is to analysed.
  	It also containd b2Vec2  and b2PointState Variables variables for the normal and position vector and state at the point of contact. 
  
  */
  struct contact_point_t
  {
    b2Fixture* fixtureA; //!< b2Fixture* pointer to store fixture of body A
    b2Fixture* fixtureB; //!< b2Fixture* pointer to store fixture of body B
    b2Vec2 normal; //!< b2Vec2 normal stores the Normal at point of contact
    b2Vec2 position;	//!< b2Vec2 normal stores the point of contact
    b2PointState state; //!< b2PointState stores the state of the points during the simulation
  };
  
  //! Class base_sim_t contains members that would handle the cases of collision between bodies during the simulation
  /*!
  	This class handles the cases of collision.The class inherits the members of the b2ContactListener of the Box2D API 
  */
  class base_sim_t : public b2ContactListener
  {
  public:
    
    //! Constructor for base_sim_t class
		/*!
		The constructor defines a gravity vector and using it creates a new world object for the simulation and initializes the private variables of the class.
		*/
				
    base_sim_t(); 
    
    //! Virtual destructors for the base_sim_t class. Used to destroy the world object
    //Why are these necessary?
    /*!
   	Virtual destructor will ensure that the destructor for any class that derives from base_sim_t will be called.
   	This deletes my_world and all associated objects. 
    */
    virtual ~base_sim_t();
    
    //! set_text_line function to set the m_text_line member. m_text_line stores the maximum number of lines to display.  
    //!
    
    void set_text_line(int32 line) { m_text_line = line; }
    
    //! draw_title function takes a string at outputs it at position x,y
    void draw_title(int x, int y, const char *string);
    
    //! The step function set all the variables of the struct settings_t as required to go thru the simulation step by step
    virtual void step(settings_t* settings);

		//! Parent Class Function to check if any key is pressed/not pressed & respond
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    
    //! Parent Class Function to check if any key is pressed/not pressed & respond
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }

		//! Parent Class Function to check if mouse is clicked/not clicked & respond
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    //! Parent Class Function to check if mouse is clicked/not clicked & respond
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    //! Parent Class Function to check if mouse is clicked/not clicked & respond
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    //! Parent Class Function to check if mouse is clicked/not clicked & respond
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

    b2World* get_world(void){
	return m_world;
    }
    //! Let derived tests know that a joint was destroyed.
    //! If no joint is destroyed, the complire will simply ignore.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    //! Callbacks for derived classes.
    
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    //! Callbacks for derived classes.
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    //! Callbacks for derived classes.
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    //! Callbacks for derived classes.
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //How are protected members different from private memebers of a class in C++ ?
  //!protected nonstatic base class member can be accessed by members and friends of any classes derived from that base class
  protected:

    // What are Friend classes?
    //! We define a class contact_listener_t as friend of base_sim_t, granting contact_listener_t class the access to the
    //!   protected and private members 			
    //! of the base_sim_t
    friend class contact_listener_t;
    
    b2Body* m_ground_body; //!< A ground Body member 
    b2AABB m_world_AABB; //!< Axis aligned  bounding boxes(AABB) storage variable
    contact_point_t m_points[k_max_contact_points]; //!< Vector of type contact_point_t to store all the contact points
    int32 m_point_count; //!< Memeber to maintain count of points

    debug_draw_t m_debug_draw; //!< Variable used to draw shapes
    int32 m_text_line;	//!< Member to store maximum number of text-lines in the stats
    b2World* m_world; //!< b2World object required for the simulation
	//MyContactListener mycontact;
    int32 m_step_count; //!< Maintains count of number of steps
    
    b2Profile m_max_profile; //!< Stores the Maximum Profile
    b2Profile m_total_profile; //!< Stores the Total Profile
  };
}

#endif
