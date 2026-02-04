/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * iron_sword.c
 *
 * used by iron guards in LoD.
 *
 * a iron sword redhawk 921027
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
    set_short("sword of iron");
    set_long("A iron sword that is standard issue to some of the guards " +
	     "in the legion. \n");
    set_adj("iron");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(15);
    set_pen(15);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 9000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
