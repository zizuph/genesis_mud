/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * furrobe.c
 *
 * made for use with the goblinlord.c   Tomas  -- Dec 1999
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"  
#include <ss_types.h>       
#include <tasks.h>  
#include <formulas.h>
    
inherit "/std/armour";
inherit "/lib/keep";


public void
create_armour()
{
    set_name("robe");
    set_long("The robe has been sewn using the finest blend of " +
       "furs found in Terel. You note the flawless seams as if " +
       "it was a single piece of fur.\n");

    add_item(({"fur","furs"}),
       "Mostly silver-coated sable with soft ermine trim.\n");

    set_adj(({"heavy","fur"}));
    set_default_armour(15, A_ROBE, 0, 0);
    set_am(({ 2, 2, -2}));
    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15) + 100); 
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This robe is enchanted. ", 10,          
        "It holds the virtues of the creature from whose hide "+
        "it was made from. ", 30,
        "The robe is resistant to damage by cold.\n", 50}));
    add_prop(OBJ_S_WIZINFO,
        "This robe is enchanted. It adds MAGIC_I_RES_COLD to 15.\n");


}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR) && (protectee == query_worn()))
    {
        if (prop == MAGIC_I_RES_COLD)
            return ({ 15, 1}); 
    } 
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}



int
wear(object ob)
{

   if (wearer->query_mana() <= 25) 
    {
        return "You are too mentally exhausted to wear the "+ short()+".\n";
    }
/*
if (wearer->query_alignment() <= 399) 
    {
        return "The "+short()+" resists you. You feel unworthy of wearing " +
           "the "+short()+".\n";
    }
*/



    TP->add_prop("wearing_fur",1);

    wearer->add_mana(-25);    
    wearer->add_magic_effect(this_object());
    wearer->catch_tell("The robe immediately radiates warmth over " + 
       "your entire body.\n");

    return 0;
}



int
remove(object ob)
{
   
    wearer->remove_magic_effect(this_object());
     
    TP->remove_prop("wearing_fur");

    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR))
    {
        wearer->catch_tell("You shiver uncontrollably as you remove the robe.\n");
    }

    return 0;
}
