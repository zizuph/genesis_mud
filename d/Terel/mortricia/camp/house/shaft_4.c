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

object zombie;

void
reset_room()
{
    if (!zombie) {
        zombie = clone_object(HAUN_DIR + "zombie");
        zombie -> move(TO);
    }
}

void
create_room()
{
    set_short("Shaft");
    set_long(BSN(
        "You are standing in a small shaft. It continues " +
        "west and north. The walls are supported here and there by " +
        "some wooden boards."
    ));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 80);

    add_exit(HAUN_DIR + "shaft_3", "north", "@@check");
    add_exit(HAUN_DIR + "shaft_5", "west", "@@further");

    reset_room();
}

check()
{
    if (zombie && present("zombie", TO)) {
        zombie -> command("scream");
    }
    return 0;
}

further()
{
    if (zombie && present(zombie) && TP->query_ghost() == 0) {
        if (zombie == TP) return 0;
        zombie -> command("scream");
        write("The zombie stops you from going there!\n");
        say(QCTNAME(TP) + " was pushed back by the zombie.\n");
        return 1;
    }
    return 0;
}
