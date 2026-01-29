inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("horned");
   add_adj("chitin");
   set_short("horned chitin helm");
   set_long("Mounted atop this large piece of insect shell sit two "
   	+"large, bone horns which twist and reach towards the sky.  "
   	+"It is possible these horns could impale someone, but it "
   	+"would probably injure the wearer as well and definitely "
   	+"would damage the helm.\n");
   set_ac(30);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,2300);
   add_prop(OBJ_I_VOLUME,1000);
}

