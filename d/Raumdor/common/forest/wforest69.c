/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

int open = 0;

void
create_room()
{
    forest_details = " Here there are what look like the remains of an " +
        "old tower.";
    ::create_room();
    add_item(({"tower", "remains", "ruins"}),
            "There are stone blocks lined in a nice  circle here. " +
            "The blocks seem to be charred black, like they were once " +
            "in a fire. In the center of the circle is one large stone " +
            "that resembles an altar.\n");
    add_item(({"altar", "stone", "large stone"}),
            "The altar has what looks like fresh blood stains"+
            " on it. You notice a green gem embedded at the bottom of it.\n");
    add_item(({"gem"}), "The gem is a dull green color.\n");
    add_exit(FOREST_DIR + "wforest83","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest70","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest56","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest54","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest68","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","northwest",0,FOREST_FATIGUE);
    seteuid(getuid(this_object()));
}

void
init()
{
    ::init();
    add_action("gem_press", "press");
    add_action("gem_push", "push");
}

int
gem(string action, string str )
{
    if (str != "gem")
    {
	    NF(action + " what?\n");
	    return 0;
    }
    if(open == 1)
    {
	    NF("The staircase is already open.\n");
	    return 0;
    }
    write("You press the green gem on the altar.\n");
    say(QCTNAME(TP)+ " presses the green gem on the altar.\n");  
    
    TO->open_passage();
    return 1;
}


int 
gem_press(string str)
{
    return gem("Press", str);
}

int
gem_push(string str)
{
    return gem("Push", str);
}

void
close_passage()
{
    if(open)
    {
    	tell_room(TO,"The altar moves back into position, closing the secret "+
	      "passage.\n");
    	remove_exit("down");
    	open = 0;
    	call_other(TEMPLE_DIR + "stairs1","close_passage");
    }
}

void
open_passage()
{
    if(!open)
    {
    	tell_room(TO,"The altar moves to the side, revealing a secret "+
	      "staircase leading down!\n");
    	open = 1;
    	set_alarm(30.0,0.0,"close_passage");
	    TO->add_exit(TEMPLE_DIR + "stairs1","down","@@check@@",2);
	    call_other(TEMPLE_DIR + "stairs1","open_passage");
    }
}
