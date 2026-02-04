/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * refugee_boots.c
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
    set_name("boots");
    set_short("warm fur-lined boots");
    set_pname("pairs of warm fur-lined boots");
    add_name("clothing");
    add_pname("clothings");
    set_long(
        "The warm fur-lined boots look like they " +
        "provide ample protection from the cold weather.\n");

    set_adj(({"warm","fur-lined"}));

    set_default_armour((10), A_FEET, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
