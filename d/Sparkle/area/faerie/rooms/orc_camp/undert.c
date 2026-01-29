/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_TOWER_BASE;

string extra_line = "The tower is round and constructed of solid logs sunk into the dirt. Thick strips of leather hold the logs together. A heavy ladder leads up into the tower.";

void
create_tower_room()
{
    setuid(); 
    seteuid(getuid());

    reset_room();

    set_short("Under the tall tower");
    set_long(tower_desc(extra_line));

    add_exit(OC_DIR + "undert01", "up");
    add_exit(OC_DIR + "camp15", "north");
    add_exit(OC_DIR + "camp23", "south");
    add_exit(OC_DIR + "camp20", "east");
    add_exit(OC_DIR + "camp19", "west");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_GUARD, NO);
}
