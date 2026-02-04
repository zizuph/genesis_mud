/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * collar.c
 *
   Leather collar worn by farm2_dog.c
   Tomas  --  Jan 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("collar");
    set_adj(({"studded","leather"}));
    set_short("leather collar");
    set_long("This studded leather collar looks like it was " +
       "created for a dog.\n");
    set_ac(30);
    set_at(A_NECK);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 103);
}
