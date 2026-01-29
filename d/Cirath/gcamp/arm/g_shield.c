
inherit "/lib/keep";
inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
   set_name("shield");
   set_adj("hide-covered");
   add_adj("bone");
   set_short("hide-covered bone shield");
   set_long("Bones have somehow been lashed together with stout "
   	+"cord and then wrapped and secured within a large piece "
   	+"of hide to form this shield.  While obviously not the "
   	+"best shield, it will do a decent job.\n");
   set_ac(27);
   set_at(A_SHIELD);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,3500);
}

