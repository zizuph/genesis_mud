/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * devils_helmet.c
 *
 * worn by devils knights in LoD.
 *
 * a devils helmet Redhawk921103
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
    set_short("devil's helmet");
    set_long("A devil's helmet that radiates an evil aura.\n");
    set_adj(({"devil's", "devils"}));

    set_default_armour(35, A_HEAD, 0, 0);
    set_am(({ 4, 4, -8}));
}
