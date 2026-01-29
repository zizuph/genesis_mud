 /*
 *  sword for The big wight in the deep down
 *  inherited the code from Hin_guard (-:
 *  Dondon 101093
 *
 * Added set_keep and enabled players
 * to be able to exa sword by different
 * adjectives. -- Finwe 7/98
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Shire/common/defs.h"
#include <formulas.h>
#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5


create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_short("tempered steel sword");
    set_pshort("tempered steel swords");
    set_adj(({"tempered","steel"}));
    set_long("An ancient sword from forgotten times in Fornost." +
             " It's beautifully crafted and looks dangerous.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       28,                     /* 'to hit' value    */
       24,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_NONE,                 /* nr of hands       */
       0);           /* object that defines wield and unwield functions */
    set_pm(({-2,2,0}));

    /*Weighs 5 kg  */
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(28,W_SWORD) - random(206)); 

    /* Volume 3 Ltr */
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON + random(230));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,24) + random(176));
    set_keep(0);
}


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}
