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

void
reset_room()
{
    object dwarf;
    int i;

    if (!present("dwarf", TO)) {
        for (i=0; i<NO_OF_DWARVES; i++) {
            dwarf = clone_object(TENT_DIR + "dwarf");
            dwarf -> move(TO);
        }
    }
}

void
create_room()
{
    set_short("Northwest corner");
    set_long(BSN(
        "You are standing among the audience in the northwestern " +
        "corner of the big tent, the manege is to the southeast. " +
	"There is a mast here."
    ));
    
    add_item(({"mast"}), BSN(
        "It's a sturdy mast, one out of two, that keeps this tent " +
        "risen. It looks to be fairly simple to climb it. A wire " +
        "of some kind seems to be fastened at the top of the mast."
    ));

    add_item(({"wire"}), "@@check_wire");

    add_item(({"manege"}), "@@check_manege");

    add_item(({"audience"}), BSN(
        "They are waiting for the show to start."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "tent_05", "east", 0);
    add_exit(TENT_DIR + "mast1"  , "up"  , "@@climb_up");

    reset_room();
}
