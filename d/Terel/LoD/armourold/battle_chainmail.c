/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * battle_chainmail.c
 *
 * worn by captains and lietenants in LoD.
 *
 * a dark legion chainmail redhawk 921111
 * Modified by Sorgum 941026
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour()
{
    set_name("chainmail");
    set_short("battle chainmail");
    set_long("It's a battle chainmail of good quality that is worn by " +
	     "soldiers in the legion of darkness, the quality of the " +
	     "armour differs on base of the rank the bearer " +
	     "have in the legion of darkness.\n");
    set_adj(({"battle"}));

    set_default_armour(45, A_BODY, 0, 0);
    set_am(({ 5, -2, -3}));
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,    1);
    add_prop(OBJ_I_VALUE,            900);
    add_prop(OBJ_I_WEIGHT,          8000);
}
