inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h" 

#define LEECH_MIN_SKILL 51
int alarm_id2, alarm_id, accum;

void create_weapon()
{
  set_name("leech");
  add_name(({"sword","scimitar"}));
  add_name("_shire_magebane");
  set_adj(({"sharp","black","blackened","jagged","wavy"}));
  set_short("sharp black scimitar");
  set_long("A sharp, blackened scimitar with a jagged, wavy blade "+
    "and hide-wrapped hilt. The blade is forged of an unknown "+
    "steel alloy, blackened to eliminate all reflections. The hide "+
    "wrap on the hilt is still covered with numerous bristles from "+
    "the boar it came from. "+
    "Set in the hilt is a dark red jewel that "+
    "seems to pulse slightly as you look at it.\n");
  set_default_weapon(45,35,W_SWORD,W_SLASH|W_BLUDGEON,W_NONE,TO);
  set_pm(({0,3,-3}));
  set_likely_dull(1);
  set_likely_corr(3);
  set_likely_break(2);
  add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(45,35)+random(1501));
  add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,35)+random(201));
  add_prop(MAGIC_AM_MAGIC,({78,"enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO,({
    BSN("The "+short()+" appears to be strongly magical."),1,
    BSN("The jewel in the hilt of the "+short()+" seems to draw "+
      "in magical energy."),45,
    BSN("The "+short()+" was forged ages ago by the greatest of "+
      "the orcish smiths with the aid of the maia Sauron. They "+
      "created Leech with one purpose in mind: to kill mages."),67,
    BSN("Accordingly, Leech will not even tolerate the touch of a "+
      "mage, and will force such would-be-users to drop it."),74,
    BSN("Leech stores the energy it drains, and releases the energy in "+
      "a violent burst when it can no longer contain the energy."),89,
    BSN("Leech possesses a will of its own, and is capable of forcing "+
      "those of weaker will to do its bidding!"),95}));
  add_prop(OBJ_S_WIZINFO,"The "+short()+" drains and stores a "+
    "random (10+random(51)) amount of mana from whatever it hits, until "+
    "the victim has 0 mana, at which point it stops draining. In "+
    "addition when the stored amount of energy exceeds a certain number "+
    "(150+random(51)), it releases this energy, blasting the current "+
    "enemy with a burst of energy equal to the amount of damage "+
    "done by the weapon that hit, effectively doubling damage for one "+
    "blow once every four to ten hits. Only those who are learning "+
    "sword as part of their occupation will be able to wield Leech. "+
    "(sword > 50). Leech has a special hatred of mages. "+
    "Thusly, members of a mage guild (lay or occ) will suffer "+    
    "damage and be forced to drop Leech if they should attempt to wield "+
    "it. They will also suffer double the extra damage from the special "+
    "attack. Finally, Leech will occassionally attempt to assert its "+
    "will upon the wielder. Those with weak mental facilities and "+
    "little discipline will be forced to attack someone they may not "+
    "wish to normally.\n"); 
}


int mage_drop()
{
  TP->command("drop _shire_magebane");
  return 1;
}


mixed wield()
{
  if(TP->IS_LAY_MAGE | TP->IS_OCC_MAGE)
  {
    TP->heal_hp(-250-random(151));
    TP->add_mana(-150-random(76));
    set_alarm(1.0,0.0,"mage_drop");
    SAY(" is suddenly bathed in an eerie ruby glow that seethes and "+
      "burns its way through "+HIS_HER(TP)+" body.");
    return "A piercing voice shreds your thoughts as it screams: "+
      "Infidel! I shall kill you for this sacrilage! How dare you "+
      "even attempt to use me!? If you ever try it again I will "+
      "seek you out and send you to the void!\n"+
      "For now, I will content myself with some of your lifeforce.\n";
  }
  if(TP->query_skill(SS_WEP_SWORD) < LEECH_MIN_SKILL)
  {
    return "A mocking voice echos in your head: 'You dare try to "+
      "wield me, you buffoon?! Give me to someone who knows how to "+
      "use me properly, now!'\n";
  }
  WRITEN("You wrap your hand around the hilt of the "+short()+".");
  SAY(" wields the "+short()+".");
  alarm_id = set_alarm(20.0,40.0,"leech_msg");
  alarm_id2 = set_alarm(30.0,50.0,"leech_urges");
  return 1;
}


void leech_msg()
{
  if(TP->query_attack())
    return;
  switch(random(7))
  {
    case 0:
      WRITEN("A comforting voice whispers to you: 'Soon we will "+
        "slay another foul mage!'");
      break;
    case 1:
      WRITEN("A hissing voice pleads: 'Feed me! I hunger!'");
      break;
    case 2:
      WRITEN("A rumbling voice echoes in your head: 'Kill "+
        "the mages, kill them all before they kill you!'");
      break;
  }
}

