/*      Created by:     Lord Charok, 16'th of August 2001 for Clay Valley.
 *                      This sword is magically enchanted to be more solid
 *                      and endure hits longer, thus the likely_dull,
 *                      likely_corr and likely_break will be modified.
 *
 *                      Copyright(c) Charok @ Clay Valley, T Windahl.
 *
 *                      Copy given to Stralle to use on Genesis, no major 
 *                      changes allowed. (Balance is naturally ok!)
 *      Purpose:        
 *      Modified by: Milan 23.sept.2003 
 *                      - added strict_types 
 *                      - fixed runtime in wield
 *                      - cleaned up wield/unwield functionality (messy code)
 *                   Cotillion 13.Oct.2004
 *                      - fixed ::did_hit to make it breakable.
 *
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep"; // making it keepable and will default it to keepable

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>

#define TO      this_object()
#define TP      environment(TO)
/* But wielding this sword in one hand gives HIT+5 and PEN-5
 * To simplyfy code base value will be set after single hand.
 */ 
int HIT = 42 + random(4);
int PEN = 41 + random(4);

int THIT, TPEN;

int sword_is_in_both = 0;
 
void
create_weapon()
{
    set_name("bastardsword");
    set_pname("bastardswords");
    add_name("sword");
    set_adj("blackened");
    set_short("blackened bastardsword");
    set_pshort("blackened bastardswords");
    set_long("@@query_long");

    set_keep(1);
    
    set_likely_dull(4);
    set_likely_corr(6);
    set_likely_break(4);

    set_wf(TO);
    set_hit(HIT);
    set_pen(PEN);
 
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
 
    set_hands(W_ANYH);
 
    add_prop(OBJ_I_WEIGHT,  2000); /* 5 kg */
    add_prop(OBJ_I_VOLUME,  2500); /* 2.5 litres */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + 100 + random(20));
    add_prop(OBJ_M_NO_BUY, 1);
                          
  add_prop(MAGIC_AM_MAGIC,({60, "enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The " + TO->query_short() + " appears to be magical in some way. ",1,
    "The onyx pommelstone on the " + TO->query_short() + " seems to " +
        "emit this magic. ", 45,
    "It appears the magic in this weapon is made to make it last longer. ", 65,
    "The blackened surface of the sword glimmers to your sensitive eyes " +
        "and you see that the magic is imbued not only in the onyx stone, " +
        "but also in the very blade itself. ", 75,
    "The " + TO->query_short() + " will also withstand corrosion better than "
+
        "other swords. ", 90,
    "It seems that this fine weapon would not break very easily due to the strong " +
        "magic protecting it. ", 95}));
  add_prop(OBJ_S_WIZINFO,"The " + TO->query_short() + " is magically enchanted to " +
        "endure hard use for a longer period of time than regular swords. Also " +
        "it will withstand corrosion better and will not break very easily.\n"); 

}
 

string 
query_long()
{
  if(!query_wielded())
    return "This bastardsword is about four feet long and the blackened double " +
    "edged blade itself is two inches wide. The blade is sharply jagged a foot up " +
    "from the crossguard. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a metal cord and at the bottom there is a pommelstone made of onyx.  The " +
    "crossguard is straight and in both ends two smaller onyx stones are fastened.\n";
    
  if(!sword_is_in_both)
    return "This bastardsword is about four feet long and the blackened double " +
    "edged blade itself is two inches wide. The blade is sharply jagged a foot up " +
    "from the crossguard. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a metal cord and at the bottom there is a pommelstone made of onyx. The " +
    "crossguard is straight and in both ends two smaller onyx stones are fastened. " +
    "The sword fits well in your hand, even though it is quite heavy on your wrist.\n";
    
    return "This bastardsword is about four feet long and the blackened double " +
    "edged blade itself is two inches wide. The blade is sharply jagged a foot up " +
    "from the crossguard. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a metal cord and at the bottom there is a pommelstone made of onyx.  The " +
    "crossguard is straight and in both ends two smaller onyx stones are fastened. " +
    "The sword fits well in the grip of your strong hands.\n";
}

 
int
wield_sword(string arg)
{
  mixed tmp;

  object* gWeapons = TP->query_weapon(-1);
  //arg may be 0 - caused runtime in parse_command call. Milan
  if(arg && parse_command(arg, TO, " [the] %o 'two-handedly' "))
  {
     if(TO->query_wielded())
     {
        if(sword_is_in_both)
          TP->catch_msg("You are already wielding the " +TO->query_short()+
		 " two-handedly.\n");
        else
          TP->catch_msg("You are already wielding the " +TO->query_short()+
		 ".\n");
        return 1;
     }
     if(sizeof(gWeapons)!=0)
     {
       TP->catch_msg("Your hands are too occupied to wield this sword two-handedly.\n");
       return 1;
     }

     if(TP->query_skill(SS_WEP_SWORD) < 55 && !(TP->query_npc()))
     {
         TP->catch_tell("You are not skilled enough to wield this sword!\n");
         return 1;
     }

     sword_is_in_both = 1; 
     set_hit(HIT - 5);
     set_pen(PEN + 5);
     set_hands(W_BOTH);

     tmp = wield_me();

     if(tmp == 1) 
	return 1;

     TP->catch_msg(tmp);
     
     sword_is_in_both = 0;
     set_hit(HIT);
     set_pen(PEN);
     set_hands(W_ANYH);
     return 1;
  }
  return 0;
}
 
