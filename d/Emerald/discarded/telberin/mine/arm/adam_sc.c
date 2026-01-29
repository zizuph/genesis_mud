 
/* mine/arm/adam_sc.c is cloned by mine/npc/warlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
   set_name("armour");
   add_name("scale");
   add_adj("scale");
   add_adj("adamantine");
   add_adj("dewar");
   set_short("adamantine scale armour");
   set_long( "This beautifully wrought adamantine scale "+
         "armour is of the greatest quality you have ever seen.\n" );
 
   set_ac(40);
   set_at(A_BODY);
   /*    impale  slash   bludgeon   */
   set_am(({       -1,     3,      -2 }));
   add_prop(OBJ_I_VALUE, 1120);
   add_prop(OBJ_I_WEIGHT, 9000);
   add_prop(OBJ_I_VOLUME, 7680);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "This scale armour is found on the "+
        "warlord in the Emerald mines at /d/Emerald/room/mine/maze6. "+
        "It is magical becuase of the metal involved, adamantine.\n" );
 
}
 
