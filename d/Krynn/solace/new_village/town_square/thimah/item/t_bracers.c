/*
** Thimah's Bracers
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
    set_name("bracers");
    set_short("iron-reinforced leather bracers");
    set_pshort("pairs of iron-reinforced leather bracers");
    set_long("Great care has been put into keeping this pair of leather bracers in top condition. The bracers are reinforced with iron, which can be seen between the stitches on the inside. Leather straps hold the bracers close to the wearer's arms. It is obvious the previous owner cared a lot about this piece of armour.\n");
    set_adj("iron-reinforced");
    add_adj("iron reinforced");
    add_adj("leather");
    set_ac(33);
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, 1500);
}
