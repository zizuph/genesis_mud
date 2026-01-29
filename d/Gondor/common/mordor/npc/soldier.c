#pragma  strict_types

#include <stdproperties.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>
#include "../sys/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

inherit  ("/std/monster");
inherit  ("/d/Gondor/morgul/feeling");

private static string *weapons   = ({}),
                      *armours   = ({});
private static status initialized;
private static object victim;
private static int    attack_alarm;

public void
reset_soldier() {}

public nomask void
reset_monster() {
  if (!initialized) {
    object old_tp = TP;
    int x;
    set_this_player(TO);
    for (x = 0; x < sizeof(weapons); x++) {
      object weapon = clone_object(weapons[x]);
      weapon->move(TO, 1);
      weapon->wield_me();
    }
    for (x = 0; x < sizeof(armours); x++) {
      object armour = clone_object(armours[x]);
      armour->move(TO, 1);
      armour->wear_me();
    }
    set_this_player(old_tp);
    refresh_mobile();
    MONEY_MAKE(random(12), "copper")->move(TO, 1);
    MONEY_MAKE(random(6), "silver")->move(TO, 1);
    initialized = 1;
  }
  reset_soldier();
}

public void
create_soldier() {
  set_race_name("human");
}

public nomask void
create_monster() {
  int r = random(11);

  seteuid(getuid(TO));
  add_name("_mordor_monster");
  add_name("_mordor_soldier");

  set_skill(SS_AWARENESS,    55 + r);
  set_skill(SS_CLIMB,        25 + r);
  set_skill(SS_BLIND_COMBAT, 80 + r);
  set_skill(SS_WEP_SWORD,    30);
  set_skill(SS_WEP_POLEARM,  30);
  set_skill(SS_WEP_AXE,      30);
  set_skill(SS_WEP_KNIFE,    30);
  set_skill(SS_WEP_CLUB,     30);

  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(LIVE_I_SEE_DARK, 2);
  add_prop(MORGUL_I_SULAMBAR_RES, 1);

  set_whimpy(45);
  set_learn_pref(({ 1, 1, 1, 0, 0, 1 }));
  set_pick_up(75);
  set_exp_factor(50);

  enable_reset();
  create_soldier();
  reset_monster();
}

public nomask int
query_knight_prestige() {
  return (-query_alignment());
}

static nomask void
add_weapon(string path) {
  object weapon;
  if (stringp(path) && SAFE_LOAD(path) && (weapon = find_object(path)) &&
      (function_exists("create_object", weapon) == "/std/weapon"))
    weapons += ({ path });
  else
    throw ("Invalid weapon: " + path + "\n");
}

static nomask void
add_armour(string path) {
  object armour;
  if (stringp(path) && SAFE_LOAD(path) && (armour = find_object(path)) &&
      (function_exists("create_object", armour) == "/std/armour"))
    armours += ({ path });
  else
    throw ("Invalid armour: " + path + "\n");
}

private nomask void
start_follow(object who) {
  object *followers;
  if (!objectp(who) || !objectp(present(who, ENV(TO))) ||
      (who != query_attack()) || (who == victim))
    return;
  if (pointerp(followers = who->query_follower()) &&
      (member_array(TO, followers) < 0))
    who->add_follower(TO);
  else
    clone_object("/d/Gondor/common/lib/follow_shadow")->follow(who, TO);
  victim = who;
}

public varargs void
remove_victim(object who) {
  if (objectp(who) && (who != victim))
    return;
  victim = 0;
}

public void
attack_object(object who) {
  ::attack_object(who);
  start_follow(who);
}

public void
attacked_by(object who) {
  object room = ENV(TO), *arr;
  ::attacked_by(who);
  start_follow(who);
  while (objectp(room) && !room->query_prop(ROOM_I_IS))
    room = ENV(room);
  arr = filter(all_inventory(room), &->id("_mordor_monster"));
  arr->notify_ob_attacked_me(TO, who);
}

