#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void
create_room()
{
    set_short("Pier");
    set_long("A heavy wooden pier extends into the River"
	+" Carnen here, where a faraway ship sometimes ties up.  A"
       +" stout wooden sign stands nearby.\n");

    add_exit(RHUN_DIR+"stown3/pier2","southeast");

    add_item("sign","The sign bears a picture of a donut covered "+
             "with white icing.\n");
}
