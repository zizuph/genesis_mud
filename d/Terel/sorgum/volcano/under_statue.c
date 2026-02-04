inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("under crag.");
    set_long(BSN(
	"The snow is uncounted thousands of feet above.  " +
	"You are below a crag whose titan bulge was not stayed as " +
	"the dawn of Genesis had shaped i, but which gleams red and " +
	"stupendous in the sunset with the carved and polished features " +
	"of a God."
    ));
    
    add_item(({"statue", "crag"}), BSN(
	"Mortals could have fashioned it.  It must have been chisled " +
	"by the hands of Gods.  It looks down haughty and majestic upon " +
        "you.  The long, narrow eyes, and long-lobbed ears and thin nose " +
        "and pointed chin all speak of a race that is not of men but of "
        "Gods."				       
    ));						      

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "precip02", "east", 0);
}


