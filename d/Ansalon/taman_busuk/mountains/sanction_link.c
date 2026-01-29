#include "local.h"

inherit MOUNTAINS_BASE;

#include <macros.h>

void
create_mountains_room()
{
    set_short("road outside Sanction");
    set_long("This is the road just outside Sanction, " +
	"still lacking a proper long description.\n");
    
	if (LOAD_ERR(MOUNTAINS_OBJECT))
      {
          write("Bug! please report immediately...\n");
          return;
      }

	add_exit("","east","@@enter_map:" + MOUNTAINS_OBJECT + "|S@@");
}
