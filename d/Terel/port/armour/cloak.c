/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * c_cloak.c
 *
 * A cloak, suitable for a witch. Mortricia 920720
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

public void
create_terel_armour()
{
    set_name("cloak");
    set_short("dusty cloak");
    set_long("A dusty cloak.\n");
    set_adj("dusty");
    set_default_armour(5, A_ROBE, 0, TO);
}
