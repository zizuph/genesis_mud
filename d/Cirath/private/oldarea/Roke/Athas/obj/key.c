inherit "/std/object";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_object()
{
  set_short("hotel key");
	set_long(BSS("This small key is to one of the hotelrooms at the "+
		"Elfstone Taverna and Inn.\n"));
  set_adj("hotel");
  set_name("key");
  add_name("tjop_dej_rom");

	add_prop(OBJ_I_VALUE, 5);
}

