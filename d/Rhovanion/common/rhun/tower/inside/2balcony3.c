inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
    set_short("Balcony");
    set_long("This is a stone balcony surrounding this tower at its"+
	" second floor.  The forest lies below and all around you." +
	"  Far off to the west, you can see the Sea of Rhun.\n");

    add_exit(RHUN_DIR+"tower/inside/2balcony4", "north", 0);
}
