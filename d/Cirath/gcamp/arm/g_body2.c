inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("mail");
   set_adj("padded");
   add_adj("bone");
   set_short("padded bone mail");
   set_long("Interlocked pieces of bone act as protection in this "
   	+"unusual suit of armour.  The bone seems to be attached to a "
   	+"padded suit underneath that offers additional protection.  "
   	+"The combination of padding and bone creates a very light, "
   	+"yet protective suit of armour.\n");
   set_ac(30);
   set_at(A_BODY|A_ARMS);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,1500);
}

