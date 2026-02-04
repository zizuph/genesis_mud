/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots.c
 *
 * worn by forst giants
 *
 * Sorgum 951216
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour ()
{
    set_name (({"boots", "pair of boots"}));
    set_pname ("pairs of boots");
    set_short ("pair of giant boots");
    set_pshort ("pairs of steel boots");
    set_long ("Large boots wiyth bloodstains on them.\n");
    set_adj (({"giant"}));

    set_default_armour (10, A_FEET, 0, 0);
}
