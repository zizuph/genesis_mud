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
    set_name("cloak");
    set_short("horse hide cloak");
    set_pname("horse hide cloaks");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "The horse hide cloak is rather large. It looks " +
        "as if something tore it right off of the horse. " +
        "The cloak smells like rotting carcass, as if it " +
        "wasn't cured properly. What looks like the foreleg " +
        "skin of the horse is used to wrap around the wearers " +
        "neck.\n");

    set_adj(({"horse","hide"}));

    set_default_armour((10), A_ROBE, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
