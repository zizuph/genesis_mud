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
    set_name("hat");
    set_short("simple hat");
    set_long("A simple hat. It looks old.\n");
    set_adj(({"simple"}));

    set_default_armour(5, A_HEAD, 0, 0);
    set_am(({ 1, 1, -2}));
}
