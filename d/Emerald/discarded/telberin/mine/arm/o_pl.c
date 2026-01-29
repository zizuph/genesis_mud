 
/* mine/arm/o_pl.c is cloned by mine/npc/chaoslord.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("armour");
    add_name("plate");
    add_name("platemail");
    add_adj("plate");
    add_adj("onyx");
    add_adj("dewar");
    set_short("onyx platemail");
    set_long( "This glittering black armour is magically "+
              "forged, bringing the onyx plates together into a body "+
              "armour that is nearly invincible.\n" );
 
    set_ac(42);
    set_at(A_BODY);
    /*    impale  slash   bludgeon   */
    set_am(({      2,      2,      -4 }));
    add_prop(OBJ_I_VALUE, 1330);
    add_prop(OBJ_I_WEIGHT, 9560);
    add_prop(OBJ_I_VOLUME, 7680);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,  "This platemail is found on the "+
             "chaoslord in the Emerald mines at /d/Emerald/room/mine/maze31. "+
             "The onyx itself is the magical part of this armour.\n" );
}
 
