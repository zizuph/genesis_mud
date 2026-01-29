/*
* Created by: Luther
* Date: August 2001 
*
* File: /d/Cirath/tyr/jail/alley.c
* Comments: Entrance to the alley by the jail.
*/

#pragma strict_types

inherit "/std/room";
#include <stdproperties.h>
#include <ss_types.h>
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#define ROPE_WALL "rope_wall"

int i, u, r;
object ob1, ob2, ob3, ob4, ob5, ob6, ob7, ob8, ob9;

void
jalla_func();

void
jalla_func2(object foo);

void
jalla_func3();

void
jalla_func4(object again);

void
jalla_func5();

void
jalla_func6(object reap);

void
reset_room()
{ 	
    object npc = present ("zarth", TO);
    i = 0;
    u = 0;
    r = 0;
    if(!objectp(npc))
	{
    	    bring_room_mob("zarth", TYR_NPC+"q_res.c", 1, 1);
	}
}

void
create_room()
{
   set_short("Alley beside jail");
   set_long("You stand in a dark and dismal alley. Garbage litters "
        +"the ground and sewege is everywhere. The occasional brick "
        +"falls to the ground from above. Looking up the alley you see "
        +"shadows dancing around.\n");
 
   add_item(({"bricks", "athasian bricks", "walls", "brick"}), "The walls "
        +"to the jail seem in pretty bad shape. Loking up you can see a wall "
        +"almost completely gone from decay. You hope noone throws a brick "
        +"down on you.\n");

   add_item(({"garbage", "sewege"}), "The ground is litered in the stuff. "
        +"You notice pipes running from the jail into the alley dumping sewege.\n");

   add_item(({"pipes", "pipe"}), "The pipes stick out of the jail dumping "
        +"raw sewege everywhere. Pretty disguisting!\n");

   add_item(({"walls", "wall"}), "The building walls are in bad shape "
        +"and you wouldn't want to try and climb them.\n");
  
   OUTSIDE;

   add_exit(TYR_JAIL + "alley", "south", 0, 1);
   reset_room();   
}

void
init()
{
    ::init();
    add_action("climb_wall", "climb");
}

int
climb_wall(string str)
{
	object obj, rp, *ob; 
	int i;
   	notify_fail("Climb what?\n");
    	if(str!="wall")
        	return 0;
       	if (str == "wall")
     	{
     	
     	if (TP->query_wiz_level())
     	{
     		TP->catch_msg("You climb up to the jail.\n");
     		TP->move_living("M", TYR_JAIL + "jail2_5.c",1);		    
     		return 1;
     	}	
     		
        ob = deep_inventory(TP);
    	for(i = 0; i < sizeof(ob); i++)
		if(ob[i]->id("_rope_"))
		{
		    TP->catch_msg("You toss the rope up the wall, and up through "+
		      	"the small opening.\n");
		    tell_room("/d/Cirath/tyr/jail/jail2_5.c", "You see a rope thrown in the small hole "
		  	+"of the wall, then you hear someone climbing up the wall outside\n", TP);		
		    TP->move_living("climbing up the wall.\n", TYR_JAIL + "jail2_5.c",1);
		    TP->add_prop(ROPE_WALL, 1); 
		    return 1;
		}
	TP->catch_msg("You try to climb the wall but only succeed in falling down.\n");
	return 1;
	}
return 0;
}

void
jalla_func()
{	
	if (!i)
	{
	if (!ob1 || !ob2 || !ob3 || !ob4)
	{
     write("Some guards jump out of the shadows.\n");
   		
        ob1 = clone_object("/d/Cirath/tyr/npc/zarth_guard.c");
	ob1 -> arm_me();
    	ob1 -> move(TO);
         	
        ob2 = clone_object("/d/Cirath/tyr/npc/zarth_guard.c");
        ob2 -> arm_me();
    	ob2 -> move(TO);
		
	ob3 = clone_object("/d/Cirath/tyr/npc/zarth_guard.c");
        ob3 -> arm_me();
    	ob3 -> move(TO);
	
        ob4 = clone_object("/d/Cirath/tyr/npc/zarth_guard.c");
        ob4 -> arm_me();
    	ob4 -> move(TO);
	i = 1;
	}
    }
}

void
jalla_func2(object foo)
{    
	if (ob1 || ob2 || ob3 || ob4)
	foo->catch_msg(" A guard stands in your way forcing you to " +
		"attack him instead.\n");
	if (ob1)
	{
		foo->attack_object(ob1);
	}
	if (ob2)
	{
		foo->attack_object(ob2);
	}
	if (ob3)
	{	
		foo->attack_object(ob3);
	}
	if (ob4)
	{
		foo->attack_object(ob4);
	}
}

void
jalla_func3()
{	
	if (!u)
	{
	if (!ob5 || !ob6 || !ob7 || !ob8)
	{
     	write("Some lancers arrive from the south.\n");
   		
        ob8 = clone_object("/d/Cirath/tyr/npc/zarth_lancer.c");
	ob8 -> arm_me();
    	ob8 -> move(TO);
         	
        ob5 = clone_object("/d/Cirath/tyr/npc/zarth_lancer.c");
        ob5 -> arm_me();
    	ob5 -> move(TO);
		
	ob6 = clone_object("/d/Cirath/tyr/npc/zarth_lancer.c");
        ob6 -> arm_me();
    	ob6 -> move(TO);
	
        ob7 = clone_object("/d/Cirath/tyr/npc/zarth_lancer.c");
        ob7 -> arm_me();
    	ob7 -> move(TO);
	u = 1;
	}
    }
}

void
jalla_func4(object again)
{    
	if (ob5 || ob6 || ob7 || ob8)
	again->catch_msg(" A lancer stands in your way forcing you to " +
		"attack him instead.\n");
	if (ob5)
	{
		again->attack_object(ob5);
	}
	if (ob6)
	{
		again->attack_object(ob6);
	}
	if (ob7)
	{	
		again->attack_object(ob7);
	}
	if (ob8)
	{
		again->attack_object(ob8);
	}
}

void
jalla_func5()
{	
	if (!r)
	{
	if (!ob9)
	{
     	write("A keen male human arrives.\n");
   	
        ob9 = clone_object("/d/Cirath/tyr/npc/zarth_reaper.c");
        ob9 -> arm_me();
    	ob9 -> move(TO);
	r = 1;
	}
    }
}

void
jalla_func6(object reap)
{    
	if (ob9)
	{	
		reap->attack_object(ob9);
	}	
}
