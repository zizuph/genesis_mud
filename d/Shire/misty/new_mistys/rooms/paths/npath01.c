/*
 * Path in the Misty Mountains
 * By Finwe, September 2004
 */

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit PATH_BASE;

void
//create_room()
create_mt_room()
{
    set_vbfc_extra(path_desc1);

    add_exit(PATH_DIR + "npath02", "northeast",0,5);
    add_exit("/d/Shire/misty/p5", "south",0,5);
    //add_exit(PATH_DIR + "tpath02n1","up","@@climb_mt",0,1);
}

/*init()
{
    ::init();
    add_action("climb_mt", "climb");

}*/
