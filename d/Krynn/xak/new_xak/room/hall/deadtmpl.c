/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#include "../../local.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  INROOM;

public void
create_xak_room()
{
    set_short("The Temple of the Dead");
    set_long("You are in the temple of the dead. This is a part of " +
             "the temple that in olden times would have only been " +
             "entered by the priests and priestesses of Mishakal. A " +
             "bas-relief of Mishakal graces the east wall. The room " +
             "rises to be topped by a sixty-foot dome.\n");

    add_item(({"relief", "bas-relief", "bas relief", "mishakal", "bas"}),
             "It is quite simply a bas-relief in honour of this great " +
             "goddess.\n");

    add_exit(HALL + "northtmpl", "north");
    add_exit(HALL + "southtmpl", "south");

}
