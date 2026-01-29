/* forest7.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"

inherit  FORESTBASE;
#include "stream_drink.h"

object   animal;

void
reset_qualinesti_room()
{

    if ( !animal )
    {
        animal = random_animal();
        animal->move(TO, 1);
    }

}

void
create_forest()
{
    add_my_desc("You notice a shallow stream flowing from within the " +
        "bushes to the north and circling towards south.\n");
    
    add_item("stream",
        "The stream flows gently, circling among trees. " +
        "From time to time a small fish leaps from it, sending the drops of " +
        "water into the air.\n");
    add_item("water",
        "The water in the stream seems to be clear and cold.\n");
        
    add_cmd_item(({"stream", "water", "from stream"}),
        "drink", "@@drink_water");

    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "forest6.c", "west", 0, 2);
    add_exit(FDIR + "forest8.c", "east", 0, 2);
    add_exit(FDIR + "path5.c", "southwest", 0, 2);
    add_exit(FDIR + "path6.c", "south", 0, 2);
    add_exit(FDIR + "path7.c", "southeast", 0, 2);

    reset_qualinesti_room();
    
}
