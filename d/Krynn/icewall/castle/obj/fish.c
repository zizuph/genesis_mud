/* A piece of fish -- created by Stevenson */
/* this fish is part of the polar bear quest */

inherit "/std/food";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_food()
{
   set_name("fish");
	set_pname("fish");
   set_adj("salty");
   add_name("icefish");
   set_short("piece of salty fish");
   set_pshort("pieces of salty fish");
   set_long("This is a piece of fish which was caught in "
      + "the icewall sea, a favorite of polar bears.\n");
   set_amount(200);
}
