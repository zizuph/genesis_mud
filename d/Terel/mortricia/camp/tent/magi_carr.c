/* A carriage. Mortricia 920927 */
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
#define HAUN_DIR        CAMP_DIR + "house/"

void
reset_room()
{
    object shrine, scroll;

    shrine = present("shrine");

    if (!shrine) {
        shrine = clone_object(TENT_DIR + "shrine");
        shrine -> move(TO);
	scroll = clone_object(TENT_DIR + "scroll");
	scroll -> move(shrine);
    } else {
	shrine -> add_prop(CONT_I_LOCK, 0);
	shrine -> add_prop(CONT_I_CLOSED, 0);
	scroll = present("scroll", shrine);
	if (!scroll) {
	    scroll = clone_object(TENT_DIR + "scroll");
	    scroll -> move(shrine);
	}
    }
    shrine -> add_prop(CONT_I_CLOSED, 1);
    shrine -> add_prop(CONT_I_LOCK, 1);
}

void
create_room()
{
    set_short("Magician's carriage");
    set_long(BSN(
        "You are inside the magician's carriage. He prefers to " +
	"have his carriage here, behind the tent, and not among " +
	"the others -- in fact, he is a very solitary person. " +
	"Moreover, he also seems to be that kind of man that " +
	"esteems spiritual values rather than wordly pleasures " +
	"or temporal affairs. Apart from the shrine, the only " +
	"thing in here is a small carpet."
    ));
    
    add_item(({"carpet"}), BSN(
        "It is a thin woven carpet."
    ));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TENT_DIR + "behind3", "east", 0);

    reset_room();
}
