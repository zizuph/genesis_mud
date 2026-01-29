/*
 *
 *  Armour for the beacon attendant
 *
 *  Gorboth, January 1996
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("leggings");
    set_adj(({"steel","chainmail"}));
    set_short("pair of chainmail leggings");
    set_pshort("pairs of chainmail leggings");

    set_long(BSN("These leggings are composed of many hundreds of"
      + " bright steel rings which interlock to weave tube-like hose."
      + " The legs have been bound tightly by cords of rawhide and"
      + " leather woven between the rings at the crotch. Though heavy,"
      + " they offer excellent protection from harm."));

    set_default_armour(33, A_LEGS, ({2,2,-4}), TO);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(33)+TP->query_skill(SS_TRADING));
}
