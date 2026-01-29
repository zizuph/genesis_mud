/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#include "../../local.h"
#include <macros.h>

inherit  INROOM;

public void
create_xak_room()
{
    set_short("The North Temple");
    set_long("You are standing in the north temple. The floor here is is " +
	     "a bad state and an old sewer pipe protrudes from the floor " +
	     "and leads down into further darkness below.\n");

    add_exit(HALL + "deadtmpl", "south");
    add_exit(MIDDLE + "flourroom", "down", "@@down");

    add_item(({"pipe", "sewer pipe", "floor"}), "The Cataclysm seems to " +
	     "have forced the old sewer pipe up through the floor.\n");
}

public void
down()
{
    write("You slide down the sewer pipe a long way before finally " +
	  "it empties out into another room. You land on a huge " +
          "big bag full of flour which explodes and covers you and " +
          "the whole room is a fine white powder.\n");

    tell_room(TO, QCTNAME(TP) + " jumps into the sewer pipe and slides down " +
	      "into the darkness.\n", TP);
    return 0;
}
