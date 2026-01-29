 
/* mine/wep/d_dag.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
 
void
create_weapon()
{
   set_name("dirk");
   set_short("steel dirk");
   set_long( "This long throwing dagger can be used for "+
        "close quarter combat. The blade is made of steel.\n" );
   set_adj("steel");
 
   set_default_weapon(14, 17, W_KNIFE, W_SLASH | W_IMPALE,
      W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 5631);
   add_prop(OBJ_I_VOLUME,  5917);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(14, 17) + random(60) );
   add_prop(OBJ_S_WIZINFO,  "A steel dirk, not special.\n" );
}
