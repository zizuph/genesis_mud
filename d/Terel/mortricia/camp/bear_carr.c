/* A carriage. Mortricia 920927 */
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

void
reset_room()
{
    object woman;

    woman = present("woman", TO);

    if (!woman) {
        woman = clone_object(CAMP_DIR + "bearded_woman");
        woman -> move_living("M", TO);
    } else {
        if (woman->query_prop("_bearded_woman") != 1) {
	    woman -> remove_object();
            woman = clone_object(CAMP_DIR + "bearded_woman");
            woman -> move_living("M", TO);
	}
    }
}

void
create_room()
{
    set_short("A carriage");
    set_long(BSN(
        "You are inside a carriage in the west part of the " +
	"gypsy camp. From the interiors you draw the conclusion " +
	"that the owner of this carriage must be female."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_07", "east", 0);

    reset_room();
}
