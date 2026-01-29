/*  Created by: Lord Charok, 18'th of October 2001 for Clay Valley.
 *          This sword is magically enchanted to be faster and
 *          lighter then regular weapons, thus the likely_dull
 *          and likely_break will be modified plus property
 *       LIVE_I_QUICK in player 15% help will be added.
 *
 *          Copyright(c) Charok @ Clay Valley, T Windahl.
 *
 *          Copy given to Stralle to use on Genesis, no major
 *          changes allowed. (Balance is naturally ok!)
 *  Purpose:
 *  Modified by:
 *  Cotillion 13.Oct.2004
 *    - fixed ::did_hit to make it breakable.
 *  Cotillion 18.Jan.2021
 *    - fixed runtime in did_hit
 */

inherit "/std/weapon";
inherit "/lib/keep"; // making it keepable and will default it to keepable

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>

#define TO  this_object()
#define TP  environment(TO)
/*
 * But wielding this sword in one hand gives HIT+5 and PEN-5
 * To simplyfy code base value will be set after single hand.
 */
int HIT = 46 + random(2);
int PEN = 37 + random(2);

int THIT, TPEN;

int sword_is_in_both = 0;
int gSpeed = 15;
object *gWeapons;

void
create_weapon()
{
  set_name("bastardsword");
  set_pname("bastardswords");
  add_name("sword");
  set_adj("golden-hued");
  set_short("golden-hued bastardsword");
  set_pshort("golden-hued bastardswords");
  set_long("@@query_long");

  set_keep(1);

  /* Raise the dull speed but lower likely break,
   * making player having to go and sharpen all the time.
   */
  set_likely_dull(6);
  set_likely_break(3);

  set_hit(HIT);
  set_pen(PEN);

  set_wf(TO);
  set_wt(W_SWORD);
  set_dt(W_SLASH | W_IMPALE);

  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT,  (HIT + PEN + random(15)) * 65 ); /* 5,9 - 6,8 kg */
  add_prop(OBJ_I_VOLUME,  3500); /* 3.5 litres */
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + 250 + random(50));

  add_prop(MAGIC_AM_MAGIC,({60, "enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The " + TO->query_short() + " appears to be magical in some way. ",1,
    "The onyx pommelstone on the " + TO->query_short() + " seems to " +
        "emmit this magic. ", 45,
    "It appears the magic in this weapon is made to make it last longer. ", 65,
    "The magic is imbued not only in the onyx stone, but also in the very blade itself. ", 75,
    "The " + TO->query_short() + " is made very light and thus being quite fragile, " +
    "but the magic protects it from breaking too easily. ", 90,
    "It seems this weapon will actually grant the wielder higher speed in combat. ", 95}));
  add_prop(OBJ_S_WIZINFO,"The " + TO->query_short() + " is magically enchanted to " +
    "not break very easily, though the likely_dull is raised. Also it will grant " +
    "the wielder a " + gSpeed + "% increased attack rate.\n");

  add_item(({"inlay","inlays","golden inlay","golden inlays"}), "These are very nice " +
   "inlays indeed. Inserted into the platinum crossguard with a mastery skill. The " +
   "surface is totally smooth.\n");
}


string
query_long()
{
  if(!query_wielded())
    return "This bastardsword is almost four feet long and the thin double edged blade " +
    "itself is two inches wide, it is golden-hued all the way from the " +
    "crossguard to the top. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a golden cord, at the bottom there is a pommelstone made of onyx. The " +
    "platinum crossguard is straight and in both ends two smaller onyx stones are fastened. " +
    "There are nice inlays of gold on the crossguard, they look like two vines " +
    "intertwined with the roots in the pommel.\n";

  if(!sword_is_in_both)
    return "This bastardsword is almost four feet long and the thin double edged blade " +
    "itself is two inches wide, it is golden-hued all the way from the " +
    "crossguard to the top. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a golden cord, at the bottom there is a pommelstone made of onyx. The " +
    "platinum crossguard is straight and in both ends two smaller onyx stones are fastened. " +
    "There are nice inlays of gold on the crossguard, they look like two vines " +
    "intertwined with the roots in the pommel. " +
    "The sword fits well in your hand, eventhough it is quite heavy on your wrist.\n";

    return "This bastardsword is almost four feet long and the thin double edged blade " +
    "itself is two inches wide, it is golden-hued all the way from the " +
    "crossguard to the top. The hilt is seven inches long giving a good grip for " +
    "wielding the sword either single handedly or two-handedly. The hilt is bound " +
    "with a golden cord, at the bottom there is a pommelstone made of onyx. The " +
    "platinum crossguard is straight and in both ends two smaller onyx stones are fastened. " +
    "There are nice inlays of gold on the crossguard, they look like two vines " +
    "intertwined with the roots in the pommel. " +
    "The sword fits well in the grip of your strong hands.\n";
}


