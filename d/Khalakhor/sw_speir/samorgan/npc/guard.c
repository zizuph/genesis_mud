/* SaMorgan village guard
 * Tapakah, 04/2021
 */

#include <stdproperties.h>
#include <files.h>

#include "../defs.h"
#include "../quests.h"

inherit SM_WARRIOR;
inherit QUEST_NPC;

void
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

  command("say We would like some " + food_name + " to eat and " + drink_name +
          " to wash it down.");
  if (! drink_file->query_alco_amount())
    command("say Strangely we don't feel like drinking any alcohol at all.");
  command("say Three portions should be enough, one for each of us.");
  mapping menu_list = TP->query_prop(QUEST_M_GUARD_MENU_LIST);
  if (! menu_list[FETO])
    menu_list[FETO] = ([]);
  menu_list[FETO]["guard"] = ([
    my_food: 0,
    my_drink: 0,
  ]);
    
}

void
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
             menu_list[FETO]["guard"]) {
      command("say ah, getting forgetful, aren't we?");
      fd = m_indices(menu_list[FETO]["guard"]);
      command("say we would like " + fd[0] + " and " + fd[1] + ".");
    }
    else {
      command("say We have been forced to run longer guard shifts than usual.");
      command("say Can you bring us some food - for myself and for my buddies? "+
              "And don't forget the old man sergeant downstairs.");
      set_alarm(1.0, 0.0, place_order);
    }
  }
}

varargs void
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
  if (! objectp(ob)) {
    log_quest(SAMORGAN_QUEST_GROUP, SAMORGAN_QUEST_FEED_GUARDS_BIT,
              TPQRN, ob_name + " not found, got ob ", "warning");
  }
  if (! IS_DRINK_OBJECT(ob) && ! IS_FOOD_OBJECT(ob)) {
    return_item(ob, from);
    return;
  }
  
  mapping menu_list = TP->query_prop(QUEST_M_GUARD_MENU_LIST);

  if (! menu_list[FETO] || !menu_list[FETO]["guard"]) {
    return_item(ob, from,
                "We haven't asked you for any food, have we?");
    return;
  }

  mapping my_order = menu_list[FETO]["guard"];
  string name = ob->query_name();
  if (member_array(name, m_indices(my_order)) < 0) {
    return_item(ob, from,
                "This " + name + " looks appetizing, but we didn't ask "+
                "for it, thanks.");
    return;
  }
  if (!menu_list[FETO]["guard"][name] ||
      menu_list[FETO]["guard"][name] < 3) {
    command("thank " + TPQN);
    command("say Oh, here is the " + name + ". Thank you so much!");
    menu_list[FETO]["guard"][name] += ob->num_heap();
    if (menu_list[FETO]["guard"][name] >= 3) {
      command("say There is now enough for all of us!");
      ob->remove_object();
      menu_list[FETO]["guard"][name] = 3;
    }
  }
  else {
    command("thank " + TPQN);
    return_item(ob, from,
                "Oh, you already brought us one " + name + " for each. "+
                "That would be enough!");
  }  
}

void
create_khalakhor_elf ()
{
  set_samorgan_level(SM_GUARD_LEVEL);
  ::create_khalakhor_elf();  
  add_name("tower guard");
  set_short("SaMorgan guard");
  set_long("This is a Sa Morgan village guard. His slender muscular body "+
           "seems springy and ready for any action, as his eyes are "+
           "warily scanning the environment.\n");
  add_ask(({"quest", "help", "task", "job", "food", "drink"}),
          check_task);
  set_default_answer("I've got to keep the watch. Please do not distract.");
  remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}
