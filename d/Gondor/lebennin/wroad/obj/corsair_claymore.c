/*
 * Steel claymore - a standard issue 2h sword for corsairs near Linhir
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"claymore", "sword"}));
    set_short("steel claymore");
    set_pshort("steel claymores");
    set_long("A large claymore forged from quality steel. The long " +
        "heavy double-edged blade will make tremendous damage when " +
        "wielded skillfully. The hilt is made for wielding the sword " +
        "with two hands and features a plain transverse guard.\n");
    add_item("blade", "The long heavy blade is made from quality steel. The " +
        "blade runs about three and a half feet, and 2 inches wide.\n");
    add_item("hilt", "The hilt runs about 13 inches long, and is wrapped in " +
        "leather straps for increased grasp. A plain transverse guard " +
        "protects the wielder in combat.\n");
    
    set_default_weapon(35, 40, W_SWORD, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, W_SWORD));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_SWORD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
