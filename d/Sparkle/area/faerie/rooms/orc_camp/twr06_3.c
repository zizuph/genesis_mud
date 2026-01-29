/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_TOWER_BASE;

string extra_line = "";

void
create_tower_room()
{
    setuid(); 
    seteuid(getuid());

    reset_faerie_room();

    set_short("Top level of watchtower");
    set_long(tower_top(extra_line));

    add_tower_stuff();

    add_exit(OC_DIR + "twr06_2", "down");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    create_orcs(ORC_OFFICER, NO);
}
