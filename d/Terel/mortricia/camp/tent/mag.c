/* A tent room. Mortricia 920927 */
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

object magician, apparatus, hourglass;

void
reset_room()
{
    if (!magician) {
        magician = clone_object(TENT_DIR + "magician");
        magician -> move(TO);
    }
    if (!apparatus) {
        apparatus = clone_object(TENT_DIR + "apparatus");
        apparatus -> move(TO);
    }
    if (!hourglass) {
        hourglass = clone_object(TENT_DIR + "hourglass");
        hourglass -> move(TO);
    }
}

void
create_room()
{
    set_short("Small room");
    set_long(BSN(
        "You have entered a small room in the rear parts of the big " +
	"tent. There are a lot of " +
        "odd things here. You see a puppet, a shrine, a table, " +
        "a couple of chairs."
    ));
    
    add_item(({"puppet"}), BSN(
        "It's made out of porcelain."
    ));
    add_cmd_item("puppet", "get", "@@get_puppet");

    add_item(({"shrine"}), BSN(
        "It's made out of gneiss."
    ));
    add_cmd_item("shrine", "get", "@@get_shrine");

    add_item(({"table"}), BSN(
        "It's made out of ebony."
    ));
    add_item(({"chair"}), BSN(
        "It's made out of ebony."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "behind2", "west", 0);

    reset_room();
}

get_puppet()
{
    if (magician && present("magician", TO)) {
         return "The magician does not allow that.\n";
    } else {
         return "The magicians's spirit still protects it.\n";
    }
}

get_shrine()
{
    if (magician && present("magician", TO)) {
         return "The magician does not allow that.\n";
    } else {
         return "The magicians's spirit still protects it.\n";
    }
}
