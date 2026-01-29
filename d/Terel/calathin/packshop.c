/* Pack Shop of Calathin
 * /d/Terel/calathin/packshop.c
 * 
 *
 * Coded by Shinto, April 99
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <stdproperties.h>
#include "shop_check.c"


#define STORE_ROOM CALATHIN_DIR+ "pstore"
object door;

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Bag of Holding Pack Shop");
    set_long(
      "You have entered the Bag of Holding Pack Shop. A number of bags, "+
      "sacks, and backpacks can be seen hanging from the rafters and "+
      "support beams of the shop. A large wooden table sits right in the "+
      "middle of the store, obviously a work area.\n");

    set_shop_name("Bag of Holding Pack Shop");
    set_keeper_file(CALATHIN_DIR + "npc/smitt");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/pack_door");
    door->move(TO);
    add_item(({"table","wooden table"}), "This is the work "+
        "table, used in the maintenance of various types of "+
       "packs and bags. It's made of worn wood and has a brown finish.\n");

}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy pack for gold and get copper back\n"
      + "    buy pack for gold coins\n"
      + "    sell pack for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn and wielded ones.\n"
      + "    sell pack, sell second pack, sell pack 2, sell two packs\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all packs available in the store, the\n"
      + "    correct syntax is: 'list packs' also works.\n"
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
    if(ob->id("pack") || ob->id("vial") || ob->id("pouch") || ob->id("jar") || ob->id("leather") || ob->id("pole"))
        return 1;
    NF("");
    keeper->command("say I only deal in sacks, pouches, backpacks and smith supplies.");
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
    if(ob->id("pack") || ob->id("vial") || ob->id("pouch") || ob->id("jar") || ob->id("leather") || ob->id("pole"))
        return 1;
    NF("");
    keeper->command("say I only deal in sacks, pouches, backpacks and the odd Smithy component. ");
    return 0;
}


