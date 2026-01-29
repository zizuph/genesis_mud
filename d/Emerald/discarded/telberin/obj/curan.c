inherit "/std/monster";
inherit "/std/act/domove";
inherit "/d/Emerald/telberin/npc/aid_npc";

#include "/d/Emerald/defs.h"
#include "../default.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define DEBUG_WHO find_player("shiva")
#include "/d/Emerald/sys/debug.h"

#define ENEMIES_PRESENT (query_enemy(-1) & all_inventory(environment()))

#define GUARDIAN TELBERIN_DIR + "npc/guardian_spirit"

int heal(object enemy);
int shout(object enemy);
int holy_light(object enemy);
int glance(object enemy);
int summon(object enemy);
void arm_me();

static int poison_alarm;
static object *introed      = ({ });
static object *last_enemies = ({ });
static mixed *specials      = ({ });

static object *guardians = ({ });

void start_wander();
void souls();

void create_monster()
{
  set_living_name("curan");
  set_name(({ "curan", "prince", "paladin", "prince_curan" }));
  set_race_name("elf");
  set_adj(({ "tall", "muscular" }));  

  set_long("A truly imposing figure, he is tremendously well-built " +
      "and extremely tall,\neven for an elf.  Regardless of his " +
      "colossal size, it would be impossible\nto mistake his " +
      "impeccable grooming and fine elven features as anything\n" +
      "other than evidence of strong and ancient elven bloodlines.\n");

  set_appearance_offset(-45);
  set_title("Prince of Emerald, High Champion of Telan-Ri");

  set_alignment(1000);
  set_stats(({ 300, 250, 280, 150, 200, 300 }));

  set_all_hitloc_unarmed(40);
  set_hitloc_unarmed(A_BODY, 70, 45, "body");

  set_give_aid(1);

  set_alarm(1.0, 0.0, souls);

  set_skill(SS_AWARENESS, 80);
  set_skill(SS_2H_COMBAT, 100);
  set_skill(SS_WEP_SWORD, 100);
  set_skill(SS_WEP_KNIFE, 90);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_PARRY, 100);
  set_skill(SS_BLIND_COMBAT, 70);

  add_prop(LIVE_I_QUICKNESS, 100);
  add_prop(OBJ_I_RES_DEATH, 90);
  add_prop(OBJ_I_RES_MAGIC, 50);
  add_prop(LIVE_I_NO_CORPSE, 1);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NON_REMEMBER, 1);

  setuid();
  seteuid(getuid());

  MONEY_ADD(this_object(), 3000 + random(1000));

  set_alarm(1.0, 0.0, arm_me);

  add_act("@@do_something@@");
  add_cact("@@do_something_in_combat@@");
  set_act_time(8);
  set_cact_time(10);

#ifndef NO_WANDER
  start_wander();
#endif
}

void souls()
{
  add_cmdsoul(WRUNNER_DIR + "obj/wrunner_soul");
  update_hooks();
}

int query_knight_prestige() { return -10; }

void arm_me()
{
  map(({ WEP_DIR + "laensword",
         ARM_DIR + "visored_helm",
         ARM_DIR + "w_mithril_plate", ARM_DIR + "w_mithril_bracers",
         ARM_DIR + "w_mithril_greaves", ARM_DIR + "emerald_ring",
      }), clone_object)->move(this_object(), 1);
  command("wield all");
  command("wear all");
}
  
void add_introduced(string str)
{
  object *intro_to = filter(FILTER_LIVE(all_inventory(environment()) -
      ({this_object()})), &operator(<)(,0) @ &member_array(, introed));
  
  if (!sizeof(intro_to))
  {
    return;
  }

  introed += intro_to;
  set_alarm(1.0, 0.0, &command("introduce me"));
}

string do_something()
{
  object *who = FILTER_LIVE(all_inventory(environment()));
  object *bad;
  string target;
  
  if (!sizeof(who))
  {
    return "";
  }

  bad  = filter(who, &operator(<=)(, -100) @ &->query_alignment());
  bad += filter(who - bad, &operator(>)(, 0) @ &->query_prop(LIVE_I_UNDEAD));

  if (sizeof(bad))
  {
    target = bad[random(sizeof(bad))]->query_real_name();
    return ({
              "peer " + target,
              "curl " + target,
           })[random(2)];
  }

  target = who[random(sizeof(who))]->query_real_name();
  return ({
            "smile " + target,
            "pat " + target,
            "sigh contentedly",  
         })[random(3)];
}

string do_something_in_combat()
{
  return ({
            "say You dare challenge the power of Telan-Ri?!?\n",
            "say Flee now, and you might be spared.\n",
            "say You were foolish to have forced my hand.\n",
         })[random(3)];
}

void start_wander() 
{
  set_monster_home(TELBERIN_DIR + "npc_handler");
  set_restrain_path(TELBERIN_DIR); 
  set_random_move(7); 
}

void stop_wander() 
{ 
  set_random_move(0); 
}

void init_living()
{
  ::init_living();

  if (!IS_WIZ(this_player()) && 
      this_player()->query_prop(LIVE_I_UNDEAD) &&
      (member_array(this_player(), query_enemy(-1)) < 0) &&
      CAN_SEE(this_object(), this_player()) &&
      CAN_SEE_IN_ROOM(this_object()))
  {
    if (this_player()->query_average() > 50)
    {
      set_alarm(1.0, 0.0, &command("kill " + 
          this_player()->query_real_name()));
    }

    set_alarm(2.0, 0.0, &command("shout I shall smite out thine " +
        "abominous existence, fiend!\n"));
  }
}

