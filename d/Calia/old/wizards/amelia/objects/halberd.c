inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#define OBJ_S_ORIGIN_ALIGNMENT "_obj_s_origin_alignment"


void
create_weapon()
{
	set_name("halberd");
	set_short("crystal halberd");
	set_long("One end is made of very sharp, hard crystal.\n");
	set_adj("crystal");
	set_hit(35);
	set_pen(35);
	set_hands(W_BOTH);
	set_wt(W_POLEARM);
	set_dt(W_SLASH | W_IMPALE);
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35)+random(50)-25);
	add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(35,35)+
		random(50)-25);
	add_prop(OBJ_I_LIGHT, 1);
	add_prop(OBJ_S_ORIGIN_ALIGNMENT, "good");
	}
