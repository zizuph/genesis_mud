

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * s_armour.c
 *
 * worn by knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
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
    add_adj("shiny");
    set_short("shiny steel chainmail");
    set_long("This is a standard armour, worn by all of the kings "
	     + "knights.\n");
    set_ac(30);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
