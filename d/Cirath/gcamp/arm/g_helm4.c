inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("iron");
   add_adj("ridged");
   set_short("ridged iron helm");
   set_long("Formed from the strong black iron found beneath the "
   	+"Ringing Mountains north of Tyr, this helm is very tough "
   	+"and protective.  Running down the center and sides of the "
   	+"helm are spined ridges resembling fins on some sort of "
   	+"exotic fish.\n");
   set_ac(35);
   set_at(A_HEAD|A_NECK);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,700);
}

