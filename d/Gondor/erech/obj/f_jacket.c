/*
 * f_jacket.c
 * By Skippern Dec 20(c)00
 *
 * To be found on the farmers of Erech.
 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ARM       10
#define COLOURS   ({ "green", "red", "yellow", "brown", "gray", "blue" })
#define FABRIKES  ({ "wool", "cutton" })

object adj1, adj2;

/*
 * Function name:    create_armour
 * Description  :    Creates the armour object
 */
void
create_armour()
{
    adj1 = one_of_list(COLOURS);
    adj2 = one_of_list(FABRIKES);

    set_name("jacket");
    set_short(adj1+" "+adj2+" jacket");
    set_pshort(adj1+" "+adj2+" jackets");
    set_long("This is a jacket made of " + adj1 + " coloured " + adj2 + ". " +
	     "It looks comfortable to wear.\n");

    set_default_armour(ARM, A_BODY, ({ 0, 0, 0 }), 0);
    set_may_not_recover();

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARM) + random(ARM));
}
