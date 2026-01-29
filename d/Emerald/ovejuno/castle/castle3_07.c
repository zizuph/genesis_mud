/* Castle rooms thrid floor' rooms
 * Coded by Marisol (12/09/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_short("An abandoned room");
    set_em_long("The room seems to have been abandoned for a long time. "+
        "Thick layers of dust cover every single surface. An empty "+
        "fireplace opens its black mouth in expectation. A thick "+
        "carpet cover the floor. Some pictures decorate the walls. "+
        "Some furnitures are arranged around the room. A tall cabinet "+
        "with many different bottles on top of it stand on one of the "+
        "walls. A glass window faces west.\n");
 
    add_item("walls",
        "The walls are painted with a rich color, maroon and several "+
        "pictures hang on it. A window faces to the east.\n");

    add_item("room",
        "The abandoned room is gathering dust slowly. Seems that no one "+
        "has lived here in many, many years.\n");

    add_item("rug",
        "A soft and thick elven carpet. The color of the carpet is hard "+
        "to identify. It is a ligher color than the wall, like a beige "+
        "color turns grey with the dust and grime. But still very "+
        "luxurious.\n");

    add_item("fireplace",
        "The fireplace is cold stone. Just ashes and some burn-up "+
        "logs are inside of it. A metal grate holds the useless logs.\n");

    add_item("window",
        "This is a tall, ordinary window. The interior of the window "+
        "is clean but the outside is dirty. You can see leaves and "+
        "old grime covering the outside of the window, inhibiting the "+
        "entrance of light.\n");

    add_item("furnitures",
        "Big and small furnitures are scattered around the room. Several "+
        "dusty sheets are covering the bulky pieces so it is unclear what "+
        "type they are.\n");

    add_item("cabinet",
        "A wooden cabinet lays straight on the wall. Layers of dust and "+
        "grime cover both the top of the table and several glass bottles "+
        "that rest on it.\n");

    add_item(({"glass bottles", "bottles"}),
        "Very elaborate decorate glass bottles stand on top of the cabinet. "+
        "Some are round, other are square-like, all are beautiful crafted. "+
        "Some seem to have some dark liquid inside it.\n");

    add_item("pictures",
        "Pictures of landscapes and marine views adorn the walls. Even "+
        "though the pictures are darkened because grime and dust, you "+
        "can appreciate still how beautiful they are.\n");

    add_exit("castle3_02", "east");
}                                                                                                       
