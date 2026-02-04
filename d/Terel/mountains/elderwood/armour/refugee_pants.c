/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * refugee_pants.c
 *
 * worn by the std_refugee.c of Elderwood Forest.
 *
 * Tomas  June 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(MEDIUM);
    set_name("pants");
    set_short("heavy woolen pants");
    set_pname("pairs of heavy woolen pants");
    add_name("clothing");
    add_pname("clothings");
    set_long(
        "A pair of heavy woolen pants. They look warm.\n");

    set_adj(({"heavy","woolen"}));

    set_default_armour((10), A_LEGS, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
