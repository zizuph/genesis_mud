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

object gypsy_12;

void
reset_room()
{
    if (!gypsy_12) {
        gypsy_12 = clone_object(CAMP_DIR + "gypsy");
        gypsy_12 -> move(TO);
    }
}

void
create_room()
{
    set_short("Outside star carriage");
    set_long(BSN(
        "To the north there is a small carriage painted with " +
        "blue stars. There is a sign on the wall."
    ));
    
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));

    add_cmd_item("sign", "read", BSN(
        "The sign reads:\n" +
        "I will tell you about your future, please enter.\n" +
        "                    Tecla, Fortune Teller."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_06"  , "south", 0);
    add_exit(CAMP_DIR + "fort_carr", "north", 0);

    reset_room();
}
