/*
 *   /d/Gondor/ithilien/poros/armours/helmet.c
 *
 *   This is the standard helmet worn by the corsairs at the hidden base
 *   in the manor near the Poros river.
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
    set_name(({"helmet", "helm"}));
    set_short("black helmet");
    set_pshort("black helmets");
    set_long("This black steel helm is of the make typically forged in "
      + "Umbar. The helmet offers good protection for the head, and an "
      + "extended strip over the nose helps protect the face as well.\n");
    set_adj(({"black", "steel", "umbarian"}));

    set_default_armour(20,A_HEAD,({0,0,0}), 0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(20)+random(500));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(20,A_HEAD)+random(200));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
