/* MB13.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"
#include <tasks.h>

inherit MBLACK_DIR + "pass/pass_common";

#define DOWN_ROOM MBLACK_DIR + "pass/mcliff4"
#define FALLEN_ROOM MBLACK_DIR + "pass/mb7"

void fall_down(object target);

void
create_pass()
{
	set_short("A trail near the summit of Mt. Black");
	add_my_desc("The path is not steep, but it is very narrow.\n\n");

	add_exit(MBLACK_DIR + "pass/mb14", "northeast",0,0);
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

    if ( (member_array(str, ({"down", "cliff"})))==-1)
    {
	notify_fail("Climb what?\n");
	return 0;
    }
    
    if ( (str=="down") || (str=="cliff") ) 
    {
	if (this_player()->resolve_task(TASK_ROUTINE, ({SS_CLIMB,SS_DEX}))>0) 
	{
	    write("You manage to climb down the cliff ...\n\n");
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


