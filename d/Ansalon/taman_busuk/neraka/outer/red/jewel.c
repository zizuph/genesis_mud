#include "/d/Ansalon/common/defs.h";
#include "/d/Ansalon/taman_busuk/neraka/local.h";
#include "/sys/money.h"

inherit "/lib/trade";
inherit NOUTROOM;

void
create_room()
{
    set_long("You have entered a very clean, and well maintained "+
    "shop. The tables are set up in very neat and orderly ways. "+
    "The man table is to the north, and consisits of many large "+
    "black bags, and one smiling merchant. A poster is placed "+
    "behind him.\n");
    add_item("tables","There are many tables about made of oak.\n");
    add_item("table","The main table contains many black bags.\n");
    add_item("black bags","The black bags look like they contain "+
    "some sort of merchandise.\n");
    set_short("Jewel Store");
    add_cmd_item("poster","read","@@poster");
    add_item("poster","@@poster");
    add_exit(NOUTER+"red/r16","northeast","@@msg",-1);
    config_default_trade();
}

int
msg()
{
    write("You step out of this shop and back to the busy plaza.\n");
    return 0;
}

string
poster()
{
    return 
    "Welcome to Calpon's Jewelers!\n"+
    "Here, I have the following kinds of jewels for sale:\n"+
    "1. Silver rings        - 72cc\n"+
    "2. Gold rings          - 144cc\n"+
    "3. Gold bracelets.     - 216cc\n"+
    "4. Silver bracelets    - 144cc\n"+
    "5. Gold anklets        - 216cc\n"+
    "6. Silver anklets      - 144cc\n"+
    "7. Onyx pendants       - 288cc\n"+
    "8. Emerald necklaces   - 432cc\n"+
    "Just do buy #.\n"+
    "Numbers 1-6 can come with either pearl or onyx, so if you want "+
    "them with it, do 'buy # with (pearl/onyx). Added cost: (120/80)cc\n"; 
}

void
init()
{
    ::init();
    add_action("do_buy","buy");
}

int
do_buy(string str)
{
    int value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;
    string gem,str1,str2;
    object item;
    sscanf(str,"%s with %s",str1,str2);
    if(!str2)
        str1 = str;
    NF("Buy what?\n");
    if(!str1 && !str2)
        return 0;
    if(str1)
    {
        switch(str1)
        {
            case "1":
                item = clone_object(NOBJ+"ring_ns");
                item->set_metal_name("silver");
                item->add_prop(OBJ_I_VALUE,72);
            break;
            case "2":
                item = clone_object(NOBJ+"ring_ns");
                item->set_metal_name("gold");
                item->add_prop(OBJ_I_VALUE,144);
            break;
            case "3":
                item = clone_object(NOBJ+"bracelet_ns");
                item->set_metal_name("gold");
                item->add_prop(OBJ_I_VALUE,216);
            break;
            case "4":
                item = clone_object(NOBJ+"bracelet_ns");
                item->set_metal_name("silver");
                item->add_prop(OBJ_I_VALUE,144);
            break;
            case "5":
                item = clone_object(NOBJ+"anklet_ns");
                item->set_metal_name("gold");
                item->add_prop(OBJ_I_VALUE,216);
            break;
            case "6":
                item = clone_object(NOBJ+"anklet_ns");
                item->set_metal_name("silver");
                item->add_prop(OBJ_I_VALUE,144);
            break;
            case "7":
                item = clone_object(NOBJ+"pendant_ns");
                item->set_metal_name("silver");
                item->set_gem_name("onyx");
                item->add_prop(OBJ_I_VALUE,288);
            break;
            case "8":
                item = clone_object(NOBJ+"necklace_ns");
                item->set_metal_name("gold");
                item->set_gem_name("emerald");
                item->add_prop(OBJ_I_VALUE,432);
            break;
            default:
                NF("There is no such number:"+str1+"\n");
                return 0;
        }
    }
    value = item->query_prop(OBJ_I_VALUE);
    if(str2)
    {
        
        switch(str2)
        {
            case "pearl":
                item->set_gem_name("pearl");
                value += 120;
            break;
            case "onyx":
                item->set_gem_name("onyx");
                value += 80;
            break;
            default:
                NF("I don't have that kind of gem!\n");
                return 0;
        }
    }
    if(member_array(str1,({"7","8"})) != -1 && str2)
    {
        NF("Those already have gems in them, and those are the "+
           "only ones I have!\n");
        return 0;
    }
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
        return 0;
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the jeweler " +coin_pay_text+ ".\n");
    if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");
    if(item->move(TP) != 0)
    {
        write("You can't carry it.\n");
        item->move( E(TP) );
    }
    return 1;
}