public nomask void
help_friend(object enemy, object friend) {
  if (objectp(enemy) && !objectp(query_attack()) &&
      present(enemy, ENV(TO)) && F_DARE_ATTACK(TO, enemy) &&
      CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, enemy) &&
      !enemy->id("_mordor_monster")) {
    command("shout You will die for this, stinking " +
            enemy->query_race_name());
    command("kill " + enemy->query_real_name());
  }
}

public nomask void
notify_ob_attacked_me(object friend, object enemy) {
  if (objectp(query_attack()))
    return;
  if (random(10))
    set_alarm(5.0, 0.0, &help_friend(enemy, TO));
}

public nomask void
disguise_msg(object who, object helm, object arm) {
  if (!present(who, ENV(TO)))
    return;
  who->catch_msg("The " + QTNAME(TO) + " peers suspiciously at you, " +
                 "but since you are wearing the " +
                 QSHORT(helm) + " and the " +
                 QSHORT(arm) + " bearing the insignia of the " +
                 "Red Eye, " + HE(TO) + " doesn't attack you.");
}

private nomask status
query_disguised(object who = TP) {
  object helm, arm;
  if (TP->query_attack()->id("_mordor_monster"))
    return (0);
  helm = who->query_armour(TS_HEAD);
  arm = who->query_armour(TS_TORSO);
  if (helm->id("_mordor_armour") &&
      arm->id("_mordor_armour") &&
      !random(5)) {// Don't swamp the player in messages!
    set_alarm(2.0, 0.0, &disguise_msg(who, helm, arm));
    return 1;
  }
}

private nomask void do_attack(object who);

public nomask void
test_can_see(object victim) {
  if (!present(victim, ENV(TO))) {
    remove_alarm(attack_alarm);
    attack_alarm = 0;
    return;
  }
  if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO,victim)) {
    remove_alarm(attack_alarm);
    attack_alarm = 0;
    do_attack(victim);
  }
}

public nomask void
order_attack_enemy(object commander, object victim) {
  if (objectp(query_attack()))
    return;
  do_attack(victim);
}

private nomask void
do_attack(object who) {
  object *arr;
  if (objectp(query_attack()) || !objectp(present(victim, ENV(TO))))
    return;
  if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim)) {
    if (!attack_alarm || !sizeof(get_alarm(attack_alarm)))
      attack_alarm = set_alarm(5.0, 10.0, &test_can_see(victim));
    command("shout Where are the enemies? I can't see them!");
    return;
  }
  command("kill " + victim->query_real_name());
  if (objectp(query_attack())) {
    arr = filter(all_inventory(ENV(TO)),
                 &->id("_mordor_monster")) - ({ TO });
    arr->order_attack_enemy(TO, victim);
  }
}

public nomask void
init_attack() {
  if (TP->query_attack()->id("_mordor_monster")) {
    do_attack(TP);
    return;
  }
  if (objectp(query_attack()) || TP->id("_mordor_monster") ||
      (query_feeling(TP) == -1) || !CAN_SEE_IN_ROOM(TO) ||
      !CAN_SEE(TO, TP) || query_disguised(TP))
    return;
  do_attack(TP);
}

private nomask void
remove_surplus(object ob) {
  if (!objectp(ob))
    return;
  if (function_exists("create_heap", ob) == "/std/coins") {
    command("smile greedily");
    return;
  }
  if (ob->query_prop(HEAP_I_IS))
    return;
  // We do not destroy items cloned into this room:
  if (member_array(ob, ENV(TO)->query_cloned_here()) > -1)
    command("drop " + OB_NAME(ob));
  else {
    tell_room(ENV(TO), QCTNAME(TO) + " breaks the " +
              QSHORT(ob) + " with a malicious grin " +
              "and tosses the remains.\n", TO);
    set_alarm(0.0, 0.0, &ob->remove_object());
  }
}

