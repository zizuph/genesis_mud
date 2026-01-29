/*
 * ogion.c
 *
 * Used in wild/ihut.c
 *
 * This was once a part of the domain Roke.
 *
 * Modification log:
 *   - Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *   - Additional quest from Sparkle added by Gorboth, May 2017
 *   (see notes below)
 *
 * Notes:
 *   This is absolutely one of the hardest quests in the game. It is
 * not something that can be solved with a walkthrough, but requires
 * the player to fully solve the puzzle through meticulous mapping
 * and note-taking which takes, on average, 90-120 minutes of non-stop
 * effort. Once you do it, it is exceptionally satisfying in all but
 * the dreadfully measley qxp. Because we cannot fairly up the qxp and
 * only reward players who do it in this modern era, I am going to add
 * an additional quest from the Librarian in Sparkle who has learned
 * of a danger to the donut - a dreadful earthquake that is soon to
 * strike. The history of Ogion from the Earthsea books (the original
 * origin of this npc) is that he was able to stave off a massive
 * earthquake by giving up his own soul to cast the spell that would
 * prevent it. I will allow the player to petition him for a piece of
 * his soul so that he might save the donut. The player may take the
 * piece back to Nikolon in the Sparkle library for a much MUCH larger
 * quest reward than was given here in the original solution of the
 * quest. There is to be no additional code added to this npc itself,
 * but rather the quest item from Sparkle will check for the file name
 * of this npc for a solution that can work. (Gorboth)
 *
 * - Added true value quest via restoring a silly true name routine,
 * Tapakah, 7/2021.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <math.h>

int has_introduced;

string
query_true_name (string str)
{
  string *letters = explode(str, "");
  int name_length = sizeof(letters);
  string true_name = "";
  int start = NAME_TO_RANDOM(lower_case(TP->query_real_name()),
                             4181975, name_length);
  if (!start)
    start = name_length - 1;
  
  int l, p;
  for (l = 0; l < name_length; l++) {
    p = start + l;
    if (p >= name_length)
      p -= name_length;
    true_name += letters[p];
  }
  return capitalize(true_name);
}

int
query_knight_prestige ()
{
  return -5;
}

void
equip_me ()
{
  clone_object(ROKEDIR + "arm/cloak")->move(TO);

  command("wear all");
}

string
otherask ()
{
  set_alarm(1.0, 0.0, &command("peer " + OB_NAME(TP)));
  return "";
}

string
ask (string str)
{

  string name;

  if (!QDONE(ROKEGROUP, OGIONMAZE)) {
    command("say Who are you to ask a thing like that?");
    return "";
  }
    
  name = query_true_name(lower_case(TP->query_real_name()));

  TP->catch_msg(QCTNAME(TO) + " whispers to you: Your true name is " +
                name + ".\n");
  tell_room(ENV(TO), QCTNAME(TO) + " whispers something to " + QTNAME(TP) +
            ".\n", TP);

  if (!QDONE(ROKEGROUP, OGIONTRUENAME)) {
    TP->catch_msg("You feel significantly more experienced.\n");
    QSET(ROKEGROUP, OGIONTRUENAME);
    QLOG("Ogion true name quest", OGIONTRUENAMEXP);
    TP->add_exp_quest(OGIONTRUENAMEXP);
  }
  return "";
}

void remove_int()
{
  has_introduced = 0;
}

void
introduce_me(string name)
{
  object pl;

  pl = find_player(name);
  if (!objectp(pl) || environment(pl) != environment())
    return;

  set_this_player(pl);
    
  if (!QDONE(ROKEGROUP, OGIONMAZE)) {
    command("introduce myself");
    command("say Welcome to my home " + capitalize(name) + ".");
    TP->catch_msg("You feel more experienced.\n");
    QSET(ROKEGROUP, OGIONMAZE);
    QLOG("Ogion quest", OGIONMAZEXP);
    TP->add_exp_quest(OGIONMAZEXP);
    return;
  }
  
  if (!has_introduced) {
    command("introduce myself");
    command("say Nice to see you again " + capitalize(name) + ".");
    has_introduced = 1;
    set_alarm(30.0, 0.0, remove_int);
  }
}

void
add_introduced (string name)
{
  set_alarm(6.0, 0.0, &introduce_me(name));
}

void
add_sp (object ob)
{
  add_prop(LIVE_O_SPELL_ATTACK, ob);
  return;
}

void
create_monster ()
{
  set_name("noigo");
  set_living_name("noigo");
  set_title("the perfect");
  set_race_name("human");
  set_long("Though he looks quite weak you can feel a strong aura of " +
           "magic surrounding him. He seems to know true names of people " +
           "and things.\n");
  set_adj("perfect");
  set_appearance_offset(-20);
  set_height_desc("short");
  set_width_desc("lean");

  set_default_answer(VBFC_ME("otherask"));
  add_ask(({"name", "about name", "real name", "about real name",
            "for real name",
            "for name", "true name", "for true name",
            "what is my true name"}), ask);
  set_alignment(0); // perfection is neutrality, not sanctity

  set_stats(({50, 50, 50, 100, 100, 100}));

  set_skill(SS_DEFENCE, 50);
  set_skill(SS_PARRY, 50);
  set_skill(SS_FORM_CONJURATION, 100);
  set_skill(SS_ELEMENT_FIRE, 100);

  add_prop(LIVE_O_SPELL_ATTACK, TO);
}

void
spell_attack (object attacker, object target)
{
  int hurt;
  mixed *hitresult;
  string how;

  if (attacker->query_mana() < 40) {
    set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
    return;
  }
  
  attacker->add_mana(-40);

  hurt = target->query_max_hp() * 7 / 10;

  target->reduce_hit_point(hurt);

  tell_room(ENV(attacker), QCTNAME(attacker) + " stares at " +
            QTNAME(target) +
            " and does a magical gesture.\n", target);
  target->catch_msg(QCTNAME(attacker) +
                    " stares at you and does a magical gesture.\n");

  tell_room(ENV(attacker),
            "Suddenly a bright light strucks " + QTNAME(target) +
            " and throws " + target->query_objective() + " out.\n",
            target);
  target->catch_msg("A bright light burns you badly and throws you out.\n\n");

  attacker->stop_fight(target);
  target->stop_fight(attacker);

  target->move(WILDDIR + "ohut");
  target->add_prop("_enemy_of_ogion", 1);
  target->command("look");

  target->do_die(attacker);

  set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
}
