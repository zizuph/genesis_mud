/* Corridor-second floor (2)
 * Coded by Marisol (09/25/98)
 * Marisol Ramos (c) 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;

void
create_castle_room()
{

    set_long("This corridor goes straight through the residence. "+
        "To one side of the wall there is a door to the guest room. "+
        "To the other side, a long wall with interior windows almost "+
        "run down to the end of the corridor. Human voices can "+
        "be heard at the end of the corridor.\n");


    add_item("windows",
        "The windows are small with a wooden frame and two crossed "+
        "wooden stick that divided the windows in four smaller squares. "+
        "The windows are not covered with glass, they are interior "+
        "windows, but you can't see through them because they are "+
        "covered in the other side with a curtain.\n");

    add_item("floor",
        "Beautiful porcelain tiles cover the floor of the corridor.\n");

    add_item("door",
        "A simple close oak door lead to guest room.\n");

    add_exit("castle2_02.c", "north");
    add_exit("castle2_04.c", "south");
    add_exit("castle2_07.c", "east");


    reset_room();
}                                               
