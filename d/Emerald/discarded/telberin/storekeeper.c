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
inherit "/d/Genesis/lib/intro";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Emerald/defs.h"

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
    set_base_stat(SS_DEX, 76);
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

void
do_tackle()
{
    command("tackle " + query_attack()->query_real_name());
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
notify_you_killed_me(object dead)
{
    command("smile coldly");
    command("shout Prepare to meet you maker!");
    set_alarm(2.0, 0.0, &command("get all from corpse"));
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (query_attack())
        command("swear");
    else if (TP->query_npc() || TP->query_met(TO))
        command("Help! " + capitalize(LANG_ART(ob->query_nonmet_name())) +
                " is trying to kill me!");
    else
        command("Help! " + ob->query_met_name() + " is trying to kill me!");
}

void
do_die(object killer)
{
    command("scream");
    ::do_die(killer);
}


string
answer_price()
{
  string who_ask;
  int price;
  
  price = ENV(TO)->query_hire_price(TP);
  who_ask = TP->query_real_name();
  if (query_attack())
  {
      if(TP == query_attack())
          command("say to " + TP->query_real_name() + " We have a score to " +
                  "settle first.");
      else
          command("say to " + TP->query_real_name() + " I have an score to " +
                  "settle with this " + query_attack()->query_race_name() +
                  "first.");
      command("smirk");
  }
  if(!price)
    command("say "+TP->query_name()+
            ", I am afraid I can't tell you right now the price.");
  else
    command("say For you, "+TP->query_name()+
            ", the price is "+text(split_values(price))+".");
  return "";

}

