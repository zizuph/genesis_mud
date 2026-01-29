/* curan.c created by Shiva@Genesis.
 *
 * A major npc created for Telberin, he is both the prince of
 * Emerald and a very powerful paladin, perhaps the mortal
 * most favored by Telan-Ri, the god of light.
 */

#include "/d/Emerald/defs.h"

inherit EMERALD_MONSTER;
inherit "/d/Emerald/lib/intro";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include "../default.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>
#include <options.h>

#define DEBUG_WHO find_player("shiva")
#include "/d/Emerald/sys/debug.h"
#define DEBUG_ON

#define ENEMIES_PRESENT (query_enemy(-1) & all_inventory(environment()))

#define GUARDIAN TELBERIN_DIR + "npc/guardian_spirit"

static int invulnerable = 0;
static int poison_alarm;
static object *last_enemies = ({ });

int heal(object enemy);
int shout(object enemy);
int holy_light(object enemy);
int glance(object enemy);
int summon(object enemy);
int invulnerability(object enemy);

static object *guardians = ({ });

void souls_and_shadows();

void create_emerald_monster()
{
  DEBUG("Here\n");

  set_living_name("curan");
  set_name(({ "curan", "prince", "paladin", "prince_curan" }));
  set_race_name("elf");
  set_adj(({ "tall", "muscular" }));  

  set_long("A truly imposing figure, he is tremendously well-built " +
      "and extremely tall,\neven for an elf.  Regardless of his " +
      "colossal size, it would be impossible\nto mistake his " +
      "impeccable grooming and fine elven features as anything\n" +
      "other than evidence of strong and ancient elven bloodlines.\n");

  set_appearance_offset(-45); // good looking :)

  set_title("Prince of Emerald, High Champion of Telan-Ri");

  set_alignment(1000);
  set_stats(({ 300, 250, 280, 150, 200, 300 }));

  set_all_hitloc_unarmed(40); // 40 pts of armour for all hitlocs
  set_hitloc_unarmed(A_BODY, 70, 45, "body"); // 70 pts for body

  set_give_aid(1); // curan helps other telberin npcs when they are attacked

  set_alarm(0.0, 0.0, souls_and_shadows);

  set_skill(SS_AWARENESS, 100);
  set_skill(SS_2H_COMBAT, 100);
  set_skill(SS_WEP_SWORD, 100);
  set_skill(SS_WEP_KNIFE, 90);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_PARRY, 100);
  set_skill(SS_BLIND_COMBAT, 70);

  add_prop(LIVE_I_QUICKNESS, 100); // double attack rate
  add_prop(OBJ_I_RES_DEATH, 90);
  add_prop(OBJ_I_RES_MAGIC, 50);
  add_prop(LIVE_I_NO_CORPSE, 1);   // doesn't leave a corpse behind
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NON_REMEMBER, 1);
  add_prop(CONT_I_HEIGHT, 250);
  add_prop(CONT_I_WEIGHT, 62500);

  setuid();
  seteuid(getuid());

  log_my_deaths(TELBERIN_DIR + "log/curan_deaths.log");
  log_my_kills(TELBERIN_DIR + "log/curan_kills.log");

  MONEY_ADD(this_object(), 3000 + random(1000));

  add_act("@@do_something@@");
  add_cact("@@do_something_in_combat@@");
  set_act_time(8);
  set_cact_time(10);

#ifndef NO_WANDER
  set_monster_home(TELBERIN_DIR + "telberin_clone_handler");
  set_restrain_path(({ TELBERIN_DIR })); 
  set_random_move(7); 
#endif

  add_equipment(({ WEP_DIR + "laensword", ARM_DIR + "visored_helm",
         ARM_DIR + "w_mithril_plate", ARM_DIR + "w_mithril_bracers",
         ARM_DIR + "w_mithril_greaves", ARM_DIR + "emerald_ring", 
         "/d/Emerald/common/guild/newkot/obj/leather_belt",
         "/d/Emerald/common/guild/newkot/obj/kot_dagger"}));

  set_special_attack_percent(20);

  DEBUG("Here\n");
}

