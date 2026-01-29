#include "/d/Ansalon/common/defs.h";
#include "/d/Ansalon/taman_busuk/neraka/local.h";
#include "/sys/money.h"
#include <macros.h>

inherit "/lib/trade";
inherit NOUTROOM;

void
create_room()
{
    set_long("You now find yourself in a sooty, hot wooden shack. "+
    "in the corner, you see an anvil and a forge. The heat here "+
    "is almost unbearable. There is a weaponsmith here, working "+
    "on some sword.  A sign is on the wall.\n");
    
    add_item("weaponsmith","A large burly man with a black beard.\n");
    add_item("anvil","A large iron anvil wich is covered with black "+
    "soot.\n");
    add_item("forge","The forge burns hot!\n");
    add_cmd_item("sign","read","@@sign@@");
    add_item("sign","Its a nice sign.\n");
    add_exit(NOUTER+"red/r13","northwest","@@msg",-1);
    config_default_trade();
    add_event("The weaponsmith bangs on the anvil.\n");
    add_event("The weaponsmith checks on the forge.\n");
    add_event("The fire crackles and burns in the forge.\n");
    add_event("Steam begins to rise from the forge.\n");
    add_event("A cool blast of wind seeps out of the doorway.\n");
    set_event_time(30.0,45.0);
    set_events_on(1);
}

int
msg()
{
    write("You step out of this hot house and into the cool mountain air.\n");
    return 0;
}

string
sign()
{
    return 
    "        THE BLACKIRON WEAPONSMITH OF NERAKA      \n"+
    "I have the following for sale:\n"+
    "1. A dagger     - 72cc\n"+
    "2. A longsword  - 288cc\n"+
    "3. A shortsword - 144cc\n"+
    "4. A pike       - 432cc\n"+
    "5. A halberd    - 576cc\n"+
    "Just do 'buy #' to buy something.\n";
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
    object item;
    NF("Buy what?\n");
    if(!str)
        return 0;
    switch(str)
    {
        case "1":
            item = clone_object(NWEP+"gen_dagger");
        break;
        case "2":
            item = clone_object(NWEP+"gen_lsword");
        break;
        case "3":
            item = clone_object(NWEP+"gen_ssword");
        break;
        case "4":
            item = clone_object(NWEP+"gen_pike");
        break;
        case "5":
            item = clone_object(NWEP+"gen_halberd");
        break;
        default:
            NF("There is no such number: "+str+"\n");
            return 0;
    }
    value = item->query_prop(OBJ_I_VALUE);
    if (sizeof(money_arr = pay(value, TP, pay_type, 0, 0, get_type)) == 1)
        return 0;
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the weaponsmith " +coin_pay_text+ ".\n");
    if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");
    tell_room(TO,"The weaponsmith goes back and gets a "+
    item->short()+" from his stock.\n");
    say(QCTNAME(TP)+" is given the "+item->short()+".\n");
    write("You get your "+item->short()+".\n");
    if(item->move(TP) != 0)
    {
        write("You can't carry it.\n");
        item->move( E(TP) );
    }
    return 1;
}

