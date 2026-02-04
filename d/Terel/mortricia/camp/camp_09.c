/* A room. Mortricia 920927 */
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

object gypsy_9;

void
reset_room()
{
    if (!gypsy_9) {
        gypsy_9 = clone_object(CAMP_DIR + "gypsy");
        gypsy_9 -> move(TO);
    }
}

void
create_room()
{
    set_short("Gypsy camp");
    set_long(BSN(
        "You are standing in the middle part of the camp. South " +
        "from here is a strange tent."
    ));

    add_item(({"tent", "strange tent"}), BSN(
        "Indeed, it's very strange!"
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_08", "north", 0);
    add_exit(CAMP_DIR + "camp_10", "east" , 0);
    add_exit(HAUN_DIR + "house_1", "south", "@@later");
    add_exit(CAMP_DIR + "sledge", "west", 0);

    reset_room();
}

later()
{
    return 0;
}
