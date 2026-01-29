/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * furrobe.c
 *
 * made for use with the goblinlord.c   Tomas  -- Dec 1999
 *
 * Lilith, Nov 2008:
 * set_af was not defined so the magical protect, etc was not working.
 *
 * Petros, May 2009:
 * - Updated weight and value of robe
 * - Removed ALTER_PROP and use new mudlib calls for inc_prop and dec_prop
 *
 * Petros, October 2009:
 * - Removed used of inc_prop and dec_prop because it screws up the accounting
 *   for speed.
 * 
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"  
#include <ss_types.h>       
#include <tasks.h>  
#include <formulas.h>
#include <stdproperties.h>
    
inherit STDARMOUR;
inherit "/lib/keep";

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif

#define ROBE_ADDED_QUICKNESS    25

public void
create_terel_armour()
{
    set_name("robe");
    set_pname("robes");
    set_long("The robe has been sewn using the finest blend of " +
       "furs found in Terel. You note the flawless seams as if " +
       "it was a single piece of fur.\n");
    set_short("fur robe");
    set_pshort("fur robes");

    add_item(({"fur","furs"}),
       "Mostly silver-coated sable with soft ermine trim.\n");

    set_adj(({"heavy","fur"}));
    set_default_armour(25, A_ROBE, 0, 0);
    set_af(this_object());
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This robe is enchanted. ", 10,          
        "It holds the virtues of the creatures from whose hide "+
        "it was made from. ", 30,
        "The robe is resistant to damage by cold.\n", 50,
        "It also conveys some swiftness upon the wearer.\n", 70}));
    add_prop(OBJ_S_WIZINFO,
        "This robe is enchanted. It adds MAGIC_I_RES_COLD to 25, "+
         "and LIVE_I_QUICKNESS to 25.\n");

	add_prop(OBJ_COLD_WEATHER_PROTECT, 1);

}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_COLD)
    {
        return ({ 25, 1}); 
    } 

    return ::query_magic_protection(prop, protectee);
}

mixed
wear_terel_armour(object ob)
{
    if (wearer->query_mana() <= 25) 
    {
        return "You are too mentally exhausted to wear the "+ short()+".\n";
    }

    wearer->add_mana(-25);
    wearer->add_magic_effect(this_object());
    wearer->catch_tell("The robe immediately radiates warmth over " + 
       "your entire body.\n");
    wearer->add_prop(LIVE_I_QUICKNESS, wearer->query_prop(LIVE_I_QUICKNESS) + 25);
    return 0;
}

mixed
remove(object ob)
{
    object wearer = query_worn();   
    wearer->remove_magic_effect(this_object());
    wearer->add_prop(LIVE_I_QUICKNESS, wearer->query_prop(LIVE_I_QUICKNESS) - 25);
    wearer->catch_tell("You shiver uncontrollably as you remove the robe.\n");

    return 0;
}
