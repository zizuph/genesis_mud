/*
 *   /d/Gondor/arnor/armour/mithril_armour.c
 *   coded by Tigerlily, June 4, 2005 for the 
 *      massive troll
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  

int ac = 50;

void
create_armour()
{
    set_name("chainmail");
    add_name("mithril");
    set_short("great mithril chainmail");
    set_pshort("great mithril chainmails");
    set_long("This armour is made of interlocking links " +
        "of mithril, relatively light for its size yet amazingly " +
        "strong. Its design allows it to cover the body, legs " +
        "and arms.\n");
    set_adj(({"great", "mithril", "chainmail" }));
    set_default_armour(20, A_BODY | A_ARMS | A_LEGS , ({0, 0, 0}), 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR( 25, A_BODY )-2000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(300));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    query_keepable();
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
    write("The rings of mithril tinkle merrily as you put on " +
        "the mithril chainmail. It feels quite light.\n");
    obj->set_default_armour(ac, A_BODY | A_ARMS | A_LEGS , ({0, 0, 0}), 0);
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
    obj->set_default_armour(20, A_BODY | A_ARMS | A_LEGS , ({0, 0, 0}), 0);
    this_player()->update_armour(obj);
    return 0;
}
