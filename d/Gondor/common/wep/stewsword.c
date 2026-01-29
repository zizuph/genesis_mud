/* longsword  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name(({"longsword","sword","weapon"}));
    set_pname("longswords");
    add_pname("swords");
    set_short("black steel longsword");
    set_pshort("black steel longswords");
    set_long("A sharpened longsword, with  a hilt of plain " +
        "ebony and carved ivory. A tree with tangled branches " +
        "is carved into the shining white of the hilt.\n");
    set_adj("long");
    add_adj("black");
    add_adj("steel");
    add_adj("large");
    add_adj("gondorian");
    set_default_weapon(29,26,W_SWORD,W_SLASH | W_IMPALE,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,1280);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,26)+random(200)-100);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
