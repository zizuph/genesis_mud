/* mine/arm/adam_gre.c is cloned by mine/npc/warlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
void
create_armour()
{
   set_name("greaves");
   set_short("adamantine greaves");
   set_long( "These exquisitively carved greaves are made "+
         "of the finest adamantine, the polishing of years showing "+
         "up on their surface..\n" );
   set_adj("adamantine");
 
   set_ac(38);
   set_at(A_LEGS);
   /*    impale  slash   bludgeon   */
   set_am(({       -2,      0,      2 }));
   add_prop(OBJ_I_VALUE, 890);
   add_prop(OBJ_I_WEIGHT, 1230);
   add_prop(OBJ_I_VOLUME, 390);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "These greaves are found on the "+
        "warlord in the Emerald mines at /d/Emerald/room/mine/maze6. "+
        "They are magical because of the nature of the metal involved "+
        "not becuase of any special ability that the armour has.\n" );
}
