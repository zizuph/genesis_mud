/* SaMorgan village guard sergeant
 * Tapakah, 04/2021
 */

#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"
#include "../quests.h"

inherit SM_WARRIOR;

public void
place_order ()
{
  string *foods = SM_PUB->query_tavern_food();
  string food = one_of_list(foods);
  string my_food, grbg;
  sscanf(food, "%s '%s' /", grbg, my_food);
  string food_file = SM_PUB->query_tavern_food(my_food, 7);
  string food_name = food_file->query_name();
  
  string *drinks = SM_PUB->query_tavern_drink();
  string drink = one_of_list(drinks);
  string my_drink;
  sscanf(drink, "%s '%s' /", grbg, my_drink);
  string drink_file = SM_PUB->query_tavern_drink(my_drink, 8);
  string drink_name = drink_file->query_name();

  command("say I would like some " + food_name + " to eat and " + drink_name +
          " to wash it down.");
  if (! drink_file->query_alco_amount())
    command("say Strangely I don't feel like drinking any alcohol at all.");
  command("say Ask the guards upstairs what they would like to have.");
  mapping menu_list = TP->query_prop(QUEST_M_GUARD_MENU_LIST);
  if (! menu_list[FETO])
    menu_list[FETO] = ([]);
  menu_list[FETO]["sergeant"] = ([
    my_food: 0,
    my_drink: 0,
  ]);   
}

public void
check_task ()
{
  string *fd;
  mapping menu_list;
  
  if (TP->test_bit("Khalakhor",
                   SAMORGAN_QUEST_GROUP,
                   SAMORGAN_QUEST_FEED_GUARDS_BIT))
    command("say Oh, I remember you. You brought us food. "+
            "Thanks once again!");
  else {
    menu_list = TP->query_prop(QUEST_M_GUARD_MENU_LIST);
    if (! menu_list)
      command("say You should check with our lieutenant. He's at "+
              "the message board room.");
    else if (menu_list[FETO] &&
             menu_list[FETO]["sergeant"]) {
      command("say ah, getting forgetful, aren't we?");
      fd = m_indices(menu_list[FETO]["sergeant"]);
      command("say I would like a " + fd[0] + " and a " + fd[1] + ".");
    }
    else {
      command("say We have been forced to run longer guard shifts than usual.");
      command("say Can you bring us some food - for myself and for the guys " +
              "upstairs?");
      set_alarm(1.0, 0.0, place_order);
    }
  }
}

public void
receive_item (object ob, object from, string ob_name)
{
  if (! ob) {
    ob = present(ob_name, TO);
    ob->split_heap(1);
  }
  if (! TP->query_prop(QUEST_M_GUARD_MENU_LIST)) {
    return_item(ob, from);
    return;
  }
 
  if (! IS_DRINK_OBJECT(ob) && ! IS_FOOD_OBJECT(ob)) {
    return_item(ob, from);
    return;
  }
  
  mapping menu_list = TP->query_prop(QUEST_M_GUARD_MENU_LIST);

  if (! menu_list[FETO] || !menu_list[FETO]["sergeant"]) {
    return_item(ob, from,
                "I haven't asked you for any food, have I?");
    return;
  }

  mapping my_order = menu_list[FETO]["sergeant"];
  string name = ob->query_name();
  if (member_array(name, m_indices(my_order)) < 0) {
    return_item(ob, from,
                "This " + name + " looks appetizing, but I didn't ask "+
                "for it, thanks.");
    return;
  }
  
  if (! menu_list[FETO]["sergeant"][name]) {
    command("thank");
    command("say Oh, here is the " + name + ". Thank you so much!");
    menu_list[FETO]["sergeant"][name] = 1;
    command("eat all");
    command("drink all");
  }
  else {
    command("thank");
    return_item(ob, from,
                "say Oh, you already brought me one " + name + ". "+
                "That would be enough!");
  }  
}

public void
create_khalakhor_elf ()
{
  set_samorgan_level(SM_SERGEANT_LEVEL);
  ::create_khalakhor_elf();
  set_name("sergeant");
  set_short("SaMorgan sergeant");
  set_long("This is a SaMorgan guard sergeant. The grizzled face has seen "+
           "a lot of troubling times, and the eyes carry a touch of "+
           "sadness and a lot of wisdom.\n");
  add_ask(({"quest", "help", "task", "job", "food", "drink"}),
          check_task);
  add_act("stretch", 1);
  add_act("scratch chin", 1);
  set_default_answer("I'm just a simple sergeant commanding this "+
                     "tower.");
  remove_prop(LIVE_M_NO_ACCEPT_GIVE);
  set_act_time(600);
  
}
