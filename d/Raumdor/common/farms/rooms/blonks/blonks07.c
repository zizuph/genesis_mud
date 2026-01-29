/* 
 * /d/Raumdor/common/blonks/blonks07.c
 * Blonks kitchen.
 * Ardent 2020
 * Add Mrs Blonk here.
 */

#include "defs.h"

inherit FARM_BASE;

#include <stdproperties.h>
#include <macros.h>


void create_farms_room()
{
    set_items_blonks();

    set_short("The farmhouse kitchen ");

    set_long("The scent of food greets you as you step into the "+
        "kitchen. The stove in the corner is extinguished, but the "+
        "smell of cooking lingers. There is a table in the middle of "+
        "the room and a few shelves on the wall. Doors lead in "+
        "several directions.\n"); 

    add_item(({"door", "doors"}), "These are solid wooden doors. "+
        "They have been locked in place to keep them open.\n");

    add_item(({"table"}),
        "This table is made from wood. It is wide and sturdy. "+
        "Remains of some chopped carrots are spread out over the " +
        "table. There are no chairs surrounding the table, but "+
        "there is a bin under it.\n");

    add_item(({"bin"}),
        "The bin is made from wood. At the bottom you can see a few "+
        "pieces of decaying carrot.\n");

    add_item(({"shelf", "shelves"}), 
        "A few shelves line the walls. Most of them are filled with "+
        "pots and bowls. One shelf has a bundle of carrots. When you "+
        "reach for one of the carrots, you feel the stern gaze of Mrs "+
        "Blonk staring right at you and decide against it.\n"); 

    add_item(({"pot", "pots", "bowl", "bowls"}), "The pots and bowls are "+
        "used for cooking. In one of the bowls you see a bit of left "+
        "over dough.\n");

    add_item(({"stove", "oven"}), "In the corner is a well used stove. "+
        "There is nothing on the heating plate and the stove is open. "+
        "Judging from the remains Mrs Blonk bakes bread on a daily "+
        "basis. The heating plate on top is clearly less used. The "+
        "main diet here seems to be bread and carrots.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(BLONKS_DIR + "blonks06","west");
    add_exit(BLONKS_DIR + "blonks08","east");
    add_exit(BLONKS_DIR + "blonks10","north");
    add_exit(BLONKS_DIR + "blonks13","south");

    set_no_exit_msg( ({"northeast", "southeast", 
            "southwest", "northwest"}),
        "The wooden walls prevent you from going in that direction. You "+
        "should exit through one of the doors leading north, east, south "+
        "or west instead.\n");
}

int *
query_coordinates()
{
    return ({27, 7, 0}); 
}
