/* The weird shop's store room. Mortricia 920927 */
inherit "/std/room";
inherit "/lib/store_support";

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
#define WEP_DIR         MORTRICIADIR + "weapons/"
#define OBJ_DIR         MORTRICIADIR + "objects/weird/"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_room()
{
    object knife, sword, rolling_pin;
    object bag, oil;

    if (!present("knife", TO)) {
        knife = clone_object(WEP_DIR + "knife");
        knife -> move(TO);
    }
    if (!present("bag", TO)) {
        bag = clone_object(CAMP_DIR + "bag");
        bag -> move(TO);
    }
    if (!present("bottle", TO)) {
        oil = clone_object(CAMP_DIR + "oil_bottle");
        oil -> move(TO);
    }
}

void
create_room()
{
    set_short("Weird shop's store room");
    set_long(BSN(
        "The store room of the Weird Shop. What are you doing here?."
    ));
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "weird_shop", "south", 0);

    clone_object(WEP_DIR + "rolling_pin") -> move(TO);
    clone_object(WEP_DIR + "plain_sword") -> move(TO);
    reset_room();
}
