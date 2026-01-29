/* 	wfall.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("By the waterfall");
    set_long("\n"+
             "A light spray is in the air and a faint rainbow can be seen over\n"+
             "a small waterfall. The water spurts from the mountainside down into\n"+
             "the pool below. This is a place of serenity and an example of nature\n"+
             "at its best. How easy it would be to lie down here for a short while.\n"+
             "");

    add_exit ("field9","east");

    add_item(({"spray" }),
             "It's wet.\n"+
             "");
    add_item(({"rock" }),
             "It must be real heavy...\n"+
             "");
    add_item(({"rainbow" }),
             "Now isn't that just beautiful. The rainbow forms a perfect\n"+
             "arc between the pond and a large rock. (You can stop gawking now)\n"+
             "");
    add_item(({"pool","pond" }),
             "It looks very fresh and inviting. Although the water is rather\n"+
             "cold a swim would probably be real nice.\n"+
             "");
    add_item(({"waterfall" }),
             "The fall is no more than about 5 metres as the water crashes down\n"+
             "into the pond. The sound is very soothing though.\n"+
             "");
    add_item(({"mountain","mountainside" }),
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

