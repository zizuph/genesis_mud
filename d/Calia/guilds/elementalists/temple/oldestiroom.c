
 /* Worshippers skill estimation/meditation  room */
 /* by Jaacar 1996                                */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

void
create_room()
{
    set_short("Old meditation chamber");
    set_long("This small chamber has many small straw mats on the "+
        "floor. There is a small exit to the north. On the southern "+
        "wall you notice a small glowing stone, as well as a small "+
        "broken statue. To the west you see an exit has been carved into "+
        "the room leading upwards.\n");

    add_item(({"stone","glowing stone","small glowing stone","small stone"}),
        "This small glowing stone is luminous enough to light the entire "+
        "chamber with a soft light.\n");
    add_item(({"statue","small statue","broken statue","small broken statue"}),
        "It is a small broken statue. It appears it used to depicting someone "+
        "praying.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(ELEMENTALIST_TEMPLE+"oldmedroom","north",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"path4","up",0,1);

}
