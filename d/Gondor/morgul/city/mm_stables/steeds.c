/*
 *  /d/Gondor/morgul/city/mm_stables/steeds.c
 *
 *  Deagol, August 2002
 */

inherit "/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "mm_stables.h"

void
create_room()
{
    ::create_room();
    
    set_short("Inside stables of Minas Morgul?");
    set_long("If you are a mortal character, bug report your presence " +
             "here, please. And leave immediately. Thank you!\n");

    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit("office.c", "north", 0, 0, 0);
    
    reset_room();
}
