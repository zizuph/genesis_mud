#pragma save_binary

#include "default.h"
#include "dom_base.h"

setup_func() {
	level_name = "one above ground";	/* level name */
	up =   "dom_a2"; 			/* room name above */
	up_fun = 0;			/* set to "@@blocked" to block exit */
	down = "domain";			/* room name below */
	down_fun = 0;			/* set to "@@blocked" to block exit */
	dirs = ({
		/* direction, prefix, domainname, dirfunction */
		/* nort, south, east, west */

		"north", " ", "Shire", "@@openway",
		"south", " ", "Krynn", "@@openway",
		"east",  " ", "Liwitch", "@@openway",
	});
}