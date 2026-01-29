#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>
#include "../local.h"

inherit "/std/room.c";
inherit "/lib/unique";

void set_exit(string exit_name);

object minotaur;
object hat;

void reset_room()
{
    return;
}

void
create_room() 
{
    set_short("Up in a mast");
    set_long("You have climed up the mast on the pirate warship, "+
             "and reached a small platform most likely used for keeping " +
             "a lookout for enemy ships during travel.\n");
            
     add_item(({"ship", "warship"}),
                "Everything on this ship seem to have been very " +
                "carefully designed.\n");               

    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}

void set_exit(string exit_name)
{
    remove_exit("down");
    add_exit(exit_name, "down", 0, 1);
}

