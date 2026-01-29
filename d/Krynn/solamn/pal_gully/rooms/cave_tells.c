#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
string
get_tells()
{
	string cavtell;
	cavtell = one_of_list(({"The lanterns flicker on the wall.\n",
	  "Giggling can be heard echoing through the mine.\n",
	  "An Aghar Dwarf runs past you, arms flailing.\n"}));
	return cavtell;
}