/* Weapon shop of Last
 * /d/Terel/last/wepshop.c
 * 
 * Coded by Shinto, March 98
 * Modifications:
 *    Lilith Feb 2022: added inside prop
 *
 */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"


#define STORE_ROOM "/d/Terel/last/wstore"
#define STDWEPFILE "/std/weapon"

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Last Weapons Shop");
    set_long(BS(
      "You are in the Last weapon shop. "+
      "Well kept and quite clean, the owner must have some"+
      " time on his hands. All the weapons on display are "+
      "polished and shining, ready to be sold. There is a sign"+
      " with directions on it.\n"));
    set_shop_name("Last Weapons Shoppe");
    set_keeper_file("/d/Terel/last/npc/lanc");
    set_hated_race(({"goblin"}));
    set_suspected_race(({"gnome","hobbit"}));
    set_favoured_race(({"human","dwarf","elf"})); 
    add_item(({"door"}), BSN(
        "This door leads into the storeroom."));
	add_prop(ROOM_S_MAP_FILE, "town_last.txt");
    add_exit(LAST_DIR+"lroad8","north",0);
	INSIDE;
}
int
shop_hook_allow_sell(object ob)  
{
    if (function_exists("create_object", ob) != STDWEPFILE )
    {
        keeper->command("say I'm only interested in weapons, " +
            "my apologies. ");
        NF("");
        return 0;
    }

    return 1;
}

int
shop_hook_allow_buy(object ob)  
{
    if(TP->query_race_name() == "goblin")
    {
        keeper->command("say I don't do business with goblins!");
        NF("");
        return 0;
    }
    return 1;
}


