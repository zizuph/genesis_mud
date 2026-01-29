/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "To the northwest is a tall watchtower.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr07";
    set_add_camp();
    reset_room();
    set_add_tower();

    set_short("A dirty path along the northwest edge of the camp");
    set_long(camp_desc4(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp01", "northeast");
    add_exit(OC_DIR + "camp08", "southwest");
}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_THRALL, WANDER);
}
