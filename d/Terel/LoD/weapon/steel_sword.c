/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * steel_sword.c
 *
 * used by sergeants, steel guards in LoD.
 *
 * a steel sword redhawk 920727
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
    set_name(({"sword","weapon"}));
    set_pname(({"swords","weapons"}));
    set_short("sword of steel");
    set_long("A steel sword that looks like it could slice everything.\n");
    set_adj("steel");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(25);
    set_pen(30);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2000);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
