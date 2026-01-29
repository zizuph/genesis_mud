#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

public void
create_room()
{
    set_short("The northern corridor");
    set_long(BS("You've entered the northern corridor. A large tapestry "+
    "hangs on the south wall. Set in the walls are sconces with burning "+
    "torches inside them. To the west is the training hall and to the east "+
    "another exit.\n")); 

    add_item("tapestry",BS("It shows one of the most beautiful spots in "+
    "the Second Age. You see a high and steep mountain, Meneltarma, on "+
    "the island of Numenor, the ancestral home of the Dunedain. Numenor "+
    "sank below the waves when the last king, Ar-Pharazon, became too "+
    "arrogant and challenged the Valar.\n"));
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"north_train","west",0);
    add_exit(RANGER_NORTH_DIR+"song_room","east",0);
}
