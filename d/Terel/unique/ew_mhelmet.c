/*
 * ew_helmet.c
 *
 * Mergula's helmet.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 *
 * Updated the description to be more interesting.
 * Lilith, June 2005
 *
 * Added headbutt function. Limit 5 times with 1 minute cooldown.
 * Lilith, Feb 2008
 *
 * Removed headbutt function. Added proper resistance functionality 
 * described in wizinfo
 * Petros, May 2009
 *
 */

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
inherit "/lib/keep";

public void
create_terel_armour()
{
    set_name("helmet");
    set_short("plumed helmet of blackened steel");
    set_long("This helmet has been superbly crafted to "+
      "protect the head while leaving the face open so "+
      "as not to obstruct vision. Dark plumage rises "+
      "along the crest of the blackened steel, adding "+
      "intimidating height to the wearer.\n");
    set_adj("plumed");
    add_adj(({"blackened", "steel"}));
    add_item(({"crest", "plumage", "plume"}),
        "The crest of the helmet is decorated with "+
        "a long row of black horsetail that resembles "+
        "the plumage of an exotic bird.\n");

    set_default_armour(29, A_HEAD, 0, 0);
    set_am(({ 2, 2, -4}));
    set_keep(1);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This helmet was made by the dwarf Realin when he " +
	  "was captured by the legion of darkness.\n", 10,
      "It grants fire and magic resistance.\n", 50 }));
    add_prop(OBJ_S_WIZINFO, 
        "This armour gives resistance "+
        "to fire (10 levels) and resistance to magic "+
        "(10 levels). It is cloned by Mergula in the "+
        "LoD.\n");         
}

/*
 * Function name:  query_magic_protection
 * Description:    This function should return the
 *                 amount of protection versus an 
 *                 attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee  - Magic protection for who or what? 
 */
public varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    // This object grants 10% magic protection and 10% fire protection
    switch (prop)
    {
    case MAGIC_I_RES_FIRE:
    case MAGIC_I_RES_MAGIC:
        return ({ 10, 1 });
    }     
   
    return ::query_magic_protection(prop, protectee);
}

public mixed
wear_terel_armour(object obj)
{
    this_player()->add_magic_effect(this_object());
    
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
public int
remove(object obj)
{
    wearer->remove_magic_effect(this_object());    
    return 0;
}
