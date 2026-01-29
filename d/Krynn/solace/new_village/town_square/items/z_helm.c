/*
** Zahrtok's Helm
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
    set_name("helmet");
    add_name("helm");
    set_short("dark alloyed-steel helmet");
    set_pshort("dark alloyed-steel helmets");
    set_long("This is a dark alloyed-steel helmet. The metal is smooth and cold to the touch. It has a chin strap that dangles in the middle, and it smells disgusting. You recognize the smell as that of a goblin.\n");
    set_adj("dark");
    add_adj("alloyed-steel");
    add_adj("alloyed steel");
    set_ac(27);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1000);
}
