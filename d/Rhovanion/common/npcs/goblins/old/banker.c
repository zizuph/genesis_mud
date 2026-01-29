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
 * This is Shopkeeper Goblin made by Milan. 
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

#ifndef BASE_GOB
#define BASE_GOB 120
#endif

#ifndef RAN_GOB
#define RAN_GOB 30
#endif

#undef ARM_DIR
#undef WEP_DIR
#define ARM_DIR ARMOUR_DIR+"goblin/"
#define WEP_DIR WEAPON_DIR

#define SUP_GOBLIN_LEVEL      120
#define HIGH_GOBLIN_LEVEL      80
#define MEDIUM_GOBLIN_LEVEL    50

#ifndef RANDOM_WEAPONS
#define RANDOM_WEAPONS  ({ "club" })
#endif
#ifndef RANDOM_ARMOURS
#define RANDOM_ARMOURS  ({ "helm" })
#endif
#ifndef DEFAULT_ARMOURS
#define DEFAULT_ARMOURS ({ "mail","shield" })
#endif

#ifndef COMBAT_CHAT_LIST
#define COMBAT_CHAT_LIST ({ "I hate intruders like you!", \
                            "I will have fresh flesh to feed on!", \
                            "Someone go and prepare big pot!", \
                            "I will sell loot from your corpse!" })
#endif

#ifndef CHAT_LIST
#define CHAT_LIST ({ "What do you want?", \
                     "I am hungry!!!", \
                     "You got lot of money?", \
                     "You will not steal anything from me!", \
                     "You have enough money?", \
                  })
#endif


/*
 * Global variables
 */
int knight_prestige;
int base = BASE_GOB + random(RAN_GOB);
string type = "_low";
string *list_introduced = ({ });
string *list_asked_help = ({ });

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

    set_name("crotch");
    set_race_name("goblin"); 
    set_title("Banker");
    set_living_name("_gob_banker_");
    set_adj(look_1);
    add_adj("greedy");

    set_long("This greedy goblin is willing to trade even with you as "+
             "long as he has some profit.\n");

    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 36000);
    add_prop(CONT_I_VOLUME, 36000);

    set_base_stat(SS_STR, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_DEX, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_CON, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_WIS, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_INT, (base * 3 / 4) + random(base / 3));
    set_base_stat(SS_DIS, (base * 4 / 5) + random(base / 2));

    refresh_mobile(); /* full hp, mana, fatigue */


    set_alignment(-(4 * base));
    knight_prestige = 4 * base;

    set_skill(SS_BLIND_COMBAT, MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_SWORD,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_CLUB,     MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_AXE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_POLEARM,  MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_KNIFE,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_PARRY,        MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_DEFENCE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_AWARENESS,    MIN(100,(base * 3 / 4) + random(base / 2)));

    set_chat_time(10 + random(10));
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
    trig_new("%w 'introduces' %s", "react_introduce");

    add_ask("instructions", VBFC_ME("answer_help"));
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

int
react_introduce(string who, string dummy) 
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself"))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  call_out("return_introduce", 2);
  return 1;
}

void
return_introduce() {
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++) 
    if ((in_room[i]->query_race_name() == "goblin") && 
        (!in_room[i]->query_met(TO->query_real_name()))) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow goblins");
  }
  return;
}

int
query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
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
shout_for_help(string who){
  call_out("command", random(10), "shout Help!!! "+who+" wants to kill me!");
}

/*
 * Solamnian knight prestige
 */
int
query_knight_prestige()
{
    return knight_prestige;
}

string
answer_help()
{
  string who_ask = TP->query_real_name();

  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first! I like to know who am I talking to.");
    command("peer "+who_ask);
    return "";
  }
  command("say Yes, I can relieve you of the burden of heavy coins.");
  command("smile greedily");
  command("say You can change platinum and gold for copper...");
  command("say then change 100 platinum for copper...");
  command("say maybe even change platinum for 10 silver...");
  command("hmm");
  command("scratch");
  command("say Yes...");
  command("say you can do test change 100 platinum for copper too!");
  command("poke "+who_ask);
  command("think");
  command("scratch");
  command("peer "+who_ask);
  command("say O.K. I tell you...");
  command("say You can even minimize coins!");
  command("say But I don't like to do this very much.");
  command("grin");
  command("say I think that's all...");
  command("smile "+who_ask);
  command("think");
  command("oops");
  command("say I forgot the most important part!!!");
  command("say Of course I take some small fee for my service.");
  command("giggle");
  return "";
}

