/* mine/arm/adam_bra.c is cloned by mine/npc/warlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
 
string
create_armour()
{
   set_name("bracers");
   set_short("adamantine bracers");
   add_name("armour");
   set_long( "These bracers are overlapping plates of "+
         "adamantine that are worn on the shoulders and arms.\n" );
   set_adj("adamantine");
 
   set_ac(38);
   set_at(A_ARMS);
   /*    impale  slash   bludgeon   */
   set_am(({       2,      0,      -2 }));
   add_prop(OBJ_I_VALUE, 900);
   add_prop(OBJ_I_WEIGHT, 1200);
   add_prop(OBJ_I_VOLUME, 300);
 
}
 
