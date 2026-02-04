inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"

create_room()
{
    set_short("on mountain.");
    set_long(BSN(
	"You are climb higher until nothing at all but the bare rock.  "
	"If it were not so very rough and and weathered you could scarcely " +
        "ascend it further.  The various knobs, ledges and pinnicles " +
	"help you greatly though."
    ));
    
    add_item(({"mountain"}), BSN(
	"The mountain towers silent and sinister."
    ));						      

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(VOLCANODIR + "mount03", "down", 0);
}


