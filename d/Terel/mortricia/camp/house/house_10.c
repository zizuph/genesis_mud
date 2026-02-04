/* A haunted room. Mortricia 920927 */
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
#define HAUN_DIR        CAMP_DIR + "house/"

object zombie;

void
reset_room()
{
    if (!zombie) {
        zombie = clone_object(HAUN_DIR + "zombie");
        zombie -> move(TO);
    }
}

void
create_room()
{
    set_short("Tunnel");
    set_long(BSN(
        "You are standing in an under-ground tunnel. " +
        "The tunnel goes south from here. " +
        "A ladder goes up through a hole in the ceiling."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAUN_DIR + "house_1", "up", "@@z_attack");
    add_exit(HAUN_DIR + "house_9", "south", 0);

    reset_room();
}

z_attack()
{
    if (zombie && present("zombie", TO)) {
        zombie -> command("say I'll kill you!");
    }
    return 0;
}
