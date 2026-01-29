/* Skin Shop of Calathin
 * /d/Terel/calathin/skinshop.c
 * 
 *
 * Coded by Shinto, April 99
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"
#include "shop_check.c"


#define STORE_ROOM CALATHIN_DIR+ "sstore"
object door;


void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("Dardin's Skins and Furs");
    set_long(
      "You have entered Dardin's Skins and Furs. Furs, skins and pelts "+
      "of all kind cover all the walls. Several stuffed animals are "+
      "mounted around the room. There is a sign with instructions.\n");
    add_item(({"furs", "skins", "pelts"}), "They are everywhere.\n");
    add_item(({"stuffed animals", "animals", "dead animals"}), 
            "Several dead animals look to have been treated by a " +
            "taxidermist and put on display.\n");
    set_shop_name("Dardin's Skins and Furs");
    set_keeper_file(CALATHIN_DIR + "npc/dardin");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/skin_door");
    door->move(TO);

}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy skin for gold and get copper back\n"
      + "    buy skin for gold coins\n"
      + "    sell skin for copper coins\n"
      + "    sell all  - will let you sell all skins in your inventory.\n"
      + "    sell skin, sell second skin, sell skin 2, sell two skins\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all skins available in the store, the\n"
      + "    correct syntax is: 'list skins' also works.\n"
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
    if(ob->id("skin"))
        return 1;
    keeper->command("say I only deal in pelts, skins, and furs.");
    NF("");
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
    if(ob->id("skin"))
        return 1;
    keeper->command("say I only deal in pelts, skins, and furs.");
    NF("");
    return 0;
}
