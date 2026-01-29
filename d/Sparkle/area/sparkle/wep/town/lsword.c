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
    set_adj("long");
    arr = ({"sharp",30, "beautiful",23, "ordinary",15, "wooden",6,
            "black",20, "rusty",8, "dull",12, "standard",18, "steel",25});

    n = random(sizeof(arr)/2)*2;

    if (strlen(arr[n]))
    {
        add_adj(arr[n]);
        set_short(arr[n] + " " + query_name());
    }

    set_hit(12 + (arr[n+1]/4));
    set_pen(arr[n+1]);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(13, arr[n+1]) + random(61));

    set_long("You see nothing special about the "+ short() +".\n");

}

