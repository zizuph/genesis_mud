/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * devils_chainmail.c
 *
 * worn by devils knight in LoD.
 *
 * a devils chainmail Redhawk 921103
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
    set_name("chainmail");
    set_short("devil's chainmail");
    set_long("It is a devils's chainmail that has an evil aura surrounding it.\n");
    set_adj(({"devil's", "devils"}));

    set_default_armour(37, A_BODY, 0, 0);
    set_am(({5, -2, -3}));
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,              1);
    add_prop(OBJ_M_NO_BUY,                       1);
    add_prop(OBJ_I_VALUE,         600 + random(20));
    add_prop(MAGIC_I_RES_FIRE,                  40);
    add_prop(OBJ_I_WEIGHT,                    4000);
}
