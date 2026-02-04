/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bluesword.c
 * Non-magical replacement for the bluebolt.c
 * added per request of AoB
 * Tomas  -- April 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    ::create_weapon();

    set_name(({"sword", "bluesword"}));
    set_pname("swords");
    set_short("blue sword");
    set_pshort("blue swords");
    set_long("The long double-edged blade looks " + 
       "quite dangerous.\n");
    set_adj("blue");

    set_hit(35);
    set_pen(35);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 3000);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);   
}