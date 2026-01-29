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

    tower_num = "camp12";

    reset_faerie_room();

    set_short("Inside a watchtower");
    set_long(tower_desc(extra_line));

    add_exit(OC_DIR + "twr06_1", "up");
    add_exit(OC_DIR + tower_num, "out", add_tower_exit());   
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
}
