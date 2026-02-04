/*
 * Modifications
 *   November 8, 2010 - Added reset room to allow missing sandal quest to
 *                      reset properly, Petros.
 */

#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Sparkle/area/city/lib/utility_functions";

#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

#define VOLCANODIR SORGUMDIR + "volcano/"

object ghost = 0;
string sandal_room = 0;

create_room()
{
    int i;
    set_short("cottage graveyard");
    set_long(
	"The crest of the hill is bleak and windswept.  Under a giant elm " +
	"tree black gravestones stick up through the snow like the decayed " +
	"fingernails of a gigantic corpse.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);
     
    add_item(({"tree", "trees", "elm", "elm tree"}),
       "The grotesque vine-covered tree silently waves its knotted " +
       "branches far aloft.\n"
    );
 
    add_item(({"grave", "graves", "gravestone", "tombstone"}), 
       "The black gravestones are very smooth and bear no markings.\n"
							      );

    add_exit(TOMBDIR + "gpath01", "north", 0);    
    add_exit(TOMBDIR + "cottage_garden", "west", 0);
    /*
    add_exit(VOLCANODIR + "grave_yard", "east", "@@go_east");
    */

    /*
     * Set up the sandal quest here
     */

    i = random(6) + 1;
    for (int room_index = 1; room_index <= 6; ++room_index)
    {
        string current_room = (TOMBDIR + "gpath0" + room_index);
        if (room_index == i)
        {
            sandal_room = current_room;        
            sandal_room->add_prop("_sandal_present", 1);
        }
        else
        {
            current_room->remove_prop("_sandal_present");
        }
    }

    reset_room();
}

go_east()
{
     write("That way is not open yet, but soon!\n");
     return 1;
}

/*
 * Function:    reset_room
 * Description: This reset_room will check to make sure that the 
 *              ghost will always be present because it is a quest
 *              npc. Once it is solved, it will disappear, until the
 *              next reset.
 */
public void
reset_room()
{
    ::reset_room();
    
    safely_load_master_file(TOMBDIR + "ghost");
    object * ghosts = object_clones(find_object(TOMBDIR + "ghost"));
    if (sizeof(ghosts) >= 1)
    {
        ghost = ghosts[0];
        ghosts[1..]->remove_object();
    }
        
    if (!objectp(ghost)) {
        ghost = clone_object(TOMBDIR+"ghost");
        ghost->move("/d/Terel/calathin/roads/road_s05");	 
    }	          
}
