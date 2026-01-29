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

    set_short("At the southwest border of the orc camp");
    set_long(camp_desc4(extra_line));

    add_exit(OC_DIR + "camp22", "south");
    add_exit(OC_DIR + "camp19", "east");
//    add_exit(OC_DIR + "forge",  "west");
    add_exit(OC_DIR + "camp12", "northwest");
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
