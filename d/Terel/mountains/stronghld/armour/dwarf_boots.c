/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Dwarven Boots for use with the stronghold guards
 * Tomas  -- Jan 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("many pairs of boots");
    set_short("pair of fur-lined leather boots");
    set_pshort("pairs of fur-lined leather boots");
    set_long("A fine pair of leather boots " +
       "lined in fur to help protect against the cold.\n");
    set_adj(({"fur-lined","leather"}));
    set_armour_size(SMALL);
    add_name("armour");
    add_pname("armours");

    set_default_armour(10, A_FEET, 0, 0);
}