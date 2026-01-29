/**
 * Magical Armour
 * Louie 2004
 */
 
inherit "/std/armour";
//#include "../local.h"
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>

/** prototypes **/
public void set_time_to_stay(float f);

public void
create_armour()
{
	set_name("templar_armour");
	set_short("templar_armour");
	set_long("templar_armour long descrip\n");
	set_ac(40);
	set_at(A_MAGIC);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	set_shield_slot(({ A_BODY, A_HEAD, A_LEGS,
		A_R_ARM, A_L_ARM }));
	set_may_not_recover();
	//set_af(-1);
	set_af(0);
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
	
}

/** 
* Overwrite the decay, we don't want this armour breaking
*/

public void
set_armour_hits(int hits)
{
	::set_armour_hits(0);
}

/*
 * We set how long the armour lasts
 */
public void
set_time_to_stay(float f)
{
	set_alarm(f, 0.0, "remove_object");
}