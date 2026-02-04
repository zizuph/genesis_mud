/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#include "/d/Terel/common/terel_defs.h"

#define BSN(xx)        break_string(xx+"\n", 70)
#define NF(xx)         notify_fail(xx)
#define TP             this_player()
#define TO             this_object()

create_room()
{
    set_short("mystic fog");
    set_long("You are shrouded in ancient fog.\n");
    add_prop(ROOM_I_INSIDE, 0);
}



