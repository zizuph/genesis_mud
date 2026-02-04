/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * axe.c  
 *
 * An axe that goblin guards can use.
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
    set_name("waraxe");
    add_name("axe");
    set_adj(({"curved"}));
    set_short("curved waraxe");
   set_pshort("curved waraxes");
    set_long("It looks fairly sharp.\n");
    set_hit(25);
    set_pen(25);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
}
