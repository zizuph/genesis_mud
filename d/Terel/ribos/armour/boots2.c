

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots2.c
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
    
    set_name("shoes");
    set_adj("silver");
    set_short("shiny silver shoes");
    set_pshort("pairs of shiny silver shoes");
    set_long("These shoes, made of wood, are coated by shiny silver " +
	     "plates.\n");
    set_ac(8); 
    set_at(A_FEET);
    set_am(({0, 0, 0}));
}
