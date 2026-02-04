/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chainmail.c Used by std_goblin_grd.c
 * Tomas -- Dec. 1999
 */


#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    set_short("steel chainmail");
    set_long("The steel chainmail looks well made. Possibly, by dwarven " +
       "hands.\n");
    set_adj(({"steel","dwarven"}));
    set_default_armour(30, A_BODY, 0, 0);
    set_armour_size(SMALL);

    add_prop(OBJ_I_VALUE,            500);
    add_prop(OBJ_I_WEIGHT,          9000);
}