/*
 *  A flowing white cape for the beacon attendant
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
    set_name("cape");
    add_adj(({"flowing","white"}));
    set_short("flowing white cape");

    set_long(BSN("This cape has the silky sheen of material spun by"
      + " the finest looms in Minas Tirith. It is long and white, and"
      + " adds both warmth and stature to its bearer. Embroidered into"
      + " its surface with silver thread is a tree surrounded by seven"
      + " stars."));

    set_default_armour(3, A_ROBE, ({0,0,0}), TO);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+TP->query_skill(SS_TRADING)*2);
}
