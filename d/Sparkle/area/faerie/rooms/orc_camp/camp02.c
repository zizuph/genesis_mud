/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A watchtower looms over you from the north.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr08";

    set_short("Near the northern edge of the orc camp");
    set_add_camp();
    reset_room();
    set_add_tower();

    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp01", "west");
    add_exit(OC_DIR + "camp06", "southeast");
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
