/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * t_sword.c
 *
 * Vader
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
    ::create_weapon();
    set_name("sword");
    set_adj("black");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("black sword");
    set_long("A dark black sword.  It is used by Ribos' Special Guards.\n");

    set_hit(30);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
