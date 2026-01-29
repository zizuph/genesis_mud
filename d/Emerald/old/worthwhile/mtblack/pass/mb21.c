/* MB21.c, the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"
#include <tasks.h>

inherit MBLACK_DIR + "pass/pass_common";

void
create_pass()
{
	set_short("A trial near the summit of Mt. Black");
   	
	set_long("   You have reached the summit of the pass. The "+
           "actual summit of the mountain is to the east and "+
           "climbs several hundred feet to the jagged peak. "+
           "Any attempt to climb to that peak would require "+
           "genuine climbing equipment and a very high skill.\n\n");

  	 add_item(({"peak", "summit", "mount black"}), "The peak towers "+
           "hundereds of feet above your head. You would have to be "+
           "crazy or very skilled to attempt to climb it.\n");
   
	add_exit(MBLACK_DIR + "pass/mb20", "southwest",0,0);
	add_exit(MBLACK_DIR + "mb22", "north", "@@block");
}

int
block()
{
    write("You walk north but the path winds around and brings "+
	"you right back where you started. You get the feeling that "+
	"someone does not want you approaching the Volcano just yet.\n");
    return 1;
}
string
search_exit(object player, string str)
{
    if ( str == "cliffs" )
     {
       if ( (member_array("up", query_exit_cmds()))!=-1)
        {
           return("Your search reveals nothing more.\n");
         }
       add_exit("/d/Emerald/mountains/pass/mcliff5", "up");
        return("After carefully searching the cliffs, you think you "+
		"can see a way to get up to a ledge. Perhaps once "+
		"there you can climb further.\n");
     }
    return 0;
}
