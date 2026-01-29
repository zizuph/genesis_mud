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

    set_short("Along the southeast border of the camp");
    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + "camp20", "northwest");
    add_exit(OC_DIR + "camp21", "northeast");
    add_exit(OC_DIR + "camp27", "southwest");
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
