/*
** Thimah's Boots
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
    set_short("iron-reinforced leather boots");
    set_pshort("pairs of dark alloyed-steel boots");
    set_long("Great care has been put into keeping these leather boots in top condition. The boots are reinforced with iron, which can be seen between the stitches on the inside. Leather laces on the front of the boots have been pulled almost uncomfortably tight. It is obvious the previous owner cared a lot about this piece of armour.\n");
    set_adj("iron-reinforced");
    add_adj("iron reinforced");
    add_adj("leather");
    set_ac(30);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3000);
}
