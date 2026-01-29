/*
       dustcloak.c
       -----------

	Created by Kentari - July 1998 for Kayla (traveler.c) on the 
		VK-Kalaman Highway.
*/


inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"


void
create_armour()
{
    set_name("dustcloak");
    add_name("cloak");
    set_ac(4);
    set_at(A_ROBE);
    add_adj("worn");
    set_long("A dustcloak made for traveling the roads, this one has " +
	"seen its share of use. A mixture of grey and brown, it provides " +
	"a measure of protection from the dust of the road.\n");
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(4, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4));
}

