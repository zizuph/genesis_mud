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
    
    set_short("A dirty path near the northern part of the camp");
    set_long(camp_desc2(extra_line));

    add_exit(OC_DIR + "camp15", "south");
    add_exit(OC_DIR + "camp09", "west");
    add_exit(OC_DIR + "camp05", "northwest");
    add_exit(OC_DIR + "camp06", "northeast");
    add_exit(OC_DIR + "camp16", "southeast");


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
