inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
#define SHDIR(ob) "/d/Kalad/common/guilds/shadow_walkers/ob"


void
create_monster()
{
    set_name("merchant");
    set_adj("dark-cloaked");
    add_adj("thief");
    set_short("dark-cloaked thief merchant");
    set_long("A figure cloaked in black robes stands before you. "+
    "He seems to be offering some things to sell. You can ask "+
    "him about his wares if you are interested.\n");
    set_stats(({100,100,100,100,100,100}));
    set_skill(SS_DEFENCE,100);
    set_act_time(7);
    add_act("hmm");
    add_act("ponder");
    add_act("emote ties up his purse.");
    add_act("emote checks his coins.");
    add_act("say Would you like to see my wares?");
    set_default_answer("The "+short()+" says: I do not understand what "+
    "you mean.\n");
    add_ask("wares","I have the following items to sell:\n"+
    "cloak   --  A black thief cloak, for 9 silver\n"+
    "vest    --  A black thief vest, for 9 silver\n"+
    "pants   --  A pair of black thief pants, for 9 silver\n"+
    "boots   --  A pair of black thief boots, for 100 copper\n"+
    "claws   --  A pair of climbing claws, for 8 gold\n"+
    "paint   --  A tin of black paint to aid you in hiding, for 1 platinum\n"+
    "sheath  --  A dagger sheath, for 1 gold\n"+
    "backpack -- A large black backpack, for 2 gold\n"+
    "lbag    --  A large bag, for 1 gold\n"+
    "sbag    --  A small bag, for 5 silver\n"+
    "gloves  --  Special thief gloves, to aid in thievery, for 5 gold\n"+
    "dbomb   --  A special dust bomb, to aid in quick getaways, for 1 gold\n"+
    "mpaint  --  A little bottle of paint to write messages, for 6 silver\n"+
    "quiver  --  A arrow or quarrel quiver, for 6 silver\n"+
    "arrow   --  A fine arrow, for just 1 silver\n"+
    "quarrel --  A fine crossbow quarrel, for just 2 silver\n"+
/*
    "crossbow --  A powerful crossbow, for just 2 platinum\n"+
    "bow --  A short bow, for just 1 platinum\n"+
*/
    "Just 'buy <item>' to get it.\n");
    default_config_trade();
}

void
init_living()
{
    ::init_living();
    AA(do_buy,buy);
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, price, num,iprice;
    switch(str)
    {
        case "quiver":
        item = clone_object(SHDIR(shad_quiver));
        iprice = 72;
        break; 
        case "arrow":
        item = clone_object(SHDIR(shad_arrow));
        iprice = 12;
        break;
        case "quarrel":
        item = clone_object(SHDIR(shad_quarrel));
        iprice = 24;
        break;
/*
    case "crossbow":
    item = clone_object(SHDIR(shad_crossbow));
    iprice = 3456;
    break;
    case "bow":
    item = clone_object(SHDIR(short_bow));
    iprice = 1728;
    break;
*/
        case "dbomb":
        item = clone_object(SHDIR(dust_bomb));
        iprice = 144;
        break;
        case "gloves":
        item = clone_object(SHDIR(thief_gloves));
        iprice = 720;
        break;
        case "claws":
        item = clone_object(SHDIR(cat_claws));
        iprice = 1152;
        break;
        case "mpaint":
        item = clone_object(SHDIR(paint_bottle));
        iprice = 72;
        break;
        case "backpack":
        item = clone_object(SHDIR(thief_backpack));
        iprice = 288;
        break;
        case "lbag":
        item = clone_object(SHDIR(thief_lbag));
        iprice = 144;
        break;
        case "sbag":
        item = clone_object(SHDIR(thief_sbag));
        iprice = 60;
        break;
        case "cloak":
        item = clone_object(SHDIR(thief_cloak));
        iprice = 108;
        break;
        case "vest":
        item = clone_object(SHDIR(thief_vest));
        iprice = 108;
        break;
        case "pants":
        item = clone_object(SHDIR(thief_pants));
        iprice = 108;
        break;
        case "boots":
        item = clone_object(SHDIR(thief_boots));
        iprice = 100;
        break;
        case "sheath":
        item = clone_object(SHDIR(dscab));
        iprice = 144;
        break;
        case "paint":
        item = clone_object(SHDIR(paint_cont));
        iprice = 1728;
        break;
        default:
        NF("I don't have any items named "+str+".\n");
        return 0;
    }
    price = iprice;
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("You get a "+item->short()+".\n");
    say(QCTNAME(TP)+" gets a "+item->short()+".\n");
    if(item->move(TP))
    {
        write("Its too heavy, and you drop it.\n");
        item->move(E(TP));
    }
    return 1;
}
