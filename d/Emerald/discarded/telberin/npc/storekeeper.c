 
/* storkeeper.c is cloned by /telberin/tower.c */
 
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
inherit "/lib/trade";
 
#include <language.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"
 
#ifndef COMBAT_CHAT_LIST
#define COMBAT_CHAT_LIST ({ "Get out of my Tower!", \
                            "Can't you see I'm old?", \
                            "How dishonourable of you!" })
#endif
 
#ifndef CHAT_LIST
#define CHAT_LIST ({ "Are you just browsing?", \
                     "Ahhh how nice the weather is!", \
                     "Do you seriously wish to purchase something?", \
                     "You want to send a message?", \
                     "My animals cost money you know.", \
                     "Come on come one, buy something...", \
                  })
#endif
 
string *list_introduced = ({ });
 
void
create_monster()
{
  int i;
 
    if (!IS_CLONE)
        return;
 
  config_default_trade();  /* Set up the trading system */
 
    set_name("tardath");
    set_race_name("elf");
    set_title("Storekeeper");
    set_living_name("_elf_animal_trainer_");
    set_adj("old");
 
    set_long("This old elf looks after the animals that frequent the courts "+
	"of Telberin such as doves and hawks.\n");
 
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 36000);
    add_prop(CONT_I_VOLUME, 36000);
 
    set_base_stat(SS_STR, 67);
    set_base_stat(SS_DEX, 75);
    set_base_stat(SS_CON, 65);
    set_base_stat(SS_WIS, 55);
    set_base_stat(SS_INT, 72);
    set_base_stat(SS_DIS, 62);
 
    refresh_mobile(); /* full hp, mana, fatigue */
 
    set_alignment(677);
 
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_DEFENCE,      60);
    set_skill(SS_AWARENESS,    70);
 
    set_chat_time(10 + random(10));
    for (i = 0; i < sizeof(CHAT_LIST); i++)
       add_chat(CHAT_LIST[i]);
 
    set_cchat_time(random(10));
    for (i = 0; i < sizeof(COMBAT_CHAT_LIST); i++)
       add_cchat(COMBAT_CHAT_LIST[i]);
 
    set_act_time(10 + random(20));
    add_act("smile");
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
 
    add_ask(({"price","purchase price","animal","price of animal"}),
            VBFC_ME("answer_price"));
}
 
/*
 * Give the elf some cash.
 */
void
arm_me()
{
    object cash;
 
    set_this_player(this_object());
 
    seteuid(getuid(TO));
 
    cash = clone_object("/std/coins");
    cash->set_coin_type("copper");
    cash->set_heap_size(random(20));
    cash->move(this_object());
 
    cash = clone_object("/std/coins");
    cash->set_coin_type("silver");
    cash->set_heap_size(random(30));
    cash->move(this_object());
}
 
int
react_introduce(string who, string dummy)
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself"))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  set_alarm( 2.0,0.0,"return_introduce");
  return 1;
}
 
void
return_introduce()
{
  object *in_room;
  int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++)
    if ((in_room[i]->query_race_name() == "elf") &&
        (!in_room[i]->query_met(TO->query_real_name()))) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow elves");
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
   set_alarm( 2.0,0.0,"command", "get all from corpse");
}
 
void
shout_for_help(string who){
  set_alarm( itof(random(10)),0.0,"command");
}
 
string
answer_price()
{
  string who_ask = TP->query_real_name();
  int price;
 
  if(member_array(who_ask, list_introduced) == -1)
  {
    command("say Introduce yourself first! I like to know who am I talking to.");
    command("peer "+who_ask);
    return "";
  }
 
  price = ENV(TO)->query_hire_price(TP);
  if(!price)
    command("say "+TP->query_name()+
            ", I am afraid I can't tell you right now the price.");
  else
    command("say For you, "+TP->query_name()+
            ", the price is "+text(split_values(price))+".");
  return "";
 
}
 
