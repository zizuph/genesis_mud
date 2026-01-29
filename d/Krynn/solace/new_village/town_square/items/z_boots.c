/*
** Zahrtok's Boots
** Created By Leia
** June 22, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_short("dark alloyed-steel boots");
    set_pshort("pairs of dark alloyed-steel boots");
    set_long("This is a pair of dark alloyed-steel boots. The metal is smooth and cold to the touch. They tighten with leather bootstraps attached to the front, and they smell disgusting. You recognize the smell as that of a goblin.\n");
    set_adj("dark");
    add_adj("alloyed-steel");
    add_adj("alloyed steel");
    set_ac(30);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3000);
}
