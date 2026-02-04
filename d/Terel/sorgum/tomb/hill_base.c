inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("hill base");
    set_long(
        "You are at the base of a hill which slopes gently " +
        "downwards towards a small cottage.  Singing birds trill and " +
	"hover above you on stuttering wings.  In the distance rocky crags " +
        "and jagged peaks form a majestic crest that pokes above the " +
        "horizon.  A small cottage lies west of here.\n"
    );

    add_item(({"cottage", "small cottage"}), 
	"The cottage is obscured by trees.  You could " +
	"probably get a better look if you go around the trees to the west.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "hill_mid", "south", 0);    
    add_exit(TOMBDIR + "cottage_front", "west", 0);
}


