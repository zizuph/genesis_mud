/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bone.c
 *
 * A bone that a small orc would like to play with.
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
    set_name("bone");
    set_adj("white");
    set_short("white bone");
    set_long("This bone comes from a human.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}
