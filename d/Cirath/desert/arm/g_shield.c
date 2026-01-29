inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shield");
   set_adj("sturdy");
   add_adj("chitin");
   set_short("sturdy chitin shield");
   set_long("A rugged tan piece of carapace is the major "
   	+"part of this shield.  It has straps on the back to "
   	+"hold it by, as well as thick fibrous padding to "
   	+"help reduce the shock of blows.  A simple, yet "
   	+"effective item for defence.\n");
   set_ac(28);
   set_at(A_SHIELD);
   add_prop(OBJ_I_WEIGHT,4500);
   add_prop(OBJ_I_VOLUME,2000);
}

