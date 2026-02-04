/*
  A room. Mortricia 920927
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

object gypsy_10;

void
reset_room()
{
    if (!gypsy_10) {
        gypsy_10 = clone_object(CAMP_DIR + "gypsy");
        gypsy_10 -> move(TO);
    }
}

void
create_room()
{
    set_short("Middle part of camp");
    set_long(BSN(
        "You are standing in the middle part of the camp. " +
        "North from here is a tent, and there is a sign next " +
        "to it."
    ));
    
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));

    add_cmd_item("sign", "read", BSN(
        "The sign reads:\n" +
        "    Welcome to the Wheel of Chance."
    ));
    add_item(({"tent"}), BSN(
        "The tent is red."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "wheel"  , "north", 0);
    add_exit(CAMP_DIR + "camp_09", "west" , 0);
    add_exit(CAMP_DIR + "camp_11", "east" , 0);

    reset_room();
}
