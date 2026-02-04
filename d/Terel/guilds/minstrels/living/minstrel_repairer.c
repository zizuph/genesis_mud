/* A repairer base for the minstrel guild. 
 * Based on the /d/Terel/cedric/guild/Npcs/mc.c code by
 * Mortricia 
 *
 * Arman Dec 2019
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <money.h>
#include <cmdparse.h>
#include <state_desc.h>

#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/guilds/minstrels/guild_defs.h"

#define MAXLIST      30
#define STORE_ROOM   TO()
#define NUM	     4
#define FORK_1_FILE    GUILDOBJ + "fork_brass"
#define FORK_2_FILE    GUILDOBJ + "fork_silver"
#define FORK_3_FILE    GUILDOBJ + "fork_gold"

void fix_it(object instrument);

public void
set_up_repairer()
{
    set_name("bard");
    add_name("repairer");
    set_adj("journeyman");
    set_short("journeyman bard");
    set_race_name("human");

    add_prop(CONT_I_WEIGHT, 60000 + random(15000));
    add_prop(CONT_I_HEIGHT, 160 + random(40));

    set_long("Before you stands a journeyman bard of the Telberin "
       + "Minstrel's Guild. He will happily sell you some of the "
       + "tools of his trade, <list> what he has in stock, <fix> "
       + "or <repair> a damaged instrument, or <assess> the "
       + "cost to repair damaged instruments.\n");
    default_config_npc(SD_AV_EXPERT);
    set_alignment(500);
    set_all_hitloc_unarmed(200);
}

public string
no_attack()
{

   this_player()->catch_msg("You approach " +QTNAME(this_object())+ 
       " threateningly. " +QCTNAME(this_object())+ 
       " suddenly turns sprints with speed away from you!\n");
   tell_room(environment(this_player()), QCTNAME(this_player())+ 
       " approaches " +QTNAME(this_object())+ " threateningly. " +
       QCTNAME(this_object())+ " suddenly turns and sprints away!\n", 
       ({ this_player() }), this_player());

   this_object()->run_away();
   return "";
}

void
create_monster()
{
    if (!IS_CLONE) 
       return;

    set_up_repairer();

    config_default_trade();
    set_money_greed_buy(150);
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    add_prop(OBJ_M_NO_ATTACK, "@@no_attack");

    seq_new("foo");
    seq_addfirst("foo", ({ "@@do_give" }) );
}

void
init_living()
{
    add_action("do_list",   "list");
    add_action("do_buy",    "buy");
    add_action("do_repair", "assess");  
    add_action("do_repair", "repair");
    add_action("do_repair", "fix");
}

void
do_give()
{
    object fork;
    int i;

    seteuid(getuid());

    MONEY_MAKE_CC(20)->move(TO());
    MONEY_MAKE_SC(11)->move(TO());
    MONEY_MAKE_GC(3)->move(TO());

    for (i=0; i<4; i++) {
        fork = clone_object(FORK_1_FILE);
        fork->move(TO());
    }
    for (i=0; i<3; i++) {
        fork = clone_object(FORK_2_FILE);
        fork->move(TO());
    }
    for (i=0; i<2; i++) {
        fork = clone_object(FORK_3_FILE);
        fork->move(TO());
    }
}

int
do_list(string str)
{
    object *item_arr;
    int i, price, *arr;

    STORE_ROOM->short();

    item_arr = all_inventory(STORE_ROOM);

    if (!sizeof(item_arr))
    {
	command("shrug");
	NF("There is no more to sell.\n");
        return 0;
    }

    if (str == "forks")
        item_arr = filter(item_arr, "fork_filter", TO());
    else
        if (str)
            item_arr = filter(item_arr,"string_filter", TO(), str);

    item_arr = filter(item_arr, "remove_coins_from_arr", TO());

    if (sizeof(item_arr) < 1)
    {
	command("shrug");
	command("say I have no such things.");
        return 1;
    }

    write("You look at the " +query_short()+ "'s wares:\n");

    for (i = 0; i < sizeof(item_arr); i++)
    {
        if (i < MAXLIST)
        {
            price = 2 * item_arr[i]->query_prop(OBJ_I_VALUE) *
                 query_money_greed_buy() / 100;

            arr = split_values(price);
            str = sprintf("%-25s",
                 capitalize(LANG_ADDART(item_arr[i]->short())));

            if (!text(arr))
                write(str + "That item wouldn't cost you much.\n");
            else
                write(BS(str + text(arr) + ".\n"));
        }
        else
        {
            write("Truncated: " + i + ".\n");
            break;
        }
    }

    return 1;
}

fork_filter(object ob)
{
    if (member_array("minstrel_tuning_fork", ob->query_names()) >= 0)
	return 1;
    return 0;
}

weapon_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/weapon");
}

armour_filter(object ob)
{
    return (function_exists("create_object", ob) == "/std/armour");
}

string_filter(object ob, string str)
{
    return ob->id(str);
}

remove_coins_from_arr(object ob)
{
    return !ob->id("coin");
}

do_buy(string str)
{
    object  buy_ob;
    string  what, for_c, get_c;
    string  change;
    int     *result, m_res;
    int     price;

    if (!str) {
	command("say Buy what?");
	return 1;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
	if (sscanf(str, "%s with %s", what, for_c) != 2)
	    what = str;

    if (!parse_command(what, STORE_ROOM, "%o", buy_ob))
    {
	notify_fail("The " +query_short()+ " has no such thing to sell you.");
	return 0;
    }
    price = (int)2 * buy_ob->query_prop(OBJ_I_VALUE);

    set_money_give_out(what_coins(TO()));

    result = pay(price, TP(), for_c, 0, TO(), get_c);
    if (sizeof(result) == 1)
	return 0; /* Pay() handles notify_fail if we want to. */

    if ((int)buy_ob->move(TP()))
    {
        write("You drop the " + buy_ob->short() + " on the floor.\n");
        say(QCTNAME(TP()) + " drops one " + buy_ob->short() +
            " on the floor.\n");
        buy_ob->move(environment(TP()));
    }
    else
    {
        write("You get your " + buy_ob->short() + ".\n");
        say(QCTNAME(TP()) + " buys the " + buy_ob->short() + ".\n");
    }

    write ("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    change = text(result[NUM .. 2 * NUM - 1]);

    if (change) {
	write("You get " + change + " as change.\n");
    }
    return 1;
}

