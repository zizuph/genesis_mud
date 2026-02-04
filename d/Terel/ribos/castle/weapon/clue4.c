/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * clue4.c
 *
 * actually a clue for the Ribos crime quest
 *
 * Vader
 * modified by Sorgum 950711
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
    set_name("dagger");
    set_adj(({"ceremonial"}));
    set_short("ceremonial dagger");
    set_long("The blade is made of polished metal, and the hilt is " +
             "decorated with a coat of arms.  The coat of arms looks " +
             "to depict a shield, with a stripe, and some angels.\n");
    set_hit(12);    
    set_pen(13);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
}
