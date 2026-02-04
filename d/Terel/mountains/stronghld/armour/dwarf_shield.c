/* 
 * dwarf_shield.c
 * Dwarven shield for the body guard
 * Coded by Shinto 11-12-98
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name(({"shield"}));
    set_short("dwarven shield");
    set_pname("shields");
    set_long("A dwarven shield made of steel, emblazoned on the "+
                   "front of the shield are two crossed axes. Leather "+
                   "straps hold the shield to the arm.\n");
    set_adj("dwarven");

    set_armour_size(SMALL);
    set_default_armour(30, A_SHIELD, 0, 0);
}
