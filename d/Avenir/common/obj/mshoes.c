/*
 * - mshoes.c -=- Lucius
 *
 * Shoes for middle-class merchants, based on pshoes.c
 * from the Bazaar.
 */
#pragma strict_types.

inherit "/d/Avenir/inherit/cloth_arm";

#include <wa_types.h>
#include <stdproperties.h>

public string *randadj  = ({
    "clean", "white", "beige", "black", "cream",
    "fitted", "new",
}),	      *randmat  = ({
    "leather", "velvet", "suede",
}),	      *randtype = ({
    "shoes", "loafers", "moccassins",
});

public void
create_armour(void)
{
    string adj  = one_of_list(randadj),
	   mat  = one_of_list(randmat),
	   type = one_of_list(randtype);

    set_name(type);
    set_adj(({ adj, mat }));
    set_short("pair of "+ adj +" "+ mat +" "+ type);
    set_pshort("pairs of "+ adj +" "+ mat +" "+ type);

    set_long("This is a pair of "+ type +" which is worn by the "+
	"slightly more affluent middle-class. Worn more for flash "+
	"than protection, it distinguishes the merchants wearing them "+
	"as being above the peasants and lower-class, yet still not "+
	"able to afford the fine clothes of the great merchant Houses.\n");

    set_default_armour(5, A_FEET, ({ 0, 1, -1}), 0);
}
