/*
 * The Beach of Faerie, beneath the second pier
 * By Finwe, April 2005
 */
 
#include "defs.h"
#include <macros.h>
 
inherit BEACH_BASE;

void
create_beach_room()
{
    FIXEUID;
    set_short("A wide road at the base of a ridge");
    set_long(short() + ". " + s_desc_sky_outside_sky() +" The road is well " +
        "travelled and runs north towards the lake. It leads south up " +
        "the ridge and disappears. Trees and bushes surround the road. " +
        "To the north you see some piers and a beach.\n");

    reset_room();
    set_add_sea();
    set_add_forest();

    add_item(({"road"}),
        "It is wide and packed hard from constant traffic. The road " +
        "runs north towards the lake and winds its way south up and " +
        "into the ridge.\n");
    add_item(({"bushes"}),
        "The bushes are waist high and are healthy looking. They grow " +
        "scattered around and on either side of the road.\n");
    

    add_exit(FOREST_DIR + "landing", "north");
    add_exit(FOREST_DIR + "road20", "south");
}
void
reset_room()
{
}
