/* Meat Shop of Calathin
 * /d/Terel/calathin/meatshop.c
 * 
 *
 * Coded by Shinto, March 98
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"
#include "shop_check.c"


#define STORE_ROOM CALATHIN_DIR+ "mstore"
object door;

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Butcher Shop");
    set_long(
      "You have entered the butcher shop. Dried meat hangs "+
      "from various places around the shop. Behind the counter "+
      "you can see a large cutting table and several large " +
      "cutting knives. The door leads back out into the square "+
      "and the rest of the town.\n");

    set_shop_name("Ramil's Meat Shop");
    set_keeper_file(CALATHIN_DIR + "npc/ramil");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/meat_door");
    door->move(TO);
    add_item("table","The table is used for slicing up the various "+
        "types of meat.\n");
    add_item("knives","The knives are used to cut up the meats.\n");
    add_item("counter","The counter is made of wood and keeps people back from the "+
        "work of the butcher.\n");
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy meat for gold and get copper back\n"
      + "    buy meat for gold coins\n"
      + "    sell meat for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn and wielded ones.\n"
      + "    sell meat, sell second meat, sell meat 2, sell two meats\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all meats available in the store, the\n"
      + "    correct syntax is: 'list meats' also works.\n"
      + "\n";
}


int
shop_hook_allow_sell(object ob)  
{
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }
    if(ob->id("meat"))
        return 1;
    NF("");
    keeper->command("say I only deal in animal meats.");
    return 0;
}
int
shop_hook_allow_buy(object ob)  
{
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }
    if(ob->id("meat"))
        return 1;
    NF("");
    keeper->command("say I only deal in animal meats.");
    return 0;
}

