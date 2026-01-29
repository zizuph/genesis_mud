 
/* mine/arm/o_bra.c is cloned by mine/npc/chaoslord.c */
 
inherit "/std/armour";

#pragma save_binary
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("bracers");
    set_short("pair of onyx bracers");
    add_name(({"onyx bracers", "pair of onyx bracers", "pair of bracers",
                   "armour"}));
    add_pname(({"pairs of onyx bracers", "pairs of bracers", "armours"}));
    set_long( "These glittering black bracers are forged "+
              "plates of onyx that are worn over the shoulders.\n" );
    set_adj("onyx");
 
    set_ac(39);
    set_at(A_ARMS);
    /*    impale  slash   bludgeon   */
    set_am(({       0,      2,      -2 }));
    add_prop(OBJ_I_VALUE, 987);
    add_prop(OBJ_I_WEIGHT, 1280);
    add_prop(OBJ_I_VOLUME, 300);
}
 
