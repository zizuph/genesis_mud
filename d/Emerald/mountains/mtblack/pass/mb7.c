/* MB7.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"
#include <tasks.h>

inherit MBLACK_DIR + "pass/path_common";

#include "/d/Emerald/defs.h"

#define UP_ROOM MBLACK_DIR + "/pass/mcliff1.c"

void
create_path()
{
	set_short("At the base of the Black Cliffs");
	add_my_desc("The path ends at the base of the cliffs. The mist "+
		"enshrouds them making the features hard to make out. "+
		"All you can really see is that they are very steep.\n\n");

	add_prop(ROOM_I_INSIDE,0);
	
    add_item(({"cliffs", "cliff"}), "As you look toward the "+
		"cliffs the mist clears completely and you see them clearly "+
		"for the first time. They rise straight out of the ground "+
		"to a height of at least 200 meters. The rock of the cliffs "+
		"is so black as to appear to be the absence of light itself. "+
		"Yet as you look closely you see a faint shimmer of silver "+
		"flecks.  Suddenly the air shifts and the cliffs are "+
		"enshrouded with mist again.\n");
	add_item(({"flecks", "silver flecks"}), "The mist has moved in again "+
		"and you can't make out the silver flecks you thought you "+
		"saw.\n");

	add_exit(MBLACK_DIR + "pass/mb6", "southwest",0,0);	
	
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

    if ( (member_array(str, ({"up", "cliff"})))==-1)
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
	    write("The cliff is too steep for you to climb\n");
	    return 1;
	}
    }
} 
    
