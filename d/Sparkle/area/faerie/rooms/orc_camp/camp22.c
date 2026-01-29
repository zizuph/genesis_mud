/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();
    
    set_short("Along the southwest border of the camp");
    set_long(camp_desc1(extra_line));

    add_exit(OC_DIR + "camp18", "north");
    add_exit(OC_DIR + "camp25", "southeast");
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
