/* Ranger spear  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name(({"spear","polearm","weapon"}));
    set_pname("spears");
    add_pname("polearms");
    set_short("broad-bladed oak spear");
    set_pshort("broad-bladed spears");
    set_long("A broad-bladed spear made of oak wood, its broad head made of steel.\n"+
        "It is long and heavy, so it must be wielded in both hand, as an impaling\n"+
        "weapon. The spear was made in Gondor.\n");
    set_adj("gondorian");
    add_adj("bright");
    add_adj("steel");
    add_adj("broad-bladed");
    add_adj("oak");
    set_default_weapon(22,16,W_POLEARM,W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME,4500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22,16)+random(200)-100);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
