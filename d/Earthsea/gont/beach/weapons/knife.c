/* 
 * Knife
 * Originally coward knife from old Roke castle
 * Coded by Gresolle in 1992
 * Modifietorhead later
 * Recycled by Finwe, July 1997
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_short("sharp knife");
    set_adj("lethal");
    set_name("knife");
    set_pname("knives");
    set_pshort("sharp knives");
    set_long("This sharp knife fits comfortably into your hand. " +
        "The blade is sharp and allows you to defend yourself. " +
        "It's not the best weapon, but it is better than nothing.\n");
    set_default_weapon(9, 15, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, 150);
}
