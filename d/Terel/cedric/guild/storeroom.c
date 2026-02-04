inherit "/std/room";

#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <stdproperties.h>

#pragma save_binary

/*
 * Storeroom for weapon check-in at the Minstrels guild.
 * Cedric 1/93
 */

void
create_room()
{
    set_short("Weapons storeroom");
    set_long(BS("This utterly ordinary room should contain many bins, "
    + "each filled with the weapons of people in the minstrel's "
    + "guild.\n"));
    add_exit(CEDRICDIR+"guild/entrance", "out", 0);
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

public object
this_room()
{
    return this_object();
}
