/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * refugee_tunic.c
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
    set_name("tunic");
    set_short("heavy woolen tunic");
    set_pname("heavy woolen tunics");
    add_name("clothing");
    add_pname("clothings");
    set_long(
        "A heavy woolen tunic dyed light grey with green fringe.\n");

    set_adj(({"heavy","woolen"}));

    set_default_armour((10), A_TORSO, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
