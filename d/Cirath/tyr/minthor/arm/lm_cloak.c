inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("cape");
   set_adj("velvet");
   add_adj("red");
   set_short("red velvet cape");
   set_long("Reaching from the back of the neck almost to the "
	+"floor, this long red velvet cape is exquisitely made "
	+"and tailored.  Lined with some form of fur and trimmed "
	+"in gold, you have never seen its equal.  It hangs with "
	+"some weight as well, which makes you think it was made "
	+"for more than just looking good.\n");
   set_ac(4);
   set_am(({0,0,1}));
   set_at(A_ROBE);
}

