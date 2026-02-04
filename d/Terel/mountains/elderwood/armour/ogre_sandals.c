/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_sandals.c
 *
 * a pair of ogre-sized sandals for std_ogre.c of the elderwood forest
 *
 * Tomas   May, 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(LARGE);

    set_name("sandals");
    set_pname("pairs of sandals");
    set_short("pair of large leather sandals");
    set_pshort("pairs of large leather sandals");
    set_long("The pair of large leather sandals look " +
       "like whats left of a very large boot. Leather " +
       "straps weave through a piece of iron covering " +
       "the shins up to the knee.\n");

    set_adj(({"large","leather"}));
    add_name("armour");
    add_pname("armours");
    add_name("large armour");
    add_pname("large armours");

    set_default_armour(7, A_FEET, 0, 0);
}
