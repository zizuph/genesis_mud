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
    set_name("cuirasse");
    set_short("large iron cuirasse");
    set_pname("large iron cuirasses");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "The large iron cuirasse looks like an old " +
        "farm plow smashed and bent to fit a very large " +
        "shoulder. heavy leather straps wrap around the " +
        "right arm and mid-torso securing the cuirasse " +
        "in place. It looks very heavy but offers good " +
        "protection for the shoulder and neck.\n");

    set_adj(({"large","iron"}));

    set_default_armour((20), A_NECK | A_R_ARM, 0, 0);

  /*          I  S  B  */
    set_am(({1, 1, 1}));

    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,8000);

}
