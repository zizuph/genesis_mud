/* A tent room. Mortricia 921025 */
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
create_room()
{
    set_short("Small backyard");
    set_long(BSN(
	"You are standing on a small backyard behind a big " +
	"tent. You can enter the tent via a small opening " +
	"to the northeast. West from here is a carriage."
    ));
    add_item(({"carriage", "wagon"}), BSN(
	"It's a weird looking wagon, you can enter it by " +
	"going west."
    ));
    add_item(({"opening"}), BSN(
	"The opening has been made in the canvas."
    ));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(TENT_DIR + "behind2",   "northeast", 0);
    add_exit(TENT_DIR + "magi_carr", "west" , 0);
}
