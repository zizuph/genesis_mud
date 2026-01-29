/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The Hall of the Ancestors");
        set_long(BS(
           "You find yourself in a large hallway. The floor of the hall"
	 + " is in a bad state of repair and has collapsed in several"
	 + " places. The hall is otherwise completely empty.", 70));

	add_exit(CDIR + "middlecrypt1.c", "west", 0);
	add_exit(CDIR + "southcrypt4.c", "south", 0);

	add_item("floor", "The floor has several large chasms in it that"
		+ " lead down into darkness.\n");

	INSIDE
        DARK
}
