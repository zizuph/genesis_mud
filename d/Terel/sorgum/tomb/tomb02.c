inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

#define COFFIN (TOMBDIR + "coffin")

init()
{
     ::init();
     add_action("enter_coffin", "enter");
}

void
create_room()
{
    set_short("Downstairs in tomb");
    set_long(
        "You have decsended the stone steps into the dark recesses of the " +
	"tomb.  There are many marble slabs bearing coffins or remains of " +
	"coffins.  There is an archway above the an exit to the north.\n"
    );

    add_item(({"coffins"}), 
        "Some of the coffins are sealed and intact while others have " +
	"nearly vanished leaving silver handles and plates isolated " +
        "amidst certain curious heaps of white dust.  One newer coffin " +
	"in particularly interesting and bears an inscription.\n"
    );

    add_item(({"dust", "white dust"}), 
	"The white dust is the decayed remains of bones and sinews.\n"
    );

    add_item(({"arch", "archway"}), 
	"The arch is covered with funeral carvings.\n"
    );

    add_item(({"new coffin", "newer coffin", "interesting coffin"}), 
	"The coffin's interior is lined with fine velvet.  It actually " +
	"looks rather comfortable and inviting.  The lid of the coffin " +
        "is splintered riddled with holes.  The edges of the holes have " +
        "deposits of crusted blood around them.  The coffin has an " +
	"inscription on it.  Perhaps you should examine it.\n"
    ); 

    add_item(({"inscription"}), 
        "The inscription bears the unmistakable letters of YOUR name!\n" 
    );

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(TOMBDIR + "tomb01", "up", 0);	      
    add_exit(TOMBDIR + "tomb03", "north", 0);
	      
}

int enter_coffin(string str)
{
     notify_fail("Enter what?\n");
     if ((str == "coffin") || (str == "newer coffin")) {

     if (COFFIN->is_occupied()) {
	  write("Someone is already in there.  You can't enter it now.\n");
	  tell_room(QCTNAME(TP) + "tries to enter the occupied coffin.\n");
     }
     else {
	    TP->move_living("X", TOMBDIR + "coffin");
	    tell_room(QCTNAME(TP) + "enters the coffin.\n");
       }

     return 1;
    }

   return 0;
}
