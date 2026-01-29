/*
 * The nexus apparatus. It opens a portal if the right combination is set to 
 * the Necromancers of Vile Darkness guildhalls. This is the alternative
 * way to join the guild for those that arent directly invited.
 *
 */

inherit "/std/object.c";

#include <stdproperties.h>
#include "../nov.h"

int xaxis;   
int yaxis;   
int zaxis; 

int circle1;
int circle2;
int circle3;

int plane;  

void
create_object()
{
    
    set_short("steel nexus apparatus");
    set_pshort("steel nexus apparatuses");
    set_name("apparatus");
    add_adj("steel");
    add_adj("nexus");
    set_long("This is a steel nexus apparatus.\n");

    add_prop(OBJ_M_NO_GET, "The steel nexus apparatus is too heavy to move.\n");
    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  50000);
    
    /*xaxis = random(10);
    yaxis = random(10);
    zaxis = random(10);*/
    
    xaxis = 6;
    yaxis = 3;
    zaxis = 7;
    
    circle1 = random(10);
    circle2 = random(10);
    circle3 = random(10);
    
    
    setuid();
    seteuid(getuid());
 
}

int
summon_portal(string str)
{
     
     
     if (str != "button")
     {
     	write("Push what? the button?\n");
     	return 1;
     }
     
     if ((circle1 == xaxis) && (circle2 == yaxis) && (circle3 == zaxis))
     {
     	
     	tell_room(environment(this_object()), "The black button on the " +
     	"nexus apparatus suddently glows, and a black magical pentagram suddently " +
     	"materialize in the front of the steel nexus apparatus.\nThe nexus apparatus " +
     	"resets with a sound of 3 separate clicks that gives away a sound echo.");
        clone_object(NOV_DIR +"obj/nportal4")->move(environment(this_object()), 1); 
        
        xaxis = random(10);
        yaxis = random(10);
        zaxis = random(10);
        
        return 1;
        
     }
      
      tell_room(environment(this_object()), this_player()->query_the_name()+" pushes the black " +
      "button, but nothing happens.\n", this_player());
      write("You push the black button but nothing happens.\n");
      
      return 1;
}


int
check_circles(string str)
{
	if (str == "outer circle")
	{
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" examines the " +
          "outer circle on the nexus apparatus, and find out that its tiny steel arrow " +
          "points at the number of "+circle1+".\n", this_player());
          write("You examine the outer circle on the nexs apparatus and find out that its tiny " +
          "steel arrow points at the number of "+circle1+".\n");
          
          return 1;
        }
        
        
        if (str == "middle circle")
	{
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" examines the " +
          "middle circle on the nexus apparatus, and find out that its tiny steel arrow " +
          "points at the number of "+circle2+".\n", this_player());
          write("You examine the middle circle on the nexs apparatus and find out that its tiny " +
          "steel arrow points at the number of "+circle2+".\n");
          
          return 1;
        }
        
        
        if (str == "inner circle")
	{
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" examines the " +
          "inner circle on the nexus apparatus, and find out that its tiny steel arrow " +
          "points at the number of "+circle3+".\n", this_player());
          write("You examine the inner circle on the nexs apparatus and find out that its tiny " +
          "steel arrow points at the number of "+circle3+".\n");
          
          return 1;
        }
        
        write("check what circle? the outer, middle or the inner circle?\n");
        return 1;
}

int
adjust_circles(string str)
{
	if (str == "outer circle")
	{
		
	  circle1 = circle1 + 1;
	  
	  if (circle1 > 10)
	  {
	  	circle1 = 0;
	  }
	  
	 
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" adjusts the " +
          "outer circle on the nexus apparatus. Its tiny steel arrow " +
          "now points at the number of "+circle1+".\n", this_player());
          write("You adjust the outer circle on the nexs apparatus. Its tiny " +
          "steel arrow now points at the number of "+circle1+".\n");
          return 1;
        } 
        
        if (str == "middle circle")
	{
		
	  circle2 = circle2 + 1;
	  
	  if (circle2 > 10)
	  {
	  	circle2 = 0;
	  }
	  
	 
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" adjusts the " +
          "middle circle on the nexus apparatus. Its tiny steel arrow " +
          "now points at the number of "+circle2+".\n", this_player());
          write("You adjust the middle circle on the nexs apparatus. Its tiny " +
          "steel arrow now points at the number of "+circle2+".\n");
          return 1;
        }   
        
        
        if (str == "inner circle")
	{
		
	  circle3 = circle3 + 1;
	  
	  if (circle3 > 10)
	  {
	  	circle3 = 0;
	  }
	  
	  
		
          tell_room(environment(this_object()), this_player()->query_the_name()+" adjusts the " +
          "inner circle on the nexus apparatus. Its tiny steel arrow " +
          "now points at the number of "+circle3+".\n", this_player());
          write("You adjust the inner circle on the nexs apparatus. Its tiny " +
          "steel arrow now points at the number of "+circle3+".\n");
          return 1;
        } 
        
        write("Adjust what? the outer, middle or the inner circle?\n");
        return 1;
}             


void
init()
{
    ::init();
    add_action(summon_portal, "push");
    add_action(check_circles, "check");
    add_action(adjust_circles, "adjust");
}