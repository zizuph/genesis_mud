

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * h_g_armour.c
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
    
    set_name(({"plate", "platemail", "armour", "armor"}));
    set_adj("silver");
    set_short("shiny silver platemail");
    set_long("This not only can protect you from an opponents blows, but can "
	     + "blind him in bright sunlight.\n");
    set_ac(25);
    set_at(A_BODY);
    set_am(({0,0,0}));
}
