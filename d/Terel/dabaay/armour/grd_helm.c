/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stew_pot.c
 *
 * worn by the militia in Dabaay.
 *
 * Goldberry November, 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_armour_size(SMALL);
    set_name("helm");
    set_short("iron helm");
    set_pname("iron helms");
    add_name("armour");
    set_long(
        "A sturdy iron helm.  The thick metal, flat top, and rough-cut "+
        "edges, give the impression that this helm was once a cooking-pot "+
        "of some kind.  It was clearly made for those with small heads.\n");

    set_adj(({"iron"}));

    set_default_armour((20+random(5)), A_HEAD, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 1, 0}));
}
