/*
 * ELEVATOR_TOP.c
 * This is the room outside the top of the elevator.
 * Alaron December 1996
 */

#include <tasks.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lake/elevator.h"
#include "defs.h"

inherit "/std/room";

#define ELEV "/d/Emerald/lake/elevator"
#define DOWN_ROOM LAKE_DIR + "mguide_room"
#define FALLEN_ROOM LAKE_DIR + "outside_elevator"

void fall_down(object target);

void
create_room()
{
    set_short("Small clearing near a road");
    set_long("   You are standing in a small clearing at the edge of "+
	     "a hard, packed dirt road. The road meanders to the east "+
	     "and west of here, following the cliff face to the south "+
	     "and the edge of an impressive forest bordering the north. "+
	     "The southern edge of the clearing is dominated by a huge "+
	     "section of the cliff face which rises up above the rest, "+
	     "forming a dome shape which hovers over the road. In the "+
	     "center of the dome shape is an incredibly large set of "+
	     "silver double doors. The clearing and road nearby is "+
	     "surrounded by low, wild growing greenery.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"road", "dirt road", "packed dirt road", "hard road"}),
	     "The road just north of the clearing runs east-west "+
	     "with the cliff top running parallel on the southern "+
	     "side of the path as an immense, towering forest looms over "+
	     "the road on the north side.\n");

    add_item( ({"cliff", "cliff face", "cliff top"}),
	     "The cliff face rises up out of the ocean inlet far "+
	     "below to come to an angular halt above the road, forming "+
	     "a dome-shaped hill which houses a set of silver "+
	     "double-doors. Just below the edge, you can see a small cave.\n");

    add_item( ({"cave", "small cave"}), 
             "If you could just climb down to it, you think you could "+
             "enter the cave.\n");

    add_item( ({"forest", "impressive forest", "looming forest", "woods",
		"north"}),
	     "The forest runs parallel to the road for quite a ways in "+
	     "either direction. The edge of the forest rests a good "+
	     "distance back from the road, separated by fields of "+
	     "greenery and bushes.\n");

    add_item( ({"low greenery", "greenery", "shrubs", "bushes",
		"shrubbery"}),
	     "The greenery surrounding the clearing and the road "+
	     "is wild and overgrown, tendrils of dark, thick green "+
	     "plants reach out from the forest floor in an attempt "+
	     "to swallow up the moist soil of the road.\n");

    add_item( ({"doors", "silver doors", "double doors", 
		"door", "silver double doors", "silver door",
		"dome", "dome shape"}),
	     "The shadowed doors contained within the dome-shape "+
	     "of risen stone loom before you. They are impressive "+
	     "and made of pure silver. Were it not for the overhang "+
	     "of stone above them, they would be gleaming brilliantly "+
	     "in the sunlight. In the middle of the doors you notice "+
	     "a carved setting containing an emerald. The doors "+
	     "are @@open_or_shut@@.\n");

    add_item(({"emerald", "setting", "carved setting"}),
	     "The emerald is a fine cut. It has been delicately cut "+
	     "and shaved to form a diamond-shape carefully inlaid into "+
	     "its silver setting.\n"+
	     "The emerald is @@emerald_desc@@.\n");

    add_exit(LAKE_DIR + "elevator", "south", "@@determine_enterable@@");
    add_exit(KROAD_DIR + "road0", "north", 0);
  
}

string
emerald_desc()
{
    object elevroom;

    if (LOAD_ERR(ELEV)) {
	return "broken and smashed";
    }

    elevroom = find_object(ELEV);

    if ((elevroom->query_move_status()!=MOVE_MOVING) &&
	(elevroom->query_level()==3)) {
	return "glowing brilliantly";
    } else return "dim and unpolished";
}

int
elev_is_here()
{
    object elevroom;

    if (LOAD_ERR(ELEV)) return 0;

    elevroom=find_object(ELEV);

    if ( (elevroom->query_move_status()!=MOVE_MOVING) &&
	(elevroom->query_level()==3)) return 1;
    else
	return 0;
}

int
determine_enterable()
{
    if (LOAD_ERR(ELEV)) 
    {
	write("There seems to be something wrong here. Notify a wizard.\n");
	return 1;
    }

    if (elev_is_here()) return 0;
    else {
	write("The silver doors are sealed shut.\n");
	return 1;
    }
}

string
open_or_shut()
{
    if (elev_is_here()) return "open";
    else return "shut";
}
    
init()
{
    ::init();
    add_action("push_emerald", "push");
    add_action("push_emerald", "press");
    add_action("push_emerald", "touch");
    add_action("push_emerald", "hit");
    add_action("climb_cliff", "climb");
    LOAD_CLONE_HANDLER("/d/Emerald/kroad/clone_handler");
}

int
push_emerald(string str)
{
    object elevroom;

    if ( (member_array(str, ({"emerald", "stone", "glowing emerald"})))==-1)
    {
	notify_fail("Push what?\n");
	return 0;
    }
	
    if (LOAD_ERR(ELEV)) {
	notify_fail("There is something wrong here. Notify a wizard.\n");
	return 0;
    }

    elevroom=find_object(ELEV);

    if (elev_is_here()) {
	notify_fail("You press your hand against the emerald stone on the "+
		    "open doors, but nothing happens.\n");
	return 0;
    } else {
	write("You press your hand against the dim emerald stone. It "+
	      "glows briefly and you feel a flash of warmth against "+
	      "your skin.\n");
	elevroom->call_elevator(1);
	return 1;
    }
}


int
climb_cliff(string str)
{

    if ( (member_array(str, ({"down", "cliff"})))==-1)
    {
	notify_fail("Climb what?\n");
	return 0;
    }
    
    if ( (str=="down") || (str=="cliff") ) 
    {
	if (this_player()->resolve_task(TASK_ROUTINE, ({SS_CLIMB,SS_DEX}))>0) 
	{
	    write("You manage to climb down the cliff and enter a small cave.\n\n");
	    this_player()->move_living("down the cliff",DOWN_ROOM,0,0);
	    return 1;
	}
	else 
	{
	    fall_down(this_player());
	    return 1;
	}
    }
} 

void
fall_down(object target)
{
    target->catch_msg("You struggle against the side of the cliff "+
		      "but lose your hold ....\n\nYou slip and fall!!\n\n");
    target->heal_hp( -(target->query_hp()/2) ); // take away 50% of hits! heh
        
    tell_room(FALLEN_ROOM, QCTNAME(target)+" comes crashing down the "+
	      "side of the cliff!!\n");
    
    target->move_living("falling down the cliff", FALLEN_ROOM, 0, 0);
}


