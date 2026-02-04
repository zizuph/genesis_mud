inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("hill middle");
    set_long(
        "You are halfway down a hill which slopes gently downwards " +
	"towards a small cottage.  Singing birds trill and hover above you " +
        "on stuttering wings.  In the distance rocky crags and jagged peaks " +
	"form a majestic crest that pokes above the horizon.\n"
    );

    add_item(({"cottage", "small cottage"}), 
	"The cottage is to far away to get a good look at.  You could " +
	"probably get a better look at the bottom of the hill.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "hill_base", "north", 0);
    add_exit(TOMBDIR + "hill_top", "south", 0);    
}


