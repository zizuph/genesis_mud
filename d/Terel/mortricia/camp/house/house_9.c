/* A haunted room. Mortricia 920927 */
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

object creep;

void
reset_room()
{
    object box;

    if (!present("box", TO)) {
        box = clone_object(HAUN_DIR + "box");
        box -> set_adj("glowing");
        box -> set_short("glowing box");
        box -> move(TO);
    }
    if (!creep) {
        creep = clone_object(HAUN_DIR + "creep");
        creep -> move(TO);
    }
}

void
create_room()
{
    set_short("Tunnel");
    set_long(BSN(
        "You are standing in an under-ground tunnel " +
        "that continues to the north and west. " +
        "A shaft opens up to the south."
    ));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 10);

    add_exit(HAUN_DIR + "house_8" , "west" , "@@check");
    add_exit(HAUN_DIR + "house_10", "north", "@@check");
    add_exit(HAUN_DIR + "shaft_1" , "south", "@@further");

    reset_room();
}

check()
{
    if (creep && present("creep", TO)) {
        creep -> command("scream");
    }
    return 0;
}

further()
{
    if (creep && present(creep) && TP->query_ghost() == 0) {
        if (creep == TP) return 0;
        creep -> command("scream");
        write("The creep stops you from going there!\n");
        say (QCTNAME(TP) + " was pushed back by the creep.\n");
        return 1;
    }
    return 0;
}
