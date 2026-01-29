// file name: /d/Avenir/common/dead/mon/bogl_cook.c
// creator(s): Lilith June 2021
// last update:
// purpose: goblin cook for the BOGL encampment
//          serves up the fish dishes from the bazaar
// note:   
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster.c";
inherit "/lib/trade";
#include <language.h>
#include <macros.h>
#include <money.h>
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#define STAND_DIR "/d/Avenir/common/bazaar/Obj/food/"
#define NUM sizeof(MONEY_TYPES)
#define BOBJ "/d/Avenir/common/bazaar/Obj/"
#define ZOBJ "/d/Avenir/common/city/zigg/obj/"


string pay_type, get_type, coin_pay_text, coin_get_text;
int *money_arr;
int test;


void
equip_me()
{
	
    seteuid(getuid());

    clone_object(ZOBJ+"soap")->move(TO,1);
    add_armour(BOBJ+"worn/apron");
    add_weapon(BOBJ+"wield/c_knife");

}
string 
my_long()
{
	string str;
    str = CAP(HE(TO)) +" is a "+query_adj()	+" "+ query_gender_string() 
	    + " goblin who seems to be "
	    + query_exp_title() +" in size.\n";
    str += CAP(HE(TO)) +" is a proud member of B.O.G.L. and she is a cook "
	    + "for this tribe.\n" 
		+ CAP(HIS(TO)) +" hands are covered in stains and burns from "
		+ "preparing food.\n"
        + CAP(HE(TO)) +" appears to be remarkably even-tempered for a goblin.\n"
		+ CAP(HE(TO)) +" seems to take pride in "+ HIS(TO) +" horns, "
		+"which are painted purple.\n"
		+ CAP(HE(TO)) +" has a smile on "+HIS(TO)+" face, showing clean fangs.\n"
		+ CAP(HIS(TO)) +" eyes are dark, kind, and honest.\n"
		+ CAP(HIS(TO)) +" skin is light brown and surprisingly clean for a goblin.\n";
    return str;
}	
	
public void
create_monster(void)
{

    string str = one_of_list(({"cooking"}));

    set_adj(str);
	set_name("cook");
    add_name("bogl", "_Avenir_BOGL_goblin");
    set_race_name("goblin"); 
	  set_gender(G_FEMALE);
    set_short(str +" "+ query_gender_string() +" goblin");
    set_pshort(str + " goblins");
    set_long(my_long);
    //Thick skinned little sucker.
    set_all_hitloc_unarmed(25);
    default_config_npc(random(40) + 40);
	set_skill(SS_DEFENCE, 25);
    set_skill(SS_UNARM_COMBAT, 25);
	set_act_time(60);
	add_act("soapbubble");
	add_act("soapwash");
	add_act("rub lotion");
	add_act("eat food");
	add_act("itch back");
	add_act("emote hums a little melody.");
	add_act("emote sweeps the floor.");
	add_act("emote picks a bone up off the ground.");
	add_act("emote fillets a fish.");
	add_act("sigh content");
	add_act("boggle");
	add_act("nod under");
    set_chat_time(20);
	add_chat("I like my job. I never go hungry since I'm a cook.");
	add_chat("I've got food for sale if you want any.");
	add_chat("Hungry for some fish, are you? Ask me about my menu.");
	add_chat("Seafood is delicious and versitile. Please try my cooking.");
	add_chat("Eating seafood reduces our bloodlust and improves our body odor.");
	add_chat("Hizarbin showed us that a fish-based diet is best for goblins.");	
	add_chat("@@give_menu");
	add_chat("@@give_prices");   
	 add_ask(({"menu","help","food","fish","potato"}),
        "@@give_menu",1);
    add_ask(({"price","prices","cost","money","dish"}),
        "@@give_prices",1);

	set_default_answer(VBFC_ME("what_me"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_M_HAS_MONEY, 500);
    add_prop(CONT_I_HEIGHT,   90);
	add_prop(CONT_I_WEIGHT, 90000);

   config_default_trade();
   set_money_give_max(2000);
   set_money_give_out(({ 2000, 700, 50, 4}));
   set_money_give_reduce(({1,1,1,1}));

   seteuid(getuid(TO));

}

string
what_me()
{
	switch(random(7))
	{
		case 0:
			command("say Slow down. I don't understand you.");
			break;
		case 1:
			command("say I don't know these things you ask about.");
			break;
		case 2:
			command("emote shrugs.");
			break;
		case 3:
			command("say Please stop asking me questions, you are scaring me.");
			break;
		case 4:
			command("emote looks anxiously around.");
			break;
		case 5:
			command("say Ask someone else, please.");
			break;
		case 6:
			command("emote pretends not to hear.");
			break;
	}
	return "";
}


public int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;

    name = arg[0];
    num = arg[1];
    ob = arg[2];

    for (i = 0; i < 10; i++)
    {
        num--;
        file = STAND_DIR + name;
        drink = clone_object(file);
        drink->move(TO);
        if (num < 1)
            break;
    }

	command("give foods to "+ OB_NAME(ob));

    return 1;
}

/*
 * Function name: do_order
 * Description:   The buyer orders food
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
public int
do_order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    NF("Buy what?\n");
    if (!str)
        return 0;

    /* Has the player defined how payment will be done and what change to get
       back? */
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    if (num > 10)
    {
        set_alarm(1.5, 0.0, &command("say I cannot carry that much."));
        return 1;
    }

    switch(str1)
    {
        case "soup":
        case "soups":
        case "fish soup":
            name = "soup";
            price = num * 12;
            break;
        case "stew":
        case "stews":
        case "potato stew":
            name = "stew";
            price = num * 24;
            break;
        case "mollusks":
        case "mollusk":
        case "boiled mollusk":
            name = "mollusk";
            price = num * 48;;
            break;
        case "meal":
        case "meals":
        case "fish meal":
            name = "fish";
            price = num * 200;
            break;
        case "eel":
        case "fried eel":
        case "plate of fried eel":
            name = "eel";
            price = num * 530;
            break;
        default:
            command("say What is that?");
	    return 1;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
    {
        command("say No money - no food.");
        command("say Strangers have to pay.");
        return 1;
    }

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
        write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    return move_item(({name, num, TP}));
}
 
public string
give_menu(void)
{
    command("emote takes a deep breath.");
    command("emote exhales: We got the hot fish soup...the potato stew..."+
        "the boiled mollusk...the fish meal and the plate of fried eel.");
    return "Try ordering something. You don't regret it.";
}
public string
give_prices(void)
{
    command("smile joy");
    command("emote I keep my prices as low as I can. ");
    command("emote announces: Twelve coppers for the soup...Twentyfour "+
        "for the stew...Fortyeight for the mollusk. The fish meal is "+
        "twohundred...The eel is fivehundredandthirty");
    return "All are tasty, filing, and healthy."; 
}

public void
init_living(void)
{
    ::init_living();
    add_action(do_order,"buy");
    add_action(do_order,"order");
}
