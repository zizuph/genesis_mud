/*
 *  /d/Gondor/anorien/druedain/amon-din/arm/schain_gloves.c
 *
 *  Armour for the beacon attendant
 *  Gorboth, January 1996
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("gloves");
    set_short("pair of chainmail gloves");
    set_pshort("pairs of chainmail gloves");
    set_adj(({"steel","chainmail"}));

    set_long(BSN("These gloves are comprised of hundreds of small"
      + " interlocking steel rings. They are supple and light,"
      + " offering both protection and relative comfort. The length"
      + " of the gloves allows for protection nearly to the elbow."));

    set_default_armour(23, A_ARMS | A_HANDS, ({0,0,0}), TO);
    add_prop(OBJ_I_WEIGHT,1750);
    add_prop(OBJ_I_VOLUME,288);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(23)+TP->query_skill(SS_TRADING));
}
