/* the recruiter of the thieves, by Aridor 12/13/95*/

#include "../guild.h"
inherit M_FILE
inherit "/d/Genesis/lib/shop";
inherit "/lib/store_support";

#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <money.h>
#include <language.h>
#define SCARF   "/d/Krynn/solamn/thief/obj/scarf3"
#define DUDGEON "/d/Krynn/solamn/thief/obj/dudgeon"
#define PANTS   "/d/Krynn/solamn/palan/obj/pants"
#define SHIRT   "/d/Krynn/solamn/palan/obj/lshirt"
#define TORCH   "/d/Krynn/solamn/thief/obj/torch"
#define MAXLIST 30

object waitfornod = 0;
object *myownstuff = ({});
void do_nod(object actor, string adverb);

void
equip_me()
{
    object obj;

    seteuid(getuid(TO));
    (obj = clone_object(SCARF))->move(TO);
    myownstuff += ({obj});
    (obj = clone_object(DUDGEON))->move(TO);
    myownstuff += ({obj});
    clone_object(CHALK_OBJ)->move(TO);
    (obj = clone_object(PANTS))->move(TO);
    myownstuff += ({obj});
    (obj = clone_object(SHIRT))->move(TO);
    myownstuff += ({obj});
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    (obj = MONEY_MAKE(100,"copper"))->move(TO);
    myownstuff += ({obj});
    (obj = MONEY_MAKE(50,"silver"))->move(TO);
    myownstuff += ({obj});
    (obj = MONEY_MAKE(3,"gold"))->move(TO);
    myownstuff += ({obj});
    command("wear all");
    command("wield all");
}

void
create_krynn_monster()
{
    set_name("finias");
    set_living_name("finias");
    add_name("recruiter");
    set_adj("long-legged");
    add_adj("olive-skinned");
    set_title("the Merchant");
    set_gender(0);
    set_long("This is a long-legged, olive-skinned man in his best years. " +
	     "He looks very agile. He seems to be selling and buying " +
	     "things. Actually he seems to carry an entire shop around with him. " +
	     "Use the commands 'list', 'buy', 'value', 'show' and 'sell' just like " +
	     "in any normal shop.\n");
    set_race_name("human");
    default_config_mobile(110);
    set_all_attack_unarmed(90, 90);
    set_all_hitloc_unarmed(90);
    set_skill(SS_BACKSTAB, 80);
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_PICK_POCKET, 80);
    set_skill(SS_FR_TRAP, 80);
    set_skill(SS_HIDE, 80);
    set_skill(SS_SNEAK, 80);
    set_skill(SS_OPEN_LOCK, 80);
    set_skill(SS_ACROBAT, 80);
    set_skill(SS_TRADING, 100);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);

    set_alignment(-100);
    set_knight_prestige(-1);
    set_whimpy_dir("north");
    set_whimpy(50);

    set_introduce(1);
    
    set_alarm(1.0,0.0,"equip_me");

    set_random_move(20);
    set_pick_up(10);
    set_act_time(10);
    add_act("say Torches, torches, cheap torches!");
    add_act("say Would you like to buy some torches?");
    add_emote_hook("nod", 2.0, do_nod);
    /*    trig_new("%s 'nods' %s","do_nod"); */

    enable_reset(100);
    config_default_trade();
    set_max_values(10,5);
    set_store_room(file_name(TO));
    set_money_greed_buy(105);
    set_money_greed_sell(105);
}

object *
all_inventory(object obj)
{
    return (efun::all_inventory(obj) - myownstuff);
}

void
reset_monster()
{
    object obj;

    ::reset_monster();
    all_inventory(TO)->remove_object();
    FIND_STR_IN_OBJECT("coins",TO)->remove_object();
    myownstuff -= ({ 0 });
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(TORCH)->move(TO);
    clone_object(CHALK_OBJ)->move(TO);
    (obj = MONEY_MAKE(100,"copper"))->move(TO);
    myownstuff += ({obj});
    (obj = MONEY_MAKE(50,"silver"))->move(TO);
    myownstuff += ({obj});
    (obj = MONEY_MAKE(3,"gold"))->move(TO);
    myownstuff += ({obj});
    
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
	write("Truncated...\n");
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
	return shop_hook_bought_items(item);

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
    
    if (MONEY_ADD(TO,-val))
      return 1;

    command("say I can't afford to buy " + LANG_THESHORT(obj) + ".");
    NF("");
    return 0;
}



int
prospective_member(object who)
{
  if (who->query_wiz_level()) return 1;

    //no layman guild yet.
    if(who->query_guild_name_lay())
      return 0;
    //no good aligned occ guild.
    if(who->query_alignment() > 100)
      return 0;
    //no magic occ guild.
    if (who->query_guild_style_occ() == "magic")
      return 0;
    return 1;
}

varargs void
react_introduce(mixed who = 0)
{
    object person;

    ::react_introduce(who);
    if (!who)
      return;

    person = find_player(who);
    if (!person || E(person) != E(TO))
      return;

    if (prospective_member(person))
      set_alarm(3.0,0.0,"recruit",person);
}

void
wh(object who,string str)
{
    command("whisper to " + who->query_real_name() + " " + str);
}

void
recruit(object who)
{
    wh(who,"Hello my friend. You look like someone I might have need for.");
    wh(who,"If you are interested in something new, just give me a nod.");
    set_alarm(20.0,0.0,"timeoutnod",who);
    waitfornod = who;
}

void
do_nod(object actor, string adverb)
{
    object who;
    string person = actor->query_name();
    
    if(!waitfornod)
      return;
    
    if(L(waitfornod->query_name()) != L(person))
      return;

    who = waitfornod;
    waitfornod = 0;

    seteuid(getuid(TO));
    write_file("/d/Krynn/solamn/thief/guild/log/recruited",
	       C(person) + " asked " + extract(ctime(time()),4,15) + "\n");

    wh(who,"In order to prove your usefulness for our task, you need " +
       "to figure out where to go first.");
    set_alarm(1.0,0.0,"next_thing",who);
}

EMOTE_HOOK

/*
public void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "nod")
    {
	do_nod(actor->query_name());
    }
}
*/
void
next_thing(object who)
{
    wh(who,"Here is what you need to do:");
    set_alarm(1.0,0.0,"next_thing2",who);
}

void
next_thing2(object who)
{
    wh(who,"Find a movable room.");
    set_alarm(1.0,0.0,"next_thing3",who);
}

void
next_thing3(object who)
{
     wh(who,"Enter the door that lies in the center.");
     set_alarm(1.0,0.0,"next_thing4",who);
}

void
next_thing4(object who)
{
    wh(who,"Then you have found your destination.");
    wh(who,"A hint on the side: A map might be helpful.");
}

void
timeoutnod(object who)
{
    if (!waitfornod)
      return;
    waitfornod = 0;
    command("say Guess not.");
    command("shrug .");
}
