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

object demon;

void
reset_room()
{
    if (!demon) {
        demon = clone_object(HAUN_DIR + "demon");
        demon -> move(TO);
    }
}

void
create_room()
{
    set_short("Shaft");
    set_long(BSN(
        "You are standing in a shaft. It continues south " +
        "and west. The walls are supported here and there by " +
        "some wooden boards."
    ));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 60);

    add_exit(HAUN_DIR + "shaft_2", "west", "@@check");
    add_exit(HAUN_DIR + "shaft_4", "south", "@@further");

    reset_room();
}

check()
{
    if (demon && present("demon", TO)) {
        demon -> command("scream");
    }
    return 0;
}

further()
{
    if (demon && present(demon) && TP->query_ghost() == 0) {
        if (demon == TP) return 0;
        demon -> command("scream");
        write("The demon stops you from going there!\n");
        say(QCTNAME(TP) + " was pushed back by the demon.\n");
        return 1;
    }
    return 0;
}
