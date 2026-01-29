/*
 *   /d/Gondor/ithilien/poros/armours/shield.c
 *
 *   This is the standard shield used by the corsairs along the poros.
 *
 *   Talisan,  February 1996
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"shield"}));
    set_short("black shield");
    set_pshort("black shields");
    set_long("This round, black steel shield is of the make typically forged in Umbar. It is "
      + "fairly light weight, and of medium size. Crested upon the "
      + "front of the shield is the form of a great winged drake.\n");
    set_adj(({"black", "round", "umbarian", "steel", "light", "medium"}));

    set_default_armour(20,A_SHIELD,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(20)+random(100));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(20,A_SHIELD)-random(250));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
