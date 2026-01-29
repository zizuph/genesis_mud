#pragma save_binary

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/common/guild/north/northern_hq.h"

object a_rack, w_rack;

void reset_room();

create_room()
{
    set_short("The short corridor");
    set_long(BS("You've entered the short corridor. A vivid tapestry "+
    "hangs on the east wall.  On the walls are sconces with burning "+
    "torches inside them. From the north comes a peaceful light and "+
    "to the south is another exit.\n"));

    add_item("tapestry",BS("The tapestry shows Turin, one of the strongest "+
    "fighters of the First Age, wielding the black sword Gaurthang. He has "+
    "dealt the death stroke to Glaurung, the Father of Dragons, close to "+
    "Cabed-in-Aras. Cabed-in-Aras is a high cliff by the river of Esgalduin "+
    "in long lost Beleriand.\n"));

    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR+"song_room","south",0);
    add_exit(RANGER_NORTH_DIR+"start_room","north",0);
    reset_room();
}

void
add_stuff()
{
    if (!objectp(a_rack))
    {
        a_rack = clone_object(RANGER_DIR + "obj/a_rack");
        a_rack->move(TO);
    }
    if (!objectp(w_rack))
    {
        w_rack = clone_object(RANGER_DIR + "obj/w_rack");
        w_rack->move(TO);
    }
}


void
reset_room()
{
    add_stuff();
}

