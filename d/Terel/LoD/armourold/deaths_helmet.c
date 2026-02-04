/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * deaths_helmet.c
 *
 * worn by deaths knights and master knights in LoD.
 *
 *  a "deadly" helmet Redhawk920924
 * Modified by Sorgum 941026
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
    set_name("helmet");
    set_short("death's helmet");
    set_long("A darkened helmet that gives you the creeps. It looks like it " +
	     "belongs to Death himself. \n");
    set_adj(({"death's"}));
    add_adj("deaths");

    set_default_armour(38, A_HEAD, 0, 0);
    set_am(({ 4, 4, -8}));
}
