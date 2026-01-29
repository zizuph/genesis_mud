/* handaxe  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name(({"handaxe","axe","weapon"}));
    set_pname("handaxes");
    add_pname("axes");
    set_short("shiny steel handaxe");
    set_pshort("shiny handaxes");
    set_long("A light Gondorian handaxe, made of strong oak and shiny steel.\n"+
        "It is a one-handed weapon, but nasty just the same.\n");
    set_adj("shiny");
    add_adj("steel");
    add_adj("light");
    add_adj("gondorian");
    set_default_weapon(22,29,W_AXE,W_SLASH|W_BLUDGEON,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(22,29)+random(200)-100);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
