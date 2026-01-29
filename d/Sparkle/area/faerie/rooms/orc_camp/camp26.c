/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "Watchtowers surround the path.";
void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    reset_room();
    set_add_tower();
    
    set_short("A dirty path in an orc camp");
    set_long(camp_desc4(extra_line));

    add_exit(FOREST_DIR + "path03", "south");
    add_exit(OC_DIR + "camp27", "east");
    add_exit(OC_DIR + "camp25", "west");
}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_THRALL, NO);
}
