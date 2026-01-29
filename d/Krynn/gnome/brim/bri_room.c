/* created by Aridor, 06/15/94 */
/* add_item("note") (line 27 was added by Macker as a temporary
		hint to mortals that there is a bug and
		"Brimsch" is unavailable. */

inherit "/d/Krynn/std/room";
#include "brimsch.h"

object gnome;

void
reset_room()
{
    if (gnome)
      return;
    gnome = clone_object(BRIMSCH);
    gnome->move_living("xxx",TO);
}


void
create_room()
{
    set_short("A small chamber");
    set_long("You are in a small chamber. It is a typical " +
	     "gnomish workroom with a large table in the " +
	     "middle and a lot of junk lying around.\n");
/*          + "You see a new note stuck on the wall with " +
	    "some sort of strange adhesive.\n");
	    add_item(({"note"}), "It says:\nOnVacation. WillBeBackSoon. -Brimsch.\n");
*/
    add_item(({"table","junk"}),"It is just junk that's lying " +
	     "on the table. You cannot detect anything useful " +
	     "here.\n");
    INSIDE;
    LIGHT;
    add_exit(HALLWAY,"west");
    seteuid(getuid(TO));
    set_alarm(1.0,0.0,"reset_room");
}
