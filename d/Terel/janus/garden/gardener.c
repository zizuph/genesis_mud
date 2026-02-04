/*
  A tent guard. Mortricia 920927
  converted into a gardener 921106
  lifted some code from witch.c (Mortricia) 930228
  Borrowed the teacher code from M's acrobat.c 930714
  Janus

    Modified: 13 June 2003, by Bleys
        - Updated to use modern includes.
        - Now logging to the correct quest log file.
    2017-12-04 - Cotillion
    - Fixed item cloning
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/d/Terel/std/teacher";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <money.h>

#include "/d/Terel/include/quest_bits.h"

#define NUM             4
#define SPELL_DELAY     15
#define ALIGN           50
#define FINE_FEE        200
#define DIPLOMA_FEE     15

public void set_up_skills();

public void
create_monster()
{
  ::create_monster();
  
  set_name("joe");
  add_name("gardener");
  set_short("master gardener");
  set_long("A man of average height, brown hair and blocky " +
           "build. He is dressed in green overalls and has black " +
           "boots. On his head he has a worn straw hat. Bobbing " +
           "from his mouth is a piece of straw. In his right hand " +
           "he is carrying a mean looking pitchfork. " +
           "He can probably help you with anything involving this " +
           "garden, or answer any questions you have about this place " +
           "or its inhabitants.\n");
  set_race_name("human");
  set_adj(({"brown-haired", "green-clad"}));
  set_gender(0);
  set_alignment(100);
  set_stats(({95,75,90,50,50,95}));
  set_gender(0);
  
  set_skill(SS_WEP_CLUB, 90);
  set_skill(SS_2H_COMBAT, 90);
  set_skill(SS_BLIND_COMBAT, 90);
  set_skill(SS_AWARENESS, 90);
  set_skill(SS_LANGUAGE, 60);
  set_skill(SS_DEFENCE, 91);
  set_skill(SS_HERBALISM, 70);
  set_skill(SS_UNARM_COMBAT, 93);
  set_skill(SS_WEP_POLEARM, 99);
  set_skill(SS_SPELLCRAFT, 90);
  set_skill(SS_WEP_SWORD, 80);
  set_skill(SS_DEFENCE, 80);
  set_skill(SS_PARRY, 85);
  
  enable_intro();
  
  set_hp(9999);
  set_mana(9999);
  set_fatigue(9999);
  
  set_all_hitloc_unarmed(33);
  set_all_attack_unarmed(75, 25);
  
  config_default_trade();
  set_money_give_reduce( ({ 0, 2, 3, 3 }) );
  
  set_cact_time(5);
  
  set_aggressive(0);
  
  set_act_time(15);
  add_act(({"smile"}));
  
  add_prop(LIVE_I_QUICKNESS, 85);
  add_prop(LIVE_I_SEE_DARK, 3);
  add_prop(LIVE_I_SEE_INVIS, 2);
  add_prop(LIVE_O_SPELL_ATTACK, TO);
  
  set_chat_time(2);
  add_chat("Want to get a gardeners diploma? You only need to "+
           "pay a fee of 15 copper coins.");
  add_chat("Want to learn something about herbs? I could teach you.");
  add_chat("Anything you want to ask about?");
  
  create_skill_raise();
  set_up_skills();

  remove_prop(NPC_M_NO_ACCEPT_GIVE);

  add_prop(OBJ_M_HAS_MONEY, ({ 30, 5 }));
  equip(({ JANUS_DIR + "garden/pfork", JANUS_DIR + "armor/shat", JANUS_DIR + "armor/bboots",
              JANUS_DIR + "armor/overall" }));
}

public void
right_msg(object me)
{
  string name;

  if (!me || environment(me) != ETO) return;
  
  name = capitalize(me->query_name());
  command("glare " + name);
  if (me->test_bit("Terel", QUEST_JJ2_GROUP, QUEST_JJ2_BIT)) {
    me->catch_msg("Thank you for doing this, again...\n");
  } else {
    if (me->query_exp() <= QUEST_JJ2_EXP ) {
      me->add_exp(me->query_exp());
    } else {
      me->add_exp(QUEST_JJ2_EXP);
    }
    me->set_bit(QUEST_JJ2_GROUP, QUEST_JJ2_BIT);
    me->catch_msg(QCTNAME(TO) + " thanks you for giving him the bracelet.\n");
    tell_room(ETO, QCTNAME(TO) + " thanks " + QTNAME(me) +
              " for bringing back the bracelet.\n", me);
    me->catch_msg("You suddenly feel more experienced.\n");
    tell_room(ETO, QCTNAME(me) + " looks more experienced.\n", me);
    /*
    write_file(QUEST_LOG, name + " solved the bracelet quest (" +
                          ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Enchanted Garden bracelet quest (bracelet quest) (" +
        ctime(time()) + ")\n");
  }
}

public void
wrong_msg(object me)
{
  string name;

  if (!me || environment(me) != ETO) return;
  
  name = capitalize(me->query_name());
  command("sneer " + name);
  me->catch_msg("Trying to get credit for something you haven't done, "+
                "aren't we?\n");
  tell_room(ETO, QCTNAME(me) + " asks for a reward and " +
            QTNAME(TO) + " explains in a clear voice that he hates " +
            "freeloaders that try to take credit for something " +
            "someone else has done.\n", me);
}

public void
me_drop(object ob, object from)
{
    command("say Thanks, but I don't need this " + ob->short() +
            ".");
    command("drop " + ob->query_name());
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!ob || living(ob)) return;
    
    if (!from || !living(from)) return;
    
    if (!CAN_SEE(TO, ob)) return;
    
    if (ob->query_name() == "coin") return;

    if (ob != present("bracelet")) {
        set_alarm(3.0, -1.0, &me_drop(ob, from));
        return;
    }
    if (ob->query_prop("_bracelet_finder") == TP->query_name()) {
      ob->remove_object();
      set_alarm(2.0, -1.0, &right_msg(from));
    } else {
      set_alarm(2.0, -1.0, &wrong_msg(from));
      set_alarm(5.0, -1.0, &me_drop(ob, from));
    }
}

public void
bug_reward(object tp)
{
    int antal;
    string name;
    
    if (!tp || environment(tp) != ETO) return;
    
    seteuid(getuid());
    antal = tp->query_prop("_killed_bugs_");
    if (antal < 1) {
        command("say Ten times nothing is still nothing.");
        command("growl");
        return;
    }
    name = capitalize(tp->query_real_name());
    write_file("/d/Terel/janus/log/vermin.cash", name +
               " got " + 10*antal + " cc for killing vermin (" +
               ctime(time()) + ")\n");
    MONEY_MAKE_CC(10*antal)->move(tp);
    command("say Well done, here you are.");
    tp->catch_msg(QCTNAME(TO) + " gives you " + 10*antal +
                  " copper coins.\n");
    tell_room(QCTNAME(TO) + " gives " + QTNAME(tp) + " some coins.\n", tp);
    tp->remove_prop("_killed_bugs_");
}

public void
queen_reward(object tp)
{
    string name;
    int i;
    
    if (!tp || environment(tp) != ETO) return;

    seteuid(getuid());
    if (tp->query_prop("_killed_queen_")) {
       tp->remove_prop("_killed_queen_");
       tp->catch_msg(QCTNAME(TO) + " thanks you for killing the queen bug.\n");
       command("say I hope that this will stop the bugs for some time.");
       tell_room(ETO, QCTNAME(TO) + " thanks " + QTNAME(tp) +
                 " for killing the queen bug.\n", tp);
       name = capitalize(tp->query_name());
       if (tp->test_bit("Terel", QUEST_JJ3_GROUP, QUEST_JJ3_BIT)) {
           tell_object(tp, "Well done. But I only reward the slaying " +
                           "of the queen once, the goodness of your " +
                           "act will your reward. May the two-faced " +
                           "one be kind to you.\n");
        } else {
           if (tp->query_exp() <= QUEST_JJ3_EXP) {
               tp->add_exp(tp->query_exp());
           } else {
               tp->add_exp(QUEST_JJ3_EXP);
           }
           tp->set_bit(QUEST_JJ3_GROUP, QUEST_JJ3_BIT);
           tell_object(tp, "You suddenly feel more experienced.\n");
           tell_room(ETO, QCTNAME(tp) +
                     " looks more experienced.\n", tp);
          /*
           write_file(QUEST_LOG, name +
                       " solved the bugqueen quest (" +
                       ctime(time()) + ")\n");
          */
          write_file(QUEST_LOG, TP->query_name() + " solved " +
              "the Enchanted Garden bug queen quest (bugqueen " +
              "quest) (" + ctime(time()) + ")\n");
        }
     } else {
        tp->catch_msg(QCTNAME(TO) + " thunders: Trying to get credit for " +
                "something you haven't done, aren't we? Better try " +
                "killing the queen bug yourself next time.\n");
        tell_room(ETO, QCTNAME(tp) + " asks for a reward and " +
                QTNAME(TO) + " explains in a clear voice that he " +
                "hates freeloaders that try to take credit for " +
                "something someone else has done.\n", tp);
        command("cackle");
     }
}

