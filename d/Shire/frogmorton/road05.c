/*
 * The road thru Frogmorton
 * By Finwe, September 1998
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
 
inherit ROAD_BASE;
 
void
create_street()
{
    set_extraline("This is the west end of the village. It is " +
        "very quiet and peaceful. The only activity is from a " +
        "smial to the east of a well to do hobbit.\n");
 
     
    add_exit(FROG_DIR + "smial04", "east");
    add_exit(FROG_DIR + "road04", "west");
 
}
 
