inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"

create_armour()
{
   set_name("shirt");
   set_adj("studded");
   add_adj("leather");
    set_long("This shirt has been cleverly crafted from a piece "
   	+"tanned animal hide that has been studded with small "
   	+"pieces of rock.  The hide itself seems thin, but the "
   	+"material is very coarse and protective, while the rocky "
   	+"studs offer added protection.\n");
   set_ac(28);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,1700);
}

