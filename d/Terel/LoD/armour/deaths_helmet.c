




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_helmet.c
 *
 * worn by deaths knights and master knights in LoD.
 *
 *  a "deadly" helmet Redhawk920924
 * Modified by Sorgum 941026
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("helmet");
    set_pname("helmets");
    set_short("death's helmet");
    set_long("A darkened helmet that gives you the creeps. It looks like it " +
	     "belongs to Death himself. \n");
    set_adj(({"death's"}));
    add_adj("deaths");

    set_default_armour(40, A_HEAD, 0, 0);
}
