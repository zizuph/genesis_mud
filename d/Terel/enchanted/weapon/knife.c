/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * knife.c
 * A black knife, worn by witches. Mortricia 920720
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();
    set_name("knife");
    set_pname("knives");
    set_short("black knife");
    set_long("It's black knife. It seems to be very sharp.\n");

    set_adj(({"black"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(15);
    set_pen(15);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}
