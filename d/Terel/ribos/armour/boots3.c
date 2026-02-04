

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots3.c
 *
 * worn by knights in Ribos
 *
 * Vader
 * Modified by Sorgum 950602
 *
 * Modified for use with the new standard armour for Terel.
 * Torm, Sep 98
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    
    set_name("boots");
    set_adj("silver");
    set_short("shiny silver plated boots");
    set_pshort("pairs of shiny silver plated boots");
    set_long("These boots are made of leather, but are covered in silver " +
	     "plates.\n");
    set_ac(15);
    set_at(A_FEET);
    set_am(({0, 0, 0}));
}
