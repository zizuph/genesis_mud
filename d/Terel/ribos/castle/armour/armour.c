
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * armour.c
 *
 * worn by the better knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
 * Modified by Bronco 950719
 *
 * Modified for use with the new standard armour for Terel.
 * Torm, Sep 98
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name(({"mail", "chainmail", "chain mail", "armour", "armor"}));
    set_adj("steel");
    set_short("fine steel chainmail");
    set_long("This is a prime example of the craftsmanship of the Ribos " +
	     "smiths.  It is a gleaming suit of steel chainmail, worn " +
	     "by only the best Ribos Knights.\n");
    set_ac(33);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
