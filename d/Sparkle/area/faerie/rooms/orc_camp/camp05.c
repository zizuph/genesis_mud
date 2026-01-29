/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "Filth and garbage lay all over the camp, and trampled " +
    "under foot in the mud.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();

    set_short("A dirty path in the northern part of the camp");
    set_long(camp_desc3(extra_line));

    add_exit(OC_DIR + "camp01", "north");
    add_exit(OC_DIR + "camp10", "southeast");

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
