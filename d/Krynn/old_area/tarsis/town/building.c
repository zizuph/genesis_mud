/* A building in Tarsis */

#include "/d/Krynn/common/defs.h" /* A few useful defines */
#include "../local.h"             /* Tarsis defines */

inherit INROOM

create_tarsis_room()
{
    set_short("Inside building");
    set_long("You are inside a wooden building.\n");

    add_exit(TOWN + "street", "west");
}