void souls_and_shadows()
{
  object sh;

  DEBUG("Her1\n");
  add_cmdsoul("/d/Emerald/common/guild/newkot/warrior_soul");
  update_hooks();

  if (sh = clone_object("/d/Emerald/common/guild/newkot/kot_shadow"))
  {
    DEBUG(sh->shadow_me(this_object(), "", "", ""));
  }
}

int query_knight_prestige() { return -10; }

int query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

// perform some random actions when not in combat
string do_something()
{
  object *who = FILTER_LIVE(all_inventory(environment()));
  object *bad = ({ });
  string target;
  int i = 0;
  
  while (i < sizeof(who))
  {
    if (IS_WIZ(who[i]))
    {
      who = exclude_array(who, i, i);
      continue;
    }
 
    if ((who[i]->query_alignment() < -100) ||
        who[i]->query_prop(LIVE_I_UNDEAD))
    {
      bad += ({ who[i] });
    }

    i++;
  }

  if (!sizeof(who))
  {
    return "";
  }
  if (sizeof(bad))
  {
    target = bad[random(sizeof(bad))]->query_real_name();
    return ({
              "peer " + target,
              "ktdisgust " + target,
           })[random(2)];
  }

  target = who[random(sizeof(who))]->query_real_name();
  
  return ({
            "smile " + target,
            "pat " + target,
            "sigh contentedly",  
         })[random(3)];
}

// perform some random actions when in combat
string do_something_in_combat()
{
  return ({
            "say You dare challenge the power of Telan-Ri?!?\n",
            "say Flee now, and you might be spared.\n",
            "say You were foolish to have forced my hand.\n",
         })[random(3)];
}

void init_living()
{
  ::init_living();

  // auto attack undead mortals w/ stat average > 50
  if (!IS_WIZ(this_player()) && 
      this_player()->query_prop(LIVE_I_UNDEAD) &&
      (member_array(this_player(), query_enemy(-1)) < 0) &&
      CAN_SEE(this_object(), this_player()) &&
      CAN_SEE_IN_ROOM(this_object()))
  {
    if (this_player()->query_average() > 50)
    {
      set_alarm(3.0, 0.0, &command("kill " + 
          this_player()->query_real_name()));
    }

    set_alarm(2.0, 0.0, &command("shout I shall smite out thine " +
        "abominous existence, fiend!\n"));
  }
}

// reconfigure our special attacks in accordance with our enemies
void update_specials(object *enemies)
{
  object *undead;

  remove_all_special_attacks();

  if (!sizeof(enemies))
  {
    // hmmm...somehow we got here w/o any enemies
    DEBUG("Specials 1");
    add_special_attack(heal, 45, "heal");
    add_special_attack(shout, 15, "shout");
    add_special_attack(holy_light, 15, "holy light");
    add_special_attack(glance, 5, "glance");
    add_special_attack(summon, 15, "summon");
    add_special_attack(invulnerability, 5, "invulnerability");
    return;
  }

  undead = filter(enemies, &operator(>)(, 0) @
      &->query_prop(LIVE_I_UNDEAD));

  if (!sizeof(undead))
  {
    DEBUG("specials 2");
    // no undead enemies, so don't use the anti-undead attacks
    add_special_attack(heal, 45, "heal");
    add_special_attack(shout, 20, "shout");
    add_special_attack(glance, 10, "glance");
    add_special_attack(summon, 15, "summon");
    add_special_attack(invulnerability, 10, "invulnerabilty");
    return;
  }

  if (sizeof(undead) == 1)
  {
    DEBUG("Specials 3");
    // one undead...use some anti-undead stuff
    add_special_attack(heal, 40, "heal");
    add_special_attack(shout, 10, "shout");
    add_special_attack(glance, 10, "glance");
    add_special_attack(holy_light, 20, "holy light");
    add_special_attack(summon, 10, "summon");
    add_special_attack(invulnerability, 10, "invulnerability");
    return;
  }
  
  DEBUG("Specials 4");
  // several undead...let's beat the crap out of them!
  add_special_attack(heal, 40, "heal");
  add_special_attack(glance, 10, "glance");
  add_special_attack(holy_light, 30, "holy light");
  add_special_attack(summon, 10, "summon");
  add_special_attack(invulnerability, 10, "invulnerability");
}

