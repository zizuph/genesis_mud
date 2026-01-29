/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A watchtower stands southeast of here.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    tower_num = "twr04";
    set_add_camp();
    reset_room();
    set_add_tower();

    set_short("Along the southeast border of the camp");
    set_long(camp_desc5(extra_line));

    add_exit(OC_DIR + tower_num, "tower", add_tower_entr());
    add_exit(OC_DIR + "camp26", "west");
    add_exit(OC_DIR + "camp23", "northwest");
    add_exit(OC_DIR + "camp24", "northeast");
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
