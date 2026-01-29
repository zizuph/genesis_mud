 
/* mine/arm/adam_hel.c is cloned by mine/npc/warlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
   set_name("helmet");
   set_short("adamantine helmet");
   set_long( "This beautifully wrought helmet is fashioned "+
       "with care and beauty. It's polished surface gleams with "+
       "an inner light of it's own.\n" );
   set_adj("adamantine");
 
   set_ac(15);
   set_at(A_HEAD);
            /*    impale  slash   bludgeon   */
   set_am(({       -1,      -1,     2 }));
   add_prop(OBJ_I_VALUE, 870);
   add_prop(OBJ_I_WEIGHT, 2560);
   add_prop(OBJ_I_VOLUME, 1060);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "This helmet are found on the "+
        "warlord in the Emerald mines at /d/Emerald/room/mine/maze6. "+
        "It is magical becuase of the metal involved, adamantine.\n" );
}
 
