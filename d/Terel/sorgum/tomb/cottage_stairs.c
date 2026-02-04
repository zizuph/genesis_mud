/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("cottage stairs");
    set_long(
        "The staircase is huge and steep.  It is fashioned from vast blocks " +
        "as if for the feet of giants.  A reek of infinite mustiness " +
        "wells forth.  It is so rank that it could only be the result of " +
        "unwholesome decades of decay.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "cottage_cellar", "down", 0);
    add_exit(TOMBDIR + "cottage_bookroom", "up", 0);
}


