inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>

#include "../bhunters.h"

int coins_count;

void create_armour()
{
    set_name("belt");
    set_adj(({ "leather", "broad"}));
    set_short("broad leather belt");
    set_long("@@my_long");

    set_ac(5); 
    set_at(A_WAIST);
    set_likely_break(1);
    
    //add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 200);
}

string my_long()
{
	return "A broad, leather belt with massive steel buckle. " +
		(coins_count ? "A thin strap, with " + coins_count  + " steel black rectangles " +
		"threaded, has been attached to it.\n" :
		"A thin strap on that can be used to thread blood coins on have been attached to it.\n");
}

public void init()
{
	::init();
	add_action("thread", "thread");
	add_action("remove", "remove");
}

int remove(string a)
{
	FIX_EUID;
	notify_fail("Remove what?\n");
	if(!strlen(a))
		return 0;
	int count;
	string part;
	if(!parse_command(a, ({}), " %d %s 'from' 'belt' / 'strap' ", count, part))
		return 0;
	if(!count)
		return 0;
	if(count == 1 && part != "blood coin" && part != "rectangle")
		return 0;
	if(count > 1 && part != "blood coins" && part != "rectangles")
		return 0;
	notify_fail("You don't have so many coins on your belt.\n");
	if(coins_count < count)
		return 0;
	coins_count -= count;
	object *coins = ({});
	while(count--)
		coins += ({clone_object(BHOBJ + "blood_coin")});
	coins->move(TP);
	write("You remove " + LANG_NUM2WORD(sizeof(coins)) + " blood " + 
		(sizeof(coins) == 1 ? "coin" : "coins") + " from your belt.\n");
	return 1;
}

int thread(string a)
{
	object *coins;
	notify_fail("Thread what?\n");
	if(!strlen(a))
		return 0;
	if(!parse_command(a, all_inventory(TP), " %i 'on' 'strap' ", coins))
		return 0;

	coins = NORMAL_ACCESS(coins, "is_blood_money", TO); 
	if(!sizeof(coins))
		return 0;
	coins_count += sizeof(coins);
	coins->remove_object();
	write("You thread " + LANG_NUM2WORD(sizeof(coins)) + " blood " +
	(sizeof(coins) == 1 ? "coin" : "coins") + " on the strap attached to your belt.\n");
	return 1;
}
	
int is_blood_money(object ob)
{
	return ob->is_blood_money();
}

public string query_auto_load()
{
	return MASTER + ":cc#" + coins_count;
}

public string query_recover()
{
	return 0;
}

public void init_arg(string arg)
{
	string tmp;
	if(!strlen(arg))
		return;
	sscanf(arg, "%s#%d", tmp, coins_count);
}

public int is_hunters_belt()
{
	return 1;
}


