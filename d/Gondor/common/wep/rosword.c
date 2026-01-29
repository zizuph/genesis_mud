/* The typical sword of the Rohirrim */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name(({"sword","weapon","longsword"}));
    set_short("rohirrim longsword");
    set_pshort("rohirrim longswords");
    set_long("The sword is long and bright, and there are green gems set in the hilt.\n"+
        "This is the typical sword of the Men of Rohan.\n");
    set_adj("rohirrim");
    add_adj("long");
    add_adj("green-hilted");
    add_adj("bright");
    set_default_weapon(29,25,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(29, W_SWORD));
    add_prop(OBJ_I_VOLUME,3900);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,25)+250);
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL,1);
}
