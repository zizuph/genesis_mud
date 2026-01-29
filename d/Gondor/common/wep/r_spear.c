/* Ranger spear  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name(({"spear","polearm"}));
    set_pname("spears");
    add_pname("polearms");
    set_short("broad-bladed oak spear");
    set_pshort("broad-bladed spears");
    set_long("A broad-bladed spear made of oak wood, its broad head made of steel.\n"+
        "The spear was made in Gondor.\n");
    set_adj("ranger");
    add_adj("bright");
    add_adj("steel");
    add_adj("broad-bladed");
    add_adj("oak");
    set_default_weapon(13,24,W_POLEARM,W_IMPALE,W_BOTH,0);
    add_prop(OBJ_I_WEIGHT,8500);
    add_prop(OBJ_I_VOLUME,4500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(13,24)+random(200)-100);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}
