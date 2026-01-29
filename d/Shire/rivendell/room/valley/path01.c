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
 
    set_extraline("The valley is peaceful and serene here. " +
        "This is one of the last refuges for elves in the " +
        "world. Everywhere you look, you see their fair faces " +
        "and hear their melodious voices. Northeast will take " +
        "you to the Last Homely House of Elrond while southwest " +
        "will take you to the base of the ridge.");

    add_item(({"house", "last homely house", "house of elrond", 
            "last homely house of the east", 
            "last homely house east of the sea"}),        
        "The house stands in the distance in the center of the " +
        "valley. Details can't be made out from this distance " +
        "other than it looks large.\n");

 
    add_exit(VALLEY_DIR + "stairs02", "southwest");
    add_exit(VALLEY_DIR + "path02",   "northeast");
 
}
 
string short_desc()
{
    return "A path in the valley of Imladris";
}
