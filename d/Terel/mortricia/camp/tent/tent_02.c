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
    object human;
    int i;

    if (!present("human", TO)) {
        for (i=0; i<NO_OF_HUMANS; i++) {
            human = clone_object(TENT_DIR + "human");
            human -> move(TO);
        }
    }
}

void
create_room()
{
    set_short("Big tent");
    set_long(BSN(
        "You are standing among the audience in the big tent. " +
        "To the southwest is a manege and far above it you " +
        "see some kind of wire going across the tent."
    ));
    
    add_item(({"manege"}), "@@check_manege");
    add_item(({"wire"}), "@@check_wire");

    add_item(({"audience"}), BSN(
        "They are waiting for the show to start."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "tent_01", "north", 0);
    add_exit(TENT_DIR + "tent_03", "south", 0);
    add_exit(TENT_DIR + "tent_05", "west" , 0);

    reset_room();
}
