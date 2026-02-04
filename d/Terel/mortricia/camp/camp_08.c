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

object guard;

void
reset_room()
{

    if (!guard) {
        guard = clone_object(CAMP_DIR + "m_guard");
        guard -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You are standing in the eastern part of the camp. West from here " +
        "is a carriage, and east from here is a tent which has " +
	"a sign next to it."
    ));
     add_item(({"carriage"}), BSN(
        "This carriage is larger than the others you have seen."
    ));
    add_item(({"tent"}), BSN(
        "The tent is red."
    ));
   
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));

    add_cmd_item("sign", "read", BSN(
        "The sign reads:\n" +
        "    Welcome to the Wheel of Chance."
    ));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_HIDE, 40);

    add_exit(CAMP_DIR + "camp_07"  , "north", 0);
    add_exit(CAMP_DIR + "camp_09"  , "south", 0);
    add_exit(CAMP_DIR + "mana_carr", "west" , "@@go_west");
    add_exit(CAMP_DIR + "wheel"    , "east" , 0);

    reset_room();
}

go_west()
{
    if (TP -> query_wiz_level() > 0) return 0;

    if (TP == guard) return 0;
    if (guard && living(guard) && present(guard) &&
        CAN_SEE(guard, TP)) {
	write("The guard stops you from going west.\n");
	say(QCTNAME(TP)+" is stopped by the guard from going west.\n");
	return 1;
    } else {
	return 0;
    }
}
