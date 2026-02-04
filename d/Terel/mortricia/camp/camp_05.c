/*
  A camp room. Mortricia 920927
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

object gypsy_5;

void
reset_room()
{
    if (!gypsy_5) {
        gypsy_5 = clone_object(CAMP_DIR + "gypsy");
        gypsy_5 -> move(TO);
    }
}

void
create_room()
{
    set_short("Northern part of camp");
    set_long(BSN(
        "You are standing in the northern part of the camp " +
        "between two tents."
    ));
    
    add_item(({"sign"}), BSN(
        "It's an ordinary sign with readable letters on it."
    ));

    add_cmd_item("sign", "read", BSN(
        "The sign reads:\n" +
        "WEIRD SHOP"
    ));
    add_item(({"tents", "tent"}), BSN(
        "There are a northern tent and a southern tent."
    ));
    add_item(({"northern tent"}), BSN(
        "The north tent has an exit. " +
        "There is a sign above the exit."
    ));
    add_item(({"southern tent"}), BSN(
        "This tent has no entry on this side, but noise and " +
        "laughter from many people emerges from it."
    ));


    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_04", "east" , 0);
    add_exit(CAMP_DIR + "weird_shop"   , "north", 0);
    add_exit(CAMP_DIR + "camp_06", "west" , 0);

    reset_room();
}
