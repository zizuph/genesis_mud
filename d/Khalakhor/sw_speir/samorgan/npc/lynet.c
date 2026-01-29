/*
 * A poor girl in Sa Morgan that asks to help with clothing
 * Tapakah, 04/2021
 */

#pragma strict_types

#include <macros.h>

#include "../defs.h"
#include "../quests.h"

#define SHOP (ROOM + "dshop-store")

inherit SM_GIRL;
inherit "/d/Khalakhor/common/npc/quest-npc";

void
make_shopping_list ()
{
  object store = find_object(SHOP);
  if (! store) {
    LOAD_ERR(SHOP);
    store = find_object(SHOP);
  }
  store->reset_room();
  object *items = all_inventory(store);
  string name;
  mapping shopping_list = (["tally": 0]);
  
  foreach (object item: items) {
    name = item->query_name();
    if (shopping_list[name])
      continue;
    shopping_list[name] = ({ item->query_short(), 0 });
  }
  command("say Could you buy me a " + shopping_list["tunic"][0] + "?");
  command("say and a " + shopping_list["belt"][0] + " to go along with it?");
  command("sigh");
  command("say and a " + shopping_list["boots"][0] +
          " although I am not really into that style.");
  command("say but the shop doesn't seem to have anything else.");
  command("say you can find all the items at Arinia's Dress Shop.");
  TP->add_prop(QUEST_M_GIRL_SHOPPING_LIST, shopping_list);
}

void
place_order ()
{
  setuid(); seteuid(getuid());
  if (TP->test_bit(domain, SAMORGAN_QUEST_GROUP, SAMORGAN_QUEST_GIRL_SHOPPING_BIT)) {
    command("say you already helped me before, thank you so much.");
    return;
  }
  command("say so you would like to help me out? How generous!");
  command("say I am extremely short on money now, so I can only reward "+
          "you later. And not anything inappropriate, mind you!!");
  command("say I need someone to buy me an outfit for my new job. It should be "+
          "a pretty tunic, a belt to match and a pair of nice boots.");
  command("emote looks at her feet.");
  command("say yeah, definitely boots.");
  log_quest(SAMORGAN_QUEST_GIRL_SHOPPING_BIT,
            TPQN, "Started quest");
  set_alarm(1.0, 0.0, make_shopping_list);
}

void
create_khalakhor_elf ()
{
  set_name("lynet");
  ::create_khalakhor_elf();
  set_exp_factor(50); // not worth to bother and spoil others' fun
  set_default_answer("say My new job is the only thing on my mind", 1);
  add_act("emote looks at the closet with frustration.");
  add_act("sigh");
  add_act("fidget");
  add_ask(({"closet", "clothes", "sigh", "sighs"}),
          "say I am supposed to start a new job next week, but I don't have "+
          "an appropriate wardrobe for it. Would you help me out?\n", 1);
  foreach (string q: ({"quest", "help", "task", "job"}))
    remove_ask(q);
  add_ask(({"quest", "help", "task", "job"}), place_order);
}

void
extra_reward ()
{
  command("say I have the entire outfit now. I am so happy!");
  command("hmm");
  command("say I should definitely reward you.");
  GET_GEM(SAMORGAN_QUEST_GIRL_SHOPPING_GEM);
  command("give gem to " + TPQN);
}

void
reward_player ()
{
  do_reward_player(SAMORGAN_QUEST_GIRL_SHOPPING_BIT,
                   SAMORGAN_QUEST_GIRL_SHOPPING_EXP, QUEST_M_GIRL_SHOPPING_LIST);
}

void
receive_item (object ob, object from)
{
  if (! TP->query_prop(QUEST_M_GIRL_SHOPPING_LIST))
    return_item(ob, from);

  mapping shopping_list = TP->query_prop(QUEST_M_GIRL_SHOPPING_LIST);
  string name = ob->query_name();
  
  if (! shopping_list[name]) {
    return_item(ob, from,
                "Thanks, but I didn't ask you to bring me this " +
                name + " sorry.");
    return;
  }
  if (shopping_list[name][0] != ob->query_short()) {
    return_item(ob, from, "Thanks, but this " + name + " is not the " +
                shopping_list[name][0] + " I asked you to bring.");
    return;
  }
  if (shopping_list[name][1]) {
    return_item(ob, from, "Thanks, but you already brought me this " + name + ".");
    return;
  }

  command("say Thank you SO MUCH for bringing this to me. This "+
          shopping_list[name][0] + " is exactly what I wanted! "+
          "I will put it immediately in my closet.");
  tell_room(ENV(TO),
            "Lynet puts her new " + shopping_list[name][0] +
            " into the closet and locks it.\n");
  ob->remove_object();
  shopping_list[name][1] = 1;
  shopping_list["tally"]++;
  if (shopping_list["tally"] >= 3)
    set_alarm(1.0, 0.0, reward_player);    
}
