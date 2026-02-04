//This weapon is ILLEGAL.
//Have it follow the weapon rules.
//Notify Tepisch or Rastlin when it is fixed.
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * swordofchaos.c
 *
 * used by captains in LoD.
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
    set_name(({"sword"}));
    set_pname("swords");
    add_pname("weapons");
    set_short("blackened-steel bastard sword");
    set_long("A sword that seems to be able to slice most things " +
	     "that come in the way for it.  It's a sword that is " +
	     "wielded by the officers in the legion of darkness.\n");
    set_adj(({"blackened-steel","steel","bastard"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(30);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 10000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_RIGHT); /* You can wield it in any hand. */
}
