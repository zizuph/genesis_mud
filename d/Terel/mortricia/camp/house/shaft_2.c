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

object ghost;

void
reset_room()
{
    if (!ghost) {
        ghost = clone_object(HAUN_DIR + "ghost");
        ghost -> move(TO);
    }
}

void
create_room()
{
    set_short("Shaft");
    set_long(BSN(
        "You are standing in a shaft. It continues east and " +
        "northwest. The walls are supported here and there " +
        "by some wooden boards. "
    ));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 50);
	add_prop(LIVE_I_UNDEAD,80);

    add_exit(HAUN_DIR + "shaft_1", "northwest", "@@check");
    add_exit(HAUN_DIR + "shaft_3", "east", "@@further");

    reset_room();
}

check()
{
    if (ghost && present("ghost", TO)) {
        ghost -> command("scream");
    }
    return 0;
}

further()
{
    if (ghost && present(ghost) && TP->query_ghost() == 0) {
        if (ghost == TP) return 0;
        ghost -> command("scream");
        write("The ghost stops you from going there!\n");
        say(QCTNAME(TP) + " was pushed back by the ghost.\n");
        return 1;
    }
    return 0;
}
