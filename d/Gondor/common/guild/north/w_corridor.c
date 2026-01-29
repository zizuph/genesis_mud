#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

public void
create_room()
{
    set_short("The western corridor");
    set_long(BS("You have entered the western corridor. On the walls are "+
    "burning torches set in sconces. On the east wall hangs a beautiful "+
    "tapestry. To the north is the training hall, south the shop and "+
    "west is a cosy room.\n"));

    add_item("tapestry",BS("On the tapestry you see a scene from the most "+
    "famous tale of the First Age. "+
    "You see Luthien dancing in the moonlight. She's in the forest of "+
    "Neldoreth at the river Esgalduin, in long lost Beleriand. "+
    "Beren is watching her as he hides among the shadows.\n"));
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"north_train","north",0);
    add_exit(RANGER_NORTH_DIR+"inn","west",0);
    add_exit(RANGER_NORTH_DIR+"shop","south",0);
}