int
do_repair(string str) 
{
    int testflag,cost,damage; 
    object instrument;
    mixed result;

    if (!str)
    {
	command("say What do you want me to "+query_verb()+"?");
	return 1;
    }

    if (query_verb()=="assess")
        testflag = 1;
    else
	testflag = 0;

    if (parse_command(str, TP(), "%o", instrument)
    && member_array("minstrel_instrument",instrument->query_names()) >= 0)
    {
    	damage = instrument->query_damage();
	if (damage < 1)
	{
	    NF("The " +short()+ " looks the "+instrument->query_name()+" over "
	    + "with the trained eye of an expert, and says, \"I see nothing "
	    + "wrong with your instrument, friend.\"\n");
	    instrument->set_damage(0);
	    return 0;
	}
	cost = damage * damage * damage;
	result = pay(cost, TP(), "", testflag, TO(), "", 0);
	if (intp(result))
	    switch (result)
	    {
		case 3: 
		    write("The " +short()+ " asks "+cost+" copper coins to repair your "
		    + "instrument.\n");
		    return 1;
		default:
		    write("The " +short()+ " begins to take your money, then stops, "
		    + "confused. \"Odd!\" he exclaims. \"An error code "+result
		    + " kept me from taking your money. Better tell the "
		    + "guildmaster.\" The " +short()+ " shrugs and returns to his work.\n");
		    return 1;
	    }
	if (testflag)
	{
	    write("The " +short()+ " asks "+text(result)+" to repair the "
	    + instrument->query_name()+".\n");
	    return 1;
	}
	else
	{
	    write("You pay "+text(result)+" to the " +short()+ ", who carefully "
	    + "looks your "+instrument->query_name()+" over.\n");
	    set_alarm(4.0, 0.0, &fix_it(instrument));
	    return 1;
	}
    }
    else
    {
	NF("The " +short()+ " glares at you and goes back to his work.\n");
        return 0;
    }
}

void fix_it(object instrument)
{
    switch (instrument->query_damage())
    {
	case 1..4: 
	    write("The " +short()+ " remarks: Why, it's only out of tune! Don't you know "
	    + "how to tune your own "+instrument->query_name()+"?\nHe "
	    + "quickly tunes the instrument and hands it back to you.\n");
	    break;
	case 5:
	    write("The " +short()+ " seems amused. \"They don't get much more out of "
	    + "tune than this, do they?\" he laughs. He quickly tunes the "
	    + instrument->query_name()+" and hands it back to you.\n");
	    break;
	case 6..10:
	    write("The " +short()+ " takes the damaged instrument gingerly and "
	    + "places it on his workbench. Working quickly, but with great "
	    + "love and care, his deft fingers fly over the instrument. When "
	    + "he hands it back to you, the "+instrument->query_name()
	    + " looks as fine as the day "+environment(instrument)->
	    query_muse_name() + " first handed it into your care.\n");
	    break;
    }
    instrument->set_damage(0);
}

