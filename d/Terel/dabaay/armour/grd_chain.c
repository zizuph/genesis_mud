/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fry_pan.c
 *
 * worn by the militia in Dabaay.
 *
 * Goldberry, November 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(SMALL);
    set_name("chainmail");
    set_short("iron chainmail");
    set_pname("iron chainmails");
    add_name("armour");
    set_adj(({"iron"}));
    set_long(
        "A well made shirt of iron chainmail.  The dark rings are consistant "+
        "in shape and size, and the temper is strong. Clearly, the militia of "+
        "Dabaay wear these shirts proudly.\n");

    set_default_armour((30+random(5)), A_BODY, 0, 0);
    set_am(({0,2, -1}));
}
