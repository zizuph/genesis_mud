/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
 
    set_extraline("The air is fresh and warm here. It seems " +
        "to relax your mind and body as you stand here. East " +
        "you see a bridge in the valley and southwest takes you " +
        "towards the stairs at the base of the ridge."); 

    add_item(({"house", "last homely house", "house of elrond", 
            "last homely house of the east", 
            "last homely house east of the sea"}),        
        "The house stands in the distance in the center of the " +
        "valley. Details can't be made out from this distance " +
        "other than it looks large.\n");
    add_item(({"bridge", "stone bridge"}),
        "The bridge is large and spans a river.\n");
 
    add_exit(VALLEY_DIR + "path01", "southwest");
    add_exit(VALLEY_DIR + "path03",  "east");
 
}
 
string short_desc()
{
    return "A path in the valley of Imladris";
}
