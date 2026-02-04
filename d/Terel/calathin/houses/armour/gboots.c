/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * boots worn by house4_captain.c
 * Tomas, 11/19/1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name(({"boots", "pair of boots"}));
    set_pname("pairs of boots");
    set_short("pair of grey boots");
    set_pshort("pairs of grey boots");
    set_long("A pair of polished grey boots.\n");
    set_adj(({"polished","grey"}));
    add_name("armour");
    add_pname("armours");

    set_default_armour(15, A_FEET, 0, 0);
}

