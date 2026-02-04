/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * s_armour.c
 *
 * worn by knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
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
    ::create_armour();
    set_name(({"mail", "chainmail", "chain mail", "armour", "armor"}));
    set_adj("steel");
    set_short("shiny steel chainmail");
    set_long("This is a standard armour, worn by all of the king's "
	     + "knights.\n");
    set_ac(30);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
