/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_helm.c
 *
 * worn by the Dunker.
 *
 * Goldberry April 2000
 */

#include <wa_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    int aclass = 35+random(5);

    set_armour_size(LARGE);
    set_name("helm");
    set_short("heavy iron helm");
    set_pname("heavy iron helms");
    add_name("armour");
    set_long(
        "A heavy iron helm. Crafted from thick metal, this helm looks big "+
        "enough to cover two human heads at once.\n");

    set_adj(({"heavey","iron"}));

    set_default_armour(aclass, A_HEAD, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));

    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(aclass, A_HEAD))*2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/6);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(aclass) + 1000);

}
