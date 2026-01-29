#include <tasks.h>              
#include "/d/Emerald/defs.h"

inherit "/std/room";
void fall_down(object target);    // actual falling down code.


/*
 * Difficulty can be one of TASK_SIMPLE, TASK_ROUTINE, TASK_FORMIDABLE,
 * or TASK_IMPOSSIBLE. The last two require skill to even attempt.
 */

void
create_room()
{
    set_short("A steep cliff");
    set_long("   You are standing on a small foothold on the side of "+
	     "sheer cliff. It looks like you would have to climb to "+
	     "get either up or down from here.\n\n");
    
    add_prop(ROOM_I_INSIDE,0);   // outdoors room ... for pigeons, etc..
    
    add_item("cliff",
	     "Its a cliff. Looks pretty dangerous.\n");
    
}

void
init()
{
    ::init();
    add_action("climb_cliff", "climb");
}

int
climb_cliff(string str)
{

    if ( (member_array(str, ({"up", "down", "cliff"})))==-1)
    {
	notify_fail("Climb what?\n");
	return 0;
    }
    
    if ( (str=="up") || (str=="cliff") ) 
    {
	if (this_player()->resolve_task(TASK_FORMIDABLE, SS_CLIMB)) 
	{
	    write("You manage to climb up the cliff ...\n\n");
	    this_player()->move_living("up the cliff",UP_ROOM,0,0);
	    return 1;
	}
	else 
	{
	    fall_down(this_player());
	    return 1;
	}
    }
    else  
    {
	if (this_player()->resolve_task(TASK_FORMIDABLE, SS_CLIMB)) 
	{
	    write("You manage to climb down the cliff ... \n\n");
	    this_player()->move_living("down the cliff",DOWN_ROOM,0,0);
	    return 1;
	}
	else 
	{
	    fall_down(this_player());
	    return 1;
	}
    }
} // end of function
    
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
     
	

    
