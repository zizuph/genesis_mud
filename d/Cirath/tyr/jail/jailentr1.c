/*
* Created by: Zayn
* Date: March 97 
*
* File: /d/Cirath/tyr/jail/jailentr1.c
* Comments: Entrance to the jail.
*	    Edited by luther.
*/


#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd.c", 2, 1);
}

void
create_room()
{
   set_short("Path to Jail");
   set_long("You are on a side path which stretches towards the "
        +"jail of Tyr. Further to the northwest you see the tall "
        +"tower that is the jail of Tyr. Even at this distance you "
        +"can feel the chill of evil exuded by the years of torture "
        +"that have taken place here. The tower has large barred "
        +"windows starting on the second floor and when you listen "
        +"carefully, you are almost positive you can hear faint screams "
        +"of pain echoing from within. You can see where the building "
        +"might have been a beautiful home once, but that is all gone.\n");
 
   add_item(({"bricks", "athasian bricks", "walls"}), "The walls are made"
        +"of very thick athasian bricks. Bashing through those walls "
        +"would be impossible, so this building would be very suitable"
        +"for a prison.\n");

   add_item("building", "Once the former home of High Templar Pandora, this "
        +"old building now serves as the new jail. A 2 story building with a "
        +"alley on one side.\n");

   add_item("gate", "The gate is tall and blocks the way into the alley.\n"); 
   
   add_item("alley", "A small alley on the right side of the jail. It looks "
        +"dark and dismal with a tall closed gate. Shadows flicker on the walls "
        +"and you think you catch a glimpse of someone in there.\n");
        
   add_cmd_item("gate", "open", "You try to open the gate but it is securely locked.\n"); 

   ADD_SUN_ITEM
     
   add_exit(TYR_SLAVE + "rd_pe_03", "west", 0, 1);
   add_exit(TYR_JAIL + "jailentr2", "northeast", 0, 1);
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
	object guard = present ("guard", TO);
   	notify_fail("Climb what?\n");
    	if(str!="gate")
        	return 0;
       	
  	if (str == "gate" && (!objectp(guard)))
     	{
        TP->catch_msg("You climb over the gate.\n");
        TP->move_living("climbing climbing over the gate.", "/d/Cirath/tyr/jail/alley.c",1);
               
        return 1;
        }
        else
      	{
      		if (this_player()->query_wiz_level())
      		{
      			TP->catch_msg("You climb over the gate.\n");
      			TP->move_living("climbing climbing over the gate.", "/d/Cirath/tyr/jail/alley.c",1);
      			return 1;	
      		}	 
        TP->catch_msg(QCTNAME(guard)+ " prods you along, saying stay on the path. "
      		+"The alleys can be dangerous.\n");
        return 1;
	}   

    return 0;
}