/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_boots.c
 *
 * a pair of ogre-sized boots for std_ogre.c of the elderwood forest
 *
 * Tomas   May, 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(LARGE);

    set_name("boots");
    set_pname("pairs of boots");
    set_short("pair of massive worn boots");
    set_pshort("pairs of massive worn boots");
    set_long("The pair of worn out boots are massive in size. " +
       "The material looks like horse hide and smell as if " +
       "the leather wasn't cured. The soles are riddled with " +
       "holes. The toes of the boots are stretched and torn " +
       "as if the feet inside were to large for the boots.\n");

    set_adj(({"massive","worn"}));
    add_name("armour");
    add_pname("armours");
    add_name("large armour");
    add_pname("large armours");

    set_default_armour(10, A_FEET, 0, 0);
}
