/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * refugee_hat.c
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
    set_name("hat");
    set_short("fur-lined hat");
    set_pname("fur-lined hats");
    add_name("clothing");
    add_pname("clothings");
    set_long("The hat is fur-lined and is made to cover the head " +
        "and ears. It looks quite warm.\n");

    set_adj(({"fur-lined"}));

    set_default_armour((10), A_HEAD, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
