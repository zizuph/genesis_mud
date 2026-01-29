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
    set_vbfc_extra(path_desc2);

    add_exit(PATH_DIR + "npath28", "northwest",0,5);
    add_exit(PATH_DIR + "npath26", "east",0,5);
}
