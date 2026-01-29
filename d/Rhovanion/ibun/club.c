#pragma save_binary

inherit "/std/weapon";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

#define WEAPON_HIT 21
#define WEAPON_PEN 26

int club_is_in_both;

void create_weapon()
{
    halb_is_in_both = 0;

    set_name("club");
    set_pname("clubs");
    set_adj("mysterious");
    set_short("mysterious club");
    set_long("@@query_long");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);

    set_wt(W_CLUB); 
    set_dt(W_IMPALE); 

    set_hands(W_ANYH);
    set_wf(this_object());

    add_prop(OBJ_I_WEIGHT,  6000); /* 5 kg */
    add_prop(OBJ_I_VOLUME,  5000); /* 2.5 litres */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
                          (90+random(21)) / 100);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"This club looks weird to you.\n",1,
      "It may be better or worse depending how you use it.\n",25,
      "The club works best against good opponents.\n",78 }));
}

string query_long()
{
  if(!query_wielded())
     return "This is as far you can see, a very nice club.\n";
  if(!you_are_evil)
    return "This is the best club you ever saw maybe,  "+
           "but it doesnt seem to like you.\n";
  return "This is a mysterious club. It fits exactly into your hands "+
         "and it seems like if it is hitting on its own.\n";
}

void init()
{
    ::init();
    add_action("wield_club", "wield");
}

int wield_halberd(string arg)
{
  mixed err;

  if(parse_command(arg, TO, " [the] %o 'in' [the] 'both' 'hands' "))
  {
     you_are_evil = 1;
     set_hit(2*WEAPON_HIT);
     set_pen(2*WEAPON_PEN);
     set_hands(W_BOTH);
     set_short("excellent halberd");
     remove_adj("strange");
     set_adj("excellent");
     err = wield_me();
     if(err == 1) return 1;
     err = implode(explode(err,"excellent"),"strange");
     write(err);
     halb_is_in_both = 0;
     set_hit(WEAPON_HIT);
     set_pen(WEAPON_PEN);
     set_hands(W_ANYH);
     remove_adj("excellent");
     set_adj("strange");
     set_short("strange halberd");
     return 1;
  }
  return 0;
}

void enter_env(object dest, object old)
{
  ::enter_env(dest, old);
  if(dest->query_name() == "_misty_goblin_")
  {
     halb_is_in_both = 1;
     set_hit(2*WEAPON_HIT);
     set_pen(2*WEAPON_PEN);
     set_hands(W_BOTH);
     set_short("excellent halberd");
     remove_adj("strange");
     set_adj("excellent");
  }
}

void leave_env(object from, object to)
{
  halb_is_in_both = 0;
  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_hands(W_ANYH);
  remove_adj("excellent");
  set_adj("strange");
  set_short("strange halberd");
  ::leave_env(from, to);
}

void unwield()
{
  if(TP->query_name() == "_misty_goblin_") return 0;

  halb_is_in_both = 0;
  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_hands(W_ANYH);
  remove_adj("excellent");
  set_adj("strange");
  set_alarm(0.0, 0.0, "set_short", "strange halberd");
  return;
}

int try_hit(object enemy)
{
  int skill, stat, skill_e, stat_e, pen, perf, pdam;
  mixed *hitresult;
  object me;
  string text, ptext;

  me = query_wielded();
  skill = me->query_skill(SS_WEP_POLEARM);
  stat = me->query_stat(SS_STR);
  skill_e = enemy->query_skill(SS_DEFENCE);
  stat_e = enemy->query_stat(SS_DEX);

  if(!halb_is_in_both)
  {
    if(random(100) < (skill/2)) return 1;
    me->catch_msg("You try to hit "+QTNAME(enemy)+" with your halberd "+
                  "but it suddenly twists in your hand and you miss.\n");
    enemy->catch_msg(QCTNAME(me)+" tries to hit you with "+
                     me->query_possessive()+" halberd but it suddenly twists "+
                     "in "+me->query_possessive()+" hand and "+
                     me->query_pronoun()+" misses.\n");
    me->tell_watcher(QCTNAME(me)+" tries to hit "+QTNAME(enemy)+" with "+
                     me->query_possessive()+" halberd but it suddenly twists "+
                     "in "+me->query_possessive()+" hand and "+
                     me->query_pronoun()+" misses.\n", enemy);
    return 0;
  }

  if ((random(100) < (skill/2)) && 
      (random(skill+stat) > random(skill_e+stat_e)))
  {
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_IMPALE, me, -1);
    perf = hitresult[2] * 100 / pen;
    pdam = hitresult[0];

    ptext = "a poor";
    if (perf > 15)
      ptext = "a nice";
    if (perf > 30)
      ptext = "a good";
    if (perf > 45)
      ptext = "a succesful";
    if (perf > 60)
      ptext = "a very succesful";
    if (perf > 75)
      ptext = "a wonderful";
    if (perf > 90)
      ptext = "an excellent";

    text = "unharmed";
    if (pdam > 0)
      text = "tickled";
    if (pdam > 2)
      text = "grazed";
    if (pdam > 5)
      text = "slightly hurt";
    if (pdam > 10)
      text = "hurt";
    if (pdam > 17)
      text = "rather hurt";
    if (pdam > 25)
      text = "very hurt";
    if (pdam > 35)
      text = "smashed";
    if (pdam > 50)
      text = "crushed";
    if (pdam > 70)
      text = "massacred";
    if (pdam > 90)
      text = "seeing death coming";

    me->catch_msg("You make "+ptext+" blow on "+QTNAME(enemy)+" with your "+
                  "halberd.\n"+capitalize(enemy->query_pronoun())+" seems "+
                  "to be "+text+".\n");
    enemy->catch_msg(QCTNAME(me)+" makes "+ptext+" blow on you with "+
                     me->query_possessive()+" halberd.\n"+
                     "You are "+text+".\n");
    me->tell_watcher(QCTNAME(me)+" makes "+ptext+" blow on "+QTNAME(enemy)+
                 " with "+me->query_possessive()+" halberd.\n"+
                 capitalize(enemy->query_pronoun())+" seems to be "+
                 text+".\n", enemy);
    if (enemy->query_hp() <= 0)
    {
      enemy->do_die(me);
      return 0;
    }
  }
  return 1; /* Try hit */
}

query_recover() { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
