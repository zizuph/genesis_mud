/*
 * The orc camp of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"

inherit OC_BASE;

string extra_line = "A large watchtower looms to the west.";

void
create_camp_room()
{
    setuid(); 
    seteuid(getuid());

    set_add_camp();
    set_add_tower();
    reset_room();

    set_short("At the western edge of the orc camp");
    set_long(camp_desc5(extra_line));

    add_exit(OC_DIR + "camp12", "south");
    add_exit(OC_DIR + "camp04", "northeast");


}


public void
init()
{
    ::init();

}
void
reset_room()
{
    create_orcs(ORC_SCOUT, WANDER);
}
