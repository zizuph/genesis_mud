/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stew_pot.c
 *
 * worn by halflings and kobolds in and around Dabaay.
 *
 * Goldberry June 10, 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(SMALL);
    set_name("pot");
    set_short("stew pot");
    set_long(
        "A stew pot of sturdy construction.  From the hardwood-handle, to the "+
        "quality tempered-iron, this pot has the looks of a fine cooking vessel.  "+
        "For a person of small stature, this pot would do well for protecting the "+
        "head.\n");

    set_adj(({"stew"}));

    set_default_armour(18, A_HEAD, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
