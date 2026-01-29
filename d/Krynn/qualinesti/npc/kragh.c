/* kragh.c
 * Kragh, the Daergar who is transporting good between Newports, Pax Tharkas
 * and Thorbardin.  
 *
 * Blizzard, 30/05/2003
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>
#include "../local.h"

inherit M_FILE
inherit "/d/Genesis/lib/shop";
inherit "/lib/store_support";
inherit "/std/act/action";

#define        MAXLIST             30
#define        LOST_SCOUTS         "_lost_scouts"
#define        ELF_CAMP_QUEST      "_elf_camp_quest"
#define        SPOKEN_WITH_DWARF   "_spoken_with_dwarf"

public void    arm_me();
public void    do_answer(string what, object who);
public string  ask_dracs();

object         *myownstuff = ({ });

void
add_own_stuff(object ob)
{
    if ( !myownstuff )
        myownstuff = ({ });
    
    myownstuff += ({ ob });
}

public void
create_merchant()
{
    set_name("kragh");
    add_name("merchant");
    set_living_name("kragh");
    set_race_name("dwarf");
    set_title("Redhammer of Daergar");
    set_long("This stocky black-bearded dwarf has a light-brown skin, gray " +
        "hair and smoothy cheeks. From beneath his helmet his deep brown " +
        "eyes peer out watchfully. He looks for a merchant, but you have " +
        "no doubts that, as every Daergar, he is also a skilled and cruel " +
        "warrior.\n"); 
    set_adj("stocky");
    add_adj("black-bearded");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(0);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_HEIGHT, 140);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    set_stats(({ 140, 120, 160, 110, 130, 150 }));
    set_skill(SS_TRADING, 90);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 70);
    
    set_alignment(-500);
    set_knight_prestige(100);

    set_act_time(6);
    add_act("say Curse those hill dwarves!");
    add_act("say Hey ye! Wanna trade?");
    add_act("emote watches the road silently.");
    add_act("emote paces around, mumbling something under his nose.");
    add_act("say Those dracs seem to be lookin' for something.");
    add_act("emote searches the wagon for something.");
    add_act("say I hope those elves think before they shoot someone!");
    add_act("say Traveling this road is dangerous. Ye may get shot " +
        "by elves or captured by dracs!");
        
    set_cact_time(3);
    add_cact("glare");
    add_cact("say By Reorx! I'll smash you!");
    add_cact("say Attacking me was you last mistake!");
    add_cact("emote roars madly.");
    
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({ "draconians", "about draconians", "dracs", "drac" }), 
        VBFC_ME("ask_dracs"), 1);
    add_ask(({ "Qualinesti", "about Qualinesti", "qualinesti", 
        "about qualinesti" }), "say Hmph. I don't like that forest! There " +
        "are too many elves in there!", 1);
    add_ask(({ "forest", "about forest" }), "say Ye mean Qualinesti? " +
        "Are ye blind?! It's to the northwest!", 1);
    add_ask(({ "elf", "elves" }), "say Elves! It is strange they have " +
        "not fled yet! But dracs do their job!", 1);
    add_ask(({"Qualinost", "qualinost", "about Qualinost", "about qualinost"}),        
        "say Hmph! Who cares about that city! It's not even half as " +
        "great as Thorbardin!", 1);
    add_ask(({ "task", "job", "help" }),
        "say I dont need yer help! Ye wanna trade or not?!", 1);
    add_ask(({ "Thorbardin", "thorbardin" }), VBFC_ME("thorbardin_ask"), 1);
    
    seteuid(getuid(TO));
    arm_me();
}

public void
create_krynn_monster()
{
    create_merchant();
    enable_reset(100);
    config_default_trade();
    set_max_values(20, 10);
    set_store_room(file_name(TO));
    set_money_greed_buy(120);
    set_money_greed_sell(120);
}
    
public string
default_answer()
{
    command("say What ye mean?! Speak up or get lost!");
    command("say ...unless ye got somethin' to sell.");
    return "";
}

void
thorbardin_ask()
{
    command("say Ignorant!");
    command("smirk");
}

public string
ask_dracs()
{
    set_alarm(1.0, 0.0, &do_answer("dracs", TP));
    return "";
}

public void
do_answer(string what, object who)
{
    if ( !objectp(who) || E(who) != E(TO) )
        return;

    if ( who->query_prop(SPOKEN_WITH_DWARF) )
    {
        TO->command("emote refuses to speak with you.");
        say(QCTNAME(TO) + " refuses to speak with " + QTNAME(who) + ".\n");
        return;
    }
    
    if ( !who->query_prop(ELF_CAMP_QUEST) && !who->query_prop(LOST_SCOUTS) )
    {
        TO->command("say There are many draconians in this area, so " +
            "watch yer back if ye wanna stay alive!");
        return;
    }
    
    switch(what)
    {
    case "dracs":
        TO->command("say Hmm, why are ye interested in that?");
        who->catch_msg(QCTNAME(TO) + " peers at you suspiciously.\n");
        say(QCTNAME(TO) + " peers at " + QTNAME(who) + "suspiciously.\n", who);
        
        set_alarm(2.0, 0.0, &do_answer("dracs1", who));
    break;
    case "dracs1":
        TO->command("say Maybe I saw them, maybe not!");
        TO->command("emote grunts.");
        set_alarm(2.0, 0.0, &do_answer("dracs2", who));
    break;
    case "dracs2":
        TO->command("say There is a lot of them in this area these days. " +
            "It seems they are lookin' for something.");
        set_alarm(3.0, 0.0, &do_answer("dracs3", who));
    break;
    case "dracs3":
        TO->command("say I passed by one group of dracs yesterday - just " +
            "as they left the forest, not so far to the north from here, " +
            "and headed towards Pax Tharkas.");
        TO->command("say They were leadin' an elf with them. I was " +
            "wonderin' why he was still alive.");
        set_alarm(5.0, 0.0, &do_answer("dracs4", who));
    break;
    case "dracs4":
        TO->command("emote tugs his beard.");
        TO->command("say Strange, but it was not my business to ask!");
        set_alarm(2.0, 0.0, &do_answer("dracs5", who));  
    break;
    case "dracs5":
        TO->command("say And I have my own business to do as well! " +
            "Leave me now!");
        TO->command("emote gestures and you understand the conversation " +
            "is over.");
        
        if ( TP->query_prop(LOST_SCOUTS) || TP->query_prop(ELF_CAMP_QUEST) )
        {
            if ( !TP->query_prop(SPOKEN_WITH_DWARF) )
                 TP->add_prop(SPOKEN_WITH_DWARF, 1);
        }
        
    break;
    }    
}
      
int
query_option(int opt)
{
    if ( opt == OPT_UNARMED_OFF )
        return 1;
}

public void
arm_me()
{    
    object tmp;
    int    i;
    
    tmp = clone_object( ARM + "dwarven_chain" );
    tmp->move(TO, 1);
    add_own_stuff(tmp);
    
    tmp = clone_object( ARM + "dwarven_boots" );
    tmp->move(TO, 1);
    add_own_stuff(tmp);

    tmp = clone_object( ARM + "leggings" );
    tmp->move(TO, 1);
    add_own_stuff(tmp);

    tmp = clone_object( ARM + "hard_helm" );
    tmp->move(TO, 1);
    add_own_stuff(tmp);
    
    tmp = clone_object( WEP + "hammer" );
    tmp->move(TO, 1);
    add_own_stuff(tmp);
    
    command("wield all");
    command("wear all");
}

void
react_attack(object attacker)
{
    TO->command("say So you wanna fight?! Die then!");
    TO->command("laugh");
}

void
attacked_by(object attacker)
{
    ::attacked_by();
    
    set_alarm(1.0, 0.0, &react_attack(attacker));    
}

void
reset_merchant()
{
    (all_inventory(TO) - myownstuff)->remove_object();
    myownstuff -= ({ 0 });
}

nomask void
reset_monster()
{
    reset_merchant();
    ::reset_monster();
}

void
init_living()
{
    init_shop();
    ::init_living();
}

int
do_list(string str)
{
    object *item_arr;
    int i, max, price, *arr;

    call_other(store_room, "load_me");

    item_arr = all_inventory(find_object(store_room));
    item_arr -= myownstuff;

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    if (str == "weapons")
        item_arr = filter(item_arr, "weapon_filter", this_object());
    else if (str == "armours")
            item_arr = filter(item_arr, "armour_filter", this_object());
    else if (str)
	item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
	return shop_hook_list_no_match(str);
 
    max = MIN(MAXLIST, sizeof(item_arr));
    for (i = 0; i < max; i++)
    {
	price = query_buy_price(item_arr[i]);
	shop_hook_list_object(item_arr[i], price);
    }

    if (max < sizeof(item_arr))
    {
	write("There is something more in the wagon, but it is hidden " +
	    "too deep.\n");
    }

    return 1;
}

int
do_show(string str)
{
    object *item_arr;
    int i, *arr;

    call_other(store_room, "load_me");

    item_arr = all_inventory(find_object(store_room));
    item_arr -= myownstuff;

    if (!sizeof(item_arr))
    {
	shop_hook_list_empty_store(str);
	return 0;
    }

    item_arr = FIND_STR_IN_ARR(str, item_arr);

    if (sizeof(item_arr) < 1)
    {
	return shop_hook_list_no_match(str);
    }

    shop_hook_appraise_object(item_arr[0]);
    item_arr[0]->appraise_object();

    return 1;
}

int
do_buy(string str)
{
    object *item, store;
    string str1, str2, str3;

    if (!str || str =="")
    {
	notify_fail("Buy what?\n");
	return 0;
    }
 
    call_other(store_room, "load_me"); /* Make sure storeroom is loaded */

    /*  Did the player specify payment and change? */
    if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
    /* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        if (sscanf(str, "%s for %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str1, store);
    item -= myownstuff;

    if (!sizeof(item))
	return shop_hook_buy_no_match(str1);

    item = buy_it(item, str2, str3);
    if (sizeof(item))
    {   
        switch ( random(5) )
        {
        case 0:
            TO->command("say Ye! Just dont try to cheat me!");
	break;
	case 1:
	    TO->command("say Good choice!");
	    TO->command("emote grins dwarvishly.");
	break;
	case 2:
	    TO->command("say I really enjoy doin' business with ye!");
	break;
	case 3:
	    TO->command("say Deal!");
	break;
	case 4:
	    TO->command("say Ye will not regret that!");
	break;
        }
            
	return shop_hook_bought_items(item);
    }
    return 0; /* Player tried to buy a non buyable object. */
}

