/*
       scarf.c
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
    set_name("scarf");
    set_ac(1);
    set_at(A_ROBE);
    add_adj("light");
    set_long("A light scarf to cover the face when traveling dusty " +
	"roads. Very plain, but effective all the same.\n");
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(1, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
}

