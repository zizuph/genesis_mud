

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots.c
 *
 * worn by knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
 * Modified for use with the new standard armour for Terel.
 * Torm, Sep 98
 */

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDARMOUR;

public void
create_terel_armour()
{
    
    set_name("boots");
    set_adj("silver");
    set_short("shiny silver boots");
    set_pshort("pairs of shiny silver boots");
    set_long("These boots, made of polished silver, are used by the " +
	     "Ribos Knights.\n");
    set_ac(30);
    set_at(A_FEET);
    set_am(({0, 0, 0}));
}
