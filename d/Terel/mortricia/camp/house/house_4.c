/*
  A haunted room. Mortricia 920927
 */
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
    if (!creep) {
        creep = clone_object(HAUN_DIR + "creep");
        creep -> move(TO);
    }
}

void
create_room()
{
    set_short("Haunted House");
    set_long(BSN(
        "You are standing in an under-ground tunnel. The tunnel " +
        "continues to the east and south, and there is also a " +
        "smaller opening to the northwest."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_3", "east"     , 0);
    add_exit(HAUN_DIR + "house_5", "south"    , 0);
    add_exit(HAUN_DIR + "horror1", "northwest", "@@to_chamber");

    reset_room();
}

to_chamber()
{
    if (creep && present("creep", TO)) {
        creep -> command("scream");
        return 0;
    }
    return 0;
}
