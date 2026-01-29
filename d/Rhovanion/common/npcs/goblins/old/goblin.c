/*
 * /d/Gondor/mordor/npc/towerorc.c
 *
 * This is the default orc in the Cirith Ungol. This orc will also patrol in
 * Torech Ungol from time to time. It is a very nice orc, for everything
 * in this orc is adjustable with only one patch. His armour and weapons are
 * dependant on his average stats and his skills will also be dependant on
 * his stats. The orc has several attack cries, which he obviously not waists
 * on wizards. With a slight chance he will get a key to the tower at
 * Cirtih Ungol and you can also give him a whip.
 *
 * I spent some time time coding this sucker and even more on debugging and
 * enhancing it. If you want to copy this orc and adjust it for your own
 * purposes, I do not mind you doing so IF you leave this header in tact.
 * You can add your own header AFTER this one.
 *
 * /Mercade 27 September 1993
 *
 * Revision history:
 */

/*
 * This is standard Goblin made by Milan. 
 * I used lots of ideas from Mercade's  towerorc.c
 *
 * Basic constants that deternine the Goblin are BASE_GOB, RAN_GOB
 *
 */

inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Rhovanion/defs.h"

#include "/d/Rhovanion/lib/kill_log.h"

#ifndef BASE_GOB
#define BASE_GOB 30
#endif

#ifndef RAN_GOB
#define RAN_GOB 90
#endif

#undef ARM_DIR
#undef WEP_DIR
#define ARM_DIR ARMOUR_DIR+"goblin/"
#define WEP_DIR WEAPON_DIR

#define SUP_GOBLIN_LEVEL      120
#define HIGH_GOBLIN_LEVEL      80
#define MEDIUM_GOBLIN_LEVEL    50

#ifndef RANDOM_WEAPONS
#define RANDOM_WEAPONS  ({ "pole", "sword", "axe", "club" })
#endif
#ifndef RANDOM_ARMOURS
#define RANDOM_ARMOURS  ({ "helm", "shield" })
#endif
#ifndef DEFAULT_ARMOURS
#define DEFAULT_ARMOURS ({ "mail" })
#endif

#ifndef ALIGNLOOKS
#define ALIGNLOOKS ({"cruel","angry","mean","foul","brutal","sinister", \
                  "ugly","nasty","evil","savage","dangerous","strong" })
#endif

#ifndef COMBAT_CHAT_LIST
#define COMBAT_CHAT_LIST ({ "I hate intruders in our caves!!!", \
                            "We will have fresh flesh to feed on!", \
                            "Someone go and prepare our pot!" })
#endif

#ifndef CHAT_LIST
#define CHAT_LIST ({ "What is our lord going to do with that prisoner?", \
                     "I am hungry!!!", \
                     "Watch out! I have news that there are intruders in our cave." \
                  })
#endif


/*
 * Global variables
 */
int knight_prestige;
int base = BASE_GOB + random(RAN_GOB);
string looks = ONE_OF_LIST(ALIGNLOOKS);
string type = "_low";

