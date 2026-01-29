#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    mixed *arr;
    int n;

    set_name("halberd");
    set_pname("halberds");

    arr = ({"glowing",35, "black",23, "beautiful",20, "vicious",20,
      "sharpened",30, "long",18, "heavy",28, "lethal",30 });

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n]))
    {
        add_adj(arr[n]);
        set_short(arr[n] + " " + query_name());
    }

    set_long("The "+ short() +" would probably do some damage.\n");

    set_hit(15 + (arr[n+1]/4));
    set_pen(arr[n+1]);
    set_wt(W_POLEARM);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE, arr[n+1]*arr[n+1]); 
}