void
init()
{
    ::init();
    add_action(wield_sword, "wield");
}
 
void
leave_env(object from, object to)
{
  sword_is_in_both = 0;
  set_hit(HIT);
  set_pen(PEN);
  set_hands(W_ANYH);
    
  if(TO->query_wielded())
	(TO->query_wielded())->command("$unwield " + OB_NAME(TO));
  
  ::leave_env(from, to);
}

mixed
unwield(object obj)
{
  set_hit(HIT);
  set_pen(PEN);
  set_hands(W_ANYH);
  sword_is_in_both = 0; 
  return 0;
}

mixed
wield(object obj)
{
  if (TP->query_npc())
  {
        set_hit(HIT + 10);
        set_pen(PEN + 10);
        return 0;
  }

  if (TP->query_skill(SS_WEP_SWORD) < 55)
  {
     return "You are not skilled enough to wield this sword!\n";
  } 

  if (sword_is_in_both == 0)
  {
    if(TP->query_stat(SS_STR) < 80)
    {
      return "You are not strong enough to wield this sword single " +
	     "handedly.\n";
    }
    else
    {
      set_hit(HIT);
      set_pen(PEN);
      set_hands(W_ANYH);
      return 0;
    }
  }

  // (sword_is_in_both == 1)
  if(TP->query_stat(SS_STR) < 45)
    return "You are not strong enough to wield this sword.\n";
  return 0;
}

/*
 * Function name : query_hitloc_id
 * Description   : Will extract hitloc_id from object enemy, based on
 *                 the hdesc of the hitloc. We need this function since
 *                 this info is not available directly from within hit_me()
 *                 It gives us the hitloc_id regardless of humanoid.
 * Returns       : hitloc_id    if found
 *                        -1    if no hitloc_id is found
 */
int
query_hitloc_id(string hdesc, object enemy)
{
  int i, *hitloc_id;
  int a;
  object co;
  mixed hitloc;

  co = enemy->query_combat_object();
  hitloc_id = co->query_hitloc_id();

  a = sizeof(hitloc_id);
  
  for (i = 0; i < a; i++)
  {
    hitloc = co->query_hitloc(hitloc_id[i]);
    
    if (hitloc[2] == hdesc)
      return hitloc_id[i];
  }
  return -1;
}

