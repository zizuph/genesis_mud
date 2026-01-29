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

    set_name("sword");

    set_adj("short");
    arr = ({"sharp",25, "beautiful",20, "ordinary",13, "wooden",5,
        "black", 18, "broken", 4, "rusty", 8, "dull", 10 });

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n]))
    {
        add_adj(arr[n]);
        set_short(arr[n] + " " + query_name());
    }

    set_hit(15 + (arr[n+1]/4));
    set_pen(arr[n+1]);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(13, arr[n+1]) + random(51));

    set_long("You see nothing special about the "+ short() +".\n");

}

