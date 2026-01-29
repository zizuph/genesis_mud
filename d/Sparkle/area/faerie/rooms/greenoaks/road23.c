/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit TOWN_BASE;

void
create_town_room()
{
    set_short("A plaza in southern Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is wide " +
        "and frequently visited by many elves. Trees surround the plaza, " +
        "forming a circular crown. A square building stands north of " +
        "the plaza.\n");

    set_add_road();
    set_add_trees();
    set_add_forest();
    set_add_plaza();
    set_add_plain_bldg("It is wide and sits north of the road.\n");

    add_item(({"northern building", "wide building", "north building"}),
        "The building is large and square. Unlike most other buildings, " +
        "there aren't too many trees around it.\n");
    add_item(({"crown", "circular crown", "circle of trees", "ring of trees"}),
        "This is a series of trees that encircle the place. They are " +
        "tall and form a circle around the plaza an seem to crown it.\n");

    add_exit(GO_DIR + "front", "south");
    add_exit(GO_DIR + "road22", "west");
    add_exit(GO_DIR + "road20", "northeast");


}

/*
 * Function name: init
 * Description:
 */
public void
init()
{
    ::init();

}
