
/* Machete. To be used by the insectoids in the manor garden
in Re Albi. Coded by Marisol (1/20/98) Marisol Ramos @ 1998*/


inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>


void
create_weapon()
{
    set_name("staff");
    set_short("witch staff");
    set_adj("witch");
    set_long("This is a witch staff. It is a long and slim oak staff "+
        "with some ribbons and charms tied to the top of it.\n");

    add_item(({"ribbons", "charms"}),
        "There are some ribbons of bright color: red, green and "+
        "blue tied up to some weird feathers and shells that the witch "+
        "used as charms, but doesn't seems that help her much at the "+
        "end.\n");

    set_adj("slim");

    set_hit(30);
    set_pen(15);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,15) + random(25) -10);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/1);

}
