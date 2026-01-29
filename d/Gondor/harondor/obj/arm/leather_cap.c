/* 
 * Standard Haradrim cap from Harondor.
 * Serif, July 2001.
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
    set_name(({"helmet", "cap"}));
    set_short("black leather cap");
    set_pshort("black leather caps");
    set_long("This black leather cap is made of tanned leather from "
      + "some thick-skinned beast, and offers a little protection for "
      + "the head. It seems well-crafted and has a few scatches in "
      + "it, probably from heavy use.\n");
    set_adj(({"black", "leather", "haradrim"}));

    set_default_armour(15,A_HEAD,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(20)+random(300));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(20,A_HEAD)+random(200));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
