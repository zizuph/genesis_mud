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
#include "/d/Terel/mortricia/camp/tent/tent.h"

object guard;

void
reset_room()
{
    if (!guard) {
        guard = clone_object(TENT_DIR + "b_guard");
        guard -> move(TO);
    }
}

void
create_room()
{
    set_short("At the southeastern corner");
    set_long(BSN(
        "You are standing among the audience in the southeastern " +
        "corner of the big tent. The manege is to the northwest. " +
	"There is a mast here. To the " +
        "southwest there is a curtain that prevents you to " +
        "see the rear parts of the tent."
    ));
    
    add_item(({"mast"}), BSN(
        "It's a sturdy mast, one out of two, that keeps this tent " +
        "risen. It looks to be fairly simple to climb it. A wire " +
        "of some kind seems to be fastened at the top of the mast."
    ));
    add_item(({"wire"}), "@@check_wire");
    add_item(({"manege"}), "@@check_manege");

    add_item(({"audience"}), BSN(
        "They are awaiting a performance."
    ));

    add_item(({"curtain"}), BSN(
        "The thick curtain glitters."
    ));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 75);

    add_exit(TENT_DIR + "tent_03", "north"    , 0);
    add_exit(TENT_DIR + "behind1", "southwest", "@@go_rear");
    add_exit(TENT_DIR + "mast2"  , "up"       , "@@climb_up");

    reset_room();
}

go_rear()
{
    if (TP -> query_wiz_level() > 0)
        return 0;

    if (TP == guard) return 0;
    if (guard && present(guard) && CAN_SEE(guard, TP)) {
        write("The guard stops you from going there.\n");
        say("The guard stops " + QCTNAME(TP) + " from going " +
            "southwest.\n");
        return 1;
    } else {
        return 0;
    }
}
