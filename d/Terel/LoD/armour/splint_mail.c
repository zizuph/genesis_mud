




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * splint_mail.c
 *
 * worn by grunts, corproals in LoD.
 *
 * a splint mail Redhawk 920812
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
    set_name("splint mail");
    set_short("splint mail");
    set_long("It's a small elf made splint mail of good quality.\n");
    set_adj(({"splint"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_default_armour(10, A_BODY, 0, 0);
    set_am(({-2, 0, 2}));
}
