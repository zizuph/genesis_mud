/*
 * refnas.c
 *
 * Used in nyreese/cas_c7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <comb_mag.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <options.h>

void
create_monster ()
{
  set_living_name("refnas");
  set_name("refnas");
  set_race_name("wizard");
  set_short("evil wizard");
  set_long("This is the evil wizard who rules the castle.\n");
  set_adj("evil");

  set_alignment(-750);

  default_config_npc(100);

  set_skill(SS_DEFENCE, 50);
  set_skill(SS_PARRY, 50);
  set_skill(SS_WEP_POLEARM, 100);
  set_skill(SS_AWARENESS, 80);
  set_exp_factor(110); // beefed up a wee bit
  NEVERKNOWN;

  add_prop(LIVE_O_SPELL_ATTACK, TO);
}

int
query_knight_prestige ()
{
  return 500;
}

void
equip_me ()
{
  clone_object(ROKEDIR + "arm/glowing-mail")->move(TO);
  clone_object(ROKEDIR + "arm/glowing-shield")->move(TO);
  clone_object(ROKEDIR + "arm/glowing-helmet")->move(TO);
  clone_object(ROKEDIR + "wep/refnasstaff")->move(TO);
  clone_object(ROKEDIR + "obj/wand")->move(TO);

  command("wear all");
  command("wield all");
}

void
add_sp (object ob)
{
  add_prop(LIVE_O_SPELL_ATTACK, ob);
}

void
spell_attack (object attacker, object target)
{
  int hurt;
  mixed *hitresult;
  string how, how2;

  if (attacker->query_mana() < 40) {
    set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
    return;
  }
  if (random(10) < 3) {
    set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
    return;
  }
  attacker->add_mana(-40);

  hurt = F_PENMOD(70, 100);
  hurt -= hurt * target->query_magic_res(MAGIC_I_RES_FIRE) / 100;

  hitresult = target->hit_me(hurt, 0, attacker, 0);
  target->catch_msg(QCTNAME(attacker) + " points his staff at you.\n");
  tell_room(ENV(TO), QCTNAME(attacker) + " points his staff at " +
            QTNAME(target) + ".\n", target);

  how = " fumbles his spell!";
  how2 = how;
  if (hitresult[0] > 75)  {
    how = " throws a large ball of green fire at you. It engulfs and burns you.";
    how2 = " throws a large ball of green fire at " + QTNAME(target) + ". "
      + QCTNAME(target) + " burns before your eyes.";
  }
  else if (hitresult[0] > 50) {
    how = " chants a spell weakening you.";
    how2 = " chants a spell, leaving " + QTNAME(target) + " weaker.";
    target->add_tmp_stat(SS_STR, ftoi(-hitresult[0] / 5), 5);
    target->heal_hp(ftoi(hitresult[3]/2.0));
  }
  else if (hitresult[0] > 25) {
    how = " curses you. You feel less confident.";
    how2 = " curses " + QTNAME(target) + ".";
    target->add_panic(hitresult[0]);
    target->heal_hp(ftoi(itof(hitresult[3])/2.0));
  }
  else if (hitresult[0] > 0) {
    how = " touches you, filling you with a cold, death-like feeling.";
    how2 = " touches " + QTNAME(target) + ", sending a shiver through " +
      query_possessive() + " body.";
  }
  target->catch_msg(QCTNAME(attacker) + how + "\n");
  tell_room(ENV(TO), "The wizard" + how2 + "\n", target);

  if (target->query_hp() <= 0)
    target->do_die(attacker);

  set_alarm(itof(1 + random(10)), 0.0, &add_sp(attacker));
}
