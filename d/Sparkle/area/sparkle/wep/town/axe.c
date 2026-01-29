#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

public void
create_weapon()
{
    mixed  *arr;
    int n;

    set_name("axe");
    set_pname(({"axes", "weapons", }));

    arr = ({"small",15, "old",9, "dwarven",22, "dull",8, "large",17});

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n]))
    {
        add_adj(arr[n]);
        set_short(arr[n] + " " + query_name());
    }

    set_long("You see nothing special about the "+ query_name() +".\n");

    set_hit(15 + (arr[n+1]/4));
    set_pen(arr[n+1]);
    set_wt(W_AXE);
    set_dt(W_BLUDGEON | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12, arr[n+1]) + random(41));
}

