#pragma save_binary

#include "default.h"
#include "dom_base.h"

setup_func() {
	level_name = "one above ground";
	up =   "dom_a2"; 	
	up_fun = 0;
	down = "domain";
	down_fun = 0;
	dirs = ({
		/* direction, prefix, domainname, dirfunction */

		"north", " ", "Shire", "@@openway",
		"south", " ", "Krynn", "@@openway",
		"east",  " ", "Liwitch", "@@openway",
		"west",  " ", "Terel", "@@openway"
	});
}
