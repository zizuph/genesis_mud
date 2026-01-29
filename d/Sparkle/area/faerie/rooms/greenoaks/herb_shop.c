/*
 * Herb Shop of Green Oaks
 * By Finwe, August 2004
 * Updated by Gronkas, August 3, 2016 to fix typo
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;

void add_stuff();
static object toluca;

 
void
create_indoor_room()
{
    set_short("Herb shop of Green Oaks");
    set_long("This is the inside of the Herb Shop of Green Oaks. The " +
        "building is large and plain looking. A wide counter runs the " +
        "width of the building. Behind the counter are many shelves " +
        "lined with jars, boxes, drawers, and drying racks. Bunches " +
        "of plants hang upside down as they dry. A rich, earthy scent " +
        "fills the air.\n");

    set_add_ceiling_flat("Bunches of plants hang upside from it, " +
        "drying to be resold later.");
    add_item(({"racks", "drying racks"}),
        "They are racks made of strips of wood. They are rectangular " +
        "and sit on shelves and hold plants that are dried.\n");
    add_item(({"jars", "bottles"}),
        "They are various sizes and line shelves behind the counter. " +
        "The jars hold many herbs that have been collected. Some " +
        "are clear and others dark, and all made of glass.\n");
    add_item(({"boxes"}),
        "These are made of wood and look well used. Some are long, " +
        "rectangular, large and square. They hold many dried herbs " +
        "and are neatly stacked and lined on shelves behind the counter " +
        "or used in the drawers. \n");
    add_item(({"drawers"}),
        "The drawers are made of wood and look worn. They are long " +
        "full of boxes that can be pulled out. They store dried herbs " +
        "and are stacked neatly on shelves behind the counter.\n");
    add_item(({"strips of wood"}),
        "They are lengths of narrow wood in a criss-cross pattern. The " +
        "strips of wood are used in drying racks to hold plants that dry.\n");
    add_item(({"counter"}),
        "It is a wide piece of polished wood. It is about waist high " +
        "and runs the width of the shop. Light scratches are visible " +
        "in the counter where boxes, jars, or drawers have marred the " +
        "surface.\n");
    add_item(({"wood"}),
        "It is used in various articles in the shop including the " +
        "shelves, drawers, and boxes behind the counter. The wood is " +
        "worn from constant use.\n");
    add_item(({"shelves"}),
        "They are large and line the walls. Made of wood, the shelves " +
        "are crowded with jars, boxes, drawers, and drying racks.\n");
    
    add_exit(GO_DIR + "road09", "west");
 
}

void reset_room() 
{ 
    add_stuff();
}

void
add_stuff()
{

    if(!present(toluca))
    {
        toluca = clone_object(NPC_DIR + "herbalist");
        toluca->move(TO);
    }

}
