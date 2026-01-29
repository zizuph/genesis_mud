#include "/d/Kalad/defs.h"

inherit "/std/room";

/* This is the storage room for the equipment rack of the Khiraa */
/* Sarr 2.Apr.97 */


void
create_room()
{
    set_short("The storage room");
    set_long("This is the storage room for the rack.\n");
    INSIDE;
}

