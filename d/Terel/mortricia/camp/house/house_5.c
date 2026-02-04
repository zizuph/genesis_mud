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

void
reset_room()
{
    object box;

    if (!present("box", TO)) {
        box = clone_object(HAUN_DIR + "box");
        box -> set_adj("white");
        box -> set_short("white box");
        box -> move(TO);
    }
}

void
create_room()
{
    set_short("Tunnel");
    set_long(BSN(
        "You are standing in an under-ground tunnel that " +
        "goes in the north-south direction."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_4", "north", 0);
    add_exit(HAUN_DIR + "house_6", "south", 0);

    reset_room();
}
