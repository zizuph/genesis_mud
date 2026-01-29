/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "Shouts echo from the watchtower to the east.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr02";
    set_add_camp();
    reset_room();
    set_add_tower();
    
    set_short("At the northeastern edge of the camp");
    set_long(camp_desc1(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp03", "north");
    add_exit(OC_DIR + "camp11", "south");
    add_exit(OC_DIR + "camp06", "west");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    create_orcs(ORC_SCOUT, WANDER);
}
