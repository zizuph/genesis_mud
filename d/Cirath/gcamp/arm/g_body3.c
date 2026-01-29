inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shirt");
   set_adj("iron-studded");
   add_adj("leather");
   set_short("iron-studded leather shirt");
   set_long("This thick peice of leather has been heavily studded "
   	+"with large pieces of iron almost to the point where this "
   	+"shirt has become a suit of mail.  Instead, it has "
   	+"remained relatively light, while offering a good deal of "
   	+"protection.\n");
   set_ac(38);
   set_at(A_BODY|A_ARMS);
   add_prop(OBJ_I_WEIGHT,15000);
   add_prop(OBJ_I_VOLUME,7500);
}

