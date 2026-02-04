/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * thword.c
 *
 * used by Ribos corner knights
 *
 * Vader
 * modified by Sorgum 941025
 * Modified by Bronco 950719
 */

#include "/d/Terel/include/Terel.h"

inherit "/std/weapon";

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
    set_long("A silver and black longsword, made for " +
	     "and used by only the strongest Ribos knights.\n");
    set_hit(36);
    set_pen(30);
/*
 * XXX
 * Add twohanded attribute
 * and set the weight and volume
 *
 */
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
}
