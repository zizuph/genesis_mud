/* Gem Shop of Calathin
 * /d/Terel/calathin/gemshop.c
 * 
 *
 * Coded by Shinto, March 98
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"


#define STORE_ROOM CALATHIN_DIR+ "gem_store"
object door;

void
create_shop()
{
    set_short("Marila's Fine Gems");
    set_long("You've entered Marila's Fine Gems, before you stands "+
                   "a counter. The counter is filled with numerous types "+
                   "of gems found all of the lands. The store itself is "+
                   "finely crafted in oak. Behind the counter you can see "+
                   "various tools used for cutting gems. The doorway "+
                   "south leads back out to the road.\n");
    set_store_room(STORE_ROOM);
    set_shop_name("Marila's Fine Gems");
    set_keeper_file(CALATHIN_DIR + "npc/marila");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/gem_door");
    door->move(TO);
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy gem for gold and get copper back\n"
      + "    buy gem for gold coins\n"
      + "    sell gem for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn and wielded ones.\n"
      + "    sell gem, sell second gem, sell gem 2, sell two gems\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all gems available in the store, the\n"
      + "    correct syntax is: 'list gems' also works.\n"
      + "\n";
}

int
shop_hook_allow_sell(object ob)  
{
    if(TP->query_race_name() == "goblin")
    {
        keeper->command("say I don't do business with goblins.");
        keeper->command("say Now please go away.");
        NF("");
        return 0;
    }
    if(ob->id("gem"))
        return 1;
    NF("");
    keeper->command("say This is a gem shop, thats what I buy and sell.");
    return 0;
}
int
shop_hook_allow_buy(object ob)  
{
    if(TP->query_race_name() == "goblin")
    {
        keeper->command("say I don't deal with goblins.");
        NF("");
        return 0;
    }
    return 1;
}

