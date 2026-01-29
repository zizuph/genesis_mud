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

    set_short("Near the western edge of the orc camp");
    set_long(camp_desc1(extra_line));

    add_exit(OC_DIR + "camp14", "east");
    add_exit(OC_DIR + "camp12", "west");
    add_exit(OC_DIR + "camp09", "northeast");
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
