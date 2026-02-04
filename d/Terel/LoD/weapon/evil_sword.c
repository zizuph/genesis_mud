/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * evil_sword.c
 *
 * used by evil guards in LoD.
 *
 * a evil sword redhawk 921108
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
    set_name(({"shortsword","sword"}));
    set_pname(({"shortswords","swords"}));
    set_short("steel shortsword");
    set_long("A sword that radiates evil.\n");
    set_adj(({"steel","evil"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(15);
    set_pen(18);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 3000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
