 
/* mine/arm/d_bra.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
string
create_armour()
{
   set_name("bracers");
   set_short("sardonyx bracers");
   set_long( "Closely related to onyx, this deep black "+
        "magical rock has been forged to make shoulder plates for a "+
        "suit of armour.\n" );
   set_adj("sardonyx");
 
   set_ac(41);
   set_at(A_ARMS);
   /*    impale  slash   bludgeon   */
   set_am(({       1,      1,      -2 }));
   add_prop(OBJ_I_VALUE, 1091);
   add_prop(OBJ_I_WEIGHT, 1566);
   add_prop(OBJ_I_VOLUME, 787);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
}
