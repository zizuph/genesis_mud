/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * dtooth.c
 *
 * On the Red Dragon in the orc caves of Terel
 * Coded by Shinto 12-21-98
 *
 * Revisions:
 * 	Rhyn, Nov 2007:    Changed short to end confusion with lame Krynn teeth
 * 	Lucius, Oct, 2017: Reduced hit/pen. 42/42 -> 40/40
 *
 * Updated by Shanoga, November 2018
 *  - Tooth was not using standard recovery and was resetting
 *    the durability values on each recovery. Fixed to use standard
 *    recovery (removed Terel recovery).
 */
#include "/d/Terel/include/Terel.h"

/* inherit STDWEAPON; */

#include <wa_types.h>
#include <formulas.h>

inherit "/std/weapon";
inherit "/lib/keep";


/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"tooth"}));
    add_name("dagger");
    set_short("charred dragon tooth");
    set_long("A tooth of an enormous fire-breathing dragon. The tip could easily pierce "+
                  "into steel, rock, or flesh.\n");
    add_adj("charred");
    add_adj("dragon");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_default_weapon(40,40,W_KNIFE,W_IMPALE,W_ANYH,TO);
    add_prop(OBJ_I_RES_FIRE,100);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,({ 100, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" was once the tooth of an very old red dragon.\n",20,
           "The "+short()+" will strike true and deadly.\n",60,
           "The "+short()+" can provide some protection from fire.\n",90}));
    add_prop(OBJ_S_WIZINFO, "The "+short()+" is the tooth of a very old red "+
                   "dragon in Terel. It has a hit and pen of 42, and provides 20% "+
                   "resistance to fire. The dragon is fairly tough and quite deadly");
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE, 20000);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 750);
   

}


/*
 * Function name:  query_magic_protection     (see /std/object.c)
 * Description:    This function should return the amount of 
 *                 protection versus an attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee - Magic protection for who or what?
 */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    /* Check to see if the tooth is still enchanted */
    if (query_prop(OBJ_I_IS_MAGIC_WEAPON) && (protectee == query_wielded()))
    {
        if (prop == MAGIC_I_RES_FIRE)
            return ({ 20, 1}); 
    } 
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}

/*
 * Function name: wield          (This is excerpted from /std/weapon.c)
 * Description  : This function might be called when someone tries to wield
 *                this weapon. To have it called, use set_wf().
 * Arguments    : object obj - The weapon we want to wield.
 * Returns      : int  0 - The weapon can be wielded normally.
 *                     1 - The weapon can be wielded, but print no messages.
 *                    -1 - The weapon can't be wielded, use default messages.
 *                string - The weapon can't be wielded, use this message.
 */
mixed
wield(object ob)
{
    /* Check to see if the boots are still enchanted */
    if (!query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        return 0;
    }

    /* add_magic_effect() is defined in /std/object.c  It adds    
     * to the wearer the resistance as described in the function  
     * query_magic_protection (above).                            
     */
    wielder->add_magic_effect(this_object());

    /* We return 0 so that the normal wear messages occur.        */ 
    return 0;
}

/*
 * Function name: unwield        (This is excerpted from /std/weapon.c)
 * Description  : This function might be called when someone tries to 
 *                    unwield the weapon. To have it called, use set_wf().
 * Arguments    : object obj - The weapon to unwield.
 * Returns      : int  0 - unwield the weapon normally.
 *                     1 - unwield the weapon, but print no messages.
 *                    -1 - Don't unwield the weapon, print default message.
 *                string - Don't unwield the weapon, use this message.
 */
mixed
unwield(object ob)
{
    /* The magical resistance should only work when the owner is   
     * wearing the armour, so we have to remove_magic_effect()     
     * when the boots are removed.                                 
     */
    wielder->remove_magic_effect(this_object());

    /* Again, returning 0 so the normal remove message is given.   */ 
    return 0;
}