mixed test_race_func(object ob, string race_to_test)
{
  return (living(ob) && ob != TP && ob->query_race_name()==race_to_test);
}


void leech_attack()
{
  object *karr;
  karr = filter(all_inventory(ENV(TP)),"test_race_func",TO,"elf");
  if (!sizeof(karr))
    karr = filter(all_inventory(ENV(TP)),"test_race_func",TO,"human");
  if (!sizeof(karr))
    karr = filter(all_inventory(ENV(TP)),"test_race_func",TO,"dwarf");
  if (!sizeof(karr)) {
    WRITEN("A sad voice murmurs: 'There is nothing here worth "+
      "feeding upon. I will release you for now, but "+
      "feed me soon, or pay the ultimate price!'");
    return;
    }
  else if (karr[0]->query_race_name()=="elf")
  {
    WRITEN("A sinister voice says to you: 'Kill that elf, I must "+
      "be fed!'");
    TP->command("kill elf");
    return;
  }
  else if (karr[0]->query_race_name()=="dwarf")
  {
    WRITEN("A domineering voice commands: 'Kill that dwarf, I despise "+
      "dwarves!'");
    TP->command("kill dwarf");
    return;
  }
  else if (karr[0]->query_race_name()=="human")
  {
    WRITEN("A quiet voice whispers insideously into your ear: '"+
      "Slay the human, appease my hunger!'");
    TP->command("kill human");
    return;
  }
}


void leech_urges()
{
  if(MENT_STATS < (280 + random(56) + random(66)))
  {
    write("You feel a strong urge coming from the "+short()+
      ".\nYou muster all your willpower and attempt to resist.\n"+
      "However, the "+short()+" wins, leaving you exhausted "+
      "and the "+short()+" in control.\n");
    SAY(" seems to be involved in some internal struggle that "+
      "leaves "+HIM_HER(TP)+" tired, sweaty, and glassy eyed.");
    TP->add_fatigue(-30);
    TP->add_mana(-10);
    leech_attack();
    return;
  }
  write("You feel a strong urge coming from the "+short()+
    ".\nYou muster all your willpower, and attempt to resist.\n"+
    "With a final, draining effort, you beat back the urge "+
    "and retain control of your body.\n");
    SAY(" seems to be involved in some internal struggle that "+
      "leaves "+HIM_HER(TP)+" somewhat tired and sweaty.");
  TP->add_fatigue(-15);
  TP->add_mana(-5);
  return;
}


int unwield()
{
  object wielder = query_wielded();
  remove_alarm(alarm_id);
  remove_alarm(alarm_id2);
  WRITEN("You release your grip upon the "+short()+".");
  say(QCTNAME(wielder)+" unwields the "+short()+".\n");
  return 1;
}


/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}


int burn_me(object enemy, int dam) 
{
  int res;
  object wielder;
  wielder = query_wielded();
  res = enemy->query_magic_res(MAGIC_I_RES_MAGIC);
  dam = dam - (res*dam/100);

  if(enemy->IS_LAY_MAGE || enemy->IS_OCC_MAGE)
  {
    dam = dam*2;
  }
  if(dam<1)
  {
    enemy->catch_msg("A pulse of blood-red energy leaps from the "+ 
      short()+" , but misses you.\n");
    return 1;
  }
  enemy->heal_hp(-dam);
  enemy->catch_msg("A bolt of blood-red energy leaps from the "+short()+
    " and burns you badly!\n");
  wielder->catch_msg(QCTNAME(enemy)+" is burnt by the energy surge "+
    "from the "+short()+".\n");
  tell_watcher(QCTNAME(enemy)+" is briefly illuminated in blood-red "+
    "light as a bolt of energy slams into "+HIS_HER(enemy)+
     " body.\n",enemy);

  return 1;
}


int drain_me(object enemy, int dam) 
{
  int res, drained, amount;
  object wielder;
  wielder = query_wielded();
  res = enemy->query_magic_res(MAGIC_I_RES_DEATH);                    
  amount = random(51) + 10;
  drained = amount - random((res*amount/100)+1);

  if(drained < 1 || enemy->query_mana() < 1)
  {  
    enemy->catch_msg("The jewel on the "+short()+" pulses, but nothing "+   
      "seems to happen.\n");
    wielder->catch_msg("The jewel on the "+short()+" pulses, but "+   
      "nothing seems to happen.\n");
    return 1;
  }

  enemy->add_mana(-drained);
  enemy->catch_msg("The jewel on the "+short()+" pulses brighter, and "+
    "you feel drained.\n");
  wielder->catch_msg("The jewel on the "+short()+" pulses brighter as "+
    "your blow connects.\n");

  accum = accum + drained;
  if(accum>150+random(51))
  {
    burn_me(enemy,dam);
    accum = 0;
    return 1;
  }

  return 1;
}


public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  if(phurt>0)
  {
    drain_me(enemy,dam/3);
  }
}


query_recover()  { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }


