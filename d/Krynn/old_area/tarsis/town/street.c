/* An outside room in Tarsis */

#include "/d/Krynn/common/defs.h" /* This one is always good to have */
#include "../local.h"             /* Tarsis defines */

inherit OUTROOM

public void
create_tarsis_room()
{
    set_short("Main street of Tarsis");
    set_long("You are standing on the main street of Tarsis, it runs " +
	     "north and south. To the east is an entrance to the a " +
	     "larger building.\n");

    add_item("street", "The street is rather dirty.\n");
    add_item("building", "The building is made of wood.\n");

    add_exit(TOWN + "building", "east");
}
