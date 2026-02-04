/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bteeth.c
 * teeth from a bear  
 *
 * Vader
 * modified by Sorgum 950707
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
    set_name("club");
    set_adj("wooden");
    set_short("wooden club");
   set_pshort("wooden clubs");
    set_long("A large wooden club capable of much damage.\n");

    set_hit(20);
    set_pen(15);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
}
