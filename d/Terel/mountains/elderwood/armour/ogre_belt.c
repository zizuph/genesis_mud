/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_horse_cloak.c
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
    set_name("belt");
    set_short("wide shoulder-strap belt");
    set_pname("wide shoulder-strap belts");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "The wide leather belt looks large enough to fit a horse! " +
        "The waist belt is very wide, made of strong leather. " +
        "A thinner strap runs diagonally across the " +
        "chest, connecting to a strong metal loop in the back. " +
        "The large unadorned metal buckle sits firmly in the middle.\n");

    set_adj(({"wide","leather","black","shoulder-strap"}));

    set_default_armour((10), A_WAIST, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
