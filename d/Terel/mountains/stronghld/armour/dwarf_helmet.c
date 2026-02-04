/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Dwarven helmet for use with the stronghold
 * Tomas  -- Jan 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("helmet");
    set_short("horned helmet");
    set_pname("helmets");
    set_long("A dwarven war helmet decorated with two large "+
       "horns protruding from either side.\n");
    set_adj(({"horned"}));
    add_adj("war");
    set_armour_size(SMALL);

    set_default_armour(35, A_HEAD, 0, 0);
}