/* Weapon shop of Calathin
 * /d/Terel/calathin/wepshop.c
 * 
 * Coded by Shinto, March 98
  */

#pragma strict_types

inherit "/d/Terel/std/shop";
#include "/d/Terel/include/Terel.h"
#include "shop_check.c"


#define STORE_ROOM "/d/Terel/calathin/wstore"
#define STDWEPFILE "/std/weapon"
object door;

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("Amaylin's Quality Weapon Shop");
    set_long(
      "You are in Amaylin's Quality Weapon Shop. "+
      "The shop is well tended and sports many different "+
      "types of weapons along the north, west, and east walls. "+
      "A large work desk stands against the west wall, where "+
      "the weapons are sharpened and tended to.\n");
    set_shop_name("Amaylin's Quality Weapon Shop");
    set_keeper_file("/d/Terel/calathin/npc/amaylin");
    set_hated_race(({"kender"}));
    set_suspected_race(({"gnome","hobbit","dwarf"}));
    set_favoured_race(({"human","half-elf","elf"})); 
    door = clone_object(CALATHIN_DIR + "obj/wep_door");
    door->move(TO);
    add_item("desk","The desk is made of study wood. Weapons on laid "+
        "across it to be sharpened and tended to.\n");
}
int
shop_hook_allow_sell(object ob)  
{
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }

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
    if(race_invis_enemy())
    {
        NF("");
        return 0;
    }

    if (function_exists("create_object", ob) != STDWEPFILE )
    {
        keeper->command("say I'm only interested in weapons, " +
            "my apologies. ");
        NF("");
        return 0;
    }

    return 1;
}

