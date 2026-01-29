/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

void
create_tunnel()
{
    add_std_herbs("underground");

    set_short("A cave ledge");
    set_long("This is a ledge inside the cave. It is wide rough looking " +
        "and seems to stretch  deep into the mountain. Thick darkness " +
        "fills the cave, and the only source of light comes from down " +
        "below near the entrance.\n");
    add_item(({"ledge"}),
        "It is an irregular shaped rock. The ledge is rough and wide.\n");

    reset_room();
    
    add_exit(TUN_DIR + "cv03", "east");
    add_exit(TUN_DIR + "cv01", "up");

}
void
init()
{
   ::init();
}

void
reset_room()
{
    set_searched(0);
}