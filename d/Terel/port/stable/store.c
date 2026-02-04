/* The stable store room. Mortricia 93111 */
inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#undef PORT
#define PORT "/d/Terel/port/"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define HORSE_DIR       MORTRICIADIR + "horses/"
#define RIDE_PROP       "_can_ride_here"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_room()
{
}

void
create_room()
{
    set_short("The rear parts of the stable");
    set_long(BSN(
        "The rear parts of the stable. What are you doing here?"
    ));
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(RIDE_PROP, 1);

    add_exit(PORT + "stable/stable", "east", 0);

    clone_object(PORT + "monster/mare")->move(TO);
    clone_object(PORT + "monster/stallion")->move(TO);
    clone_object(PORT + "monster/bstallion")->move(TO);
    clone_object(PORT + "monster/courser")->move(TO);

    reset_room();
}
