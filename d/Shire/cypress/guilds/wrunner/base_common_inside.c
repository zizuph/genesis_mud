/*
 * This file file contains all the indoor common items Thalandrone
 * such as variations of buildings.
 * This way these routines aren't  spread over several files 
 * and makes maintaining these routines much easier.
 *
 * To use any of these routines, this file must be inherited 
 * by the base file, then simply call the routine(s) within 
 * the room definition.
 *
 * Example:

    void
    create_road_room()
    {

        set_add_houses("They are two storied and made of brick " +
            "and appear well kept. ");
    }
    
 * To pass nothing to the routine, simply pass "" in place of text.
 * By Finwe, July 2001
 *
 * 2001/07/18 Last update
 * 2011/07/19 Lavellan - added "inside" property.
 * 2011/07/20 Lavellan - Removed command_driver inherit.
 */
 
#include "/d/Shire/cypress/sys/defs.h"
//#include "../local.h"
inherit AREA_ROOM;
//inherit "/cmd/std/command_driver";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


/*
 * Each of these variables defines the respective
 * set_ routine within this file. To create a new 
 * routine, define it here.
 */

static string add_all_rooms = "",
              add_column_bldg = "",
              add_column_windows = "",
              add_column_walls = "";


/*
 * Function name : set_add_all_rooms
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_all_rooms()
{
    add_item(({"stone blocks", "white stone blocks"}),
        "The white stone blocks are hewn of white marble. They " +
        "are very large and perfectly square. They are polished " +
        "smooth and used in construction of the building. \n");
}



/*
 * Function name : set_add_column_bldg
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_column_bldg()
{
    add_item(({"columns", "column", "engaged column", 
            "engaged columns"}),
        "The engaged columns are set into the walls at regular " +
        "intervals. The bases are carved to resemble great roots " +
        "of trees. The pedestals are carved into life-like " +
        "trunks. The tops of the columns are bushy tree tops " +
        "that rise above the the walls about an arm's length. " +
        "On top of the trees rest the ceiling.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling is made of stone blocks. It is perfectly " +
        "seamless and polished smooth. It rests on the top of " +
        "the columns, forming gaps between the column tops and " +
        "the ceiling. The gaps allow fresh air and light to fill " +
        "the room. From the ceiling hang lights that glow with " +
        "an uncommon brilliance.\n");
    add_item(({"ground", "floor"}),
        "The floor is made of stone blocks. The floor is clean " +
        "and and textured lightly.\n");
    add_item(({"lights", "hanging lights"}),
        "The lights are hanging balls of crystal, decorated " +
        "with streaming clear gems that refract the light into a " +
        "rainbow of colors throughout the room.\n");
    add_item(({"crystals", "crystal", "balls of crystal"}),
        "The balls of crystal are fist size and made of clear " +
        "crystal. There is a magical light inside each one that " +
        "illuminates the room.\n");
    add_item(({"clear gems"}),
        "The clear gems decorate the lights, catching the light " +
        "and refracting it back as rainbows in the room.\n");
    add_prop(ROOM_I_INSIDE,1);
}

/*
 * Function name : set_add_column_walls
 * Arguments     : str: none
 * Description   : adds standard items to all rooms. 
 */

void set_add_column_walls(string str)
{
    add_item(({"walls", "wall"}),
        "The walls are made of large white stone blocks. There " +
        "are no visible joints or cracks between the blocks. " +
        "Set in regular intervals in the walls are engaged " +
        "columns. " + str + "\n");
}


/*
 * Function name : set_add_column_windows
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_column_windows(string str)
{
}

