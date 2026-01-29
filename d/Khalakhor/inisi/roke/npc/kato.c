/*
 * kato.c
 *
 * Used in wild/c1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Tidied up a bit by Tapakah, 07/2021
 */

/* The black monk Kato. He might give an evil
 * player a small task. Made by: Joshua 941225
 * with a good deal of help from Glindor among others 
 *
 * Updated: 950304 Jakob
 *
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

#include "defs.h"

inherit "/std/monster";

#define KATO_I_GAVE_PAINT 1

int roseq, fatq, grassq;
string *paint_name;
int has_introduced;

void
assign_paint_3 ()
{
  command("say hee hee doesn't that sound fun?");
  clone_object(ROKEDIR + "obj/can")->move(TO);
  command("give can to " + TP->query_real_name());
  TP->add_prop(KATO_I_GAVE_PAINT, 1);
}

void
assign_paint_2 ()
{
  command("say I know there's that disgusting cute dragon. " +
          "I want it to be painted black!");
  command("emote laughs demonically");
  set_alarm(2.0, 0.0, assign_paint_3);
}

string
assign_paint_1 ()
{
  if (! QDONE(ROKEGROUP, POTIONQUEST)) {
    command("say I need you to prove your worthiness first.");
    return "";
  }
  if (TP->query_prop(KATO_I_GAVE_PAINT)) {
    command("say Bah, I have already given you the paint!");
    return "";
  }

  if (TP->query_alignment() < 0) {
    command("say Yes hee hee we have to make some fun of them " +
            "...listen carefully now...");
    set_alarm(2.0, 0.0, assign_paint_2);
    return "";
  }
}

void
reward_potion_5 ()
{
  set_this_player(TP);
  if (!QDONE(ROKEGROUP, POTIONQUEST)) {
    TP->catch_msg("You feel more experienced!\n");
    TP->add_exp_quest(POTIONQUESTXP);
    QSET(ROKEGROUP, POTIONQUEST);
    QLOG("Kato quest", POTIONQUESTXP);
  }
}

void
reward_potion_4 ()
{
  set_this_player(TP);
  command("grin " + OB_NAME(TP));
  command("say Fool! Here is your reward!");
  say(QCTNAME(TO) + " gives 1 copper coin to " + QTNAME(TP) + "\n");
  TP->catch_msg(QCTNAME(TO) + " gives 1 copper coin to you.\n");
  MONEY_MAKE_CC(1)->move(TP);

  set_alarm(2.0, 0.0, reward_potion_5);
}

void
reward_potion_3 ()
{
  command("say he he The power is mine!");
  set_alarm(2.0, 0.0, reward_potion_4);
}

void
reward_potion_2 ()
{
  set_this_player(TP);
  tell_room(environment(), QCTNAME(TO) + " closes his left palm.\n");
  command("shiver");
  tell_room(environment(), QCTNAME(TO) + " open his hand again, and " +
            "to your surprise you discern a jewel in his hand!\n");
  set_alarm(2.0, 0.0, reward_potion_3);
}

void
reward_potion_1 ()
{
  TP->catch_msg(QCTNAME(TO) + " says: Well done " + QTNAME(TP) + ", well " +
                "done..\n");
  tell_room(environment(), QCTNAME(TO) + " puts the rose, " +
            "grass and the greasy piece of fat in his " +
            "left palm. He mumbles an incantation...\n");
  set_alarm(2.0, 0.0, reward_potion_2);
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);
  if (!from)
    return;

  if (from->query_alignment() > -1) {
    command("grin");
    command("say Sorry I dont trust you enough to " +
            "accept things from you.");
    set_alarm(2.0, 0.0, &command("drop " + OB_NAME(ob)));
    return;
  }
  set_this_player(from);
  if (QDONE(ROKEGROUP, POTIONQUEST)) {
    command("ponder");
    command("say we've been through this before, haven't we?");
    set_alarm(2.0, 0.0, &command("drop " + OB_NAME(ob)));
    return;
  }
  
  if (ob->id("grass")) {
    grassq = 1;
    command("say Hee hee my favourite grass.");
    command("wink");
    ob->remove_object();
  }

  if (ob->id("fat")) {
    fatq = 1;
    command("say Poor child.");
    command("grin sad");
    ob->remove_object();
  }

  if (ob->id("rose")) {
    roseq = 1;
    command("say A thing of beauty is a joy forever!");
    command("laugh evilly");
    ob->remove_object();
  }

  if (roseq == 1 && fatq == 1 && grassq == 1) {
    roseq = fatq = grassq = 0;
    set_alarm(2.0, 0.0, reward_potion_1);
  }
}

void
assign_potion_2 ()
{
  say(QCTNAME(TO) + " whispers something to " + QTNAME(TP) + "\n");
  TP->catch_msg(QCTNAME(TO) + " says: Do this, and I will reward " +
                "you handsomely! \n");
  return;
}

void
assign_potion_1 ()
{
  
  say(QCTNAME(TO) + " whispers something to " + QTNAME(TP) + "\n");
  TP->catch_msg(QCTNAME(TO) + " says: Bring me a rose, some " +
                "hallucinating grass and a piece of fat from a child not " +
                "yet being baptised.\n");
  set_alarm(2.0, 0.0, assign_potion_2);
  return;
}

string
tasks ()
{
  if (TP->query_alignment() > -1) {
    command("puke");
    command("say I don't want any help from goodie goodies as you. ");
    command("finger");
    return "";
  }

  if (QDONE(ROKEGROUP, PAINTQUEST) && QDONE(ROKEGROUP, POTIONQUEST)) {
    command("say I have no more use for you, begone.");
    return "";
  }
  
  say(QCTNAME(TO) + " whispers something to " + QTNAME(TP) + "\n");
  TP->catch_msg(QCTNAME(TO) + " says: Hmm, you look like the right one " +
                "...listen carefully now... \n");
  if (! QDONE(ROKEGROUP, POTIONQUEST))
    set_alarm(2.0, 0.0, assign_potion_1);
  else if (! QDONE(ROKEGROUP, PAINTQUEST))
    set_alarm(2.0, 0.0, assign_paint_1);
  return "";
}

void
equip_me ()
{
  object wep;
  clone_object(ROKEDIR + "arm/cloak.c")->move(this_object());
  wep = clone_object(ROKEDIR + "wep/weapon2.c");
  wep->set_up(1);
  wep->move(this_object());
  wep = clone_object(ROKEDIR + "wep/weapon2.c");
  wep->set_up(1);
  wep->move(this_object());
  command("wear all");
  command("wield all");
}

void
remove_int ()
{
  has_introduced = 0;
}

void
add_introduced (string person)
{
  if (!has_introduced) {
    set_alarm(1.0, 0.0, &command("introduce myself"));
    has_introduced = 1;
    set_alarm(15.0, 0.0, remove_int);
  }
}

string
otherask ()
{
  set_alarm(1.0, 0.0, &command("peer " + OB_NAME(TP)));
  return "";
}

void
create_monster ()
{
  roseq = fatq = grassq = 0;
  paint_name = ({});
  set_name("kato");
  set_title("lesser servant of the Presence");
  set_race_name("human");
  set_adj(({"evil", "smirking", "sadistical"}));
  set_long("This black-clad humanoid only slightly resemble " +
           "a human - his limbs are twisted and grotesque, " +
           "and you can only just make out the contours of his face, " +
           "hidden beneath his dark hood. He is smirking sadistically " +
           "at you, his evil intentions readily apparent.\n");
  set_gender(0);
  set_skill(SS_UNARM_COMBAT, 40);
  set_skill(SS_WEP_KNIFE, 90);
  set_skill(SS_2H_COMBAT, 75);
  set_alignment(-600);

  remove_prop(NPC_M_NO_ACCEPT_GIVE);

  /* str dex con int wis dis */
  set_stats(({110, 110, 110, 70, 70, 75}));

  set_chat_time(5 + random(7));  /* the time between speaking */
  add_chat("hee hee hee");
  add_chat("I am a genius, only a fool would deny that!");
  add_chat("Hmm, I need a volunteer...");
  add_chat("I may have a task for you.");
  add_chat("Hurumpf, I want to teach them a lesson. " +
           "I dont like merry people. ");
  add_chat("My master will undo the creation, by reverting the " +
           "seven sacraments! ");

  set_cchat_time(3 + random(5));  /* as above, obs random! */

  add_cchat("Fool! Can't you see that even if you kill me there " +
            " will be another one to come.");
  add_cchat("You might be able to kill me, but you " +
            "will never be able to annhilate evilness as such.");

  set_act_time(5 + random(15));
  add_act("grin");
  add_act("laugh");
  add_act("smirk");
  add_act("growl");
  add_act("hmm");
  
  add_ask(({"task", "quest", "volunteer", "help", "job", "worthiness"}), tasks);
  add_ask(({"sacrament", "sacraments"}), QCTNAME(TO) + " says: The"
          + " baptism is the first sacrament. \n");
  add_ask("baptism", QCTNAME(TO) + " says: Once you are baptised you"
          + " are protected... \n");
  add_ask(({"them", "dragon", "black", "lesson"}),
          assign_paint_1);
  set_default_answer(otherask);
  seteuid(getuid());
}

int
query_knight_prestige ()
{
  return 200;
}
