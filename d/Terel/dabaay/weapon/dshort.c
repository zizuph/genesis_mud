/*
 * magical shortsword
 * Goldberry 1/12/2000
 *
 ********************************************
 *
 * Does extra damage to intoxicated targets.
 * On a random(12)>3 against a target with
 * query_intoxicated > 0, it will do additional
 * damage equal to the target's percentage of
 * intoxication (query_intoxicated/intoxicated_max)
 * multiplied by the initial hit.
 * Max damage is dam * 2
 *
 */
 
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>

#define MIN_WIELD 75

public void
create_weapon()
{
    set_wf(TO);
    set_name("shortsword");
    add_name("sword");
    set_adj("glistening");
    set_short("glistening shortsword");
    set_long(
        "This is a very sharp, but fairly simple shortsword. "+
        "The hilt and pommel are unadorned, but highly "+
        "polished steel. The handle is wrapped with braided- "+
        "silver wire. The blade, however, is quite remarkable "+
        "with the way it seems to sparkle and glitter. The "+
        "blade appears to be made some sort of silver alloy, "+
        "but it is impossible to make a positive "+
        "determination of the colour.\n");
    
    set_default_weapon( /* See /sys/wa_types.h for maxima */
       45,                     /* 'to hit' value    */
       42,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_ANYH);                 /* either hand       */


   add_prop(OBJ_I_WEIGHT,5500); 
   add_prop(OBJ_I_VOLUME,2000); 
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 1300);
   add_prop(OBJ_S_WIZINFO, "The sword does more damage  " +
      "to intoxicated targets.\n");

   add_prop(MAGIC_AM_MAGIC, ({ 62, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" is deadly against the inebriated.\n",20}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

mixed
wield(object what)
{

    int success;

    /* Broken */
    if (query_prop(OBJ_I_BROKEN))
        return "It is of no use, the blade is too far gone.\n";

    /* Too drunk to wield */   
    if (TP->query_intoxicated() > 0)
    {
        TP->command("$drop weapons"); 
        return "You cannot seem to get a proper grip on "+
               "the "+ short() +".\n";
    }

    /* Stat checks */
    success = TP->query_stat(SS_DEX) / 2;
    success += TP->query_skill(SS_WEP_SWORD) / 3;
    if (success < MIN_WIELD)
        return "You do not feel confident enough to wield this "+
               "blade.\n";

    return 0;
}

public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;
    int toxmax, tox;
     
    tox = enemy->query_intoxicated();

    if ((phurt > 0) && (tox > 0) && (random(12) > 3))
    {
        wielder = query_wielded();
        toxmax = enemy->intoxicated_max();

        enemy->heal_hp(- (dam * tox / toxmax));
        enemy->catch_tell(
            "The blade on the "+short()+" seems to double as "+
            "it strikes you a blow in a dazzling flurry of "+
            "light.\n");
        wielder->catch_tell(
            "The "+short()+" sparkles and flashes as it "+
            "connects with "+enemy->query_the_name(wielder)+".\n");
        wielder->tell_watcher(
            "A dazzling flare of sparkling lights seemingly "+ 
            "explode from the "+short()+" as "+QTNAME(wielder)+
            " strikes a connecting blow.\n", enemy);    
     }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

