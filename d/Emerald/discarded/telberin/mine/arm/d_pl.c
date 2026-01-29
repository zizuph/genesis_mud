 
/* mine/arm/d_pl.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
   set_name("armour");
   add_name("scale");
   add_name("scalemail");
   add_adj("sardonyx");
   add_adj("dewar");
   set_short("sardonyx scalemail");
   set_long( "Overlapping plates of hard sardonyx on a "+
        "rigid leather background, treated to make it hard as metal "+
        "complete this beautiful piece of armour.\n" );
 
   set_ac(46);
   set_at(A_BODY);
   /*    impale  slash   bludgeon   */
   set_am(({      1,      2,      -3 }));
   add_prop(OBJ_I_VALUE, 1650);
   add_prop(OBJ_I_WEIGHT, 9960);
   add_prop(OBJ_I_VOLUME, 7980);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "This scalemail is found on the "+
        "daemonlord in the Emerald mines at /d/Emerald/room/mine/chasm14. "+
        "The sardonyx is the magical part of this armour, lending great "+
        "durability to the wearing of it.\n" );
}
 
