/* The arms shop of Minas Tirith

*/
#pragma strict_types

inherit "/d/Gondor/common/lib/shop";
inherit "/d/Gondor/minas/lib/minas_fof.c";

#include "/d/Gondor/defs.h"

#define STORE_ROOM "/d/Gondor/minas/rooms/armsstore"  /* Where the items are stored */

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Minas Tirith Arms Shoppe");
    set_long(BS(
      "You are in the Minas Tirith Arms Shoppe. "+
      "The place is filled with armours and weapons, probably brought "+
      "here from distant lands. There is a poster on the wall, and " +
      "the exit to the street is north.\n"));
    set_shop_name("Minas Tirith Arms Shoppe");
    set_keeper_file(MINAS_DIR+"npc/merdol");
    set_no_sell_prop(({GONDOR_M_ROHIRRIM_NO_SELL,
                         GONDOR_M_TIRITH_NO_SELL}));
    set_hated_race(({"goblin"}));
    set_suspected_race(({"gnome","elf"}));
    set_favoured_race(({"human","dwarf"})); 
    add_item(({"door"}), BSN(
        "The door is probably leading into the storeroom of the "+
        "shop. The door is standing open, but the shop keeper " +
        "probably would not be amused if you tried to go there. "));
    add_exit(MINAS_DIR+"n3crc2", "north", 0,0);
}

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x) && !armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n"+
               "The shopkeeper says: I do not trade in anything but weapons and armours!\n";
    else
        return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
  keeper->command("eyebrow");
  keeper->command("say Where did you get this "+ob->short()+"?");
  if (ob->query_prop(GONDOR_M_ROHIRRIM_NO_SELL))
    {
      keeper->command("say This was crafted by our allies, the Rohirrim!");
      keeper->command("say You must have stolen it....or even worse!");
      keeper->command("say Get out, before I call the guards on you!");
    }
  else if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    {
      keeper->command("say This is equipment from the Gondorian armies!");
      keeper->command("say You are not supposed to be carrying this,");
      keeper->command("say you must have stolen it...or even worse!");
      keeper->command("say Leave! Or I call the guards!");
    }
}

int
query_shop_no_business(mixed pl)
{
    if (query_friend_or_foe(pl) < 0)
    {
        NF("");
        return 1;
    }
    return 0;
}

