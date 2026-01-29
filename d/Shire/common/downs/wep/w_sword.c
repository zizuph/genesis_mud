 /*
 *  sword for wight's in the deep down
 *  inherited *stole* the code from Hin_guard (-:
 *  Dondon 101093
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <formulas.h>
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#define F_VOLUME_WEAPON this_object()->query_prop(OBJ_I_WEIGHT)/5


int hit = 35,
    pen = 35;

create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_short("steel sword");
    set_pshort("steel swords");
    set_adj("steel");
    set_long("An ancient sword from forgotten times in Fornost. " +
        "It's finely crafted with ancient designs enscribed along " +
        "the edges of the blade. The sword is made of gleaming " +
        "steel and is heavy.\n");

    add_item(({"designs", "ancient designs"}),
        "The ancient designs are stylized scrolling that decorate " +
        "the edges of the blade. They are enscribed on both sides " +
        "of the blade but look dull with time.\n");

    set_default_weapon(hit, pen, W_SWORD, W_IMPALE | W_SLASH, W_NONE,0);   
    set_pm(({-2,2,0}));

    set_default_weapon(hit,pen,W_SWORD, W_SLASH|W_IMPALE, W_BOTH,0);   
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(hit,W_SWORD) + random(1500)); 

    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON + random(201)); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(hit,pen)* (110 + random(21)) / 100);
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
