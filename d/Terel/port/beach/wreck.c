inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#define TP              this_player()
#define TO              this_object()

#define BEACH        "/d/Terel/port/beach/"
#define WRECK        "/d/Terel/port/wreck/"
#define DECK         WRECK + "deck"

public void
reset_room()
{
}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

public void
create_room()
{
    set_short("next to the wreck");
    set_long("You are standing next to an old wreck. " +
             "To the north is the beach, which you can " +
             "reach via a stone to the north. " +
             "You better decide what to do, since falling into " +
             "the water would kill you in a few minutes.\n");

    add_item(({"water", "sea"}), "It looks very cold.\n");

    add_item(({"beach"}), "It looks safer than the stones.\n");

    add_item(({"stone", "stones"}), "They are indeed slippery.\n");

    add_item(({"wreck"}), "It was a sailing ship. It looks very old. " +
                          "It is fairly intact however, and you should " +
                          "be able to enter it, provided that " +
                          "you find an entrance to it, that is.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(BEACH + "s2",    "north", 0, 3);

    reset_room();
}

public int
do_climb(string str)
{
    int climb;
    
    notify_fail("Climb what?\n");
    if (str != "wreck" && str != "up on wreck") return 0;

    climb = TP->query_skill(SS_CLIMB);
    climb = (climb + random(climb))/2;
    if (climb <= 10) {
        write("You don't manage to climb up on the wreck.\n");
        say(QCTNAME(TP) + " fails to climb up on the wreck.\n");
        return 1;
    }
    write("You climb up on the wreck.\n");
    TP->move_living("climbs up on the wreck", DECK);
    
    return 1;
}
