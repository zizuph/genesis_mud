/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * splint_mail.c
 *
 * worn by grunts, corproals in LoD.
 *
 * a splint mail Redhawk 920812
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
    set_name("splint mail");
    set_short("splint mail");
    set_long("It's a small elf made splint mail of good quality.\n");
    set_adj(({"splint"}));

    set_default_armour(10, A_BODY, 0, 0);
    set_am(({-2, 0, 2}));
}
