inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

object dweller1;
object dweller2;

init()
{
     ::init();
}


reset_room()
{
    if (!dweller1) {
        dweller1=clone_object(TOMBDIR + "dweller4");
        dweller1->move(this_object());
    }

    if (!dweller2) {
        dweller2=clone_object(TOMBDIR + "dweller4");
        dweller2->move(this_object());
    }

    if ((dweller1) && (dweller2))
        dweller1->team_join(dweller2);
}


void
create_room()
{
    object door;
    
    set_short("Under the tomb");
    set_long(
        "Underneath the tomb the air is cold and damp and filled with " +
	"a sickening musty stench.  Filthy water drips from the walls and " +
        "ceiling.\n"
    );

    add_prop(ROOM_I_INSIDE,1);    
/*
    add_exit(TOMBDIR + "tomb_core", "north", -3);
*/
    /*    add_exit(TOMBDIR + "tomb_core", "east", "@@go_east"); */
    add_exit(TOMBDIR + "under_ne3", "southeast", -3);
    add_exit(TOMBDIR + "under_nw3", "southwest", -3);
    reset_room();
}

go_north()
{
    if (dweller1 && dweller1->query_name() != "corpse") {
	dweller1->command("slap " + TP->query_real_name());
	dweller1->command("say You ain't getting by me.");
	return 1;
    }

    if (dweller2 && dweller2->query_name() != "corpse") {
	dweller2->command("slap " + TP->query_real_name());
	dweller2->command("say You ain't getting by me.");
	return 1;
    }

    return 0;
}

go_east()
{
     write("Ummm, no way.  Even Benton is afraid to go that way.  " +
	   "Maybe at a later date it will be safer.\n");
	   
     return 1;
}
