inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on mountain.");
    set_long(BSN(
	"The shrubs become very sparse and often there is nothing " 
	"but tough grass to cling to."
    ));
    
    add_item(({"mountain"}), BSN(
	"The mountain towers silent and sinister."
    ));						      

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "mount01", "down", 0);
    add_exit(VOLCANODIR + "mount03", "up", 0);
}


