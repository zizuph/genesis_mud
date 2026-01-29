inherit "/d/Emerald/std/room";

#include "../../defs.h"

#include <macros.h>
#include <stdproperties.h>

object apothecary;

void
reset_room()
{
    if (!apothecary)
    {
        setuid();
        seteuid(getuid());
	     
        apothecary =
            clone_object(TELBERIN_MERCANTILE_DIR + "apothecary/apothecary");
                
        apothecary->move(this_object(), 1);
        tell_room(this_object(),
            QCTNAME(apothecary)+" walks into the shop.\n");
    }    
}


void
create_emerald_room()
{
    set_short("You are in a gem shop\n");
    set_em_long("Blah blah blah.\n");

    add_prop(ROOM_I_INSIDE, 1);
   
    reset_room();
}
