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
#define TENT_DIR        CAMP_DIR + "tent/"

object gypsy_11;

void
reset_room()
{
    if (!gypsy_11) {
        gypsy_11 = clone_object(CAMP_DIR + "gypsy");
        gypsy_11 -> move(TO);
    }
}

void
create_room()
{
    set_short("Middle part of camp");
    set_long(BSN(
        "You are standing in the middle part of the camp. " +
        "North from here you see a small tent, and to the " +
        "south you see a very large tent."
    ));

    add_item(({"tent", "tents"}), BSN(
        "There is a big tent south from here and a " +
        "smaller one to the north."
    ));
    add_item(({"big tent", "large tent"}), BSN(
        "There is a big tent south from here. You can hear " +
        "the laughter of many people coming from it."
    ));
    add_item(({"small tent"}), BSN(
        "There is a small tent north from here."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_10", "west" , 0);
    add_exit(CAMP_DIR + "camp_01", "east" , 0);
    add_exit(TENT_DIR + "tent_01", "south", 0);

    reset_room();
}