void reduce_light(int i)
{
  add_prop(CONT_I_LIGHT, query_prop(CONT_I_LIGHT) - i);
}

/* this is called from the combat object each combat round and is
 * where we start execution of any special attacks we wish to
 * perform this round.
 * returns 0 if we should execute regular attacks this round (no special)
 * returns 1 if we should not execute regular attacks this round (special)
 */
int special_attack(object enemy)
{
  object *enemies = ENEMIES_PRESENT;

  DEBUG(sizeof(enemies));

  /* update our special attacks if we have new enemies or old
   * enemies have left.
   */
  if ((sizeof(enemies) != sizeof(last_enemies)) ||
      (sizeof(enemies & last_enemies) != sizeof(last_enemies)))
  {
    last_enemies = enemies;
    update_specials(enemies);
  }

  /* First we check to see if the room is bright enough to see in...
   * If not, take care of it, and skip regular attacks.
   */
  if (!CAN_SEE_IN_ROOM(this_object()))
  {
    tell_room(environment(), QCTNAME(this_object()) + " chants in " +
        "an unknown tongue, and bright light fills the area.\n",
        this_object());
    add_prop(CONT_I_LIGHT, query_prop(CONT_I_LIGHT) + 20);
    set_alarm(60.0, 0.0, &reduce_light(20));
    return 1;
  }

  return ::special_attack(enemy);
}

/* Special attack: Holy Light
 * Effects:        1) 20 additional levels of light for 2 seconds
 *                 2) undead enemies receive a hit_me of MAGIC_DT 
 *                    with a pen of random(200) + 100
 */
int holy_light(object enemy)
{
  object *enemies = ENEMIES_PRESENT;
  int i, res;

  if (environment()->query_prop(ROOM_M_NO_MAGIC))
  {
    return 0;
  }

  tell_room(environment(), QCTNAME(this_object()) + " mumbles a prayer " +
      "and the room is illuminated by bright light.\n", this_object());
 
  add_prop(CONT_I_LIGHT, query_prop(CONT_I_LIGHT) + 20);

  for (i = sizeof(enemies); i--;)
  {
    if (!enemies[i]->query_prop(LIVE_I_UNDEAD))
    {
      continue;
    }

    res = enemies[i]->query_magic_res(MAGIC_I_RES_LIFE);
    enemies[i]->hit_me((random(200) + 100) * (100 - res) / 100, MAGIC_DT, 
        this_object(), -1);
    enemies[i]->catch_msg("\nYou are burned by the light!\n\n");
    enemies[i]->do_die(this_object());
  }

  set_alarm(2.0, 0.0, &reduce_light(20));
  return 1;
}

/* Special Attack: Heal
 * Effects:        1) Heals 120 + random(200) hps
 *                 2) Heals 20 + random(50) fatigue
 *                 3) Reduces panic by 20 + random(20)
 */
int heal(object enemy)
{
  if (environment()->query_prop(ROOM_M_NO_MAGIC))
  {
    return 0;
  }

  tell_room(environment(), QCTNAME(this_object()) + " mumbles a prayer " +
      "and immediately seems refreshed!\n");

  heal_hp(120 + random(200));
  add_fatigue(20 + random(50));
  add_panic(-20 - random(20));
  return 1;
}

/* Special attack: Holy Shout
 * Effects:        1) adds random(20) panic to evil enemies and
 *                    an additional random(20) to undead enemies
 */