public void
cat_reward(object tp)
{
    object katt = present("cat", ETO);
    string name, test, test2;
    int i;
 
    if (!tp || environment(tp) != ETO) return;
    
    seteuid(getuid(this_object()));
    
    if (!katt) {
        tp->catch_msg(QCTNAME(TO) + " growls: Well, don't you think you " +
                "should accomplish something " +
                "before you claim a reward? Like getting my cat back.\n");
        tell_room(ETO, QCTNAME(tp) + " asks for a reward and " +
                  QTNAME(TO) + " explains in a clear voice that to " +
                  "get a reward one has to do something first.\n", tp);
        command("grin");
        return;
    }
    test = tp->query_name();
    test2 = katt->query_prop("_cat_finder");
    if (test == test2) {
       command("thank " + tp->query_real_name());
       name = capitalize(tp->query_name());
       command("smile " + tp->query_real_name());
       if (tp->test_bit("Terel", QUEST_JJ1_GROUP, QUEST_JJ1_BIT)) {
           tell_object(tp, "You have done this once! " +
                           "Don't you remember?\n");
       } else {
           if (tp->query_exp() <= QUEST_JJ1_EXP ) {
               tp->add_exp(tp->query_exp());
           } else {
               tp->add_exp(QUEST_JJ1_EXP);
           }
           tp->set_bit(QUEST_JJ1_GROUP, QUEST_JJ1_BIT);
           tell_object(tp, "You suddenly feel more experienced.\n");
           tell_room(ETO, QCTNAME(tp) +
                          " has become more experienced.\n", tp);
          /*
           write_file(QUEST_LOG, name +
                  " solved the cat quest (" + ctime(time()) + ")\n");
          */
          write_file(QUEST_LOG, TP->query_name() + " solved " +
              "the Enchanted Garden lost cat quest (cat quest) (" +
              ctime(time()) + ")\n");
       }
       tell_room(ETO, QCTNAME(TO) + " pats the cat on its head and " +
          "the cat suddenly runs away again into the "+
          "fields of flowers, chasing a large butterfly.\n");
       katt->remove_object();
       return;
    }
    if (!test2) {
        tp->catch_msg(QCTNAME(TO) + " thunders: Trying to get credit " +
                "for something you " +
                "haven't done aren't we?\n");
        tell_room(ETO, QCTNAME(tp) + " asks for a reward and " +
            QTNAME(TO) + " explains in a clear voice that he hates " +
            "freeloaders that try to take credit for something " +
            "someone else has done.\n", tp);
        command("cackle");
        return;
    }
}

