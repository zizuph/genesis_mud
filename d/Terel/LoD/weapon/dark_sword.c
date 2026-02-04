/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * dark_sword.c
 *
 * used by darkness knights and dark guards and the war officer in LoD.
 *
 * dark legion sword Redhawk 921104
 * modified by Sorgum 941025
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"sword"}));
    set_pname("swords");
    add_pname("weapons");
    set_short("darkness sword");
    set_long("A sword of darkness that is a bit better than the standard" +
	     " weapons that the legion of darkness wields.\n");
    set_adj("darkness");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(27);
    set_pen(28);
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 10000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
