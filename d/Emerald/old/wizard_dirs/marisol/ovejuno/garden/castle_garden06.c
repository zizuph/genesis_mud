/* Manor's Garden VI
* Coded by Marisol (8/28/97)
 * Modified by Marisol (07/27/98) to be used in the village of Ovejuno
 * in Emerald
* Copyright (c) Marisol Ramos 1997 */

#include "defs.h"
inherit CASTLE_GARDEN;

void
create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. There is an "+
        "intersection here. The east path goes to the center of the "+
        "the garden and the north one continues to the rest of the "+
        "enclosure. The path is overgrown with weeds and tall grass. On "+
        "both sides of the path, a blanket of pale-purplish flowers "+ 
        "cover the ground intermingling with the weeds and "+
        "grass. The air is scented with a rich sweet aroma.\n");

    add_item(({"flowers", "pale-purplish flowers"}),
         "This is Lavander. It is a very fragant plant with spikes "+
         "of pale-purplish flowers and yield an aromatic oil known "+
         "as oil of lavander. Here in this garden, rotten flowers "+
         "decay on the ground and new ones blossoms releasing a very "+
         "rich sweet aroma.\n");

    add_item("plants",
        "The ground is covered with many pale-purplish flowers, "+
        "some blossiming in the plants and some rotting in the ground. "+
        "Breaking between the soft purple flowers are yellow flowers "+
        "from the weeds that have invaded this garden.\n");

    add_exit("castle_garden10", "east");
    add_exit("castle_garden11", "north");
    add_exit("castle_garden04", "south");

}
