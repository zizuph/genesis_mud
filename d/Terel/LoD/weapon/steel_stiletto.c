/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * steel_stiletto.c
 *
 * used by guards in LoD.
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>

#define MY_HIT 16
#define MY_PEN 20

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"stiletto"}));
    set_short("steel stiletto");
    set_long("A steel stiletto thats look like it could slice everything.\n");
    set_adj("steel");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(MY_HIT);
    set_pen(MY_PEN);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 750);
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE);
    set_dt(W_IMPALE); /* You can both 'slash' and 'impale' with it */
    set_wf(TO);

    /* Last, how shall it be wielded? */
    set_hands(W_LEFT); /* You can wield it in any hand. */
}

int
wield(object ob)
{
    if (TP->query_prop("_LoD_NPC"))
    {
        set_hit(22);
        set_pen(18);
        TP->update_weapon(TO);
    }
}

int
unwield(object ob)
{
    if (query_hit() > MY_HIT)
        set_hit(MY_HIT);
    if (query_pen() > MY_PEN)
        set_pen(MY_PEN);
    if (query_wielded())
        query_wielded()->update_weapon(TO);
}
