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

object gypsy_4;

void
reset_room()
{
    if (!gypsy_4) {
        gypsy_4 = clone_object(CAMP_DIR + "gypsy");
        gypsy_4 -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You are standing in the northern part of the gypsy camp. " +
        "There is a small tent southwest from here. " +
        "To the west a path opens up. " +
        "Further north is a rather large carriage."
    ));
    
    add_item(({"tent", "small tent"}), BSN(
        "It seems to be used as a pub."
    ));
    add_item(({"carriage"}), BSN(
        "It's a carriage on which balls and cones have been painted."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_03", "south", 0);
    add_exit(CAMP_DIR + "camp_05", "west",  0);
    add_exit(CAMP_DIR + "jugg_carr", "north", 0);

    reset_room();
}
