/*
 * Base for shamans on level 2
 * - Boreaulam, August 2014
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

int armour_type;

#define ARMOUR_AC 39
#define ARMOUR_TYPE_BONUS 6

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{
	armour_type = random(3);
	string * adjs = ({"leather", "ringmail", "platemail"});
	int *armour_mods = ({0,0,0});

    set_adj(adjs[armour_type]);
	armour_mods[armour_type] += ARMOUR_TYPE_BONUS;
    set_ac(ARMOUR_AC);
	set_am(armour_mods);
} /* create_armour */

/*
 * Function name:        query_type
 * Description  :        type of armour
 */
int
query_type()
{
	return armour_type;
 } /* query_type */

/*
 * Function name:        query_long_add
 * Description  :        addition of long description depends on type
 */
string
query_long_add()
{
	switch(armour_type)
	{
		case 0:
			return "a quick study of the leather suggests that this armour " +
				"will offer some additional protection against any impaling " +
				"attack";
		case 1:
			return "a quick study of the overlapping rings suggests that " +
				"this armour will offer some additional protection against " +
				"any slashing attack";
		case 2:
			return "a quick study of the overlapping metal plates suggests " +
				"that this armour will offer some additional protection " +
				"against any crushing attack";
	}
	return "";
 } 
 /* query_long_add */

/*
 * Function name:        set_weight
 * Description  :        set weight depends on material
 */
void
set_weight(int w)
{
	float *density =({0.8, 1.0, 1.2});
    add_prop(OBJ_I_VOLUME, ftoi(density[armour_type] * itof(w)));
    add_prop(OBJ_I_WEIGHT, ftoi(density[armour_type] * itof(w)));
 } /* set_weight */


void 
set_at(int type)
{
	::set_at(type);

	set_weight(F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_AC, type));
/*	set_value(F_VALUE_ARMOUR(ARMOUR_AC));  */
}

 
