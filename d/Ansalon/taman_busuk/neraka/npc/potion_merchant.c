/* Ashlar, 10 May 97 - A potion merchant in the blue quarter */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit "/lib/trade";

void
create_krynn_monster()
{
    set_name("buzlik");
    set_race_name("goblin");
    set_adj("short");
    set_long("This goblin is most likely the owner of the shop. He is " +
        "short, even for a goblin. His hands are stained, probably from " +
        "making his potions.\n");
    add_ask(({"potion","potions","wares"}),VBFC_ME("return_potions"));
    add_ask("love potion",VBFC_ME("return_love_potion"));
    set_default_answer("The "+short()+" says: What was that?!\n");
    set_stats(({120,80,130,70,80,92}));
    set_introduce(1);
    set_title("the Potion Merchant");
    set_act_time(3);
    add_act("say I got der potions you need.");
    add_act("say If you interested in a potion, just ask.");
    add_act("say Best prices!");
    set_cact_time(1);
    add_cact("shout Scum!");
    add_cact("say You will pay for this dearly!");
    add_cact("say Get out of here!");
    config_default_trade();
}

/*
void
arm_me()
{
    object arm, wep;
    seteuid(getuid(TO));
    arm = clone_object(NARM+"dwarf_cloak");
    arm->move(TO);
    arm = clone_object(NARM+"dwarf_lplate");
    arm->move(TO);
    wep = clone_object(NWEP+"dwarf_axe");
    wep->move(TO);
    command("wear all");
    command("wield all");
}
*/

string
return_potions()
{
	return "None yet!\n";
	/*
    return "The "+short()+" says: I have the following for sale:\n"+
    "1. An emerald studded platinum bracelet     190cc\n"+
    "2. A golden ring with a diamond             200cc\n"+
    "3. A silver ruby pendant                    180cc\n"+
    "4. A steel opal dragon medallion(magic!)    250cc\n"+
    "Just do: buy #\n";
    */
}

/*
void
init_living()
{
    add_action("do_buy","buy");
    ::init_living();
}


int
do_buy(string str)
{
    int int_str, value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;
    object item;
    switch(str)
    {
        case "1":
            item = clone_object(NOBJ+"bracelet_ns.c");
            item->set_metal_name("platinum");
            item->set_gem_name("emerald");
            value = 190;
        break;
        case "2":
            item = clone_object(NOBJ+"ring_ns.c");
            item->set_metal_name("gold");
            item->set_gem_name("diamond");
            value = 200;
        break;
        case "3":
            item = clone_object(NOBJ+"pendant_ns.c");
            item->set_metal_name("silver");
            item->set_gem_name("ruby");
            value = 180;
        break;
        case "4":
            item = clone_object(NOBJ+"dmedallion_ns.c");
            item->set_metal_name("steel");
            item->set_gem_name("opal");
            value = 250;
        break;
        default:
            NF("I don't have that number item for sale.\n");
            return 0;
    }
    item->add_prop(OBJ_I_VALUE,value);        
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
        return 0;
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the smith " +coin_pay_text+ ".\n");
    if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");
    if(item->move(TP))
    {
        write("You get your "+item->short()+", but its too heavy, and drop it.\n");
        item->move(E(TP));
        return 1;
    }
    write("You get your "+item->short()+".\n");
    if(str == "4")
        command("say That, my friend, brings good luck!");
    return 1;
}
*/
