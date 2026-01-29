/*  The travel-cloaks of the Rangers of the North */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
    set_name("cloak");
    add_name(({"armour","robe"}));
    set_adj("ranger");
    add_adj(({"heavy","dark-green","travel-stained"}));
    set_short("travel-stained dark-green cloak");
    set_long("This is a travel-stained, hooded cloak made of heavy "+ 
    "dark-green cloth.\n");
    set_default_armour(3, A_ROBE, (({ -1, 0, 1})), 0);
    add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}
