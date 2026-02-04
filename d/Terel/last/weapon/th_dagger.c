/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * th_dagger.c
 *
 * used by Trevin in Last.
 *
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
    set_name(({"dagger"}));
    set_short("throwing dagger");
    set_long("A steel throwing dagger, well balanced and very sharp.\n");
    set_adj("steel");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(18);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 750);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE);
    set_dt(W_IMPALE); /* You can both 'slash' and 'impale' with it */
    set_wf(TO);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}

