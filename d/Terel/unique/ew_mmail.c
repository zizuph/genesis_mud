/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_mail.c
 *
 * Mergula's breastplate.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 *
 * Updated description, updated to use magic_effect, added
 * ability to disenchant the armour / dispell its magic.
 * Lilith, June 2005
 *
 * Added missing WIZINFO prop
 * Lilith, March 2009
 *
 * - Removed evil limitation on armour
 * - Reduced resistance protection to reasonable levels
 * - Added proper recovery code
 * - Changed to A_BODY, and updated value and weight accordingly
 * Petros, May 2009
 */

#include <wa_types.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";

public void
create_terel_armour()
{
    set_name("breastplate");
    set_short("blackened steel breastplate");
    set_long("It is a blackened steel breastplate of superb "+
	"dwarven quality. It provides excellent protection "+
        "for the chest while supplying an intimidating "+
        "visual display of a moulded, muscular torso.\n");
    set_adj("steel");
    add_adj("blackened");

    set_default_armour(42, A_BODY, 0, 0);
    set_am(({ 0, 8, -8}));

    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This breastplate has been made by the dwarf Realin when he " +
	  "was captured by the legion of darkness. Mergula forced " +
	  "Realin to make it somewhat resistant against fire  "+
      "and magic.\n", 10 }));
    add_prop(OBJ_S_WIZINFO, 
        "This armour has ac 42 and gives 10 levels of res_magic "+
        "and 10 levels of res_fire.\n");

}

/*
 * Function name:  query_magic_protection     (see /std/object.c)
 * Description:    This function should return the amount of 
 *                 protection versus an attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee - Magic protection for who or what?
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
    int fire;

    /* Check to see if the boots are still enchanted */
    if (!query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        return 0;
    }

    /* add_magic_effect() is defined in /std/object.c  It adds    
     * to the wearer the resistance as described in the function  
     * query_magic_protection.                           
     */
    this_player()->add_magic_effect(this_object());
    this_player()->catch_tell("The breastplate magically molds "+
        "itself to your body.\n"); 
   
    return 0;
}


int
remove(object ob)
{
   /* The magical resistance should only work when the owner is   
     * wearing the armour, so we have to remove_magic_effect()     
     * when the boots are removed.                                 
     */
    wearer->remove_magic_effect(this_object());
    return 0;

}

public int
disenchant_object(object disenchanter)
{
    /* Disenchant the item */

    /* Reset magical properties */
    remove_prop(OBJ_I_IS_MAGIC_ARMOUR);
    remove_prop(MAGIC_AM_MAGIC);
    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The breastplate once possessed some magical power, but it is " +
        "now gone.\n", 50 }));

    /* No longer magical, can't be over 40 */
    set_ac(40);

    /* It isn't worth as much without the magic */
    add_prop(OBJ_I_VALUE, 257); 

    /* No reason to restrict purchase of the breastplate anymore */
    remove_prop(OBJ_M_NO_BUY);

    /* Remove the magic effect if the item is worn */
    if (query_worn())
    {
        this_player()->remove_magic_effect(this_object());
    }

    // When disenchanted from recovery, we don't display the message.
    if (objectp(disenchanter))
    {
        /* Give a message indicating that it was disenchanted */
        tell_room(environment(this_object()), "The blackened "+
           "steel breastplate glows darkly for a moment and "+
           "then goes dull, as if it has lost something "+
           "vital!\n");
    }
    
    /* Return 1, indicating that it was disenchanted */
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "#ima#" 
        + query_prop(OBJ_I_IS_MAGIC_ARMOUR) + "##";
}

void
init_recover(string arg)
{
    string foobar;
    int is_magic_armour;
    
    init_arm_recover(arg);
    if (sscanf(arg, "%s#ima#%d##", foobar, is_magic_armour) != 2
        || !is_magic_armour) 
    {
        disenchant_object(0);
    }
}
