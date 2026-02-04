/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Commander scalemail for Stronghold commander.c
 * Tomas  -- 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"  
#include <ss_types.h>       
#include <tasks.h>  
#include <formulas.h>
    
inherit STDARMOUR;
inherit "/lib/keep";


public void
create_terel_armour()
{
    set_name("scalemail");
    set_pname("scalemail");
    set_adj(({"mithril"}));
    set_short("mithril scalemail");
    set_long("The mithril scalemail is covered in overlapping " +
       "scales made from polished mithril. The scales are woven " +
       "into a quilted backing reinforced by a hardened leather " +
       "skin.\n");

    set_keep(1);
    set_armour_size(SMALL);
    set_default_armour(50, A_BODY, 0, TO);
    
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,    1);
    add_prop(OBJ_S_WIZINFO, "The scalemail is magical to increase " +
       "its AC to 50 and to provide cold_resistance at 35. It also is very light\n");
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
         "This "+short()+ " is enchanted. ", 10,          
         "The suit radiates warmth. ", 30,
         "The robe is resistant to damage by cold.\n", 50}));

    add_prop(OBJ_I_VALUE,            900);
    add_prop(OBJ_I_WEIGHT,          5000);
}


varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (query_prop(OBJ_I_IS_MAGIC_ARMOUR) && (protectee == query_worn()))
    {
        if (prop == MAGIC_I_RES_COLD)
            return ({ 35, 1}); 
    } 
    else
    {
        return ::query_magic_protection(prop, protectee);
    }
}



int
wear_terel_armour(object ob)
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
    wearer->catch_tell("The " +short()+ " immediately radiates warmth over " + 
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
        wearer->catch_tell("You shiver uncontrollably as you remove the "+short()+".\n");
    }

    return 0;
}

