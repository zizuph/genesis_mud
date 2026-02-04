inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP           this_player()
#define TO           this_object()

#define BEACH        "/d/Terel/port/beach/"
#define WRECK        "/d/Terel/port/wreck/"
#define GULL         "/d/Terel/port/monster/gull"

static object gull;

public void
reset_room()
{
    if (!gull) {
        gull = clone_object(GULL);
        gull->move_living(0, TO);
    }
}

public void
init()
{
    ::init();
}

public void
create_room()
{
    set_short("in the mast");
    set_long("You are up in the mast of an old wreck. The view up here is " +
             "quite excellent. " +
             "To the north you see a beach, and you also see the sharp rocks " +
             "that made this ship into a wreck. Below to the west, you see " +
             "the roof of a cabin. Far west you see a village and two piers. " +
             "Further to the north, beyond the beach, you see a vast forest " +
             "and to the east are some high cliffs. To the south is nothing " +
             "but the sea.\n");

    add_item(({"water", "sea"}), "It looks very cold. It is empty as far " +
                                 "from a few seagulls searching for food.\n");

    add_item(({"beach"}), "It looks far safer than this wreck.\n");

    add_item(({"wreck"}), "It was a sailing ship. It looks very old, " +
                          "but it seems to be fairly intact.\n");
                          
    add_item(({"mast"}), "You are up in it.\n");
    
    add_item(({"stone", "stones", "rocks", "rock"}),
             "You can reach the beach by walking on them.\n");

    add_item(({"forest", "trees"}), "The vast forest gives you an eerie " +
                                    "feeling.\n");
    
    add_item(({"roof", "cabin"}), "It is in pretty bad condition.\n");
    
    add_item(({"village", "houses"}), "You see some houses beyond a fence, " +
                                      "that's all.\n");
                                      
    add_item(({"cliff", "cliffs"}), "They look whiteish, probably made of " +
                                    "limestone.\n");
    
    add_item(({"pier", "piers"}), "At the closest pier, you think you " +
                                  "see a ship. The other pier is too far " +
                                  "away, for you to discern any details.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(WRECK + "deck",  "down", 0);

    set_alarm(1.0, -1.0, "reset_room");
}
