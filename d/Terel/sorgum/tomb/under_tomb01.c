inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

init()
{
     ::init();
}

void
create_room()
{
    object door;
    
    set_short("Under the tomb");
    set_long(
        "Underneath the tomb the air is cold and damp and filled with " +
	"a sickening musty stench.  Filthy water drips from the walls and " +
        "ceiling.\n"
    );
    add_prop(ROOM_I_INSIDE,1);
    add_exit(TOMBDIR + "tomb01", "up", 0);
    add_exit(TOMBDIR + "under_nw", "northwest", -5);
    add_exit(TOMBDIR + "under_ne", "northeast", -5);    
}

