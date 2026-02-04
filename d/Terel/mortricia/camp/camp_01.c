/*
  A path in camp. Mortricia 920927
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

object gypsy_1;

void
reset_room()
{
    if (!gypsy_1) {
        gypsy_1 = clone_object(CAMP_DIR + "gypsy");
        gypsy_1 -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You have entered the gypsy camp, and you " +
        "see tents, carriages, and people everywhere."
    ));
    
    add_item(({"tent", "tents"}), BSN(
        "There is a big tent southwest from here and a " +
        "smaller one to the northwest."
    ));
    add_item(({"big tent"}), BSN(
        "There is a big tent southwest from here. You can hear " +
        "the laughter of many people coming from it."
    ));
    add_item(({"small tent"}), BSN(
        "There is a small tent northwest from here."
    ));
    add_item(({"carriage", "carriages"}), BSN(
        "The closest carriage is the one a bit to the south."
    ));
    add_item(({"people"}), BSN(
        "Indeed, it seems to be a popular place to visit for " +
        "citizens of Calathin."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "entrance", "east" , 0);
    add_exit(CAMP_DIR + "camp_03" , "north", 0);
    add_exit(CAMP_DIR + "camp_11" , "west" , 0);
    add_exit(CAMP_DIR + "camp_02" , "south", 0);

    reset_room();
}
