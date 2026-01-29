#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

varargs public void
set_type(string adj)
{
    mixed  *arr = ({
                     "dull",    6, "rusty",          7, "old",    8,
                     "small",  10, "blood stained", 11, "black", 12,
                     "large",  13, "long",          13,
                     "jagged", 14, "vicious",   15, "vibrating", 17, });
    int     n;

    if (!strlen(adj))
    {
        n = random(sizeof(arr)/2)*2;
    }
    else
    {
        n = member_array(adj, arr);
        if (n < 0)
            n = random(sizeof(arr)/2)*2;
    }

    remove_adj(query_adjs());
    set_adj("hunting");
    set_adj(arr[n]);
    set_pen(arr[n+1]);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( 9, arr[n+1]) + random(41));
}

public void
create_weapon()
{
    set_name("knife");
    set_pname(({"knives", "weapons", }));
    set_long("You see nothing special about the "+ query_name() +".\n");

    set_hit(9);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);

    set_type();
}

string
query_recover()
{
    string *adjs = query_adjs();

    adjs -= ({ "hunting" });

    if (sizeof(adjs) != 1)
        return 0;

    return ::query_recover() + "#U#" + adjs[0];
}

void
init_recover(string arg)
{
    string  dummy, adj;

    sscanf(arg, "%s#U#%s", dummy, adj);
    set_type(adj);
    ::init_recover(arg);
}

