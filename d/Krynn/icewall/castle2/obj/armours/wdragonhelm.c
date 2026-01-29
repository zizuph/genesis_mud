inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_armour()
{
    set_name("mask");
    set_ac(31);
    set_at(A_HEAD);
    set_am( ({ -4, 4, 0 }) );
    add_adj( ({ "white", "face" }) );
   set_short("white face mask");
    set_long("It's a white face mask. You are not able to hide your face when you " +
	     "wear it, but you are positive this is an excellent piece of " +
	     "armour. Not only your face, but your entire head is protected with it.\n");
    add_prop(OBJ_I_VOLUME, 550);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(31, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31));
}
