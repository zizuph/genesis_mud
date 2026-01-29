/* mcliff2.c the southern cliff of Mt. Black*/
/* Geraden 22 January 1997 */

#include <tasks.h>              
#include "/d/Emerald/defs.h"

inherit MBLACK_DIR + "pass/cliff_common";

#define FALLEN_ROOM MBLACK_DIR + "pass/mb7"
#define UP_ROOM MBLACK_DIR + "pass/mcliff3"
#define DOWN_ROOM MBLACK_DIR + "pass/mcliff1"

void fall_down(object target);

void
create_cliff()
{
	set_short("Niche");
	add_my_desc("You stop in a small niche barely wide enough to cling to and "+
		"decide to wait a moment before you continue.\n\n");
	
	add_item(({"niche"}), "The niche is so narrow that you can only "+
		"get one foot and half of your body into it, but it "+
		"suffice to hold you while you take a break.\n");

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
	if (this_player()->resolve_task(TASK_ROUTINE, ({SS_CLIMB,SS_DEX}))>0) 
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
	if (this_player()->resolve_task(TASK_ROUTINE, ({SS_CLIMB,SS_DEX}))>0) 
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