int shout(object enemy)
{
  object *enemies, *special;

  if (environment()->query_prop(ROOM_M_NO_MAGIC))
  {
    return 0;
  }

  enemies = ENEMIES_PRESENT;
  special = filter(enemies, &operator(<)(, -100) @ &->query_alignment());
  special += filter(enemies, &operator(>)(,0) @ &->query_prop(LIVE_I_UNDEAD));

  tell_room(environment(), QCTNAME(this_object()) + " shouts in " +
      "some unknown tongue.\n", this_object());
 
  enemies->catch_msg("Though you can't understand his words, " +
      "they affect your profoundly, striking fear into your heart.\n");
  enemies->add_panic(random(20));
  special->add_panic(random(20));
  return 1;
}

/* Special Attack: Holding Glance
 * Effects:        Temporarily paralyzes target, reducing combat
 *                 abilities to almost nothing.
 */
int glance(object enemy)
{
  object *enemies = ENEMIES_PRESENT;
  object who, hold;

  if (environment()->query_prop(ROOM_M_NO_MAGIC) || !sizeof(enemies))
  {
    return 0;
  }

  who = enemies[random(sizeof(enemies))];
  if (hold = clone_object(OBJ_DIR + "hold"))
  {
    hold->move(who, 1);
    who->catch_msg(query_The_name(who) + " mumbles a prayer and shoots " +
        "a quick glance at you; immediately, you feel your mind and " +
        "body freeze.\n");
    tell_room(environment(), QCTNAME(this_object()) + " mumbles a prayer " +
        "and shoots a quick glance at " + QTNAME(who) + "; immediately " +
        who->query_pronoun() + " freezes in place.\n",
        ({ this_object(), who }));
  }

  return 1;
}

/* Special Attack: Summon
 * Effects:        Summon guardian spirits to aid in combat. Up to five
 *                 spirits may be under Curan's command at once
 */
int summon(object ob)
{
  int ran, arrived = 0;
  object target, *enemies = ENEMIES_PRESENT;
  object guardian;

  if (environment()->query_prop(ROOM_M_NO_MAGIC))
  {
    return 0;
  }

  tell_room(environment(), QCTNAME(this_object()) + " cries out to " +
      "his god, asking for holy assistance.\n", this_object());

  for (ran = MIN(5 - sizeof(guardians -= ({ 0 })), random(4) + 1); ran--;)
  {
    if (!(guardian = clone_object(GUARDIAN)))
    {
      return 0;
    }

    if (sizeof(enemies))
    {
      target = enemies[random(sizeof(enemies))];
      for_each(enemies - ({ target }), &guardian->attack_object());
      guardian->attack_object(target);
    }

    if (!guardian->move(environment()))
    {
      guardians += ({ guardian });  
      arrived++;
    }
    else
    {
      guardian->remove_object();
    }
  }

  tell_room(environment(), (arrived == 1 ? "A " + guardian->short() +
      " answers" : CAP(LANG_WNUM(arrived)) + " " + guardian->short() + 
      "s answer") + " his summons.\n");

  return 1;
}

/* Special Attack: Wrath of Telan-Ri
 * Effects:        *ack*
 */
int wrath()
{
  return 0;
}

/* Special Attack: Holy Fury
 * Effects:        hmmmm
 */
int fury()
{
  return 0;
}

void remove_invulnerability() 
{ 
  tell_room(environment(), QCTNAME(this_object()) + "'s aura fades.\n",
      this_object());
  invulnerable = 0; 
}

int invulnerability(object enemy)
{
  tell_room(environment(), QCTNAME(this_object()) + " quietly mutters " +
      "a prayer.\nA brilliant, white aura surrounds him.\n", this_object());

  invulnerable = 1;
  set_alarm(25.0, 0.0, &remove_invulnerability());
  return 1;
}

int reduce_hit_point(int hps)
{
  if (invulnerable && (hps > 0) && 
      (!this_interactive() || !IS_WIZ(this_interactive())))
  {
    hps = 0;
  }

  return reduce_hit_point(hps);
}

