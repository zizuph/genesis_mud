/* 	lawn.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Beautiful lawn");
    set_long("\n"+
             "You are walking a garden path laid on a green soft lawn.\n"+
             "The garden around you is well kept so you better stick\n"+
             "to the path. The mountains rise high further south.\n"+
             "");

    add_exit("gravel","south");
    add_exit("mansion","east");

    add_item(({"garden" }),
             "Someone obviously tends to this garden with great skill.\n"+
             "");
    add_item(({"lawn" }),
             "It's very strange, but the lawn looks newly cut...\n"+
             "");
    add_item(({"path","mountains" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

