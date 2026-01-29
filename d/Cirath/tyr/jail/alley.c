/*
* Created by: Luther
* Date: August 2001 
*
* File: /d/Cirath/tyr/jail/alley.c
* Comments: Entrance to the alley by the jail.
*/


#pragma strict_types

inherit "/std/room";
#include "defs.h"

void
create_room()
{
   set_short("Alley beside jail");
   set_long("You stand in a dark and dismal alley. Garbage litters "
        +"the ground and sewege is everywhere. The occasional brick "
        +"falls to the ground from above. Looking up the alley you see "
        +"shadows dancing around. The way out of here is blocked be a gate.\n");
 
   add_item(({"bricks", "athasian bricks", "walls", "brick"}), "The walls "
        +"to the jail seem in pretty bad shape. Loking up you can see a wall "
        +"almost completely gone from decay. You hope noone throws a brick "
        +"down on you.\n");

   add_item(({"garbage", "sewege"}), "The ground is litered in the stuff. "
        +"You notice pipes running from the jail into the alley dumping sewege.\n");

   add_item(({"pipes", "pipe"}), "The pipes stick out of the jail dumping "
        +"raw sewege everywhere. Pretty disguisting!\n");

   add_item(({"shadow", "shadows"}), "Looking up the alley you see shadows "
        +"dancing on the walls. Looking closer you think you see someone.\n");
           
   add_item("gate", "The gate is tall and blocks the way out.\n"); 
   
   add_cmd_item("gate", "open", "You try to open the gate but it is securely locked.\n"); 

   OUTSIDE;

   add_exit(TYR_JAIL + "alley1", "north", 0, 1);
   reset_room();
   
}


void
init()
{
    ::init();
    add_action("climb_gate", "climb");
}

int
climb_gate(string str)
{
	notify_fail("Climb what?\n");
    	if(str!="gate")
        	return 0;
       	
  	if (str == "gate")
     	{
        TP->catch_msg("You climb over the gate.\n");
        TP->move_living("climbing climbing over the gate.", "/d/Cirath/tyr/jail/jailentr1.c",1);
               
        return 1;
        }
        return 0;
}