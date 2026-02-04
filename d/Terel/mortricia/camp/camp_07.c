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

object gypsy_7;

void
reset_room()
{
    if (!gypsy_7) {
        gypsy_7 = clone_object(CAMP_DIR + "gypsy");
        gypsy_7 -> move(TO);
    }
}

void
create_room()
{
    set_short("Eastern part of the camp");
    set_long(BSN(
        "You are standing in the eastern part of the camp. There " +
        "are two carriages north and west from here."
    ));
    
    add_item(({"carriage", "carriages"}), BSN(
        "Which one? The northern or western one?"
    ));
    add_item(({"northern carriage"}), BSN(
        "This carriage is painted black."
    ));
    add_item(({"western carriage"}), BSN(
        "This carriage is painted yellow."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "wres_carr", "north", 0);
    add_exit(CAMP_DIR + "camp_08"  , "south", 0);
    add_exit(CAMP_DIR + "bear_carr", "west" , 0);
    add_exit(CAMP_DIR + "camp_06"  , "east" , 0);

    reset_room();
}
