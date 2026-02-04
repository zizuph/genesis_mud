/*
  A tent room. Mortricia 920927
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

object guard;

void
reset_room()
{
    if (!guard) {
        guard = clone_object(TENT_DIR + "tent_guard");
        guard -> move(TO);
    }
}

void
create_room()
{
    set_short("Tent entrance");
    set_long(BSN(
        "You are standing in the tent entrance. " +
        "You probably have to pay the guard (if he is here), " +
        "if you want to go any further. There is a sign here."
    ));
    
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));

    add_cmd_item("sign", "read",
        "The sign reads:\n" +
        "Entrance fee: 1 silver coin.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 40);

    add_exit(CAMP_DIR + "camp_11", "north", 0);
    add_exit(TENT_DIR + "tent_02", "south", "@@try_south");

    reset_room();
}

try_south()
{
    if (TP -> query_wiz_level() > 0) {
        if(!(TP->query_invis()) && guard) {
            guard -> command("say Welcome wizard! Please enter!");
        }
        return 0;
    }

    if (TP == guard) return 0;
    if (guard && present(guard) && random(5) > 0 &&
        CAN_SEE(guard, TP)) {
        guard -> command("say You must pay first!");
        return 1;
    } else {
        return 0;
    }
}