private nomask object
query_max_mordor() {
  int i, max_hp, hp, nmi = -1;
  object *arr = filter(all_inventory(ENV(TO)),
                &->id("_mordor_monster")) - ({ TO });
  for (i = 0; i < sizeof(arr); i++) {
    if ((hp = arr[i]->query_hp()) > max_hp) {
      max_hp = hp;
      nmi = i;
    }
  }
  if (nmi >= 0)
    return (arr[nmi]);
}

public nomask status
query_attack_me(object x) {
  return (x->query_attack() == TO);
}

private nomask void
move_attack(object enemy, object target) {
  enemy->stop_fight(target);
  enemy->attack_object(target);
}

public void
run_away() {
  int hp = query_hp(),
      mhp = query_max_hp();
  object max_ithil, *enemies; 
  if ((100 * hp / mhp) > (query_whimpy() / 2)) {
    if (objectp(max_ithil = query_max_mordor())) {
      enemies = filter(query_enemy(-1), query_attack_me);
      max_ithil->remove_prop(OBJ_M_NO_ATTACK);
      map(enemies, "move_attack", TO, max_ithil);
      tell_room(ENV(TO), QCTNAME(TO) + " cowardly hides behind " +
                QTNAME(max_ithil) + ".\n", ({ TO, max_ithil, }));
      enemies->catch_msg("You turn to attack " +
                         QTNAME(max_ithil) + ".\n");
      add_prop(OBJ_M_NO_ATTACK, "@@query_is_behind" + ":" +
               file_name(TO) + "|" + file_name(max_ithil) + "@@");
      return;
    }
  }
  ::run_away();
}

public nomask string
query_is_behind(string prot_file) {
  object prot = find_object(prot_file);
  if (!objectp(prot) || !living(prot) ||
      !present(prot, ENV(TO)) ||
      (TP->query_attack() != prot) || !CAN_SEE(TO, prot)) {
    set_alarm(0.0, 0.0, &remove_prop(OBJ_M_NO_ATTACK));
    return (0);
  }
  return (process_string("The coward is hiding behind the " +
                         prot->query_nonmet_name() + "!\n"));
}

private nomask void
check_shields() {
  object *shields;
  command("wear all");
  shields = filter(all_inventory(TO), &operator(==)("/std/armour") @
                   &function_exists("create_object", ));
  shields = filter(shields, &operator(==)(A_SHIELD) @ &->query_at());
  shields = filter(shields, not @ objectp @ &->query_worn());
  shields -= ({ 0 });
  if (!sizeof(shields))
    return;
  tell_room(ENV(TO), QCTNAME(TO) + " breaks the " +
            QSHORT(shields[0]) + " with a malicious grin.\n", TO);
  shields[0]->remove_broken();
  command("drop " + OB_NAME(shields[0]));
  if (sizeof(shields) > 1)
    set_alarm(5.0, 0.0, check_shields);
}

public void
check_weapons(object new) {
  int new_type = new->query_wt(),
      new_sk = query_skill(SS_WEP_FIRST + new_type),
      old_sk;
  object *old = query_weapon(-1);
  if (!sizeof(old)) {
    command("wield all");
    if (!objectp(new->query_wielded())) {
      command("remove shields");
      command("wield all");
      set_alarm(5.0, 0.0, check_shields);
    }
    if (!objectp(new->query_wielded())) {
      tell_room(ENV(TO), QCTNAME(TO) + " breaks the " +
                QSHORT(new) + " with a malicious grin.\n", TO);
      new->remove_broken();
      command("drop " + OB_NAME(new));
    }
    return;
  }
  if (member_array(new, old) >= 0) {
    /* already wielding the new weapon -- probably
     * as a result of a brawl "disarm" expiring
     */
    return;
  }
  old_sk = query_skill(SS_WEP_FIRST + old[0]->query_wt());
  if ((old_sk * old[0]->query_pen() * old[0]->query_hit()) >
      (new_sk * new->query_pen() * new->query_hit()))
    old[0] = new;
  else {
    command("unwield " + OB_NAME(old[0]));
    command("wield " + OB_NAME(new));
    // Did we succeed in wielding the weapon?
    if (!objectp(new->query_wielded())) {
      command("remove shields");
      command("wield " + OB_NAME(new));
      // Did we succeed in wielding the weapon?
      if (!objectp(new->query_wielded())) {
        command("wield " + OB_NAME(old[0]));
        old[0] = new;
      }
      set_alarm(5.0, 0.0, check_shields);
    }
  }
  tell_room(ENV(TO), QCTNAME(TO) + " breaks the " +
            QSHORT(old[0]) + " with a malicious grin.\n", TO);
  old[0]->remove_broken();
  command("drop " + OB_NAME(old[0]));
}

