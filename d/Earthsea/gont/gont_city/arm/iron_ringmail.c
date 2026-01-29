/*  iron armour for seamen at Gont Port
*   Amelia 3/8/98
*
*/
inherit "/std/armour.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "defs.h"
#include "/sys/formulas.h"

#define ARMOUR_CLASS 17


void
create_armour()
{
    set_name("ringmail");
    set_adj("iron");
    set_short("iron ringmail");
    set_long(break_string("A ringmail made from hard leather "+
	"tightly sewn with rings of iron. It provides good "+
	"protection for the chest and shoulders.\n", 70));

    set_ac(ARMOUR_CLASS); 
    set_at(A_TORSO);
    set_am(({ -1, 2, -1 }));
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100));

}

void
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
