/* forest32.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>

inherit FORESTBASE;

#include "stream_drink.h"

object elf1;

void
reset_qualinesti_room()
{
    if (!elf1)
    {
        elf1 = clone_object(STD + "scout_base");
        elf1->move(TO);
        elf1->command("hide");
    }
    
}

void
create_forest()
{
    add_my_desc("There is a shallow stream flowing through the forest.\n");

    add_item("stream",
        "The stream flows gently, circling among trees. " +
        "From time to time a small fish leaps from it, sending the drops of " +
        "water into the air.\n");
    add_item("water",
        "The water in the stream seems to be clear and cold.\n");
        
    add_cmd_item(({"stream", "water", "from stream"}),
        "drink", "@@drink_water");
            
    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);
    
    add_exit(FDIR + "forest29.c", "northwest", 0, 2);
    add_exit(FDIR + "forest31.c", "west", 0, 2);
    add_exit(FDIR + "forest33.c", "east", 0, 2);
    add_exit(FDIR + "forest35.c", "southeast", 0, 2);
    add_exit(FDIR + "path5.c", "north", 0, 2);
    add_exit(FDIR + "path6.c", "northeast", 0, 2);

    reset_qualinesti_room();
    
}