void update_specials(object *enemies)
{
  object *undead;

  if (!sizeof(enemies))
  {
    // hmmm...somehow we got here w/o any enemies
    DEBUG("Specials 1");
    specials = ({
                  ({ heal,       50 }),
                  ({ shout,      15 }),
                  ({ holy_light, 15 }),
                  ({ glance,      5 }),
                  ({ summon,     15 }),
               });
    return;
  }

  undead = filter(enemies, &operator(>)(, 0) @
      &->query_prop(LIVE_I_UNDEAD));

  if (!sizeof(undead))
  {
    DEBUG("specials 2");
    // no undead enemies, so don't use the anti-undead attacks
    specials = ({
                  ({ heal,   50 }),
                  ({ shout,  20 }),
                  ({ glance, 10 }),
                  ({ summon, 20 }),
               });
    return;
  }

  if (sizeof(undead) == 1)
  {
    DEBUG("Specials 3");
    // one undead...use some anti-undead stuff
    specials = ({
                  ({ heal,       45 }),
                  ({ shout,      10 }),
                  ({ glance,     10 }),
                  ({ holy_light, 20 }),
                  ({ summon,     15 }),
               });
     return;
  }
  
  DEBUG("Specials 4");
  // several undead...let's beat the crap out of them!
  specials = ({
                ({ heal,       40 }),
                ({ shout,       5 }),
                ({ glance,     10 }),
                ({ holy_light, 30 }),
                ({ summon,     15 }),
             });
}

void reduce_light(int i)
{
  add_prop(CONT_I_LIGHT, query_prop(CONT_I_LIGHT) - i);
}

int special_attack(object enemy)
{
  object *enemies = ENEMIES_PRESENT;
  int i, j, ran;
  function attack_func;
  object poison;

  DEBUG(sizeof(enemies));
  if ((sizeof(enemies) != sizeof(last_enemies)) ||
      (sizeof(enemies & last_enemies) != sizeof(last_enemies)))
  {
    last_enemies = enemies;
    update_specials(enemies);
  }

  if (!CAN_SEE_IN_ROOM(this_object()))
  {
    tell_room(environment(), QCTNAME(this_object()) + " chants in " +
        "an unknown tongue, and bright light fills the area.\n",
        this_object());
    add_prop(CONT_I_LIGHT, query_prop(CONT_I_LIGHT) + 20);
    set_alarm(60.0, 0.0, &reduce_light(20));
    return 1;
  }

  if (!sizeof(specials) || random(5))
  {
    return 0;
  }

  ran = random(100);
  for (i = sizeof(specials); i--;)
  {
    if ((j += specials[i][1]) >= ran)
    {
      break;
    }
  }

  i = MAX(0, MIN(sizeof(specials), i));
  attack_func = specials[i][0];
  return attack_func(enemy);
}

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
    if (!enemies[i]->query_prop(LIVE_I_UNDEAD) ||
        enemies[i]->query_prop(OBJ_M_NO_MAGIC_ATTACK))
    {
      continue;
    }

    res = enemies[i]->query_magic_res(MAGIC_I_RES_LIFE);
    enemies[i]->hit_me((random(200) + 100) * (100 - res), MAGIC_DT, 
        this_object(), -1);
    enemies[i]->catch_msg("\nYou are burned by the light!\n\n");
    enemies[i]->do_die(this_object());
  }

  set_alarm(2.0, 0.0, &reduce_light(20));
  return 1;
}

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

int shout(object enemy)
{
  object *enemies, *special;

  if (environment()->query_prop(ROOM_M_NO_MAGIC))
  {
    return 0;
  }

  enemies = filter(ENEMIES_PRESENT, &operator(!=)(0) @
      &->query_prop(OBJ_M_NO_MAGIC_ATTACK));

  if (!sizeof(enemies))
  {
    return 0;
  }

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

int glance(object enemy)
{
  object *enemies = ENEMIES_PRESENT;
  object who, hold;

  if (environment()->query_prop(ROOM_M_NO_MAGIC) || !sizeof(enemies))
  {
    return 0;
  }

  who = enemies[random(sizeof(enemies))];
  if (who->query_prop(OBJ_M_NO_MAGIC_ATTACK))
  {
    return 0;
  }

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
      " answers " : CAP(LANG_WNUM(arrived)) + " " + guardian->short() + 
      "s answer") + " his summons.\n");

  return 1;
}

int wrath()
{
  return 0;
}

int fury()
{
  return 0;
}

void do_die(object killer)
{
  object *present, *enemies, *others, *undead, *damaged;

  present = FILTER_LIVE(all_inventory(environment()));
  enemies = present & query_enemy(-1);
  others = (object *)query_enemy(-1) - enemies;

  if (sizeof(guardians))
  {
    guardians->remove_spirit();
    guardians = ({ });
  }

  if (sizeof(others))
  {
    others->catch_msg("\nSuddenly, you hear a shout of rage echo " +
        "through your mind, and you are overcome by agonizing pain " +
        "as if your soul were being burned away by some intense, " +
        "unseen power.\n\n");
    others->hit_me(900, MAGIC_DT, this_object(), -1);
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
  enemies->hit_me(1200, MAGIC_DT, this_object(), -1);

  damaged->do_die(this_object());

  ::do_die(killer);
}  

void attacked_by(object ob)
{
  ::attacked_by(ob);
  get_assistance(ob);
}

void remove_poisons()
{
  int i;
  object *poisons;

  poisons = filter(all_inventory(), &operator(==)("/std/poison_effect") @
      &function_exists("create_object"));
  
  i = MIN(sizeof(poisons), random(4));
  if (i >= sizeof(poisons))
  {
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

  if (function_exists("create_object", ob) == "/std/poison_effect")
  {
    poison_alarm = set_alarm(3.0, 3.0, remove_poisons);
  }
}
