/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ogre_fur_robe.c
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
    set_name("fur");
    add_name("robe");
    add_name("furs");
    set_short("heap of fur");
    set_pname("heap of furs");
    add_name("armour");
    add_name("large armour");
    add_pname("large armours");
    set_long(
        "Various animal furs tied together to make " +
        "a rough looking robe. The furs look " +
        "mostly like dog, bear and other various " +
        "forestlife. The collection of furs looks " +
        "large enough to cover a good sized bed.\n");

    set_adj(({"heap","collection","of"}));

    set_default_armour((15), A_ROBE, 0, 0);

  /*          I  S  B  */
    set_am(({-1, 2, -1}));
}
