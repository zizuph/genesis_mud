#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/gnome/local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void
create_room()
{
    set_short("The gallery");

    set_long(BSN("You find yourself in a long gallery. This is at least what the " +
	"shiny sign on the west wall claims. You're puzzled because you " +
	"cannot find any pictures in here. The cave is brightly " +
	"illuminated by two rows of torches along the tunnel's " +
	"walls. There is a note affixed to the wall beneath the " +
	"sign and a white, round spot painted onto the floor."));

    add_exit(GGUILD + "tunnel1", "north", 0);
    add_exit(GGUILD + "joinroom", "southwest", "@@myexit", 0);
    INSIDE;
    LIGHT;

    add_item(({"torches", "rows of torches"}),
	"The torches are mounted equally spaced along the walls. "
	+ "There are light squares in between each set of two.\n");
    add_item(({"squares", "light squares"}),
	"Obviously some pictures used to be there.\n");
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock, " +
	"this tunnel leads to the gnomish\ninventor guild.\n");
    add_item(({"note", "sign"}), "You can read it.\n");
    add_cmd_item("note", "read", BSN("The pictures have been removed recently to " +
	"allow installation of a new revolutionary product of Gnomish Industries. " +
	"Using the automatic-picture-viewer it won't be necessary any more to " +
	"do that tiresome walking about and turning around but you will be " +
	"able to view the pictures of our greatest inventors from this point. " +
	"For your convenience the point has already been installed."));
    add_cmd_item("sign", "read", "'Gallery of Inventors'.\n");
    add_item(({"spot", "white spot", "white round spot", "point", "point"}), 
	"It is white and round and you can stand on it.\n");
    add_cmd_item(({"on spot", "on white spot", "on white round spot", "on point"}), "stand",
	"You manage to stand on the spot. Unfortunately nobody notices.\n");
}

int
myexit()
{
    write("Walking to the southwest you see the cave becoming higher and "
	+ "higher.\n");
    return 0;
}

wayout() { return "south north"; }
tohelp() { return "north"; }
fromhelp() { return "south"; }
area() { return "Neartheguild"; }
