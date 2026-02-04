

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * helmet2.c
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
    
    set_name("helmet");
    set_adj("silver");
    set_short("shiny silver helmet");
    set_long("This helmet, which is made of finely polished silver, " +
	     "is but\none distinguishing piece worn by all Ribos Knights.\n");
    set_ac(17);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
}
