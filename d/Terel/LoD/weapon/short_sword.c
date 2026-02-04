/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * short_sword.c
 *
 * used by grunts, korporals, small guards in LoD.
 *
 * a short sword Redhawk 920728
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
    set_name(({"sword","shortsword"}));
    set_pname(({"swords","shortswords"}));
    add_pname("weapons");
    set_short("shortsword");
    set_adj(({"short"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("An elf made short sword of good quality.\n");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(15);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 5000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
