/* Rohirrim spear  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon()
{
    set_name(({"spear","polearm","weapon"}));
    set_pname("spears");
    add_pname("polearms");
    set_short("tall ashen spear");
    set_pshort("tall ashen spears");
    set_long("A tall spear made of ash wood, its broad head made of steel.\n"+
        "The spear was made in Rohan.\n");
    set_adj("rohirrim");
    add_adj("bright");
    add_adj("steel");
    add_adj("tall");
    add_adj("ashen");
    set_default_weapon(22,17,W_POLEARM,W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,8500);
    add_prop(OBJ_I_VOLUME,4500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22,17)+random(200)-100);
}
