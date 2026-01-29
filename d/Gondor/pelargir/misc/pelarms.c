/* 
	The arms shop of Pelargir

*/

inherit "/d/Gondor/common/lib/shop";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/defs.h"

#define STORE_ROOM "/d/Gondor/pelargir/misc/pelarmstor"  /* item loc. */

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Arms shop of Pelargir");
    set_long(BSN(
       "You are in the weapons and armour shop of Pelargir. "+
       "People from all over Gondor, and even some from beyond the Sea "+
       "to the south, bring their equipment here to sell, sometimes "+
       "resulting in quite a variety."));
    set_shop_name("Arms Shop of Pelargir");
    set_keeper_file(PELAR_DIR + "npc/bagda");
    set_no_sell_prop(({GONDOR_M_TIRITH_NO_SELL}));
    set_hated_race(({"goblin"}));
    set_suspected_race(({"elf", "dwarf", }));
    set_favoured_race(({"human",})); 

    add_exit(PELAR_DIR + "streets/plaza","southeast",0);
}

mixed
shop_hook_filter_sell(object x)
{
  if (!weapon_filter(x) && !armour_filter(x))
    return "The shopkeeper says: I do not want your "+ x->short() + "!\n"+
     "The shopkeeper says: All I trade in are weapons and armours!\n";
  else
    return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("eyebrow");
    keeper->command("say Where did you get this "+ob->short()+"?");

    if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    {
        keeper->command("say This is equipment from the Gondorian armies!");
        keeper->command("say You are not supposed to be carrying this,");
        keeper->command("say you must have stolen it...or even worse!");
        keeper->command("say Leave! Or I call the guards!");
    }
}

void
fix_keeper()
{
    keeper = clone_object(keeper_file);
    // We want to call arm_me() in the keeper from the outside.
    keeper->arm_me();
    keeper->move(TO);
}

