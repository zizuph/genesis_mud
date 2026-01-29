inherit "/std/weapon";

#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define HIT 25
#define PEN 9

void create_weapon()
{
	set_name("club");
	add_name("rolling pin");
	add_name("pin");
	add_adj("heavy");
	add_adj("wooden");
	set_short("heavy wooden rolling pin");
	set_pshort("heavy wooden rolling pins");
	set_long("This rolling pin is used to flatten dough for baking. It might cause some pain if swung right.\n");
	set_default_weapon(HIT, PEN, W_CLUB, W_BLUDGEON, W_RIGHT);
	add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_CLUB));
	add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
	add_prop(OBJ_I_VOLUME, F_VOLUME_WEAPON);
}

void init()
{
	::init();
	add_action("swing_pin", "swing");
}

int swing_pin(string str)
{
	if(str == "pin" | str == "rolling pin" | str == "heavy pin" | str == "heavy rolling pin" | str == "wooden pin" | str == "wooden rolling pin" | str == "heavy wooden pin" | str == "heavy wooden rolling pin")
	{
		this_player()->catch_msg("You wildly swing the rolling pin around. Be careful, you might hit someone!\n");
	
		say(QCTNAME(this_player()) + " wildly swings " + HIS_HER(this_player()) + " heavy rolling pin around! You have to duck to avoid being hit on the head!\n");
	
		return 1;
	}
	
	else
	{
		this_player()->catch_msg("Swing what?\n");
		return 1;
	}
}