int
do_value(string str)
{
    object *item, store;
    int *arr, price, i, j, num, no_inv;

    if (!str || str =="")
    {
	notify_fail("Value what?");
	return 0;
    }

    num = sizeof(query_money_types());
    item = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(item))
	no_inv = 1;

    for (i = 0; i < sizeof(item); i++)
    {
	if (!::shop_hook_allow_sell(item[i]) ||
		!item[i]->query_prop(OBJ_I_VALUE) ||
		item[i]->query_prop(OBJ_M_NO_SELL)) 
	{
	    shop_hook_value_not_interesting(item[i]);
	    continue;
	}

	price = query_sell_price(item[i]);
	arr = give(price, this_player(), "", 1);
	shop_hook_value_held(item[i], text(arr[num .. 2 * num - 1]));
	j++;
    }

    call_other(store_room, "load_me");
    store = find_object(store_room);
    item = FIND_STR_IN_OBJECT(str, store);
    item -= myownstuff;

    if (!sizeof(item) && no_inv)
	return shop_hook_value_no_match(str);

    for (i = 0; i < sizeof(item); i++)
    {
	price = query_buy_price(item[i]);
	arr = split_values(price); /* A price with few coins possible */
	shop_hook_value_store(item[i], text(arr));
	j++;
    }	

    shop_hook_value_asking(str);
    if (j > 0)
	return 1;

    return 0;
}

int
shop_hook_allow_sell(object obj)
{
    int val = obj->query_prop(OBJ_I_VALUE);
    
    if ( !obj->query_prop(OBJ_M_NO_DROP) && !obj->query_prop(OBJ_M_NO_SELL) &&
        !obj->query_prop(OBJ_M_NO_GIVE) )
    {
        switch ( random(10) )
        {
        case 0:
            TO->command("say Deal!");
            TO->command("emote grins greedily.");
        break;
        case 1:
            TO->command("say Hmm, that's all I can pay ye for it!");
        break;
        case 2:
            TO->command("say Where did ye got it? It's hardly worthy " +
                "anythin'.");
            TO->command("emote grunts.");
        break;
        case 3:
            TO->command("say Ye lucky I am here! Otherwise ye'd have to " +
                "throw that thin' away!");
        break;
        case 4:
            TO->command("emote sighs greedily.");
        break;
        }
    }
    
    return 1;

    command("say I can't afford to buy " + LANG_THESHORT(obj) + ".");
    NF("");
    return 0;
}

void
do_die(object killer)
{
    if (query_hp() <= 0)
      reset_merchant();
    ::do_die(killer);
}
            