/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * c_cloak.c
 *
 * A cloak, suitable for a witch. Mortricia 920720
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
create_armour()
{
    set_name("cloak");
    set_short("dusty cloak");
    set_long("A dusty cloak.\n");
    set_adj("dusty");
    move(TO);

    set_default_armour(5, A_ROBE, 0, 0);
}
