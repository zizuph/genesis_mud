 
/* mine/arm/o_hel.c is cloned by mine/npc/chaoslord.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("helmet");
    set_short("onyx helmet");
    add_name("armour");
    set_long( "This black helmet is made of overlapping "+
              "onyx plates magically forged onto a base metal.\n" );
    set_adj("onyx");
 
    set_ac(15);
    set_at(A_HEAD);
    /*    impale  slash   bludgeon   */
    set_am(({       -2,      1,      1 }));
    add_prop(OBJ_I_VALUE, 900);
    add_prop(OBJ_I_WEIGHT, 2450);
    add_prop(OBJ_I_VOLUME, 1060);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,  "This helmet is found on the "+
             "chaoslord in the Emerald mines at /d/Emerald/room/mine/maze31. "+
             "The onyx itself is the magical part of this armour.\n" );
}
 
