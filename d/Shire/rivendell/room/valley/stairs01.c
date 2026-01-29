/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#include "local.h"
//#include "/d/Shire/private/shire_admin.h"
 
inherit VALLEY_BASE; 
 
 
void
create_valley_room()
{
    set_area("in a");
    set_areaname("valley");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("set of stairs");
    set_grass("sparse, dry");
    set_treetype("deciduous");;
 
    set_extraline("These steps curve around the plateau as they " +
        "descend into the valley. Melodic elvish voices fill " +
        "the air.");
 
    add_item(({"deciduous trees", "deciduous tree", "deciduous"}),
        "Large beech and oak trees cover the valley below.\n");
    add_item(({"stairs", "steps", "staircase"}),
        "The stairs are constructed of stone blocks set into " +
        "the side of the mountain. The stones are so expertly " +
        "set that you hardly notice the cracks between the " +
        "steps. The steps wind their way down towards the " +
        "valley and up towards the forest.\n");
    add_item(({"house", "last homely house", "house of elrond", 
            "last homely house of the east", 
            "last homely house east of the sea"}),        
        "The house stands in the distance in the center of the " +
        "valley. Details can't be made out from this distance " +
        "other than it looks large.\n");
    add_item(({"stone blocks", "blocks"}),
        "The stone blocks are expertly cut and set into the " +
        "side of the mountain. They make up the steps of " +
        "the staircase and are smooth.\n");
    add_item(({"cracks", "crack"}),
        "The cracks are between the stone blocks of the " +
        "staircase. They are very fine and hardly noticeable.\n");
 
    add_exit(VALLEY_DIR + "stairs02", "down", 0, 1);
    add_exit(FOREST_DIR + "plateau", "up","@@from_valley@@", 1);
 
}

string short_desc() 
{
    return "Some stairs on the side of a forest plateau";
}


void from_valley()
{
//    TELL_ADMIN(TP->query_cap_name() + ", ("+TP->query_alignment()+
//        ") left Rivendell at " + ctime(time()));
}