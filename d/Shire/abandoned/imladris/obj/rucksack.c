/*
 * A backpack carried by Elves out of Rivendell.
 * Common outfit when they are out travelling or adventuring.
 *
 * Part of code taken from rogon's lootsack, /d/Shire/moria/obj/lootsack.c
 *
 * Odin, 7.1.95
 */

inherit "/std/receptacle";

#include "/d/Shire/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

#define BACKPACK this_object, 1
#define IM_PARSE_FILE "/d/Immortal/rogon/open/parse_lib"
#define INV(x)	    all_inventory(x)

object wearer;

public void
create_container()
{
	setuid();
	geteuid();
	set_name("elven_sack");
	add_name("rucksack");
	set_pname("rucksacks");
	set_adj(({"elven"}));
	set_short("elven rucksack");
	set_pshort("elven rucksacks");
	set_long(
		"This is a large rucksack used by the elves of Rivendell when they "+
		"are out adventuring. It is very light, and the colours makes it hard "+
		"to see it. Use <sackloot> to loot something out of the sack, or <sackfill> "+
		"to retrieve something out of the rucksack.\n");

	add_prop(CONT_I_IN, 1);
	add_prop(CONT_I_WEIGHT, 400);			// 400 Kg's, elven made and very light.
	add_prop(CONT_I_VOLUME, 200);			// This is the volume when empty.
	add_prop(CONT_I_MAX_VOLUME, 35*1000);	// 35 l.
	add_prop(CONT_I_MAX_WEIGHT, 55*1000);	// 55 Kg's.
	add_prop(CONT_I_CLOSED, 1);
	add_prop(CONT_I_RIGID, 0);
	add_prop(CONT_I_TRANSP, 0);
	add_prop(OBJ_I_VALUE, 100+random(350));
	add_prop(OBJ_M_NO_SELL, "@@check_sell@@");
}

init()
{
	::init();
	add_action("do_loot", "sackfill");
	add_action("do_empty", "sackloot");
	add_action("do_keep", "sackhold");
	add_action("do_sell", "sacksell");
}

/*
wear(object to)
{
	wearer = TP;
	wearer->add_subloc("_special_look", TO);
}

remove(object to)
{
	wearer->remove_subloc("_special_look");
	wearer = 0;
}

string
show_subloc(mixed subloc, object on, object who)
{
	if(subloc != "_special_look");
		return "";
	if(who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";
	if(!query_worn())
		return "";
	if(who == ETO)
		return "You are wearing a light elven rucksack, hardly to be noticed back there.\n");
	else
		return CAP(HE_SHE(ETO))+" is wearing a light elven rucksack, and does'nt seem any encumbered by it.\n");
}
*/

mixed
check_sell()
{
	if(sizeof(all_inventory(TO)))
	return "There are things in the "+short()+", empty it first.\n";
	else
	return 0;
}

int 
is_corpse(object ob)
{
	return !living(ob) && ob->query_prop(CONT_I_IN);
}

int
is_sack(object ob)
{
	return ob->id("elven_sack");
}

int
do_loot(string str)
{
	mixed 	*what;
	object 	*loot;
	string 	rest, verb;
	object 	sack;

	verb = query_verb();

	NF("Syntax: "+verb+" <corpse> [with <sack>].\n");

	if(ENV(TO) != TP)
	return NF("You must hold the sack inorder to loot something.\n");
	
	if(!strlen(str))
	str = "corpse";

	if(parse_command(str, INV(ENV(TP)), "%i 'in' / 'into' / 'with' / 'using' [the] %s",
		what, rest))
	{
		loot = VISIBLE_ACCESS(what, "is_sack", TO);
		if(!sizeof(what) > 1)
			return NF("Which sack are you refering to?\n");
		if(sizeof(what) > 1)
			return NF("Only one sack at a time if you dont mind.\n");
		sack = what[0];
		return sack->do_loot_one(loot, rest);
	}
	else
	{
		loot = IM_PARSE_FILE->parse_environment_items(str, "");
		loot = filter(loot, "is_corpse", TO);
		return TO->do_loot_one(loot, "loot sack");
	}
}

int
do_loot_one(object *loot, string name)
{
	int 	i, x;
	object 	*what;
	object 	*got;

	if(query_prop(CONT_I_CLOSED))
		return NF("Perhaps open the "+name+" before you do that?\n");

	i = sizeof(loot);

	if(!i)
		return 0;

	write("You loot "+COMPOSITE_DEAD(loot)+" putting everything into your "+name+"!\n");
	say(QCTNAME(TP)+" loots "+QCOMPDEAD+".\n");

	while(i--)
	{
		what = all_inventory(loot[i]);
		x = sizeof(what);

		if (!x)
		{
			write("The "+loot[i]->short()+" is empty!\n");
			continue;
		}
		got = ({});
		while(x--)
			if(what[x]->move(TO) == 0)
			got += ({ what[x] });

		x = sizeof(got);
		if(!x)
		{
			write("You could not loot the "+what[x]+".\n");
			continue;
		}
		write("You loot "+COMPOSITE_DEAD(got)+" from the "+loot[i]->short()+" into "+
			name+".\n");
		say(QCTNAME(TP)+" loots "+QCOMPDEAD+" from the "+loot[i]->short()+".\n");
	}

	return 1;
}

int
do_empty(string str)
{
	object 	*objs;
	mixed 	*sacks;
	int 	i, r = 0;

	NF("Syntax: "+query_verb()+" <sack>.\n");

	if(!strlen(str))
	str = "loot sack";

	if(!parse_command(str, INV(TP), "%i", sacks))
		return 0;
	return NF(CAP(query_verb())+" which sacks?\n");

	for (i=0; i<sizeof(sacks); i++)
	if (sacks[i]->do_empty_sack())
		r = 1;
	return r;
}

int
do_empty_sack()
{
	if(query_prop(CONT_I_CLOSED))
		return NF("Perhaps open the rucksack first?\n");
	write("You retrieve "+COMPOSITE_DEAD(INV(TO))+" from the rucksack.\n");
	say(QCTNAME(TP)+" retrieves "+QCOMPDEAD+" from "+HIS_HER(TP)+" rucksack.\n");
	INV(TO)->move(INV(TP));
	return 1;
}

int
do_keep()
{
	if(query_prop(OBJ_M_NO_SELL))
	{
		write("Your rucksack is already unsellable!\n");
		return 0;
	}
	else
	if(!query_prop(OBJ_M_NO_SELL))
	{
		write("Now the rucksack can't be sold.\n");
		add_prop(OBJ_M_NO_SELL, 1);
		return 1;
	}
}

int
do_sell()
{
	if(!query_prop(OBJ_M_NO_SELL))
	{
		write("The rucksack is already sellable!\n");
		return 0;
	}
	else
	if(query_prop(OBJ_M_NO_SELL))
	{
		write("You can now sell the rucksack.\n");
		remove_prop(OBJ_M_NO_SELL);
		add_prop(OBJ_M_NO_SELL, "@@check_sell@");
		return 1;
	}
}