void
create_monster()
{
  int i;
  string look_1 = "medium";

    if (!IS_CLONE)
	return;

    if (base >= MEDIUM_GOBLIN_LEVEL){ type = "_med"; look_1 = "big"; }
    if (base >= HIGH_GOBLIN_LEVEL){ type = "_high"; look_1 = "massive"; }
    if (base >= SUP_GOBLIN_LEVEL){ type = "_sup"; look_1 = "huge"; }

    set_name("_misty_goblin_");
    set_pname("goblins");
    set_race_name("goblin"); 
    set_adj(look_1);
    add_adj(looks);
    set_short(look_1+" "+looks + " goblin");
    set_pshort(look_1+" "+looks + " goblins");

    set_long("It is a very ugly and nasty lookin' goblin.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 36000);
    add_prop(CONT_I_VOLUME, 36000);

    add_prop(DO_I_TELL_RUMOURS, 1);

    set_base_stat(SS_STR, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_DEX, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_CON, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_WIS, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_INT, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_DIS, (base * 4 / 5) + random(base / 2));

    refresh_mobile(); /* full hp, mana, fatigue */


    set_alignment(-(4 * base));
    knight_prestige = 4 * base;

    set_aggressive(random(4));

    set_skill(SS_BLIND_COMBAT, MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_SWORD,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_CLUB,     MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_AXE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_POLEARM,  MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_KNIFE,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_PARRY,        MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_DEFENCE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_AWARENESS,    MIN(100,(base * 3 / 4) + random(base / 2)));

    set_chat_time(10 + random(30));
    for (i = 0; i < sizeof(CHAT_LIST); i++)
       add_chat(CHAT_LIST[i]);

    set_cchat_time(random(10));
    for (i = 0; i < sizeof(COMBAT_CHAT_LIST); i++)
       add_cchat(COMBAT_CHAT_LIST[i]);

    set_act_time(10 + random(20));
    add_act("burp");
    add_act("hiss");
    add_act("spit");
    add_act("eat all");
    add_act("drink all");
    add_act("get all");

    set_cact_time(random(10));
    add_cact("scream");
    add_cact("grin");
    add_cact("@@do_tackle");
    add_cact("@@do_knee");
    add_cact("@@do_kick");

    trig_new("'You' 'killed' %s", "react_kill");
    trig_new("%s 'attacks' 'you!\n'", "shout_for_help");
}

/*
 * Give the goblin armour and a weapon.
 */
void
arm_me()
{
    int i;
    object cash,
           *wep_arm;

    set_this_player(this_object());

    seteuid(getuid(TO));

    clone_object(WEP_DIR + ONE_OF_LIST(RANDOM_WEAPONS) + type)->move(TO);
    clone_object(ARM_DIR + ONE_OF_LIST(RANDOM_ARMOURS) + type)->move(TO);

    for (i = 0; i < sizeof(DEFAULT_ARMOURS); i ++)
    {
        clone_object(ARM_DIR + DEFAULT_ARMOURS[i] + type)->move(TO);
    }

    command("wield all");
    command("wear all");

    cash = clone_object("/std/coins");
    cash->set_coin_type("copper");
    cash->set_heap_size(random(base));
    cash->move(this_object());
    if(base > MEDIUM_GOBLIN_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("silver");
      cash->set_heap_size(random(base / 2));
      cash->move(this_object());
    }
    if(base > HIGH_GOBLIN_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("gold");
      cash->set_heap_size(random(base / 8));
      cash->move(this_object());
    }
    if(base > SUP_GOBLIN_LEVEL)
    {
      cash = clone_object("/std/coins");
      cash->set_coin_type("platinum");
      cash->set_heap_size(random(base / 16));
      cash->move(this_object());
    }
}

void
init_attack()
{
    call_out("slow_init_attack", random(20), TP);
}

void
slow_init_attack(object tp)
{
    if (!tp || query_attack() || !present(tp, environment())) return;

    /* wizards aren't attacked... */
    if (tp->query_wiz_level()) return;

    /* Goblins aren't attacked either */
    if (tp->query_race_name() == "goblin") return;

    aggressive_attack(tp);
    if(random(2))
      call_out("command", random(10), "grin "+tp->query_real_name());
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
  object *arr;
  int i;

  ::attacked_by(ob);

  arr = FILTER_LIVE(all_inventory(environment()));
  for (i = 0; i < sizeof(arr); i++)
    if((arr[i]->query_real_name() == "_misty_goblin_") && (arr[i] != TO))
      arr[i]->notify_ob_attacked_me(ob);
}

void
notify_ob_attacked_me(object attacker)
{
    if(query_attack()) return;

    if(random(10))
      call_out("help_friend", (5 + random(10)), attacker);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        if(random(2)) command("grin " + ob->query_real_name());
        command("kill " + ob->query_real_name());
    }
}

void
do_knee()
{
    command("knee " + query_attack()->query_real_name());
}

void
do_kick()
{
    command("kick " + query_attack()->query_real_name());
}

void
do_tackle()
{
    command("tackle " + query_attack()->query_real_name());
}

void
react_kill(string who) {
   command("shout I killed "+who);
   command("laugh");
   call_out("command", 2, "get all from corpse");
}

void
shout_for_help(string who)
{
  if(random(2)) call_out("shout_for_help_2", random(10), who);
}
void
shout_for_help_2(string who)
{
  int i;
  object *arr;

  if(!who) return;
  arr = TO->query_enemy(-1);

  for(i=0; i < sizeof(arr); i++)
    if(arr[i]->query_name() == who)
      command("shout Help!!! The "+arr[i]->query_nonmet_name()+
              " wants to kill me!");
}

/*
 * Solamnian knight prestige
 */
int
query_knight_prestige()
{
    return knight_prestige;
}

int
special_attack(object enemy)
{
  object prisoner,
         *others;

  /* some special attacks dont call attacked_by() */
  if(!random(5)) attacked_by(enemy); 
  prisoner = find_living("_misty_prisoner_");
  if (!prisoner) return 0;
  if(TO->query_attack() == prisoner) return 0;
  if(present(prisoner, environment(TO))) 
    if((member_array(prisoner, TO->query_enemy(-1)) != -1) ||
       (prisoner->check_seen(TO)))
    {
       TO->attack_object(prisoner);
       prisoner->attack_object(TO);
    }
  return 0;
}

