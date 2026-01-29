/*************************************************************************
 * - Cavern room                                                       - *
 * - Entrance                                                          - *
 * - Created by Damaris 03/2001                                        - *
 * - Recoded by Damaris 02/2002                                        - *
 *************************************************************************/
#pragma strict_types
#include "../defs.h"
inherit CAVE_BASE;

void
create_khalakhor_room()
{

    config_room("northern");

    add_exit("cav0201", "south");
    add_exit("cav0102", "east");
    add_fail("auto", "You walked into a wall!\n"+
      "Ouch! That's gotta hurt!\n");
      

}