public void
check_armours(object new) {
  int new_type = new->query_at();
  object old, *old_shields;
  /*
   * If we can wear the new armour in addition to the already worn
   * armours, all if fine. 
   */
  command("wear all");
  if (objectp(new->query_worn()))
    return;
  /*
   * Is the new armour better than the old one we are wearing?
   */
  if (new_type != A_SHIELD)
    old = TO->query_armour(new_type);
  else {
    // shields are a pain:
    old_shields = filter(TO->query_armour(new_type),
                         &operator(==)(A_SHIELD) @ &->query_at());
    if (sizeof(old_shields))
      old = old_shields[0];
  }
  if (!objectp(old)) {
    // This might happen if we are wielding a two handed
    // weapon, discard the new armour:
    tell_room(ENV(TO), QCTNAME(TO) + " breaks the " + QSHORT(new) +
              " with a malicious grin.\n", TO);
    new->remove_broken();
    if (objectp(new))
      command("drop " + OB_NAME(new));
    return;
  }
  if (new->query_ac() <= old->query_ac())
    old = new;
  else {
    command("remove " + OB_NAME(old));
    command("wear " + OB_NAME(new));
    // Did we succeed in wielding the armour?
    if (!objectp(new->query_worn())) {
      command("wear " + OB_NAME(old));
      old = new;
    }
  }
  /*
   * Break what we cannot use any more:
   */
  tell_room(ENV(TO), QCTNAME(TO) + " breaks the " + QSHORT(old) +
            " with a malicious grin.\n", TO);
  old->remove_broken();
  command("drop " + OB_NAME(old));
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from) {
  ::enter_inv(ob, from);
  if (!objectp(ob) || !objectp(from))
    return;
  if (ob->id("corpse")) {
    command("get all from corpse");
    set_alarm(2.0, 0.0, &command("drop corpse"));
    return;
  }
  if (ob->query_prop(OBJ_I_BROKEN)) {
    // Clean up and remove broken objects that we pick up!
    set_alarm(0.0, 0.0, &ob->remove_object());
    set_alarm(5.0, 0.0, &command("drop broken things"));
    return;
  }
  if (function_exists("create_object", ob) == "/std/weapon") {
    set_alarm(1.0, 0.0, &check_weapons(ob));
    return;
  }
  if (function_exists("create_object", ob) == "/std/armour") {
    set_alarm(1.0, 0.0, &check_armours(ob));
    return;
  }
  if ((query_encumberance_weight() > 25) ||
      (query_encumberance_volume() > 25))
    set_alarm(1.0, 0.0, &remove_surplus(ob));
}

public nomask status
notify_you_killed_me(object victim) {
  set_alarm(2.0, 0.0, &command("get all from corpse"));
  if (victim->query_npc())
    return (1);
  seteuid(getuid(TO));
  write_file(LOG + "KILL", victim->query_real_name() +
             "(" + victim->query_average_stat() + ") was " +
             "killed by " + LANG_ADDART(short()) + " on " +
             ctime(time()) + "(" + file_name(ENV(TO)) + ").\n");
  return (1);
}