int
wield_sword(string arg)
{
  mixed tmp;

  if (!arg)
    return 0;

  gWeapons = TP->query_weapon(-1);

  if(parse_command(arg, TO, " [the] %o 'two-handedly' "))
  {
     if(TO->query_wielded())
     {
        if(sword_is_in_both)
          TP->catch_msg("You are already wielding the " +TO->query_short()+" two-handedly.\n");
        else
          TP->catch_msg("You are already wielding the " +TO->query_short()+ ".\n");

        return 1;
     }
     if(sizeof(gWeapons)!=0)
     {
       TP->catch_msg("Your hands are too occupied to wield this sword two-handedly.\n");
       return 1;
     }
     sword_is_in_both = 1;

     set_hit(HIT - 5);
     set_pen(PEN + 5);

     set_hands(W_BOTH);



     if(TP->query_skill(SS_WEP_SWORD) < 55 && !(TP->query_npc()))
     {
         TP->catch_tell("You are not skilled enough to wield this sword!\n");
         return 1;
     }

     tell_room(environment(TP), QCTNAME(TP)+ " wields the "+
     TO->query_short()+ " in both " + TP->query_possessive() +" hands.\n", TP);
     TP->catch_msg("You wield the " + TO->query_short()+ " in both your hands.\n");

     tmp = wield_me();

     if( (TO->query_wielded())->query_npc())
     {
        set_hit(HIT + 10);
        set_pen(PEN + 10);
     }

     if(tmp == 1)
      return 1;

     sword_is_in_both = 0;

     set_hit(HIT);
     set_pen(PEN);
     set_hands(W_ANYH);

     if( (TO->query_wielded())->query_npc())
     {
        set_hit(HIT + 10);
        set_pen(PEN + 10);
        return 1;
     }

     return 1;
  }

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

  (TO->query_wielded())->change_prop(LIVE_I_QUICKNESS,
    (TO->query_wielded())->query_prop(LIVE_I_QUICKNESS) - gSpeed);
  ((TO->query_wielded())->query_combat_object())->cb_update_speed();

  sword_is_in_both = 0;
  return 0;
}

mixed
wield(object obj)
{
  int same_type = 0, x;
  string *wep_names;

  if(sizeof(gWeapons))
    for(x = 0; x < sizeof(gWeapons); x++)
    {
      wep_names = gWeapons[x]->query_names();


      if(member_array("bastardsword", wep_names) > -1)
        same_type = 1;
    }

  if(TP->query_skill(SS_WEP_SWORD) < 55 && !(TP->query_npc()))
  {
     return "You are not skilled enough to wield this sword!\n";
  }

  if(sword_is_in_both == 0)
  {
    if(TP->query_stat(SS_STR) < 80 && !(TP->query_npc()))
      return "You are not strong enough to wield this sword single handedly.\n";
    else if(TP->query_skill(SS_2H_COMBAT) < 55 && same_type != 0 && !(TP->query_npc()))
      return "You are not skilled enough to wield this sword single handedly while " +
             "already wielding another bastardsword.\n";
    else if(TP->query_stat(SS_STR) < 105 && same_type && !(TP->query_npc()))
      return "You are not strong enough to wield this sword single handedly while " +
             "already wielding another bastardsword.\n";

      TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + gSpeed);
      (TP->query_combat_object())->cb_update_speed();

   }
   else
   {
      set_hit(HIT);
      set_pen(PEN);
      set_hands(W_ANYH);

      TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS) + gSpeed);
      (TP->query_combat_object())->cb_update_speed();

      if( (TO->query_wielded())->query_npc())
      {
        set_hit(HIT + 10);
        set_pen(PEN + 10);
      }

   }

  if(sword_is_in_both == 1)
    if(TP->query_stat(SS_STR) < 45 && !(TP->query_npc()))
      return "You are not strong enough to wield this sword.\n";

  if(sword_is_in_both == 1 || sword_is_in_both == 0)
    return sword_is_in_both;

}

/*
 * Function name : query_hitloc_id
 * Description   : Will extract hitloc_id from object enemy, based on
 *                 the hdesc of the hitloc. We need this function since
 *                 this info is not available directly from within hit_me()
 *         It gives us the hitloc_id regardless of humanoid.
 * Returns   : hitloc_id    if found
 *                -1    if no hitloc_id is found
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
    string where;
    object armour, me = this_object()->query_wielded();
    int x, tmp, i_am_real = !(me->query_npc());
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if ((!objectp(enemy)) || (!objectp(me)))
    {
        return 0;
    }

    string with = QSHORT(this_object());

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

    where = " the " + hdesc + " of ";

    switch (phurt)
    {
    case 0..4:
        how = ". ";
        what = "scrape";
        owhat = "scrapes";
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
        how = ". ";
        what = "wound";
        owhat = "wounds";
        break;
    case 30..49:
        how = ". ";
        what = "injure";
        owhat = "injures";
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

    if(i_am_real)
    {
        me->catch_msg("You " + what + where + enemy->query_the_name(me) +
            " with your " + with + how + "\n");
    }

    if(interactive(enemy))
    {
        enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
            " with " + me->query_possessive() + " " + with + how + "\n");
    }

    me->tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
      " with " + me->query_possessive() + " " + with + how + "\n", enemy);


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

init()
{
    ::init();
    add_action(wield_sword, "wield");
}

