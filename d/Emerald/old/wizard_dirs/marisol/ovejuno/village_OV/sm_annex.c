/* The smith's other room
 * Coded by Marisol (06/01/98)
 * Modified by Marisol (08/04/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h";
#include <stdproperties.h>
#include "defs.h"

void
create_emerald_room()
{

    set_short("A room.");
    set_long("This seems like the master's bedroom. This room is half "+
        "the size of the rest of the house. A huge bed with pillars "+
        "and a fancy dome sits in the far side of the room. A dark-wood "+
        "dresser with a big mirror rests in the wall opposite to "+
        "the bed. A very femenine bureau sits besides a window. The "+
        "room looks very neat and clean.\n");

    add_item(({"bed", "dome"}),
       "This is a very luxuriant bed. It is quite big and soft. "+
       "The mattress is of goose's down, so light and soft that "+
       "it seems like a fluffy cloud instead of a simple bed. A "+
       "decorative dome cover the bed. The fringe of the dome is "+
       "all lace and dainty bows. Definetely the smith's wife "+
       "has a hand in the decoration of this room.\n");

    add_item("pillars",
        "These are carved wooden pillars. The carving depicts "+
        "different birds flying in a spiral through all the "+
        "pillars. There are clouds and trees where the birds "+
        "fly around. Is quite lovely.\n");

    add_item("walls",
        "The walls are made with a golden-hue oakwood that made the "+
        "inside of the room looks cheerful.\n");

    add_item("window",
        "A small glass window that faces to a small garden.\n");

    add_item("garden",
        "A flower garden. Seems that the smith's wife passes her time "+
        "working with roses and lilies.\n");

    add_item("floor",
        "The floor is made with the same wood than the walls.\n");

    add_item("bureau",
        "A small carved bureau with three drawers to one side, a space "+
        "for a small stool and small mirror resting in the top of the "+
        "bureau. The carvings are small roses with ivy made of "+
        "rosewood.\n");

    add_item("dresser",
        "This is a cabinet-closet known as dresser made of dark wood. "+
        "A mirror is set in one of the closet door.\n");

    add_item(({"mirror", "mirrors"}),
        "There are two mirrors in this room. A grandfather mirror is "+
        "in the dresser, and a small copper mirror is in the bureau.\n");

    add_exit("sm_house.c", "out");

}
