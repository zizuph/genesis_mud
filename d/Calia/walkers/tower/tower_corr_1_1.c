/* A corridor on the first floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

#define OUTSIDE "/d/Calia/walkers/tower/tower_out_1"

public string outside();

create_room()
{
    set_short("Tower Corridor");

    set_long(corridor_desc + " " + basic_desc + " The corridor continues" +
        " to the west, while a draped archway to the east leads out of the" +
        " Tower.\n");
    add_item(({"drape", "drapes"}), "The drapes are dark, but completely" +
        " transparent. They look light, but are hanging unruffled by the" +
        " outside weather.\n");
    add_item("archway", "The archway leads out of the Tower. You can easily" +
        " see outside through the transparent drapes.\n");
    add_item(({"the outside", "outside", "out"}), "@@outside@@\n");

//  Add exit to outside.

    add_exit(TOWER + "tower_corr_1_2.c", "west", 0, 1);
    
    OUTSIDE->load_me();

    make_college_room();
}

string
outside()
{
    object outside = find_object(OUTSIDE);
    object *outside_live;

    if (outside->query_prop(ROOM_I_LIGHT) > 0 
        || TP->query_prop(LIVE_I_SEE_DARK))
    {
        outside_live = FILTER_LIVE(all_inventory(outside));

        if(sizeof(outside_live))
        {
            return "You see " +
            COMPOSITE_ALL_LIVE(outside_live) + " standing outside.");
        }
        else
        {
            return "You see noone outside.";
        }
    }
    else
    {
        return "The outside of the Tower is cast in darkness.";
    }
}