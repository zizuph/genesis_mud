#pragma save_binary

#include "default.h"
#include "dom_base.h"

setup_func() {
	level_name = "one below ground";
	up =   "domain"; 	
	up_fun = 0;
	down = "dom_b2";
    down_fun = 0;
	dirs = ({
		/* direction, prefix, domainname, dirfunction */

		"north", " ", "Roke", "@@openway",
		"east", " ", "Kalad", "@@openway",
         "west", " ", "Rhovanion", "@@openway",
     "south"," ","Avenir","@@openway",
     "southwest"," ","Cirath","@@openway"
	});
}