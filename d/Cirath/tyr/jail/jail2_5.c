/*
* Created by: Luther
* Date: 12 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_5.c
* Comments: Standard corridor in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 1, 1);
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("The corridor makes a ninety degree turn here, with a  "
		+"corridor intersecting it. There is a window in the east "
		+"wall. This part of the jail seems to be in big need of "
		+"repair. The corridor is lit by torches that are fastened "
		+"to the walls.\n");

	add_item(({"cell", "cells"}), "There is a cell to the north and south of "
		+"here. The east wall does not look good, you hope prisoners "
		+"do not try and escape through the holes in it.\n");

	add_item("corridor", "The corridor runs from the northwest to the "
                +"southwest. It looks well used, guards patrol the corridor "
                +"regulary.\n");

	add_item("window", "Looking out the window you can see a alley. "
		+"But you see just as much by looking at the wall. It "
		+"could fall down at any moment.\n");

	add_item("alley", "Looking out the wall you see a alley down below. "
		+"You get a weird felling someone is down there in the shadows "
		+"looking up at you.\n");

	add_item("wall", "The wall has many holes in it and should be repaired. "
		+"There are a few big openings that someone could climb through. "
		+"Atleast the window still has bars on it.\n");

	add_item("someone", "Looking closely down towards the alley, you can see movement "
		+"in the shadows. There must be someone down there watching you.\n");
		
	add_item(({"opening", "openings", "hole", "holes"}), "The wall has two big holes "
		+"in it. The bigger one looks extrememly dangerous and the smaller one "
		+"looks somewhat more safe.\n");	
		
	add_item("bigger hole", "The bigger hole has alot of jagged corners and sharp  "
		+"objects sticking everywhere. You would not want to try and escape "
		+"by that hole if there was a fire in the building.\n");
		
	add_item("smaller hole", "The smaller hole looks like someone cut a oval hole in the "
		+"bottom of the wall. It almost looks possible to climb out that way. "
		+"But you would need a rope or something to do that. Unless you want to fall "
		+"a good 25 feet.\n");	
			
	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "jail2_12.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "cell2_6.c", "north", 0,1);
	add_exit(TYR_JAIL + "cell2_8.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail2_4.c", "southwest", 0,1);
	reset_room();
}

void
init()
{
    ::init();
    add_action("climb_down", "climb");
}

int
climb_down(string str)
{
	object obj, rp, *ob; 
	int i;
   	notify_fail("Climb down what?\n");
    	if(str!="down small hole")
        	return 0;
       	if (str == "down small hole")
     	{
     		
     	if (TP->query_wiz_level())
     	{
     		TP->catch_msg("You climb down to the alley.\n");
     		TP->move_living("M", TYR_JAIL + "alley1.c",1);		    
     		return 1;
     	}     		
        ob = deep_inventory(TP);
    	for(i = 0; i < sizeof(ob); i++)
		if(ob[i]->id("_rope_"))
		{
		    TP->catch_msg("You tie the rope to the wall, and climb down through "+
		      	"the small opening.\n");
		    tell_room("/d/Cirath/tyr/jail/alley1.c", "You see a rope thrown out a hole in "
		  	+"the jail wall, then someone starts climbing down from it\n", TP);		
		    TP->move_living("through the small opening after he ties a rope to the wall.\n" 
		    	+"A guard patrol notices the rope and removes it.\n", TYR_JAIL + "alley1.c",1);
		    tell_room("/d/Cirath/tyr/jail/alley1.c", "The rope is hauled back up\n", TP);		
			    ob[i]->remove_object();
		    
		    
		    return 1;
		}
	TP->catch_msg("You climb out the small hole. With nothing to hold you, you fall to the "
		+"ground on the outside. That was extremely painfull.\n");
	tell_room("/d/Cirath/tyr/jail/alley1.c", "You hear a loud scream from up the wall\n", TP);		
	TP->move_living("climbing out the small opening.\n" 
		    	+"A guard patrol notices and laughs.\n", TYR_JAIL + "alley1.c",1);	
	
    	TP->heal_hp(-(450 + random(250)));
    	return 1;
	}
return 0;
}