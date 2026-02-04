/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ssabre.c
 *
 * used by junior Ribos knights
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
    set_name("sabre");
    add_name("sword");
    set_adj("silver");
    set_short("silver sabre");
    set_long("A silver sabre, made for and used by junior Ribos Knights.\n");

    set_hit(18);
    set_pen(15);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
