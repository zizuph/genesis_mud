inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helmet");
   set_adj("chitin");
   add_adj("collared");
   set_short("collared chitin helmet");
   set_long("This helmet is made from what appears to "
   	+"be the chitin of some desert beast.  It sits "
   	+"comfortably on the head and covers the face as "
   	+"well.  Attached to the bottom of the helmet is "
   	+"a gorget which wraps around the back of the "
   	+"helmet like a collar.  It will keep your throat "
   	+"from being exposed to danger.\n");
   set_ac(30);
   set_at(A_HEAD|A_NECK);
   add_prop(OBJ_I_VALUE,600);
}

