/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cloak.c
 * A cloak, suitable for a witch. Mortricia 920720
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("cloak");
    set_short("black cloak");
    set_adj(({"black"}));
    set_long("It is a black cloak, suitable for a witch.\n");

    set_default_armour(5, A_ROBE, 0, TO);
}
