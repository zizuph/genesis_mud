#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
   set_short("Southeastern Square");
   set_long("This is the southeastern part of the school's "
        +"training square.  Milling about are numerous "
        +"adepts in the process of training in weapons. "
        +"In the middle of the square is a large stone "
        +"fountain that is, of course, dry.\n");

   add_item("square","This square is the central courtyard "
        +"of the school and is made of hard packed dirt.\n");
   add_item("fountain","A large stone fountain with a "
        +"sculpture of a water elemental adorning the top. "
        +"At some point, you are sure that water would come "
        +"out of the sculpture, but that was long ago.\n");


	OUTSIDE;

	add_exit(WWORK+"sq4.c", "north", 0, 0);
	add_exit(WWORK+"sq1.c", "west", 0, 0);
}
