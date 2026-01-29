/*
	*Enchanted cloak
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

int ac = 40;

void
create_armour()
{
	set_name("shirt");
	add_name("ringmail");
	set_pname("shirts");
	set_adj(({"loose","ringmail"}));
	set_long("This shirt is made from metal rings clasped and fastened together, making a garment that covers from chest and shoulders down to the knee. It feels heavy. The metal of the shirt shines brightly.\n");
	set_short("loose ringmail shirt");
	set_pshort("loose ringmail shirts");
	set_default_armour(10, A_ROBE, ({ 0, 0, 0}), 0);
	add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(300));
	add_prop(OBJ_I_WEIGHT, 10000);
	add_prop(OBJ_I_VOLUME, 2000);
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
    write("You don the ringmail shirt, slipping it over your head. It settles comfortably over your shoulders.\n");
    obj->set_default_armour(ac, A_ROBE, ({ -2, 2, 0}), 0);
    add_prop(OBJ_I_WEIGHT, 3500);
    this_player()->update_armour(obj);
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
	write("With regret, you slip the ringmail off over your head.\n");
	obj->set_default_armour(10, A_ROBE, ({0, 0, 0}), 0);
	add_prop(OBJ_I_WEIGHT, 10000);
	this_player()->update_armour(obj);
	return 0;
}