public int
do_ask(string what)
{
   object ob;
   string race, name, dum, s;

   if (!what ||
       !parse_command(lower_case(what), ETO, " %o %s ", ob, s)) {
           return 0;
   }
   if (ob != TO) return 0;
   if (sscanf(s, "about %s", dum) == 1) s = dum;
   if (sscanf(s, "for %s",   dum) == 1) s = dum;
   
   if (!CAN_SEE(TO, TP)) {
       command("confused");
       command("emote mutters something about ghosts.");
       return 1;
   }

   race = capitalize(TP->query_race_name());
   name = TP->query_real_name();

   say(QCTNAME(TP) + " asks " + QTNAME(TO) + " something.\n");

   if (s == "quest" || s == "quests" || s =="help" ||
       s == "task" || s == "tasks" || s == "jobs" ||
       s == "problem" || s == "problems" || s == "job") {
      command("say Well, I have lot of problems. I have a problem " +
              "with vermin that have infested parts of the garden, " +
              "and my apprentice is gone and she had an old " +
              "bracelet of mine. And to top it all my cat is missing.");
      command("emote looks worried.");
      command("sniff");
      return 1;
   }
   if (s == "herbalism" || s == "learn" || s == "teach" ||
       s == "improve" || s == "skills") {
      command("ponder");
      command("say I can help you improve or learn how to use herbs.");
      command("smile");
      return 1;
   }
   if (s == "bug" || s == "bugs") {
      command("ponder");
      tell_room(ETO,
           "With a hint of anger in his voice "+QTNAME(TO)+" says: " +
           "They have infested the grove west of here. The bugs seems " +
           "to be of a termite species. Since the bugs eat a lot of " +
           "plants and invades my beehives I would like to have them " +
           "all terminated. If you can kill the bug-queen I'll reward " +
           "you.\n");
      return 1;
   }
   if (s == "catnip" || s == "spices" || s == "garlic" ||
       s == "herb" || s == "herbs") {
      command("ponder");
      tell_room(ETO, QCTNAME(TO) + " smiles at you and says: " +
          "If you pay me I could teach you more about different " +
          "herbs and spices.\n");
      return 1;
   }
   if (s == "hive" || s == "bug hive") {
      command("ponder");
      tell_room(ETO,
          "With an angry voice " + QTNAME(TO) + " says: " +
          "The bug hive can be found west of here. " +
          "It is quite small but it can be easily found.\n");
      return 1;
   }
   if (s == "vermin" || s == "insects") {
      command("ponder");
      tell_room(ETO, QCTNAME(TO) + " smiles at you and says: " +
          "I have some problems with some insects that has been eating " +
          "my plants in the hothouse. If you kill them I'll pay you " +
          "10 copper for each killed insect. Just come back here and ask " +
          "me for payment.\n");
      return 1;
   }
   if (s == "magenta potion" || s == "turqoise fruit" || s == "fruit") {
      command("ponder");
      tell_room(ETO, QCTNAME(TO) + " smiles at you and says: " +
          "Well, I dont want to spoil the fun, but consuming the " +
          s + " will force you to see things from a new " +
          "perspective. A very small one if I may say so.\n");
      command("giggle");
      return 1;
   }
   if (s == "red jelly" || s == "jelly" || s == "queen jelly") {
      tell_room(ETO, QCTNAME(TO) + " smiles at you and says: " +
          "That is really strong stuff. Puts hair on your chest.\n");
      command("cackle");
      return 1;
   }
   if (s == "garden" || s == "this place" || s == "flowers" || s == "fruits" ||
       s == "monsters" || s == "plants" || s == "plant" || s == "warning") {
      tell_room(ETO, QCTNAME(TO) + " frowns and says: " +
             "I have some simple rules that i expect people to live " +
             "by when they visit this place.\n" +
             "-I don't want my plants damaged in any way. That means " +
             "even touching by people that haven't taken my quick course " +
             "in gardening. There is only a small fee to be paid.\n" +
             "-Any other inhabitants are free game, but be careful, some "+
             "of the creatures here are quite tough.\n");
      return 1;
   }
   if (s == "cat" || s == "black cat") {
      tell_room(ETO, QCTNAME(TO) + " peers at you and says: " +
             "My cat is gone again. If you could get it back to me " +
             "I'd be be very grateful. If you bring my cat here just " +
             "ask me for reward and I'll repay you.\n");
      return 1;
   }
   if (s == "bracelet") {
      tell_room(ETO, QCTNAME(TO) + " tells you in a loud voice that " +
             "it's an old family heirloom and that he lent it to " +
             "his apprentice.\n");
      command("swear");
      return 1;
   }
   if (s == "bug-queen" || s ==  "bug queen" || s == "bugqueen" ||
       s == "queen") {
      tell_room(ETO, "With a wicked grin on his lips " + QTNAME(TO) +
          " says: With the egglaying queen gone the bugs will all die. " +
          "If you kill the queen and return to me and asks for " +
          "a 'just reward', you'll then would be amply rewarded.\n");
      return 1;
   }
   if (s == "termite" || s == "termites") {
      tell_room(ETO, "After a short pause, " + QTNAME(TO) + " says: " +
          "Termites and bugs in general seems to rely a lot on their " +
          "sense of smell. I have a recipe for a drug that will pacify " +
          "bugs, haven't tested it properly though.\n");
      command("ponder the advances of science.");
      return 1;
   }
   if (s == "recipe" || s == "note" || s == "drug") {
      tell_room(ETO, QCTNAME(TO) + " says: The recipe was quite " +
          "complicated so I wrote it down on a note. Unfortunately, " +
          "I have lost it somewhere in my toolshed.\n");
      command("emote curses his tendency to forget things.");
      return 1;
   }
   if (s == "toolshed" || s == "tool shed" || s == "shed") {
      command("say It is just north of here");
      command("point north");
      return 1;
   }
   if (s == "apprentice" || s == "girl") {
      tell_room(ETO,
          "With a worried look in his face " + QTNAME(TO) + " says: " +
          "She was supposed to go to the bug hive and exterminate some " +
          "bugs. I haven't seen the girl since, though.\n");
      command("ponder the unreliability of todays youth.");
      return 1;
   }
   if (s == "iron ball" || s == "ball" || s == "ball and chain") {
      command("smile");
      command("say If you pay a small fine, I'll help you get " +
              "rid of that iron ball.");
      return 1;
   }
   if (s == "fine") {
      command("grin");
      command("say It's just a trifle, only a measly 200 cp's.");
      return 1;
   }
   if (s == "diploma") {
      command("ponder");
      command("say If you have a diploma you will know what you can/can't " +
              "do, eat, kill, pick, and take here in the garden.");
      return 1;
   }
   if (s == "reward") {
      set_alarm(3.0, -1.0, &cat_reward(TP));
      return 1;
   }
   if (s == "just reward" ) {
      set_alarm(4.0, -1.0, &queen_reward(TP));
      return 1;
   }
   if (s == "payment") {
      set_alarm(2.0, -1.0, &bug_reward(TP));
      return 1;
   }
   command("shrug");
   command("say Sorry, I don't know about that.");
   return 1;
}

