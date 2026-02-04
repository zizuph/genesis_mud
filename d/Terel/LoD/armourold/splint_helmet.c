/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * splint_mail.c
 *
 * worn by grunts, corporals in LoD.
 *
 * a splint helmet Redhawk 920812
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
    set_short("splint helmet");
    set_long("A splint elf made helmet of good quality.\n");
    set_adj(({"splint"}));

    set_default_armour(15, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
