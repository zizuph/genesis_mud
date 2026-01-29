/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

string color = "blue";

set_color(string new_color)
{
    color = new_color;
}

string
the_color()
{
    return color;
}

create_weapon()
{
    set_name("mace");
    set_adj("standard");
    set_short("standard mace");
    set_long("It's the standard army mace of the @@the_color@@ dragon army.\n");
    set_default_weapon(15, 23, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_COLORABLE, 1);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    color = a[1];
    init_wep_recover(a[0]);
}
