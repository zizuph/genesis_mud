/*
	*Enchanted stag's head
	*Adds speed to the wearer and raises ac when worn
	*Altrus, June 2005
*/
inherit "/std/armour";
inherit "/lib/keep.c";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  

#define SPD	50

void create_armour()
{
	set_name("halfhelm");
	add_name("helm");
	set_pname("halfhelms");
	add_pname("helms");
	set_adj(({"antlered","stag's head"}));
	set_short("antlered stag's head halfhelm");
	set_pshort("antlered stag's head halfhelms");
	set_long("This helm is fashioned in the shape of a sleek stag's head, without a lower jaw, made from steel. It is not a full helm, however. It covers the back of the head well enough, but rides high over the ears and comes down over cheeks, leaving everything below the wearer's mouth uncovered. The antlers, which branch to four points on either side, appear to be made of steel as well, but blackened.\n");
	set_default_armour(15, A_HEAD, ({ 0, 0, 0}), 0);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(300));
	add_prop(OBJ_I_WEIGHT, 2500);
	add_prop(OBJ_I_VOLUME, 500);
	add_prop(OBJ_M_NO_BUY, 1);
	add_prop(OBJ_M_NO_SELL, 1);
	set_keep(1);
	set_wf(this_object());
}

/*
	* Function name: wear
	* Description  : This function might be called when someone tries to wear
	*                this armour. To have it called, use set_wf().
	* Arguments    : object obj - The armour we want to wear.
	* Returns      : int  0 - The armour can be worn normally.
	*                     1 - The armour can be worn, but print no messages.
	*                    -1 - The armour can't be worn, use default messages.
	*                string - The armour can't be worn, use this message.
*/
public mixed
wear(object obj)
{
	write("As the halfhelm settles on your head, your heart begins to pound, your breathing intensifies, and your legs fill with a sudden burst of energy. You feel light of foot and swift as a deer.\n");
	obj->set_default_armour(40, A_HEAD, ({ -2, 1, 1}), 0);
	TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + SPD);
	TP->update_armour(obj);
	return 0;
}

/*
	* Function name: remove
	* Description  : This function might be called when someone tries to remove
	*                this armour. To have it called, use set_wf().
	* Arguments    : object obj - The armour to remove.
	* Returns      : int  0 - Remove the armour normally.
	*                     1 - Remove the armour, but print no messages.
	*                    -1 - Do not remove the armour, print default message.
	*                string - Do not remove the armour, use this message.
*/
mixed
remove(object obj)
{
	write("Your legs feel sluggish and heavy as you remove the halfhelm.\n");
	obj->set_default_armour(15, A_HEAD, ({ 0, 0, 0}), 0);
	TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) - SPD);
	TP->update_armour(obj);
	return 0;
}
