inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

void
create_room()
{
    set_short("Tomb stairs");
    set_long(
        "The top of a staircase of rough-hewn stone.  It's a narrow " +
        "spiral staircase which is damp and peculiarly odorous that " +
        "winds endlessly down into the bowels of the hill past walls " +
        "of dripping stone blocks and crumbling mortar.  The pungent " +
	"odor of decay is quite unbearable.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOMBDIR + "tomb03", "up", 0);
    add_exit(TOMBDIR + "tomb_core", "down", 0);    
}
