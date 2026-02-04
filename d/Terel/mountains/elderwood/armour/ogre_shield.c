/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_cuirasse.c
 *
 * worn by std_ogre.c Elderwood Forest.
 *
 * Tomas  May 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(LARGE);
    set_name("shield");
    set_short("wooden tower shield");
    set_pname("wooden tower shields");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "The wooden tower shield is quite large. It looks " +
        "like someone took a wooden door, added leather straps " +
        "to it, then fashioned wagon wheel metal bands around " +
        "it for added strength. The shield looks as if it would " +
        "provide decent protection provided " +
        "the wearer was tall enough.\n");

    set_adj(({"wooden","tower","large"}));

    set_default_armour((35), A_SHIELD, 0, 0);

  /*          I  S  B  */
    set_am(({1, 1, 1}));

    set_likely_break(10);   // its wood!

    add_prop(OBJ_I_WEIGHT,11000);
    add_prop(OBJ_I_VOLUME,9000);

}
