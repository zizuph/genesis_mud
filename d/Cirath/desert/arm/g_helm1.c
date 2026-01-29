inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("hat");
   set_adj("leather");
   add_adj("wide-brimmed");
   set_short("wide-brimmed leather hat");
   set_long("Crafted from tanned giant hide, this wide-brimmed "
   	+"leather hat is perfect for protecting the head from "
   	+"the hot Athasian sun.  The dense leather formed from "
   	+"the giant's skin is all surprisingly protective.\n");
   set_ac(15);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,900);
   add_prop(OBJ_I_VOLUME,400);
}

