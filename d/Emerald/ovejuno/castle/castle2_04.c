/* Corridor-second floor (3)
 * Coded by Marisol (09/25/98)
 * Marisol Ramos (c) 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_em_long("This corridor goes straight through the residence. "+
        "To one side of the wall there is a black door to the sewing "+
        "room. To the other side, a long wall with interior windows, "+
        "open up to a brown door almost at the end of the corridor. "+
        "Human voices can be heard behind that door.\n");

    add_item("windows",
        "The windows are small with a wooden frame and two crossed "+
        "wooden stick that divided the windows in four smaller squares. "+
        "The windows are not covered with glass, they are interior "+
        "windows, but you can't see through them because they are "+
        "covered in the other side with a curtain.\n");

    add_item("floor",                         
        "Beautiful porcelain tiles cover the floor of the corridor.\n");

    /*
    add_item("brown door",
        "A simple close oak door lead to the servant quaters.\n");

    add_item("black door",
        "An ornate black door lead to the sewing room.\n");
    */


    add_exit("castle2_03", "north");
    add_exit("castle2_05", "southeast");
    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_04", "castle2_08", "east");
    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_05", "castle2_13", "west");
}                           
