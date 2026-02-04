/*
 * Modifications
 *   November 8, 2010 - Added reset room to allow missing sandal quest to
 *                      reset properly, Petros.
 */
// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Sparkle/area/city/lib/utility_functions";

object ghost = 0;
string sandal_room = 0;

void
create_room()
{
    int i;
    set_short("hill overlooking graveyard");
    set_long(
	"The crest of this hill is frozen, bleak, and windswept. "+
    "North is a path through a small family graveyard "+
    "under a giant elm tree. "+
	"You can see black gravestones stick up through the snow like the " +
	"decayed fingernails of a gigantic corpse.\n"    );

    add_prop(ROOM_I_INSIDE, 0);
     
    add_item(({"tree", "trees", "elm", "elm tree"}),
       "The grotesque vine-covered tree silently waves its knotted " +
       "branches far aloft.\n"
    );
 
    add_item(({"grave", "graves", "gravestone", "tombstone", "graveyard"}), 
       "The black gravestones are very smooth and bear no markings "+
       "that you can see from here.\n");

    add_item(({"snow", "layer of snow"}), "A thin layer of snow covers "+
        "the ground.\n");
		
    add_exit("gpath01", "north", 0);    
    add_exit("cottage_garden", "west", 0);
	add_exit("graveyard_forest", "east", 0);


    /*
     * Set up the sandal quest here
     */

    i = random(6) + 1;
    for (int room_index = 1; room_index <= 6; ++room_index)
    {
        string current_room = ("/d/Terel/common/moor/cottage/gpath0" + room_index);
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
	
    safely_load_master_file(MOBDIR + "ghost");
    object * ghosts = object_clones(find_object(MOBDIR + "ghost"));
    if (sizeof(ghosts) >= 1)
    {
        ghost = ghosts[0];
        ghosts[1..]->remove_object();
    }
        
    if (!objectp(ghost)) {
        ghost = clone_object(MOBDIR+"ghost");	
        ghost->move("/d/Terel/calathin/roads/road_s05");	
    }	          
}
