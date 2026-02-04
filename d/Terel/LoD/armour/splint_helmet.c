




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * splint_mail.c
 *
 * worn by grunts, corporals in LoD.
 *
 * a splint helmet Redhawk 920812
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
    set_short("splint helmet");
    set_long("A splint elf made helmet of good quality.\n");
    set_adj(({"splint"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(15, A_HEAD, 0, 0);
    set_am(({4, 2, -6}));
}
