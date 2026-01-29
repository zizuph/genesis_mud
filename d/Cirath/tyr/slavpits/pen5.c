inherit "std/room";
#include "defs.h"
#include <stdproperties.h>

object mon=0;

void
create_room()
{
	set_short("");
	set_long("

	add_item(({ })

	LIGHT

	add_exit(
}
reset_room()
{
	seteuid(getuid(TO));
	if(mon)
	  return;
	mon = clone_object(+"");
	mon->move(TO);
}

