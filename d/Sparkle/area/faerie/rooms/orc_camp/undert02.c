/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_TOWER_BASE;


void
create_tower_room()
{
    setuid(); 
    seteuid(getuid());

    reset_faerie_room();

    set_short("Third level of the tall tower");
    set_long(short() + ". Crude holes have been cut into the log walls. Scratches and gouges are visible in the walls from the orcs. Debris is scattered across the floor. A ladder leads up and down through the tower.\n");

    add_tower_stuff();

    add_exit(OC_DIR + "undert03", "up");
    add_exit(OC_DIR + "undert01", "down");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    create_orcs(ORC_SOLDIER, NO);
}
