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
    int     n, i;
    mixed  *arr = ({
                    "rusty",		6,
					"dull",			7,
					"old",			8,
                    "small",		10,
					"blood stained",11,
					"black",		12,
                    "large",		13,
					"long",			13,
                    "jagged",		14,
					"vicious",		15,
					"vibrating",	17,
				  });



    if (!strlen(adj)) //No type set. Pick one at random.
    {
        n = random(sizeof(arr)/2)*2;
    }
    else //Find and use the requested type.
    {
        n = member_array(adj, arr);
        if (n < 0)
            n = random(sizeof(arr)/2)*2;
    }



    remove_adj(query_adjs());
    set_adj("hunting");
    set_adj(arr[n]);



	i=(arr[n+1]/2) + 4;
	set_hit(i);
    set_pen(arr[n+1]);

	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON( i, arr[n+1]) + random(20));
}



public void
create_weapon()
{
    set_name("knife");
    set_pname(({"knives", "weapons", }));
    set_long("The metal blade of the "+ query_name() + " looks like"
      + " it could prove useful to you.\n");

    
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

