 /* Pack Shop of Calathin
 * /d/Terel/calathin/lampshop.c
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


#define STORE_ROOM CALATHIN_DIR+ "lstore"

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Magic Lamp, Lamp Shop");
    set_long(
      "You have entered the Magic Lamp, Lamp Shop. The walls are "+
      "covered with numerous lamps of all sorts of designs. A barrel "+
      "behind the counter holds a bunch of torches, ready for use. Flasks "+
      "full of oil are lined up on shelves along the back wall.\n");

    set_shop_name("The Magic Lamp, Lamp Shop");
    set_keeper_file(CALATHIN_DIR + "npc/naelan");
    set_hated_race(({"kender","goblin"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
	
    room_add_object(CALATHIN_DIR + "obj/lamp_door");

    add_item(({"table","wooden table"}), "This is the work "+
        "table, used in the maintenance of various types of "+
       "lamps and thatching of torches. "+
       "It's made of worn wood and has a brown finish.\n");
    add_item(({"shelf","shelves"}), "The shelves are stocked with "+
       "flasks of oil.\n");
    add_item(({"wall","walls"}), "The walls have lamps hanging from "+
       "every possible space.\n");
    add_item("barrel","A barrel behind the counter holds many torches.\n");

}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy lamp for gold and get copper back\n"
      + "    buy lamp for gold coins\n"
      + "    sell lamp for copper coins\n"
      + "    sell all  - will let you sell all items except for\n"
      + "                worn and wielded ones.\n"
      + "    sell lamp, sell second lamp, sell lamp 2, sell two lamps\n"
      + "                also works. You might want to change the verb to\n"
      + "                'value' or 'buy' too.\n"
      + "    If you want a list of all lamps available in the store, the\n"
      + "    correct syntax is: 'list lamps' also works.\n"
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
    if(ob->id("torch") || ob->id("flask") || ob->id("lamp") || ob->id("candle"))
        return 1;
    NF("");
    keeper->command("say I only deal in lamps, torches, and candles.");
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
    if(ob->id("torch") || ob->id("flask") || ob->id("lamp") || ob->id("candle"))
        return 1;
    NF("");
    keeper->command("say I only deal in lamps, torches, and candles.");
    return 0;
}

