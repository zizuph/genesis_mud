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
#define NO_OF_HORSES    2

void
reset_room()
{
    object horse;
    int i;

    if (!present("horse", TO)) {
        for (i=0; i<NO_OF_HORSES; i++) {
            horse = clone_object(TENT_DIR + "horse");
            horse -> move(TO);
        }
    }
    if (!present("bottle")) {
        clone_object(CAMP_DIR + "oil_bottle")->move(TO);
    }
}

void
create_room()
{
    set_short("Shed");
    set_long(BSN(
        "This shed is used to keep the creatures between the shows."
    ));
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "behind2", "east", 0);

    reset_room();
}
