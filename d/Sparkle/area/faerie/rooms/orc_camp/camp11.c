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

    set_short("Eastern edge of the orc camp");
    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + "camp07", "north");
    add_exit(OC_DIR + "camp17", "south");


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
