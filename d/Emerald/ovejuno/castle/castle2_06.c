/* Castle rooms second floor-The Lords's room
 * Coded by Marisol (09/30/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_short("Lord's room");
    set_long("This is the Lord's room. This room is simple in "+
        "design, out of character for a elven lord. There are "+
        "not pictures or tapestries decorating the walls. Instead, "+
        "hanging curtains cover the walls giving some color to "+
        "this room. A fluffy rug is spread in the floor adding "+
        "another decorating touch to this place. A big bed is set "+
        "in the far side of the room. It looks almost ascetic in "+
        "its simplicity. A small fireplace is burning cheerfully in "+
        "the north wall. A tall window, facing west, "+
        "shares the same wall as the head of the bed. Torches "+
        "are set strategically to provide a nice, mellow "+
        "light to all the room.\n");

    add_item("room",
        "A very simple and austere room. You would have never guess "+
        "that this was the Lord's room without the guards outside.\n");

    add_item("walls",
        "The walls of the room are covered with curtains.\n");
    add_item("curtains",
        "Beautiful elven fabrics seems to have been used for these "+
        "curtains. They look like felt and their color are royal blue. "+
        "This is one of the few elvish touches in this room.\n");

    add_item("rug",
        "A fluffy elven rug. One of the few elvish touches in this "+
        "room. The rug is a royal blue to compliment the curtains.\n");

    add_item("bed",
        "It is quite big but simple. The bed sheets are white without "+
        "any frilly decoration or embroidery. Two plush pillows are "+
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

    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_01", "castle2_02", "east");
}  
