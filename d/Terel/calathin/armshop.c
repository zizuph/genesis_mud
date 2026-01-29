/* Armour Shop of Calathin
 * /d/Terel/calathin/armshop.c
 * 
 *
 * Coded by Shinto, March 98
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"
#include "shop_check.c"


#define STORE_ROOM CALATHIN_DIR+ "astore"
#define STDARMFILE "/std/armour"

object door;

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Sturdy Shield Armour Shop");
    set_long(
      "You have entered the Sturdy Shield Armour Shop. The north, east, "+
      "and west walls are covered with all manner of shields, bracers, "+
      "platemails, and other types of protection. A large counter spreads "+
      "the width of the north wall.\n");

    set_shop_name("Sturdy Shield Armour Shop");
    set_keeper_file(CALATHIN_DIR + "npc/tariyn");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/arm_door");
    door->move(TO);
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy armour for gold and get copper back\n"
      + "    buy armour for gold coins\n"
      + "    sell armour for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn.\n"
      + "    sell armour, sell second armour, sell armour 2, sell two armours\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all armours available in the store, the\n"
      + "    correct syntax is: 'list armours' also works.\n"
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
    if (ob->id("bar")) 
    {  
       return 1;
    }
    if (function_exists("create_object", ob) != STDARMFILE )
    {
        keeper->command("say I only deal in armours and various smith components I'm afraid.");
        NF("");
        return 0;
    }
    return 1;
}
int
shop_hook_allow_buy(object ob)  
{
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }
    if (ob->id("bar"))
    {
       return 1;
    }
    if (function_exists("create_object", ob) != STDARMFILE )
    {
        keeper->command("say I only deal in armours I'm afraid.");
        NF("");
        return 0;
    }
    return 1;
}


