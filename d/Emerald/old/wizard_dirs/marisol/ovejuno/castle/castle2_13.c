/* Corridor-second floor 
 * Coded by Marisol (09/25/98)
 * Marisol Ramos (c) 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;

void
create_castle_room()
{

    set_long("This corridor enters to the human servant living quarters. "+
        "In this section, there are two doors on both side of the "+
        "corridor. The corridor continues a little further from here. "+
        "Human voices can be heard behind the doors.\n");


    add_item("floor",                         
        "The floor here is made polished wooden boards that shines "+
        "a rich amber color.\n");

    add_item("doors",
        "Both doors look the same, dark brown wood with brazen "+
        "door-knobs.\n");

   
    add_exit("castle2_11.c", "north");
    add_exit("castle2_09.c", "south");


    reset_room();
}                           
