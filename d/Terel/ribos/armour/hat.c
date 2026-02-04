

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hat.c
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
    
    set_name("hat");
    set_adj("silver");
    set_short("silver cloth hat");
    set_long("This hat is one of the few items a Knight of Ribos " +
	     "would wear that\ndoesn't actually have silver in it.\n");
    set_ac(4);
    set_at(A_HEAD);
    set_am(({0, 0, 0}));
}
