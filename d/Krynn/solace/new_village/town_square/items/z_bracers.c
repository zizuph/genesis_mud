/*
** Zahrtok's Bracers
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
    set_short("dark alloyed-steel bracers");
    set_pshort("pairs of dark alloyed-steel bracers");
    set_long("This is a pair of dark alloyed-steel bracers. The metal is smooth and cold to the touch. They have leather straps to hold them in place, and they smell disgusting. You recognize the smell as that of a goblin.\n");
    set_adj("dark");
    add_adj("alloyed-steel");
    add_adj("alloyed steel");
    set_ac(33);
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, 1500);
}
