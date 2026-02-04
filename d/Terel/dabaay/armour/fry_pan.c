/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fry_pan.c
 *
 * worn by halflings and kobolds in and around Dabaay.
 *
 * Goldberry, June 99
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(SMALL);
    set_name("pan");
    set_short("frying pan");
    set_long(
        "A heavy, black, iron frying pan.  This pan is large enough to cook several "+
        "eggs at once, or perhaps the better part of a pig.  Someone has affixed a "+
        "few leather thongs to the pan, making it possible to wear it on one's body.\n");

    set_adj(({"frying"}));

    set_default_armour(30, A_BODY, 0, 0);
    set_am(({1,-1, 0}));
}
