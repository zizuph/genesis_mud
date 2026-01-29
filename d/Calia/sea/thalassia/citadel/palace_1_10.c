
/*  Grand Palace in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Royal Library");
    set_long("You have entered the Royal Library of the "+
        "palace. There are shelves upon shelves upon shelves "+
        "of books here, all neatly arranged. To the south you "+
        "see one of the Royal Guard Rooms while to the east "+
        "you see a hallway leading deeper into the palace itself.\n");

    add_item(({"shelf", "shelves"}), "There are many shelves here, "+
        "all neatly arranged. On each of the shelves there are "+
        "hundreds of books, each alphabetically arranged.\n");
    add_item(({"book", "books"}), "There must be over a thousand "+
        "books in this library. You pull one off of the shelves "+
        "and quickly glance through it but do not understand "+
        "anything that is written inside. After pulling several "+
        "other books off of other shelves and looking through "+
        "them, you deduce that you will not understand any of the "+
        "books in this library.\n");

    IN;

    add_swim_exit(THALC+"palace_1_11","east",0,1);
    add_swim_exit(THALC+"palace_1_9","south",0,1);
}
