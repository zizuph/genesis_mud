/*
 *   /d/Gondor/ithilien/poros/armours/leather.c
 *
 *   This is the standard armour worn by the corsairs at the hidden base.
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
    set_name(({"armour", "armor", "leather armour"}));
    set_adj("leather");
    add_adj("black");
    set_short("black leather armour");
    set_pshort("black leather armours");
    set_long("This black leather armour is of standard Umbarian make. "
      + "The armour is light weight, and offers fair protection for "
      + "the upper body.\n");
    set_adj(({"black", "light", "umbarian"}));


    set_default_armour(13,A_BODY,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(13)+random(200));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(13,A_BODY)-random(300));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
