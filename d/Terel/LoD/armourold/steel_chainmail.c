/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * steel_chainmail.c
 *
 * worn by sergeants steel guards is LoD.
 *
 * a steel chainmail Redhawk 920921
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
    set_short("steel chainmail");
    set_long("It's a steel chainmail that the some of the soldiers " +
	     "in the legion use.\n");
    set_adj(({"steel"}));

    set_default_armour(40, A_BODY, 0, 0);
    set_am(({4,-2,-2}));
    add_prop(OBJ_I_WEIGHT, 2000);
}
