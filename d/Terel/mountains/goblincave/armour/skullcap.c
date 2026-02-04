/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * skullcap.c worn by the std_goblin_grd.c
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("cap");
    set_adj("skull");
    set_pname("caps");
    set_short("skull cap");
    set_long("This cap looks positively gruesume. Formed from what looks " +
       "like a human skull, the cap has been cured and fitted with leather " +
       "straps covering the top of the head and eyes.\n");
    set_ac(20);
    set_at(A_HEAD);
    set_armour_size(SMALL);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 800);
}
