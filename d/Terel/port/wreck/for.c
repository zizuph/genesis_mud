inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP           this_player()
#define TO           this_object()

#define WRECK        "/d/Terel/port/wreck/"
#define BEACH        "/d/Terel/port/beach/"

#define MAST         WRECK + "mast"
#define CABIN        WRECK + "cabin"


public void
reset_room()
{
}

public void
init()
{
    ::init();
}

public void
create_room()
{
    set_short("On the deck");
    set_long("You are standing on the deck of an old wreck. " +
             "Some distance to the north you see a beach. " +
             "There is a mast west from here. To the south is the " +
             "vast sea.\n");

    add_item(({"water", "sea"}), "It looks very cold.\n");

    add_item(({"beach"}), "It looks far safer than this wreck.\n");

    add_item(({"wreck"}), "It was a sailing ship. It looks very old, " +
                          "but it seems to be fairly intact.\n");
                          
    add_item(({"mast"}), "It looks climbable. But you must go closer " +
                         "to find out.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WRECK + "deck",   "west", 0);

    reset_room();
}
