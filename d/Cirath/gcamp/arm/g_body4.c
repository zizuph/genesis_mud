inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shirt");
   set_adj("chainmail");
   add_adj("steel");
   set_short("steel chainmail shirt");
   set_long("Crafted from an ancient steel, this shirt offers a "
   	+"large amount of protection.  The links in the chainmail "
   	+"are so fine they could be used to make a necklace, while "
   	+"the skillful work that was put into this shirt makes it "
   	+"appear as if it were a solid piece of metal.\n");
   set_ac(38);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,3500);
}

