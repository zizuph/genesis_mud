/*
 *  spear.c
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
    set_name("spear");
    add_name("polearm");
    set_pname("spears");
    add_pname("polearms");
    set_adj("wooden");
    set_short(short_desc());
    set_long("This long branch has been hastily sharpened at one " 
      + "end and appears to have come from a mid-sized evergreen tree " 
      + "by sticky sap coating it. Although providing a nice grip, " 
      + "the wood is soft and very flexible making it a poor choice " 
      + "for a durable weapon.\n");

    set_hit(10 + random(5));
    set_pen(10 + random(5));
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_dull(1);
    set_likely_dull(10);
    set_likely_corr(0);
    set_likely_break(10);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
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
            set_pshort("sticky wooden spears");
            add_adj("sticky");
            return "sticky wooden spear";

        case 1:
            set_pshort("thin wooden spears");
            add_adj("thin");
            return "thin wooden spear";

        case 2:
            set_pshort("splintered wooden spears");
            add_adj("splintered");
            return "splintered wooden spear";

        case 3:
            set_pshort("knotty wooden spears");
            add_adj("knotty");
            return "knotty wooden spear";

        case 4:
            set_pshort("carved wooden spears");
            add_adj("carved");
            return "carved wooden spear";

        default:
            set_pshort("wooden spears");
            return "wooden spear";

    }
    
    return 0;
}
