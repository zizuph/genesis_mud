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
  set_long("It's the standard army sword of the " + color + " dragon army.\n");
}

create_weapon()
{
    set_name("sword");
    set_adj("short");
    set_short("short sword");
    set_long("It's the standard army sword of the blue dragon army.\n");
    set_default_weapon(19, 15, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 1500);
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