public int
do_pay(string str)
{
  string  what, for_c, get_c;
  string  change;
  int     *result;
  int     price = FINE_FEE;
  int     price2 = DIPLOMA_FEE;
  object chain = present("_terel_egarden_punish_obj", TP);
  object note;
  
  if (!str) return 0;
  
  if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
    if (sscanf(str, "%s with %s", what, for_c) != 2)
      what = str;
  if (what == "fee") {
    set_money_give_out(what_coins(TO));
    result = pay(price2, TP, for_c, 0, TO, get_c);
    if (sizeof(result) == 1)
      return 0; /* Pay() handles notify_fail if we want to. */
    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    if (change) {
      write("You get, " + change + " as change.\n");
    }
    say(QCTNAME(TP) + " gives some money to " + QTNAME(TO) + ".\n");
    say("With a gesture the " + QTNAME(TO) + " presents " +
        QTNAME(TP) + " with a diploma.\n");
    note = clone_object(JANUS_DIR + "garden/diploma");
    TP->catch_msg("With a gesture " + QTNAME(TO) +
                  " gives you " + LANG_ADDART(note->short()) + ".\n");
    if (note->move(TP)) {
        TP->catch_msg("You drop the " + note->short() + ".\n");
        say(QCTNAME(TP) + " drops " + LANG_ADDART(note->short()) + ".\n");
        note->move(ETP);
    }
    return 1;
  }
  if (what == "fine" && chain) {
    set_money_give_out(what_coins(TO));
    result = pay(price, TP, for_c, 0, TO, get_c);
    if (sizeof(result) == 1)
      return 0; /* Pay() handles notify_fail if we want to. */
    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    if (change) {
      write("You get, " + change + " as change.\n");
    }
    say(QCTNAME(TP) + " gives some money to " + QTNAME(TO) + ".\n");
    TP->catch_msg("With a gesture " + QTNAME(TO) + " destroys your " +
                  chain->short() + ".\n");
    say("With a gesture " + QTNAME(TO) + " destroys the " + chain->short() +
        " that " + QTNAME(TP) + " had chained around the foot.\n");
    chain->remove_object();
    return 1;
  }
  if (what == "fine") {
    command("say You don't have to pay any fine.");
    return 1;
  }
  return 0;
}

