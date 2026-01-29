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

    set_name("rapier");

    arr = ({"thin",14, "gentlemans",18, "musketeers",22, "experts",26,
	    "plain",10, "beginners",8, "rusty",8, "dull",9,
            "fancy", 16 });

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n]))
    {
        set_adj(arr[n]);
        set_short(arr[n] + " " + query_name());
    }

    set_hit(arr[n+1]/2 +6); 
    set_pen(arr[n+1]);
    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(arr[n+1]/2 + 6, arr[n+1]) + random(51));
  
    set_long("You see nothing special about the "+ short() +".\n");
}

