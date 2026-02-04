#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: Instrument storage.  
 * Here minstrels may "borrow" instruments of power from the guild.
 * Cedric 2/93
 */

void
create_room()
{
    set_short("Instrument checkout");
    set_long(BS("Eventually you will be able to borrow (at VERY "
        + "HIGH prices) certain magical instruments.  Alas, you will "
    + "have to wait until the Guildmaster authorizes their use.\n"));
    
    add_exit(GUILD+"training", "north");
    add_exit(GUILD+"office", "southeast");
    add_prop(ROOM_I_INSIDE, 1);
}