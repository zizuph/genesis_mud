inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"

create_armour()
{
   set_name("coif");
   add_name("helm");
   set_adj("worn");
   add_adj("leather");
    set_long("This thick piece of leather is used to protect "
   	+"your head.  It fits comfortably on your brow without "
   	+"any discomfort.  Hanging from the back of it is a long "
   	+"wide piece of leather used to protect the back of your "
   	+"neck from the harsh rays of the sun.\n");
   set_ac(20);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,500);
}

