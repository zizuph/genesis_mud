/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ssword.c
 *
 * used by Ribos knights
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
    set_adj("silver");
    set_short("silver longsword");
    set_long("A silver longsword, made for and used by the Ribos " +    
	     "knights\n");
    set_hit(26);
    set_pen(30);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
