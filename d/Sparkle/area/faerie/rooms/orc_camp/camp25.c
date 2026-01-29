/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A watchtower stands south of here.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr05";
    set_add_camp();
    reset_room();
    set_add_tower();

    set_short("Along the southern border of the camp");
    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp26", "east");
    add_exit(OC_DIR + "camp22", "northwest");
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
