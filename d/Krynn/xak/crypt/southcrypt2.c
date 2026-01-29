/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

object dwarf, dwarf2;

create_xak_room()
{
        set_short("The South Crypt");
        set_long(BS(
           "You are in the middle of south corridor of the crypt beneath"
	 + " the temple of Mishakal. Coffins line the walls here"
	 + " and the stench of death assails your nostrils."
	 + "", 70));

	add_exit(CDIR + "southcrypt3.c", "east", 0);
	add_exit(CDIR + "southcrypt1.c", "west", 0);

	add_item(({"crypt", "coffin", "coffins"}), "@@coffin");
	INSIDE;
        DARK;
}

reset_xak_room()
{
	if (!dwarf)
	{
		dwarf = clone_object(MONSTER + "gully.c");
		dwarf->move(TO);
	}
	if (!dwarf2)
	{
		dwarf2 = clone_object(MONSTER + "gully.c");
		dwarf2->move(TO);
	}
}

coffin()
{
		write(BS("You examine the surrounding crypt and coffins."
	 	 + " Everything seems normal. Well as normal as can be"
		 + " expected for such a gloomy place as this.", 70));
		return "";
}



