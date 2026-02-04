/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * hat.c
 *
 * worn by fisherman on bridge between Calathin and Minstrels.
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name("tunic");
    set_short("old leather tunic");
    set_long("An old leather tunic.\n");
    set_adj(({"old", "leather"}));

    set_default_armour(7, A_BODY, 0, 0);
    set_am(({ 1, 1, -2}));
}
