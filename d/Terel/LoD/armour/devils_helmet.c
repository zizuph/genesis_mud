




/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * devils_helmet.c
 *
 * worn by devils knights in LoD.
 *
 * a devils helmet Redhawk921103
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
    set_short("flaming red helmet");
    set_long("A flaming red helmet that radiates an evil aura.\n");
    set_adj(({"flaming", "red"}));

    set_default_armour(35, A_HEAD, 0, 0);
    set_am(({ 4, 4, -8}));
}
