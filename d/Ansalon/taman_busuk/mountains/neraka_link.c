#include "local.h"

inherit MOUNTAINS_BASE;

#include <macros.h>

void
create_mountains_room()
{
	set_short("road outside Neraka");
	set_long("This is the road outside Neraka, " +
	"crossing the dusty plains towards the mountains " +
	"north of here.\n");
    
	if (LOAD_ERR(MOUNTAINS_OBJECT))
      {
          write("Bug! please report immediately...\n");
          return;
      }

	add_exit("","north","@@enter_map:" + MOUNTAINS_OBJECT + "|N@@");
}
