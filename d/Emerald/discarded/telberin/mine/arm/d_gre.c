 
/* mine/arm/d_gre.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
   set_name("hoplites");
   set_short("sardonyx hoplites");
   set_long( "This one piece greaves are forged to "+
           "fit perfectly around the calf and to protect the lower "+
           "leg.\n" );
   set_adj("sardonyx");
 
   set_ac(39);
   set_at(A_LEGS);
 
   add_prop(OBJ_I_VALUE, 1056);
   add_prop(OBJ_I_WEIGHT, 1730);
   add_prop(OBJ_I_VOLUME, 607);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "These hoplites are found on the "+
        "daemonlord in the Emerald mines at /d/Emerald/room/mine/chasm14. "+
        "They are curved leg braces that fit around the calves and "+
        "the front and back of the shin as much as can be desired. The "+
        "magical nature of the armour comes from the sardonyx.\n" );
}
 
