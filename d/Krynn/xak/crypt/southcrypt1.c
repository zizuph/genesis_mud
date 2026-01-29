/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The South Crypt");
        set_long(BS(
           "You are in the south corridor of the crypt beneath"
	 + " the temple of Mishakal. Coffins line the walls here"
	 + " and the stench of death assails your nostrils."
	 + " To the east you can hear faint sounds of activity.", 70));

	add_exit(CDIR + "southcrypt2.c", "east", 0);
	add_exit(CDIR + "entry.c", "north", 0);

	add_item(({"crypt", "coffin", "coffins"}), "@@coffin");
	INSIDE
        DARK
}

init()
{
	::init();
	ADA("listen");
}

listen(string str)
{
	write("The faint sounds are coming from your east. It sounds like"
	 + " creatures talking.\n");
	return 1;
}

coffin()
{
		write(BS("You examine the surrounding crypt and coffins."
	 	 + " Everything seems normal. Well as normal as can be"
		 + " expected for such a gloomy place as this.", 70));
		return "";
}
