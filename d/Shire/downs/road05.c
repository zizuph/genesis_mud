/*
 * Road to the Barrow Downs
 * By Finwe, December 2001
 */
 
//#pragma strict_types
 
#include "local.h"
inherit ROAD_BASE;

#define ER_DIR "/d/Shire/eastroad/western/"

void
create_road_room()
{
    set_area("west of the");
    set_extraline("The road suddenly crests a hill, looking over " +
        "everything south of it. The Downs are covered in grey " +
        "mists which dance about. Parts of the downs seem darker " +
        "and thicker than others, while an occasional hill pokes " +
        "up from the mists. The road runs south deeper into the " +
        "Downs and north away towards the Great East Road.");
    set_add_wight_sounds();

    add_exit(DOWNS_DIR + "road04", "north");
    add_exit(DOWNS_DIR + "road06", "southeast");
    
 
}

