#pragma save_binary

#include "default.h"
#include "dom_base.h"

setup_func() {
	level_name = "two above ground";
	up =   "dom_a3"; 	
	up_fun = "@@blocked";
	down = "dom_a1";
	down_fun = 0;
	dirs = ({
		/* direction, prefix, domainname, dirfunction */

		"north", " ", "Calia", "@@openway",
		"south", " ", "Gondor", "@@openway",
		"east", " ", "Emerald", "@@openway",
            "southeast", " ", "Relic", "@@openway",
            "west", " ", "Ansalon", "@@openway",
	});
}