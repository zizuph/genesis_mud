
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * helmet.c
 *
 * worn by large knights in Ribos
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
    set_name("helmet");
    set_adj("silver");
    add_adj("flat");
    set_short("flat silver helmet");
    set_long("This helmet, worn by the better Ribos Knights, is made of " +
	     "finely polished silver.  It is flat on top, and has a " +
	     "black band at the base.\n");
    set_ac(34);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
}
