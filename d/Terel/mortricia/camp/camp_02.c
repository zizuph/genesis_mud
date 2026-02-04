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

object gypsy_2;

void
reset_room()
{
    if (!gypsy_2) {
        gypsy_2 = clone_object(CAMP_DIR + "gypsy");
        gypsy_2 -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You see tents, carriages, and people everywhere. " +
        "You can enter a carriage south."
    ));
    
    add_item(({"tent", "tents"}), BSN(
        "There is a big tent west from here."
    ));
    add_item(({"big tent"}), BSN(
        "There is a big tent west from here. You can hear " +
        "the laughter of many people coming from it."
    ));
    add_item(({"carriage"}), BSN(
        "The carridge has been painted red and white."
    ));
    add_item(({"people"}), BSN(
        "Indeed, it seems to be a popular place to visit for " +
        "citizens of Calathin."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_01", "north", 0);
    add_exit(CAMP_DIR + "jest_carr", "south", 0);

    reset_room();
}
