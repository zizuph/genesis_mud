/* A shaft room. Mortricia 920927 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"

object soul;

void
reset_room()
{
    if (!soul) {
        soul = clone_object(HAUN_DIR + "soul");
        soul -> move(TO);
    }
}

void
create_room()
{
    set_short("Shaft");
    set_long(BSN(
        "You are standing in the beginning of a shaft. " +
        "It continues to the southeast and to the north " +
        "it opens up to a somewhat larger tunnel. " +
        "The shaft is supported here and there by some " +
        "wooden boards."
    ));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 30);

    add_exit(HAUN_DIR + "house_9", "north", "@@check");
    add_exit(HAUN_DIR + "shaft_2", "southeast", "@@further");

    reset_room();
}

check()
{
    if (soul && present("soul", TO)) {
        soul -> command("scream");
    }
    return 0;
}

further()
{
    if (soul && present(soul) && TP->query_ghost() == 0) {
        if (soul == TP) return 0;
        soul -> command("scream");
        write("The lost soul stops you from going there!\n");
        say(QCTNAME(TP) + " was pushed back by the lost soul.\n");
        return 1;
    }
    return 0;
}
