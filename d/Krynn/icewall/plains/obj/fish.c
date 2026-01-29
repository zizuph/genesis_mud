/* Created by Macker 11/5/94 */

inherit "/std/food";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_food()
{
   set_name("fish");
	set_pname("fish");
   set_short("piece of fish");
   set_pshort("pieces of fish");
   set_long("This is a piece of fish which was caught in "
	+ "the ice village pond. Although polar bears prefer a different sort, " +
		"the ice villagers favor these fish.\n");
   set_amount(200);
}
