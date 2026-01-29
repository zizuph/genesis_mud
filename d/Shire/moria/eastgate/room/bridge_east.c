/*
 * First Hall in Moria
 * /d/Shire/moria/eastgate/bridge_east.c
 *
 * Varian - May, 2020
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit EG_STD + "base";

#define BRIDGE 

public string desc();

/*
 * Function name:        create_eg_room()
 * Description  :        Creates a room in Moria
 */

nomask void 
create_eg_room() 
{    
    set_items_chamber();
    set_items_firsthall();

    set_short("First Hall of Moria");
    set_long("@@desc@@"); 

    add_item( ({"bridge", "long bridge", "narrow bridge"}),
        "This bridge spans a massive chasm to the west\n.");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast"}),
        "The walls appear to be solid in that direction, you " +
        "will need to try a different direction.\n");

    add_exit(EG_ROOM + "gate", "east", "@@stairs@@", 0, 0);

    reset_room();
}

/*
 * Function name:        desc
 * Description  :        Long description of the room
 */
string
desc()
{
    string long_desc = "You are in the first hall of Moria";

    if (this_player()->query_skill(SS_MORIA_MINE) > 10 )
        long_desc += " which rests on the first level, ";
    else
        long_desc += ", ";
        
    long_desc += "before";

    if (this_player()->query_skill(SS_MORIA_LORE) > 10 )
        long_desc += " the long, narrow bridge of Khazad-Dum ";
    else
        long_desc += " a long, narrow bridge ";

    long_desc += "which stretches across a great chasm.";

    return (long_desc + "\n");
}
/*desc*/

/*
 * Function name:        stairs
 * Description  :        Provides a description for climbing the stairs
 */
int
stairs()
{
    write("You climb up the massive stone steps towards the Great " +
        "Gates of Moria.\n");
    say(QCTNAME(TP) + " climbs up the massive stone steps.\n");
}
/*stairs*/

