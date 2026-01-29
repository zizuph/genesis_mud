/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/werners.c
 * Purpose    : This is the lich who sells and buys herbs, as well as jars and viles.
 * Located    : ~khiraa/temple/rooms/temple_study
 * Created By : Sarr 26.Mar.97
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/lib/trade";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#define NUM sizeof(MONEY_TYPES)

#pragma save_binary

/* The lich who sells vials, jars and herbpouches */

void
create_monster()
{
    ::create_monster();
    set_name("werners");
    set_adj("eerie");
    add_adj("hooded");
    add_name("lich");
    set_short("eerie hooded lich");
    set_long("This lich looks very ghostly. His glowing red eyes "+
    "blaze brightly from within his hood. He is sitting on a large "+
    "chest, and seems to be selling "+
    "items of intrest. You could ask him 'items' if you wanted to "+
    "know what.\n");
    add_prop(LIVE_I_UNDEAD,100);
    set_stats(({100,100,100,100,100,100}));
    set_alignment(-1000);
    set_title("the Fallen, Greater Necromancer of the Khiraa");
    add_prop(LIVE_I_SEE_DARK,50);
    set_skill(SS_DEFENCE,100);
    set_default_answer("The "+short()+" says: Would you like to "+
    "see my items?\n");
    add_ask("items","I have the following items to sell:\n"+
    "vial      -- A vial for potions, 1 gold\n"+
    "jar       -- A jar for herbs, 4 silver\n"+
    "herbpouch -- A pouch for herbs, 2 silver\n"+
    "blood vial -- To contain blood, 1 copper\n"+
    "mortar    -- A mortar to create potions, 1 platinum\n"+
    "egg       -- An imp egg, to summon forth as a carrier, 7 gold\n"+
    "stones    -- Unholy stones, 1 gold\n"+
    "lantern   -- For light, 2 gold\n"+
    "candle    -- For the lantern, 1 gold\n\n"+
    "I also have a number or herbs in my chest.\n"+
    "If you would like to look at them, 'list' \n"+
    "would be the command to enter. I am also \n"+
    "intrested in gaining more, so you may 'sell'\n"+
    "me some if you like.\n");
    default_config_trade();
}

int
do_check(string str)
{
    string the_list,*herbs;
    mapping temp,herblist;
    int i;
    temp = restore_map(KHIRAA_DIR(log/buy_log));
    herblist = temp[str];
    if(!str)
    {
        the_list = "I have entries for these people:\n";
        herbs = m_indexes(temp);
        for(i=0;i<sizeof(herbs);i++)
            the_list += C(herbs[i])+"\n";
        TP->more(the_list,0);
        return 1;
    }
    if(!mappingp(herblist))
    {
        write("There is no entry for that person.\n");
        return 1;
    }
    the_list = "This is my entry log for "+C(str)+":\n";
    herbs = m_indexes(herblist);
    for(i=0;i<sizeof(herbs);i++)
    {
        the_list += herbs[i]+" : "+herblist[herbs[i]]+"\n";
    }
    the_list += 
    "Positive indicates the person has sold more than bought.\n"+
    "Negative indicates the person has bought more than sold.\n"+
    "Penned by The Fallen.\n";

    TP->more(the_list,0);
    return 1;
}

void
init_living()
{
    ::init_living();
    AA(do_buy,buy);
    // AA(do_check,logcheck);
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, price, num,iprice;
    switch(str)
    {
        case "lantern":
        item = clone_object(KHIRAA_DIR(temple/obj/jack_lamp));
        iprice = 288;
        break;
        case "candle":
        item = clone_object(KHIRAA_DIR(temple/obj/candle));
        iprice = 144;
        break;
        case "stones":
        item = clone_object(KHIRAA_DIR(temple/obj/unholy_stones));
        iprice = 144;
        break;
        case "mortar":
        item = clone_object(LP_DIR(obj/mortar));
        iprice = 1728;
        break;
        case "egg":
        item = clone_object(KHIRAA_DIR(temple/obj/demon_egg));
        iprice = 1008;
        break;
        case "vial":
        item = clone_object(LP_DIR(obj/vial));
        iprice = 144;
        break;
        case "jar":
        item = clone_object(LP_DIR(obj/jar));
        iprice = 48;
        break;
        case "herbpouch":
        item = clone_object(LP_DIR(obj/herbpouch));
        iprice = 24;
        break;
        case "blood vial":
        item = clone_object(KHIRAA_DIR(temple/obj/blood_vial));
        iprice = 1;
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