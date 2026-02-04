/*
 * magical dagger
 * Goldberry May 2000
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
    set_name("dagger");
    add_name("weapon");
    set_pname("daggers");
    add_pname("weapons");
    set_adj("mithril-bladed");
    add_adj(({"mithril","bladed"}));
    set_short("mithril-bladed dagger");
    set_pshort("mithril-bladed daggers");
    set_long(
        "A dagger with a blade crafted of lustrous mithril. The hilt "+
        "of this impossibly-sharp weapon, is made from polished-onyx and "+
        "studded with rubies. The blade gleams and sparkles with an "+
        "remarkable brilliance.\n");
    
    set_default_weapon( /* See /sys/wa_types.h for maxima */
       35,                     /* 'to hit' value    */
       40,                     /* penetration value */
       W_KNIFE,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_RIGHT);               /* right hand only   */


   add_prop(OBJ_I_WEIGHT,1500); 
   add_prop(OBJ_I_VOLUME,1000); 
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 2300);
   add_prop(OBJ_S_WIZINFO, "The dagger does more damage  " +
      "to intoxicated targets.\n");

   add_prop(MAGIC_AM_MAGIC, ({ 62, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" is deadly against the inebriated.\n",40}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

mixed
wield(object what)
{

    int success;

    /* Broken */
    if (query_prop(OBJ_I_BROKEN))
        return "It is of no use, the weapon is too far gone.\n";

    /* Too drunk to wield */   
    if (TP->query_intoxicated() > 0)
    {
        TP->command("$drop weapons"); 
        return "You cannot seem to get a proper grip on "+
               "the "+ short() +".\n";
    }

    /* Stat checks */
    success = TP->query_stat(SS_DEX) / 2;
    success += TP->query_skill(SS_WEP_KNIFE) / 3;
    if (success < MIN_WIELD)
        return "You do not feel confident enough to wield this "+
               "weapon.\n";

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

