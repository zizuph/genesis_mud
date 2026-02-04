/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * c_cloak.c
 *
 * A dusty cloak, but of very high quality. Mortricia 931111
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
    ::create_armour();
    set_name("cloak");
    set_short("dusty cloak");
    set_long("It's a dusty cloak, but when you examine it closer you see\n"+
             "it must be of very high quality.\n");
    set_adj(({"dusty"}));

    set_default_armour(22, A_ROBE, 0, 0);
    set_am(({ -2, 0, 2}));
}
