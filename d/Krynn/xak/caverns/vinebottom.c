/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("An old house");
        set_long("You are standing in an old deserted house. The east " +
		 "wall of the house is completely gone and instead there " +
		 "is a cliff face covered in vines that rises up through " +
		 "the roof and into darkness. Water cascades down the " +
		 "vines, into the house and out through the doorway into " +
		 "the street outside.\n");

	add_exit(DDIR + "street1.c", "west", 0);

	add_item(({"cliff", "cliff face", "vine", "vines", "water", "stream"}),
		 "@@vine");

	INSIDE;
        DARK;
}

init()
{
	::init();
	ADA("climb");
}

climb(str)
{
	NF("Climb what? climb up?\n");
	if (str != "vine" && str != "vines" && str != "up" &&
	    str != "cliff" && str != "cliff face")
	  return 0;
	write("You try to climb up the vines but they are just too " +
	      "slippery.\n");
	SAY(" tries to climb up the vines but they are just too slippery.");
	return 1;
}

vine()
{
	write("Vines cover the cliff face are made very slippery by the" +
	      " water that cascades down from somewhere above.\n");
	return "";
}
