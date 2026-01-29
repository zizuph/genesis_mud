/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The Crypt");
        set_long(BS(
           "You have entered the crypts beneath the temple of Mishakal."
	 + " Being here gives you an creeping feeling that causes a shiver"
	 + " to run up your spine. This place is dark and quite frankly very"
	 + " scary. All around you it is deathly silent, not even the rats"
	 + " dare to come here....", 70));

	add_exit(CDIR + "northcrypt1.c", "north", 0);
	add_exit(CDIR + "southcrypt1.c", "south", 0);
	add_exit(CDIR + "stairs.c", "west", 0);

	INSIDE
        DARK
}
