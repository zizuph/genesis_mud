#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

#define PARENT  "/d/Krynn/"
#define TDIR    PARENT + "gnome/"

void
create_room()
{
    set_short("In a tunnel");
    
    set_long("This is a simple tunnel. You see more light to the " +
	     "south.\n");
    add_item(({"cave", "caves", "tunnel"}), "Hewn out of the solid rock, " +
	     "this tunnel leads in to the gnomish\ninventor guild.\n");
    add_exit(TDIR + "cavern32", "north", 0);
    add_exit(ROOMS + "galery", "south", 0);
    INSIDE;
    LIGHT;
}

wayout() { return "south north"; }
tohelp() { return "north"; }
fromhelp() { return "south"; }
area() { return "Neartheguild"; }
