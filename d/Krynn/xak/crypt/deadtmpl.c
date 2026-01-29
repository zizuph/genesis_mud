/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
    set_short("The Temple of the Dead");
    set_long("You are in the temple of the dead. This is a part of " +
	     "the temple that in olden times would have only been " +
	     "entered by the priests and priestesses of Mishakal. A " +
	     "bas-relief of Mishakal graces the east wall. The room " +
	     "rises to be topped by a 60-foot dome.\n");
    
    add_exit(CDIR + "northtmpl.c", "north", 0);
    add_exit(CDIR + "southtmpl.c", "south", 0);
    
    add_item(({"relief", "bas-relief", "bas relief", "mishakal", "bas"}),
	     "@@bas");
    add_item("dome", "It's very high up.\n");
    INSIDE;
    DARK;
}

bas()
{
    write("It is quite simply a bas-relief in honour of this great " +
	  "goddess.\n");
    return "";
}

