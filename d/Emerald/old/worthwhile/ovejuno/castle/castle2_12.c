/* Castle rooms second floor-Servant Quarters (female)
 * Coded by Marisol (11/24/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_short("Servant Quarters");
    set_em_long("This is the female section of the Servant Quarters of "+
        "the castle. This room is long and full of small beds. "+
        "One wall has two windows that looks outside to the west. "+
        "The other wall seems to have been added recently. Several "+
        "oil lights provide light to the quarters.\n");

    add_item("quarters",
        "The quarters are definetely female. They are neat and, "+
        "cheerful with coquetish decorations. Although there is not "+
        "much space in this room, it looks cozy and warm. A tall and "+
        "and wide closet cover all the wall at the bottom of the room"+
        "Some of the chambermaids are sitting on the beds chatting "+
        "happily.\n");

   add_item("beds",
        "A series of beds are arranged along both walls of this "+
        "room. They are made of wood and have some padding for "+
        "comfort. White sheets with frilly edge cover the beds and "+
        "plush pillows are set at the top of each beds.\n");
 
    add_item(({"pillow", "pillow"}),
        "Nice, fluffy pillows sit on top of the beds.\n");
       
    add_item(({"white sheets", "sheets"}),
        "Soft, white and clean sheets cover all the beds of this "+
        "room.\n");

    add_item("windows", 
        "Two small windows face west. It is hard to see outside "+
        "these windows because all the debris and dead leaves "+
        "plaster on the glass.\n"); 

    add_item("walls",
        "A stone and mortar wall rest to the west. The east wall is a "+
        "thin piece of wood. The wall was set unevenly the room and "+
        "you can hear the soft voices of the male servant coming across "+
        "the other side.\n");

    add_item("west wall",
        "The west wall is decorated with small pictures of fruits and "+
        "flowers, and beautiful landscapes of brooks and forests.\n");

    add_item("east wall",
        "The east wall still has its natural beige wooden color. Some "+
        "pictures of fruits and flowers have been hanged on the wall "+
        "to lighten up the wall.\n");

    add_item("pictures",
        "There are several pictures hanging on the walls. Some are "+
        "'still life', portraying fruits like apples, oranges and "+
        "melons and flowers like roses and carnations. Others are "+
        "landscapes of forests with small brooks running in the middle "+
        "of the scene.\n");

    add_item("closet",
        "An oakwood closet stands tall on the wall. One of its door "+
        "is open, reveling several dresses.\n");

    add_item("dresses",
        "Many black and white house maiden dresses, together with some "+
        "lively red and green color dresses, hang inside the closet.\n");

    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_06", "castle2_14", "south");
}                                     
