/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ssword2.c
 *
 * used by Ribos castle guards
 *
 * Vader
 * modified by Sorgum 941025
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();
    set_name("shortsword");
    add_name("sword");
    set_adj("silver");
    set_short("silver shortsword");
    set_long("A silver shortsword, made for and used by the Ribos " +
        "knights.\n");

    set_hit(24);
    set_pen(21);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
