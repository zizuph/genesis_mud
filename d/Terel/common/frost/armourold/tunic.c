/* -*- C++ -*- */

/*
 * tunic.c
 *
 * worn by frost giants
 *
 * Sorgum 951216
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
create_armour ()
{
    set_name ("tunic");
    set_short ("chainmail tunic");
    set_long ("Its a chainmail tunic of good quality that is worn by " +
	      "frost giants.\n");
    set_adj (({"chainmail"}));

    set_default_armour (25, A_BODY, 0, 0);
    
    add_prop (OBJ_I_VALUE,  900);
    add_prop (OBJ_I_WEIGHT, 9000);
}
