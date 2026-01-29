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
    set_add_tower();
    
    set_short("At the Eastern edge of the camp");
    set_long(camp_desc1(extra_line));

    add_exit(OC_DIR + "camp11", "north");
    add_exit(OC_DIR + "camp16", "west");
    add_exit(OC_DIR + "camp20", "southwest");
    add_exit(OC_DIR + "camp21", "southeast");


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
