/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A watchtower stands to the west.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr06";
    set_add_camp();
    reset_room();
    set_add_tower();
    
    set_short("The western edge of the orc camp");
    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp08", "north");
    add_exit(OC_DIR + "camp13", "east");
    add_exit(OC_DIR + "camp18", "southeast");
}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SOLDIER, WANDER);
}
