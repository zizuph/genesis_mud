/*
 * Jenglea's magical staff
 * Goldberry March, 2000
 *
 ********************************************
 *
 * Combination weapon: staff, scythe, spear
 *
 * Scythe and spear:
 * Do extra damage to intoxicated targets.
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

int scythe_flag;

void scythe_descr();
void staff_descr();
void spear_descr();
private mixed twist_it(string arg);
public string my_shaft();

public void
create_weapon()
{
    set_wf(TO);
    staff_descr();

   add_name("jenglea's staff");
   add_item("hardwood shaft","@@my_shaft@@");
   add_prop(OBJ_I_WEIGHT,5500); 
   add_prop(OBJ_I_VOLUME,2000); 
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 1300);
   add_prop(OBJ_S_WIZINFO, "The scythe and spear do more damage  " +
      "to intoxicated targets.\n");

   add_prop(MAGIC_AM_MAGIC, ({ 62, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" is deadly against the inebriated.\n",50}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

public string
my_shaft()
{
    return "Looking closely at the wooden shaft of the "+short()+
      " you realize it might be possible to twist it.\n";
}

public void
init() 
{
    ::init();

    add_action(twist_it, "twist");
}

private mixed
twist_it(string arg)
{
    int success;

    if (ENV(TO) != TP)
     return 0;

    if (arg != "shaft")
     return 0;

    if (!(TO->query_wielded()))
    {
      TP->catch_tell("You must be wielding the "+short()+".\n");
      return 1;
    }

 
    /* Stat and intox checks */
    success = TP->query_stat(SS_DEX) / 2;
    success += TP->query_skill(SS_WEP_POLEARM) / 3;
    if ((success < MIN_WIELD) || (TP->query_intoxicated() > 0))
    {
      if(scythe_flag)
      {
        staff_descr();
        TP->catch_tell("The blade on the " + short() +
        " disappears back into the shaft.\n");
        tell_room(ENV(TP),
            "As "+ QTNAME(TP) + " twists the shaft on the "+ 
            short() + ", the blade disappears back into the "+
            "shaft.\n",TP,TP);
      }
      else
        TP->catch_tell("You twist the "+short()+" but nothing happens.\n");
      return 1;
    }

    if (scythe_flag == 0)
    {
          TP->catch_tell("As you twist the " + short() +
              ", a glittering steel blade unfolds from the shaft.\n"); 
          tell_room(ENV(TP),
              "As "+ QTNAME(TP) + " twists the "+ short() +
              ", a glittering steel blade unfolds from the "+
              "shaft.\n",TP,TP);
          scythe_descr();
          return 1;
    }
    if (scythe_flag == 1)
    {
          TP->catch_tell("As you twist the " + short() +
              ", the long blade retracts back into "+
              "the shaft, and a glittering steel spear point "+
              "extends from the end.\n");
          tell_room(ENV(TP),
              "As "+ QTNAME(TP) + " twists the "+ short() +
              ", the long blade retracts back into the shaft "+
              "and a glittering steel spear point extends from "+
              "the end.\n",TP,TP);
          spear_descr();
          return 1;
    }
    if (scythe_flag == 2)
    {
          TP->catch_tell("As you twist the " + short() +
              ", the spear point retracts into the shaft.\n");
          tell_room(ENV(TP),
              "As "+ QTNAME(TP) + " twists the "+ short() +
              ", the spear point retracts into the shaft.\n",TP,TP);
          staff_descr();
          return 1;
    }
 

}


mixed
unwield(object what)
{
    if (scythe_flag)
    {
        TP->catch_tell(
            "As you release your grip on the "+ short() +
            ", the blade retracts into the shaft.\n");
        tell_room(ENV(TP),
            "As "+ QTNAME(TP) + " releases the "+ short() +
            ", the blade retracts into the shaft.\n",TP,TP);
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
    if(TO->query_wielded())
       TP->update_weapon(TO);
}

void
scythe_descr()
{
    set_default_weapon(
       44,
       52,
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

    if (scythe_flag == 0)
    {
      remove_name("staff");
      remove_name("blackened");
    }
    if (scythe_flag == 2)
    {
      remove_name("spear");
    }
    scythe_flag = 1;
    TP->update_weapon(TO);
}

void
spear_descr()
{
    set_default_weapon(
       44,
       49,
       W_POLEARM,
       W_IMPALE | W_SLASH,
       W_BOTH);
    set_name("spear");
    add_name("blackened steel");
    set_adj("blackened");
    set_adj("steel");
    set_short("blackened steel spear");
    set_long(
        "A thick and long shaft of blackened hardwood, "+
        "with a deadly-looking glittering steel blade "+
        "attached to one end. The blade tapers to an "+
        "impossibly fine point at the tip. The blade "+
        "shimmers and glistens as you look at it.\n");

    if (scythe_flag == 0)
    {
      remove_name("staff");
      remove_name("blackened");
    }
    if (scythe_flag == 1)
    {
      remove_name("scythe");
    }
    scythe_flag = 2;
    TP->update_weapon(TO);
}

public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;
    int toxmax, tox;
     
    tox = enemy->query_intoxicated();

    if ((phurt > 0) && (tox > 0) && (random(12) > 3) && (scythe_flag > 0))
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

