/*
** Thimah's Cap
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
    set_name("cap");
    add_name("helmet");
    add_name("helm");
    set_short("iron-reinforced leather cap");
    set_pshort("iron-reinforced leather caps");
    set_long("Great care has been put into keeping this leather cap in top condition. The cap is reinforced with iron, which can be seen between the stitches on the inside. A leather chin strap holds the cap tightly on the wearer's head. It is obvious the previous owner cared a lot about this piece of armour.\n");
    set_adj("iron-reinforced");
    add_adj("iron reinforced");
    add_adj("leather");
    set_ac(30);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1000);
}
