/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * colsword.c Trofast 10-23-1998
 *
 * used by the colonel in LoD.
 *
 * a steel sword redhawk 920727
 * modified by Sorgum 941025
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"sword","longsword"}));
    set_pname(({"swords","longswords","weapons"}));
    set_short("shining steel longsword");
    set_long("A sword that seems to be able to slice most things " +
	     "that come in its way.  It's the sword " +
	     "wielded by the Colonel in the legion of darkness.\n");
    set_adj(({"shining","steel"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 10000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_BOTH); /* You can wield it in both hands. */
}
