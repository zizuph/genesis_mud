inherit "/std/room";
#include "/d/Calia/tmp/abbrev.h"
#include <stdproperties.h>

void
set_guest_to(string str)
{
    string str1, str2, str3;

    if (!sscanf(str, "%s %s %s", str1, str2, str3))
	;
}

void
create_room()
{
    set_short("Crystal Dome");
    set_long(BS(
	"This is a crystal dome.  " +
	"White light shines in from the spires above, the rays focusing on a " +
	"central desk.  " +
	"\n"));
    add_exit("/d/Calia/tmp/glykron/palace/stairs", "down", 0);
}
