/*
 * Dagger
 * Originally coward knife from old Roke castle
 * Coded by Gresolle in 1992
 * Modified by Motorhead later
 * Recycled by Finwe, July 1997
 */

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_weapon()
{
    set_short("small dagger");
    set_adj("small");
    set_name("dagger");
    set_pname("daggers");
    set_pshort("small daggers");
    set_long("This is a small dagger common among poor folk. It " +
        "isn't very sharp but offers the owner some protection " +
        "against thieves, cutthroats, and undesirables.\n");
    set_default_weapon(12, 15, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, 150);
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}