void heal_hp(int hps)
{
  if (invulnerable && (hps < 0) && 
      (!this_interactive() || !IS_WIZ(this_interactive())))
  {
    return;
  }

  ::heal_hp(hps);
}

mixed hit_me(int wcpen, int dt, object attacker, int attack_id)  
{
  return ::hit_me((invulnerable ? 0 : wcpen), dt, attacker, attack_id);
}

/* Special Attack: Retributive Strike
 * Effects:        A special surprise for those who manage to kill
 *                 Curan.  Telan-Ri, not too happy about Curan's death,
 *                 makes his displeasure known to Curan's killers.
 *                 The following receive a MAGIC_DT hit_me with the
 *                 indicated pen:
 *                   Current enemies who are not present     - 700
 *                   Current, undead enemies who are present - 2200
 *                   Other present enemies                   - 900
 *                 Note: Magical resistance has no effect
 */                   
void retributive_strike()
{
  object *present, *enemies, *others, *undead, *damaged;

  present = FILTER_LIVE(all_inventory(environment())) - ({ TO });
  enemies = present & query_enemy(-1);
  others = (object *)query_enemy(-1) - enemies;

  if (sizeof(others))
  {
    others->catch_msg("\nSuddenly, you hear a shout of rage echo " +
        "through your mind, and you are overcome by agonizing pain " +
        "as if your soul were being burned away by some intense, " +
        "unseen power.\n\n");
    others->hit_me(700, MAGIC_DT, this_object(), -1);
    others->do_die(this_object());
  }         
  
  enemies->catch_msg("As " + POS(this_object()) + " lifeless " +
      "body crumbles to the ground, you hear a shout of rage echo " +
      "through your mind.\n");

  tell_room(environment(), capitalize(POS(this_object())) + 
      " body erupts in a brilliant sphere of light, which quickly " +
      "engulfs the area.\n");
  
  add_prop(CONT_I_LIGHT, 50);

  undead = 
      filter(present, &operator(>)(, 0) @ &->query_prop(LIVE_I_UNDEAD));

  damaged = filter(undead, &operator(<)(, 0) @
      &member_array(, enemies)) + enemies;
  damaged->catch_msg("The light hits you with intense power, burning " +
      "into you, sending shockwaves of pain radiating through the core " +
      "of your body as if it were burning away at your soul.\n");

  undead->hit_me(1000, MAGIC_DT, this_object(), -1);
  enemies->hit_me(900, MAGIC_DT, this_object(), -1);

  filter(damaged, &operator(>=)(0) @ &->query_hp())->do_die(this_object());
}

// Clean up when Curan dies
void do_die(object killer)
{
  // get rid of any guardians still hanging around
  if (sizeof(guardians))
  {
    guardians->remove_spirit();
    guardians = ({ });
  }

  filter(all_inventory(), 
      &wildmatch("/d/Emerald/common/guild/newkot/obj/*") @
      file_name)->remove_object();

  retributive_strike(); /*cackle*/

  ::do_die(killer);
}  

void attacked_by(object ob)
{
  ::attacked_by(ob);
  get_assistance(ob); // see if we can get aid from other npcs
}

// Curan has the ability to remove up to 4 poisons per 3 seconds
void remove_poisons()
{
  int i;
  object *poisons;

  poisons = filter(all_inventory(), &operator(==)("/std/poison_effect") @
      &function_exists("create_object"));
  
  i = MIN(sizeof(poisons), random(4));
  if (i >= sizeof(poisons))
  {
    poison_alarm = 0;
    remove_alarm(poison_alarm);
  }

  while (i--)
  {
    poisons[i]->remove_object();
  }
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (!poison_alarm &&
      function_exists("create_object", ob) == "/std/poison_effect")
  {
    poison_alarm = set_alarm(3.0, 3.0, remove_poisons);
  }
}
