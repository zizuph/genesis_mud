/*
 * A poor boy in Sa Morgan
 * Tapakah, 05/2021
 */

#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"
#include "../quests.h"

inherit SM_BOY;
inherit "/d/Khalakhor/common/npc/quest-npc";

mapping weights = (["sword": 8000, "shield": 8000, "helmet": 5000, "mail": 15000]);

void
request_armours ()
{
  command("say I also need a mail, a shield and a helm, once again, middle of "+
          "the road and not too heavy. The armours from Martin would be perfect. "+
          "And please no magical stuff as well!");
  command("say The guys from the patrol said they had extra boots and gloves, "+
          "so no need to bring those.");
  command("say I promise I am going to reward you well!");
}

void
request_weapon ()
{
  command("say I would need a sword. Not too powerful, but not too shabby either. "+
          "Not too heavy as well, if you could. "+
          "The rapier that Emmit sells would be perfect.");
  command("say Oh! No magic stuff!! I can't handle that.");
  set_alarm(1.0, 0.0, request_armours);    
}
  

void
make_shopping_list ()
{
  mapping shopping_list = ([
    "sword" : -1,
    "shield": -1,
    "mail"  : -1,
    "helm"  : -1,
    "tally" : 0,
  ]);
  TP->add_prop(QUEST_M_BOY_EQUIPMENT_LIST, shopping_list);
  set_alarm(1.0, 0.0, request_weapon);    
}

void
place_order ()
{
  setuid(); seteuid(getuid());
  if (TP->test_bit(domain, SAMORGAN_QUEST_GROUP, SAMORGAN_QUEST_BOY_EQUIPMENT_BIT)) {
    command("say you already helped me before, thank you so much.");
    return;
  }
  command("say so you would like to help me out? How generous!");
  command("say I am extremely short on money now, so I can only reward "+
          "you later.");
  command("say I need someone to buy me a set of armours and a weapon.");
  log_quest(SAMORGAN_QUEST_BOY_EQUIPMENT_BIT,
            TPQN, "Started quest");
  set_alarm(1.0, 0.0, make_shopping_list);
}

void
create_khalakhor_elf ()
{
  set_name("fearghal");
  ::create_khalakhor_elf();
  set_exp_factor(50); // not worth to bother and spoil others' fun
  set_default_answer("say I can only think about my call-up!", 1);
  add_act("emote trembles with excitement.");
  add_act("pace");
  add_act("flex");
  add_ask(({"excitement", "call-up"}),
          "say I am accepted into Sa Morgan patrol. But I need to provide "+
          "my own equipment - and I am broke. Would you help me out?", 1);
  foreach (string q: ({"quest", "help", "task", "job"}))
    remove_ask(q);
  add_ask(({"quest", "help", "task", "job"}), place_order);
  
}

string
get_equipment_name (object ob)
{
  if (! ob->query_wt()) {
    if (! ob->query_at())
      return ob->query_name();
    else {
      switch (ob->query_at()) {
      case A_HEAD:
        return "helm";
      case A_SHIELD:
        return "shield";
      case A_BODY:
        return "mail";
      default:
        return "armour";
      }
    }
  }
  else
    return ob->query_wt() == W_SWORD ? "sword" : "weapon";
}

string
check_item (object ob, string name)
{
  if (ob->query_prop(MAGIC_AM_MAGIC) ||
      ob->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
      ob->query_prop(OBJ_I_IS_MAGIC_WEAPON))
      return "I don't know how to handle magic items...";

  if (ob->query_weight() > weights[name])
      return "it's just too heavy";
  if (name == "sword") {
    if (ob->query_pen() + ob->query_hit() < 40)
      return "it's just not good enough for my task.";
    if (ob->query_pen() + ob->query_hit() > 70)
      return "it's just too good for me.";
  }
  else {
    if (ob->query_ac() < 15)
      return "it's just not good enough for my task.";
    if (ob->query_ac() > 40)
      return "it's just too good for me.";
  }
  return "";
}

void
extra_reward ()
{
  command("say I have the entire equipment set now. I am so excited!");
  command("hmm");
  command("say I should definitely reward you.");
  GET_GEM(SAMORGAN_QUEST_BOY_EQUIPMENT_GEM);
  command("give gem to " + TPQN);  
}

void
reward_player ()
{
  do_reward_player(SAMORGAN_QUEST_BOY_EQUIPMENT_BIT,
                   SAMORGAN_QUEST_BOY_EQUIPMENT_EXP, QUEST_M_BOY_EQUIPMENT_LIST);
}

void
receive_item (object ob, object from)
{
  if (! TP->query_prop(QUEST_M_BOY_EQUIPMENT_LIST))
    return_item(ob, from);
  mapping shopping_list = TP->query_prop(QUEST_M_BOY_EQUIPMENT_LIST);
  string name = get_equipment_name(ob);

  if (! shopping_list[name]) {
    return_item(ob, from,
                "Thanks, but I didn't ask you to bring me this, sorry.");
    return;
  }
  if (shopping_list[name] > 0) {
    return_item(ob, from, "Thanks, but you already brought me a " + name + ".");
    return;
  }
  string reason = check_item(ob, name);
  if (reason != "") {
    return_item(ob, from, "Thanks, but this " + name + " is not a good "+
                "fit because " + reason);
    return;
  }
  command("say Thank you SO MUCH for bringing this to me. This " + name +
          " is going to be a great fit! I will put it somewhere safe for now.");
  command("emote looks around.");
  tell_room(ENV(TO),
            "Fearghal tucks his newly received " + name +
            " under the bed.\n");
  ob->remove_object();
  shopping_list[name] = 1;
  shopping_list["tally"]++;
  if (shopping_list["tally"] >= 4)
    set_alarm(1.0, 0.0, reward_player);    

}
