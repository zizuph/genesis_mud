/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * refugee_cloak.c
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
    set_name("cloak");
    set_short("warm fur cloak");
    set_pname("warm fur cloaks");
    add_name("clothing");
    add_pname("clothings");
    set_long(
        "The fur cloak looks quite warm. The quality is " +
        "practical, but looks quite cozy to wear.\n");

    set_adj(({"warm","fur"}));

    set_default_armour((15), A_ROBE, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
