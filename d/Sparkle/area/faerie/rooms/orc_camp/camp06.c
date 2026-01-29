/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "Orcs push past you, nearly knocking you down or into the tents.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();

    set_short("A dirty path in the northeast part of the camp");
    set_long(camp_desc4(extra_line));

    add_exit(OC_DIR + "camp07", "east");
    add_exit(OC_DIR + "camp02", "northwest");
    add_exit(OC_DIR + "camp03", "northeast");
    add_exit(OC_DIR + "camp10", "southwest");

}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SCOUT, WANDER);
}
