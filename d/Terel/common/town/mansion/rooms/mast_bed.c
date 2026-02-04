/* The Marquis' bed room. Mortricia 920912 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define BSN(message)   break_string(message + "\n", 70)
#define TP             this_player()
#define TO             this_object()

int cleaned;

void
create_room()
{
    set_short("Bedroom");
    set_long(BSN(
	"This used to be a bedroom. The remnants of a large " +
	"canopied bed are scattered along the eastern wall. " +
	"There is a window above the remnants."
    ));
    add_item("window", "@@exa_window");
    add_item(({"bed", "remnants", "remnant"}),
        "The canopied bed is far too destroyed to be of use anymore. " +
        "It must have been here a long time.\n");
    add_cmd_item("window", "clean", "@@do_clean");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "rooms/mast_room", "north", 0);

    cleaned = 0;
}

exa_window()
{
    string str;

    if (cleaned) {
	str = "You see some snow-covered fields and trees, " +
	      "and that reminds you how cold it is there.";
    } else {
	str = "The window is too dirty, you cannot see anything " +
	      "through it.";
    }
    return BSN(str);
}

do_clean()
{
    string str;

    if (cleaned) {
	str = "The window is not dirty.";
    } else {
	cleaned = 1;
	str = "You clean off the dirt and dust from the window.";
    }
    return BSN(str);
}
