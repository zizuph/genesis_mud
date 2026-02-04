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

void
reset_room()
{
    object gem;

    if (!present("gem", TO)) {
        gem = clone_object(MORTRICIADIR + "objects/gem");
        gem -> move(TO);
    }
}

void
create_room()
{
    set_short("Rear part of big tent");
    set_long(BSN(
        "You are standing in the rear parts of the performance " +
        "tent. You aren't supposed to be here so if a guard " +
        "approaches you better run. The manege is to the " +
        "northwest. There is a curtain to the northeast, and " +
        "to the south there is another exit."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "tent_04" , "northeast", 0);
    add_exit(TENT_DIR + "manege"  , "northwest", 0);
    add_exit(TENT_DIR + "behind2" , "south"    , 0);

    reset_room();
}
