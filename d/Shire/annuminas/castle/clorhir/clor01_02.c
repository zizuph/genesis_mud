/* 
   Annuminas/castle/clorhir/01_02.c 
 */

#include "defs.h"
#include <ss_types.h>

inherit CLORHIR_BASE_ROOM;

void
create_clorhir_room()
{
    set_short("orange courtyard");
    set_long("@@psg_desc2@@\n");

    add_my_desc("Piles of dirt lay scattered where you fell into " +
        "the passage.\n");
    add_prop(ROOM_I_LIGHT, 0);    

//    add_exit(BAR_DIR + "bar01_02", "south");

}
