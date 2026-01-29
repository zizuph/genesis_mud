/* Castle rooms second floor-The Guess's room
 * Coded by Marisol (09/30/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_short("Guess's room");
    set_em_long("This is the guess's room. This room is simple in "+
        "design, very away from elven tastes. There are "+
        "not pictures or tapestries decorating the walls. The walls "+
        "are plain and painted light blue. A soft rug is spread in the "+
        "floor adding another elven touch to this place. A comfortable "+
        "bed is set in one corner of the room. A small fireplace is "+
        "burning cheerfully in the wall opposite to the bed. A tall "+
        "window, facing east, shares the same wall as the fireplace. "+
        "Torches are set strategically to provide a nice, mellow "+
        "light to all the room.\n");

    add_item("walls",
        "The walls are naked of any ornamentation. It is painted "+
        "with a soothing light blue color.\n");

    add_item("room",
        "A very simple room. You would have never guess "+
        "that elven guest would sleep here.\n");

    add_item("rug",
        "A soft elven rug. One of the few elvish touches in this room. "+
        "The rug is a light blue to compliment the walls.\n");

    add_item("bed",
        "It is comfortable single bed. The bed sheets are white without "+
        "any frilly decoration or embroidery. Two plush pillows are at "+
        "the top of the bed.\n");     

    add_item("fireplace",
        "The stone fireplace is burning cheerily aromatic applewood "+
        "logs. The fireplace exudes a nice warm heat through out the "+
        "room, and the pleasing aroma of the applewood fills the air.\n");

    add_item("window",
        "This is a tall, ordinary window. The interior of the window "+
        "is clean but the outside is dirty. You can see leaves and "+
        "old grime covering the outside of the window, inhibiting the "+
        "entrance of light.\n");

    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_02", "castle2_03", "east");
}                                                                                                       
