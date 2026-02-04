/*
 *  club.c
 *
 *  Britanica 160322
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDWEAPON;

mixed short_desc();

/*
 * Function name: create_weapon
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_weapon()
{
    set_name("club");
    add_name("stick");
    set_pname("clubs");
    add_pname("sticks");
    set_adj("wooden");
    set_short(short_desc());
    set_long("A gnarled old stick that looks like it has been used " 
      + "for quite some time as a smashing weapon by the many pits " 
      + "and cracks present on the thick end of this chunk of wood.\n");

    set_hit(12 + random(5));
    set_pen(5 + random(5));
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_dull(1);
    set_likely_dull(10);
    set_likely_corr(0);
    set_likely_break(5);
    
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, 100);

}

/*
 * Function name: short_desc
 * Description  : Randomly sets the plural short description and adjective.
 * Arguments    : n/a
 * Returns      : single short description of weapon
 */
mixed
short_desc()
{
    switch(random(5))
    {
        case 0:
            set_pshort("gnarled wooden clubs");
            add_adj("gnarled");
            return "gnarled wooden club";

        case 1:
            set_pshort("old wooden clubs");
            add_adj("old");
            return "old wooden club";

        case 2:
            set_pshort("splintered wooden clubs");
            add_adj("splintered");
            return "splintered wooden club";

        case 3:
            set_pshort("worn wooden clubs");
            add_adj("worn");
            return "worn wooden club";

        case 4:
            set_pshort("pitted wooden clubs");
            add_adj("pitted");
            return "pitted wooden club";

        default:
            set_pshort("wooden clubs");
            return "wooden club";

    }
    
    return 0;
}
