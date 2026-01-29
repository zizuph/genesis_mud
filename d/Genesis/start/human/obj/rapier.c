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
    mixed  *arr, *wep;
    int n, h, p;

    set_name("rapier");


/*    arr = ({
			"experts",26,
			"musketeers",22, 	
			"gentlemans",18,
			"fancy", 16,
			"thin",14, 
			"plain",12, 
			"dull",10,
			"beginners",10, 
			"rusty",9

		  });*/
    arr = ({
			({"expert", 26, 1}),
			({"musketeer", 22, 1}), 	
			({"gentleman", 18, 1}),
			({"fancy", 16, 0}),
			({"thin", 14, 0}), 
			({"plain", 12, 0}), 
			({"dull", 10, 0}),
			({"beginner", 10, 1}), 
			({"rusty", 9, 0})
		  });

    n = random(sizeof(arr) - 1);
    wep = arr[n];
    
    if (wep[2])
    {
        add_adj(wep[0]);
        add_adj(wep[0] + "'s");        
        add_adj(wep[0] + "s");
        set_short(wep[0] + "'s rapier");
    }
    else
    {
        add_adj(wep[0]);
        set_short(wep[0] + " rapier");
    }

    add_name("sword");

    p = wep[1];
    set_pen(p);
    h = (p / 2) + 8;
    set_hit(h);  /* hit = pen/2 +6 (thus anything from 10 to 19) */

    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_NONE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(h, p) + random(45));

/*    n = random(sizeof(arr)/2)*2;
	if (strlen(arr[n])) add_adj(arr[n]);
	


	i = (arr[n+1]/2) + 8;
////    set_hit(i);  /* hit = pen/2 +6 (thus anything from 10 to 19) */
/*    set_pen(arr[n+1]);

    set_wt(W_SWORD);
    set_dt(W_IMPALE);
    set_hands(W_NONE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(i, arr[n+1]) + random(45));
  
    set_short(arr[n] + " " + query_name());*/
    set_long("It looks like a very nice "+ short() +".\n");

}
