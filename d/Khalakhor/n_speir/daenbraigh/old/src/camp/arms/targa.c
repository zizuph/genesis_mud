/*
 * Goblin garrison
 * Torqual, 10/2005
 */
#pragma strict_types

inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../camp/camp.h"

void
create_khalakhor_armour()
{   
    set_name("shield");
    set_pname("shields");

    add_name("targa");
    add_pname("targas");

    set_adj("round");
    set_adj("wooden");

    set_short("round wooden shield");
    set_pshort("round wooden shields");

    set_long("The targa is constructed of wood, covered with leather and brass mounts, with loops on the back through one of which the arm is passed while the other is grasped by the hand. It measures 24 inches in diameter and can be used as a defense against both arrows and hand weapons. It has a central spike which is almost ten inches long. The shield looks light and maneuverable.\n");

    set_ac(ACLASS);
    set_at(A_SHIELD);
    set_am(({1,-1,0}));

    add_prop(OBJ_I_WEIGHT, 3400);
    add_prop(OBJ_I_VOLUME, 1100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ACLASS));
    add_prop(GG_PROPERTY,1);
}
