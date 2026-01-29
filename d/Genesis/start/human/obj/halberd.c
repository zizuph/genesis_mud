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
    int n, i;

    set_name("halberd");
    set_pname(({"halberds", "weapons", }));

    arr = ({
			"glowing",	 46,
			"black",	 36,
			"lethal",	 34,
			"vicious",	 32,
			"sharpened", 28,
			"beautiful", 26,
			"heavy",	 22,
			"long",		 18

		
		  });


    n = random(sizeof(arr)/2)*2;
	if (strlen(arr[n])) add_adj(arr[n]);



	i = (arr[n+1]/2) + 15;
	set_hit(i);
    set_pen(arr[n+1]);

    set_wt(W_POLEARM);
    set_dt(W_SLASH);
    set_hands(W_BOTH);

	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(i, arr[n+1]) + random(65));

    set_short(arr[n] + " " + query_name());
    set_long("The "+ short() +" would probably do some damage.\n");

}
