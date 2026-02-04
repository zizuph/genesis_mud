/*
 * magical scythe
 * Goldberry January, 2000
 *
 ********************************************
 *
 * Does extra damage to intoxicated targets.
 * On a random(12)>4 against a target with
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

int scythe_flag;

void scythe_descr();
void staff_descr();

public void
create_weapon()
{
    set_wf(TO);
    staff_descr();

   add_name("jenglea's scythe");
   add_prop(OBJ_I_WEIGHT,5500); 
   add_prop(OBJ_I_VOLUME,2000); 
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 1300);
   add_prop(OBJ_S_WIZINFO, "The scythe does more damage  " +
      "to intoxicated targets.\n");

   add_prop(MAGIC_AM_MAGIC, ({ 62, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" is deadly against the inebriated.\n",50}));
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
      return 0;

    /* Stat checks */
    success = TP->query_stat(SS_DEX) / 2;
    success += TP->query_skill(SS_WEP_POLEARM) / 3;
    if (success < MIN_WIELD)
      return 0; 

    TP->catch_tell("As you take hold of the " + short() +
        ", a glittering steel blade unfolds from the shaft "+
        "and locks into place.\n"); 
    tell_room(ENV(TP), 
        "As "+ QTNAME(TP) + " takes hold of the "+ short() +
        ", a glittering steel blade unfolds from the "+
        "shaft and locks into place.\n",TP,TP); 
    scythe_descr(); 
    return 0;
}

mixed
unwield(object what)
{
    if (scythe_flag)
    {
        TP->catch_tell(
            "As you release your grip on the "+ short() +
            ", the blade folds back into the shaft.\n");
        tell_room(ENV(TP),
            "As "+ QTNAME(TP) + " releases the "+ short() +
            ", the blade folds back into the shaft.\n",TP,TP);
        staff_descr();
    }
}

void
staff_descr()
{
    set_name("staff");
    add_name("blackened");
    set_adj("blackened");
    set_short("blackened staff");
    set_long(
        "A thick and long shaft of blackened hardwood.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       35,                     /* 'to hit' value    */
       32,                     /* penetration value */
       W_POLEARM,                /* weapon type       */
       W_BLUDGEON,             /* damage type       */
       W_BOTH);                 /* either hand       */
    remove_name("scythe");
    remove_name("blackened steel");
    remove_adj("steel");
    scythe_flag = 0;
}

void
scythe_descr()
{
    set_default_weapon(
       43,
       51,
       W_POLEARM,
       W_SLASH,
       W_BOTH);
    set_name("scythe");
    add_name("blackened steel");
    set_adj("blackened");
    set_adj("steel");
    set_short("blackened steel scythe");
    set_long(
        "A thick and long shaft of blackened hardwood, "+
        "with a deadly-looking glittering steel blade "+
        "attached to one end. The blade curves and tapers "+
        "from a handspan at the base, to an impossibly fine "+
        "point at the tip. The blade shimmers and glistens "+
        "as you look at it.\n");

    remove_name("staff");
    remove_name("blackened");
    scythe_flag = 1;
    TP->update_weapon(TO);
}

public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;
    int toxmax, tox;
     
    tox = enemy->query_intoxicated();

    if ((phurt > 0) && (tox > 0) && (random(12) > 4))
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

