/*
 *  /d/Shire/bree/rooms/town/stable/stable_yard.c
 *
 *  The stable yard of the Bree Stables
 *
 *  By, Palmer
 *  Date December 2002
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "stables.h"
#include <stdproperties.h>
#include <terrain.h>

// this is a base file for outdoor rooms in Faerun
inherit FAERUN_OUTDOOR_BASE;

void
create_faerun_room()
{
    set_short("In the stable yard");
    set_long("This is the stable yard. The yard continues north to the stable. \n");

    add_prop(ROOM_I_INSIDE, 0);
    add_exit("stable", "north");
    add_exit("/d/Faerun/examples/base_file/rooms/meadow01", "south");

    reset_faerun_room();
}

void reset_faerun_room()
{

}
