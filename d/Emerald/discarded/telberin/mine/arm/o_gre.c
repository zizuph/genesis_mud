 
/* mine/arm/o_gre.c is cloned by mine/npc/chaoslord.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>
 
void
create_armour()
{
    set_name("greaves");
    set_short("pair of onyx greaves");
    add_name(({"onyx greaves", "pair of onyx greaves", "pair of greaves",
                   "armour"}));
    add_pname(({"pairs of onyx greaves", "pairs of greaves", "armours"}));
    set_long( "These greaves glitter with an evil from beyond this plane.\n" );
    set_adj("onyx");
    set_ac(38);
    set_at(A_LEGS);
    /*    impale  slash   bludgeon   */
    set_am(({       2,       1,     -3 }));
    add_prop(OBJ_I_VALUE, 900);
    add_prop(OBJ_I_WEIGHT, 1230);
    add_prop(OBJ_I_VOLUME, 390);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
 
    add_prop(OBJ_S_WIZINFO,  "These greaves are found on the "+
             "chaoslord in the Emerald mines at /d/Emerald/room/mine/maze31. "+
             "The onyx itself is the magical part of this armour.\n" );
 
}
 
