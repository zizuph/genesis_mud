/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "There is a tall watchtower to the north.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr01";

    set_add_camp();
    reset_room();
    set_add_tower();
    
    set_short("At the northeastern edge of the camp");
    set_long(camp_desc3(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp07", "south");
    add_exit(OC_DIR + "camp06", "southwest");

}


public void
init()
{
    ::init();

}
void
reset_room()
{
}
