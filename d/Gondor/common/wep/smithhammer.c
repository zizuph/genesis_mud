/* normal hammer */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon()
{
    set_name("hammer");
    set_pname("hammers");
    set_short("heavy iron hammer");
    set_pshort("heavy iron hammers");
    set_long("A heavy iron hammer, typically used by a blacksmith.\n");
    set_adj("heavy");
    add_adj("blacksmith");
    add_adj("iron");
    set_default_weapon(9,8,W_CLUB,W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(9,8));
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
