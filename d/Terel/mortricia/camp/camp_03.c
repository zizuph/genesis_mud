/*
  A camp room. Mortricia 920927
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

void
reset_room()
{
    object guard;

    if (!present("guard", TO)) {
        guard = clone_object(CAMP_DIR + "guard");
        guard -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You are standing east of a small tent."
    ));
    
    add_item(({"tent", "small tent"}), BSN(
        "It seems to be used as a pub."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_01", "south", 0);
    add_exit(CAMP_DIR + "tent_pub",     "west",  0);
    add_exit(CAMP_DIR + "camp_04", "north", 0);

    reset_room();
}
