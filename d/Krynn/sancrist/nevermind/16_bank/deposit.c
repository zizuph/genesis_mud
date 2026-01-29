inherit "/d/Krynn/std/room";

#include "../local.h"
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_room()
{
    object deposit;

    set_short("gnome money deposit");
    set_long(BSN("This small room is divided in two by a thick brick wall. "
	+ "The only two openings in the wall are a steel door in the left "
	+ "part and a barred window directly in front of you. There is a "
	+ "large sign next to the window."));

    add_exit(GGUILD + "workshop", "east", 0);
    add_exit(GGUILD + "bank", "corner", "@@go_corner");
    INSIDE;
    LIGHT;

    add_item(({"window", "barred window"}), "There is a small wizened "
	+ "gnome sitting behind it.\n");
    add_item(({"door", "steel door"}), "It looks sturdy.\n");
    add_cmd_item(({"door", "steel door"}), "open", "It is locked.\n");
    add_cmd_item(({"door", "steel door"}), "unlock", "You don't have a "
	+ "key that fits.\n");

    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_no_show_composite(1);
    deposit->set_short("deposit");
    deposit->move(TO);
}

int
go_corner()
{
    write("You head for the little corner...\n");
    say(QCTNAME(TP) + " squeezes " + OBJECTIVE(TP) + "self into a corner.\n");
    return 0;
}
