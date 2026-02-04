/*
 *  Sword for House4_captain.c  
 *  11/19/1999 -- Tomas
 */
 
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;
inherit "/lib/keep";
inherit "/d/Terel/include/cloned_weapons.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>


public void
create_weapon()
{
    set_name("sabre");
    add_name("sword");
    set_adj("ivory-handled");
    set_short("ivory-handled sabre");
    set_long("The sabre looks quite deadly. Its long curved blade " +
       "runs from its solid steel guard to its tapered tip. You cant " +
       "help but notice its most noticable trait the ivory handle. " +
       "The handle has been carved from two solid pieces of white " +
       "ivory, bound together by tight gold and silver cord.\n");

    
    set_default_weapon( /* See /sys/wa_types.h for maxima */
       42,                     /* 'to hit' value    */
       42,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_LEFT);                 /* left handed       */


   add_prop(OBJ_I_WEIGHT,6500); 
   add_prop(OBJ_I_VOLUME,2500); 
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 1200);
   add_prop(OBJ_S_WIZINFO, "The sword does more damage  " +
      "to trolls, giants and ogres.\n");

   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" was designed to do more damage on Trollkind.\n",20}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}



public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;

    if ((phurt >= 0) && 

      (enemy->query_race_name() == "troll" || enemy->query_race_name() == "ogre"
      || enemy->query_race_name() == "giant") && (random(10) > 7))

    {
        wielder = query_wielded();
        enemy->heal_hp(- ((random(dam/2)) + dam / 2));
        enemy->catch_tell("Sparks fly "+
                     "as the "+short()+" connects with your body.\n");
        wielder->catch_tell("The "+short()+" emits a brilliant arch of light"+
            " as it connects with "+enemy->query_the_name(wielder)+".\n");
        wielder->tell_watcher("A brilliant arch of light extends forth from " +
           "the "+short()+" as "+QTNAME(wielder)+" strikes the "+QTNAME(enemy)+".\n", enemy);    
     }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}