/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                       If this is negative, it indicates fail
 *                dam:   Damage we did in hit points
 *
 * I mask this funtion to give my own descriptions to hits.
 * 
 * The flail will increase damage if there is no armour
 * where it hit, as the spikes will tear into the flesh.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
           int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;
    object armour, me = this_object()->query_wielded();
    int x, tmp, i_am_real = !(me->query_npc());
    int hitloc_id;
    string wound_desc = ({"nasty wounds", "bleeding wounds", "bloody scratches",
             "open wounds", "gaping wounds", "torn flesh", "shredded skin",
             "deep cuts",
	     "vicious wounds", "chunks of gore on the jagged edge and blood " +
             "gushing from the wounds",
	     "chunks of flesh on the jagged edges"})[random(10)];

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    hitloc_id = query_hitloc_id(hdesc, enemy);
    armour = enemy->query_armour(hitloc_id);

    if(!armour)
    {
      /* This gives a bonus damage of 7% if the sword hits
         an unprotected area
       */
      phurt = phurt * 107 / 100;
    }

    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return 0;
    }

    with = this_object()->query_short();

    if (phurt == -1 || phurt == -2)
    {
        enemy->add_panic(1);

        if (i_am_real && !me->query_option(OPT_GAG_MISSES))
        {
            me->catch_msg("You aim for the " + hdesc + " of " +
                enemy->query_the_name(me) + " with your " + with +
                " but miss.\n");
        }
        if (interactive(enemy) && !enemy->query_option(OPT_GAG_MISSES))
        {
            enemy->catch_msg(me->query_The_name(enemy) + " aims for your " +
                hdesc + " with " + me->query_possessive() + " " + with +
                ", but misses.\n");
        }
        me->tell_watcher(QCTNAME(me) + " aims for the " + hdesc + " of " +
            QTNAME(enemy) + " with " + me->query_possessive() + " " +
            with + ", but misses.\n", enemy, 0, 1);
        return 1;
    }

    enemy->add_panic(-3 - (phurt / 5));
    where = " the " + hdesc + " of ";

    switch (phurt)
    {
    case 0..4:
        how = ". ";
        what = "tickle";
        owhat = "tickles";
        break;
    case 5..9:
        how = ". ";
        what = "graze";
        owhat = "grazes";
        break;
    case 10..19:
        how = ". ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 20..29:
        how = ", rather bad. ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 30..49:
        how = ", very bad. ";
        what = "hurt";
        owhat = "hurts";
        break;
    case 50..69:
        how = ", very hard. ";
        what = "smash";
        owhat = "smashes";
        break;
    case 70..89:
        how = ", with a bone crushing sound. ";
        what = "smash";
        owhat = "smashes";
        where = " ";
        break;
    default:
        how = ". ";
        what = "massacre";
        owhat = "massacres";
        where = " ";
    }

    if(hdesc == "arms")
      if(random(1))
        hdesc = "left arm";
      else
        hdesc = "right arm";
      
    if(hdesc == "legs")
      if(random(1))
        hdesc = "left leg";
      else
        hdesc = "right leg";

    tmp = random(3);

    if (i_am_real && !armour)
    {
        if(tmp == 0)
          me->catch_msg("You " + what + where + enemy->query_the_name(me) +
              " with your " + with + how + "Using the momentum of the attack you " +
              "lunge forward with your " + with + " allowing the jagged edges on " +
              "the blade rip into the naked skin of your enemy's " + hdesc + ", " +
              "leaving " + wound_desc + ".\n");
        else if(tmp == 1)
          me->catch_msg("You " + what + where + enemy->query_the_name(me) +
              " with your " + with + how + "You twist your " + with + 
              " allowing the jagged edges on the blade rip into the naked " +
              "skin of your enemy's " + hdesc + ", leaving " + wound_desc + ".\n");
        else
          me->catch_msg("You " + what + where + enemy->query_the_name(me) +
              " with your " + with + how + "At the last moment you thrust your " +
              with + " forward allowing the jagged edges on the blade scrape into " +
              "the naked skin of your enemy's " + hdesc + ", " +
              "leaving " + wound_desc + ".\n");
    }
    else if (i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how + "\n");
    }
    
    if (interactive(enemy) && !armour)
    {
      if(tmp == 0)
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + QCTNAME(me)
+
            " uses the momentum of the attack and lunges towards you with " +
            me->query_possessive() + with + ", allowing the jagged edges on " +
            "the blade rip into your naked skin, leaving " + wound_desc + ".\n");
      else if(tmp == 1)
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + QCTNAME(me) +
            " twists " + me->query_possessive() + with + " allowing the jagged " +
            "edges on the blade rip into the naked skin on your " + hdesc + 
            ", leaving " + wound_desc + ".\n" );
      else
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + "At the last " +
            "moment " + QTNAME(me) + " thrusts " + me->query_possessive() + " "
+
            with + " forward, allowing the jagged edges on the blade scrape into " +
            "the naked skin on your " + hdesc + ", leaving " + wound_desc + ".\n" );
    }
    else if (interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + "\n");
    }    
    
    if (!armour)
    {
      if(tmp == 0)
        me->tell_watcher(QCTNAME(me) + " " + owhat + where +
            "with " + me->query_possessive() + " " + with + how + QCTNAME(me) +
            " uses the momentum of the attack and lunges towards " + QTNAME(enemy) +
            " with "  + me->query_possessive() + " " + with + ", allowing the " +
            "jagged edges on the blade rip into the naked skin, leaving " + 
            wound_desc + ".\n" );
      else if(tmp == 1)
        me->tell_watcher(QCTNAME(me) + " " + owhat + where +
            "with " + me->query_possessive() + " " + with + how + QCTNAME(me) +
            " twists " + me->query_possessive() + " " + with + " allowing the jagged " +
            "edges on the blade rip into the naked skin on the " + hdesc + 
            ", leaving " + wound_desc + ".\n" );
      else
        me->tell_watcher(QCTNAME(me) + " " + owhat + where +
            "with " + me->query_possessive() + " " + with + how + "At the last " +
            "moment " + QTNAME(me) + " thrusts " + me->query_possessive() + " " +
            with + " forward, allowing the jagged edges on the blade scrape into " +
            "the naked skin on the " + hdesc + ", leaving " + wound_desc + ".\n" );
    }
    else
    {
      me->tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
        " with " + me->query_possessive() + " " + with + how + "\n", enemy);
    }

    return 1;
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this weapon is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the weapon recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your weapon to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + " HIT#" + HIT + " PEN#" + PEN + " ";
}

/*
 * Function name: init_recover
 * Description  : When the object recovers, this function is called
 *                to set the necessary variables. If you redefine the
 *                function, you must add a call to init_wep_recover
 *                with the string that you got after querying
 *                query_wep_recover.
 * Arguments    : string argument - the arguments to parse
 */
public void
init_recover(string arg)
{
    int tmp;
    string misc;
    
    init_wep_recover(arg);
    
    tmp = sscanf(arg, "%sHIT#%d PEN#%d %s", misc, THIT, TPEN, misc);

    set_hit(THIT);
    set_pen(TPEN);
}

