/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ssword.c
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
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();
    set_name("longsword");
    add_name("sword");
    set_adj("golden");
    set_short("golden longsword");
    set_long("A golden sword.  It is used by Ribos' Honour Guards.\n");

    set_hit(30);
    set_pen(24);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
