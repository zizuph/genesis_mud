/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_helm.c
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
    set_name("helmet");
    set_short("large dented helmet");
    set_pname("lage dented helmets");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "The large dented helmet looks worse for wear. Several " +
        "dents and dings cover the rounded helmet. Its nose guard " +
        "is chipped and bent, covering more cheekbone than nose. " +
        "The helmet is crafted from heavy cast iron and is much " +
        "larger than usual. It actually resembles a large cooking " +
        "pot.\n");

    set_adj(({"large","dented"}));

    set_default_armour((20), A_HEAD, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
