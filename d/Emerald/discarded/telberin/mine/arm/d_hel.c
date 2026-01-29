 
/* mine/arm/d_hel.c is cloned by mine/npc/daemonlord.c */
 
inherit "/std/armour";
 
#include "/d/Emerald/defs.h"
#include <wa_types.h>
#include <formulas.h>
 
void
create_armour()
{
   set_name("helmet");
   set_short("sardonyx helmet");
   set_long( "A heavy magical rock that was magically forged "+
        "into a helmet makes this beautiful object. It's gloriously "+
        "sculpted lines are rare and almost priceless.\n" );
   set_adj("sardonyx");
 
   set_ac(24);
   set_at(A_HEAD);
   /*    impale  slash   bludgeon   */
   set_am(({       -2,      1,      1 }));
   add_prop(OBJ_I_VALUE, 1011);
   add_prop(OBJ_I_WEIGHT, 2661);
   add_prop(OBJ_I_VOLUME, 1210);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
   add_prop(OBJ_S_WIZINFO,  "This helmet is found on the "+
        "daemonlord in the Emerald mines at /d/Emerald/room/mine/chasm14. "+
        "The sardonyx is the magical part of this armour, lending great "+
        "durability to the wearing of it. It is based on the lines of a "+
        "visored helmet, with eyepieces rimmed with leather to be more "+
        "comfortable.\n" );
}
 