public void
init_living()
{
    ::init_living();
    
    init_skill_raise();
    add_action(do_ask, "ask");
    add_action(do_pay, "pay");
}

public void
add_light(object ob, int inc)
{
    ob->add_prop(CONT_I_LIGHT, ob->query_prop(CONT_I_LIGHT) + inc);
    environment(ob)->update_light(1);
}

public void
spell_attack(object me, object victim)
{
  int i, i3;
  int me_mana = me->query_mana();
  int spell = random(4);
  object env = environment(me);
  object *e = me->query_my_enemies();
  
  seteuid(getuid());

  if (spell == 0 && me_mana > 9) {
      me->add_mana(-10);
      tell_room(env, QCTNAME(TO) + " creates a Cloud of Darkness.\n");
      me->add_prop(CONT_I_LIGHT, me->query_prop(CONT_I_LIGHT) - 2);
      env->update_light(1);
      set_alarm(25.0, -1.0, &add_light(me, 2));
  }
  
  if (spell == 1 && me_mana > 9) {
      me->add_mana(-10);
      command("say I'll help you stand still");
      for (i=0; i<sizeof(e); i++) {
          clone_object(JANUS_DIR + "garden/balls.c")->move(e[i]);
          e[i]->catch_msg(QCTNAME(TO) + " creates an iron ball out of " +
                          "thin air around your leg.\n");
          tell_room(env, QCTNAME(TO) + " creates an iron ball out of " +
                    "thin air around " + QTNAME(e[i]) + "'s leg.\n", e[i]);
      }
  }
  
  if (spell == 2 && me_mana > 24) {
      me->add_mana(-25);
      command("say Eat this!");
      for (i=0; i<sizeof(e); i++) {
          i3 = e[i]->query_stat(SS_WIS) + e[i]->query_stat(SS_DIS);
          if (random(i3) < 150) {
              e[i]->reduce_hit_point(random(200) + 100);
              e[i]->add_fatigue(-random(5)-25);
              e[i]->catch_msg("You feel an intense pain.\n");
          } else {
              e[i]->catch_msg("You feel all tickly inside.\n");
          }
      }
  }
  
  if (spell == 3 && me_mana > 24) {
      me->add_mana(-25);
      me->command("say Are you freezing?");
      me->command("say Let me help you.");
      tell_room(env, QCTNAME(me) + " makes glowing symbol in the air.\n");
      tell_room(env, "A great ball of fire explodes.\n");
      for (i=0; i<sizeof(e); i++) {
          if (random(e[i]->query_stat(SS_DEX)) < 75) {
              e[i]->reduce_hit_point(random(300) + 200);
              e[i]->catch_msg("You sizzle like fat in fire.\n");
          } else {
              e[i]->catch_msg("You manage to avoid being " +
                              "damaged by the fireball.\n");
          }
      }
      me->command("say Feeling warmer?");
      me->command("grin");
  }
  
  set_alarm(itof(1 + SPELL_DELAY), -1.0, &set_spell_prop(me));
}

public void
set_up_skills()
{
    string me, ot;

    me = "use herbs"; ot = me;
    sk_add_train(SS_HERBALISM,    ({me, ot}),     0, 0, 20 );
}

