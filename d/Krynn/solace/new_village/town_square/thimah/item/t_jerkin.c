/*
** Thimah's Jerkin
** Created By Leia
** June 23, 2005
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
    set_name("jerkin");
    set_short("iron-reinforced leather jerkin");
    set_pshort("iron-reinforced leather jerkins");
    set_long("Great care has been put into keeping this leather jerkin in top condition. The jerkin is reinforced with iron, which can be seen between the stitches on the inside. Leather straps hold the jerkin close to the wearer's body. It is obvious the previous owner cared a lot about this piece of armour.\n");
    set_adj("iron-reinforced");
    add_adj("iron reinforced");
    add_adj("leather");
    set_ac(23);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(23));
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 19000);
}
