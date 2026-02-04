/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * small_helmet.c
 *
 * worn by small guards is LoD.
 *
 * a small shield Redhawk 920728
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
    set_name(({"shield"}));
    set_pname("shields");
    set_short("small shield");
    set_pshort("small shields");
    set_long("Its a small elf made shield of good quality.\n");
    set_adj(({"small"}));

    set_default_armour(10, A_SHIELD, 0, 0);
}
