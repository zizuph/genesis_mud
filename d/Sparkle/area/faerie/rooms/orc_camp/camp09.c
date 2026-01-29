/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "Garbage and debris clog the path, making it difficult to " +
    "walk this way.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();
    
    set_short("A dirty path in the northwest part of the camp");
    set_long(camp_desc5(extra_line));

    add_exit(OC_DIR + "camp14", "south");
    add_exit(OC_DIR + "camp10", "east");
    add_exit(OC_DIR + "camp13", "southwest");


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
