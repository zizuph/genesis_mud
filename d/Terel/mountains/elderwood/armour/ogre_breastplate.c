/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_breastplate.c
 *
 * worn by std_ogre.c of the elderwood forest
 *
 * Tomas May, 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(LARGE);
    set_name("breastplate");
    set_short("banded leather breastplate");
    set_pname("banded leather breastplates");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_adj(({"banded","leather"}));
    set_long(
        "The banded leather breastplate is huge. " +
        "It is designed to wrap around the torso " +
        "covering the back, shoulders and front of " +
        "its user. The breastplate is made of thick " +
        "leather bands woven together over a metal " +
        "frame.\n");

    set_default_armour((30), A_BODY, 0, 0);
  /*         I  S  B  */
    set_am(({0, 2,-1}));

}
