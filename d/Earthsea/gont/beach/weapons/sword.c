/*
 * Ordinary sword
 * Originally coward knife om old Roke castle
 * Coded by Gresolle in 1992
 * Modified by Motorhead later
 * Recycled by Finwe, July 1997
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_short("ordinary sword");
    set_adj("steel");
    set_name("sword");
    set_pname("swords");
    set_pshort("ordinary swords");
    set_long("This sword offers the owner some protection. It is " +
        "kind of sharp and is a step up from a dagger in " +
        "defending someone.\n");
    set_default_weapon(23, 23, W_SWORD, W_IMPALE|W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, 300);
}
