/*
 * /d/Ansalon/guild/society/room/faerie_tree.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Where kender can choose their faerie friends.
 * Coded by Gwyneth, December 2000
 */
inherit "/std/room";

#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include "../guild.h"

#define FAERIE (KGNPC + "faerie")
#define FINDER (KGOBJ + "faerie_finder")

/* Positions in the gDetails array */
#define ADJ1P    0
#define ADJ2P    1
#define HLENGTHP 2
#define HCOLOURP 3
#define HSTYLEP  4
#define ETYPEP   5
#define ECOLOURP 6
#define NAMEP    7
#define ADORNP   8
#define GENDERP  9

#define TOP ({ "a silver satin tunic", "a sky-blue silk tunic", \
		"a deep-green satin blouse", "a yellow silk shirt", \
		"a fitted orange vest", "a forest-green silk tunic", \
		"a silky lilac blouse", "a soft snow-white blouse", \
		"a bright green velvet shirt", "a midnight-blue velvet tunic", \
		"an emerald studded tunic", "a silky black tunic", \
		"a ruby studded gown", "an opaque green gown", \
		"a silvery opaque gown", "a silky bright blue gown"})
#define BOTTOM ({ "a pair of bright red leggings", \
		"a pair of bright orange pants", "a pair of black silky pants", \
		"a pair of thin blue leggings", "a pair of velvet green leggings", \
		"a ruby studded gown", "an opaque green gown", \
		"a silvery translucent gown", "a silky bright blue gown"})
#define SHOES ({ "a pair of green pointed boots", "a pair of brown pointed shoes", \
		"a pair of blue slippers", "a pair of ruby slippers", \
		"a pair of orange knee-high boots", \
		"a pair of black knee-high boots" })
#define HEAD ({ "a circlet of spring flowers", "a crown of dew", \
		"a golden circlet", "a silver circlet", "a mithril circlet",  \
		"a circlet of autumn leaves", "a circlet of spring leaves", \
		"a crown of snowflakes", "a circlet of moonlight" })
#define NECK ({ "a pearl necklace", "a necklace of daisies", "a silver locket", \
		"a diamond necklace", "a collar of starlight"})
#define BELT ({ "a belt of sunlight", "a belt of looped gold", \
		"a woven belt of rainbows", "a silver braided belt" })

static string *gAdornArr = (TOP + BOTTOM + SHOES + HEAD + NECK + BELT);

static string *gFoundFriend = ({});
mapping gDetails = ([]);

public void
create_room()
{
	set_short("a sheltered valley around a majestic willow");
	set_long("In this sheltered valley a majestic willow tree " +
		"grows, its green branches sweeping gently down to " +
		"the tiny flowers, clover and grass below. A " +
		"shimmering aura seems to radiate and shift around " +
		"the willow, but upon closer inspection, you " +
		"can see the miniature forms of faeries dancing and " +
		"playing in the air around their willow tree. A small " +
		"overgrown path leads to the west, winding out of your " +
		"view.\n");

	add_item("air", "The air is filled with tiny faeries.\n");
	add_item(({"valley", "sheltered valley"}), "This valley " +
		"is hidden in the midst of rough craggy mountains " +
		"that tower up around you.\n");
	add_item(({"mountains", "rough mountains", "craggy mountains",
		"rough craggy mountains"}), "The mountains climb above " +
		"the treeline, and are capped in snow.\n");
	add_item("snow", "The snow is flawless, having been undisturbed " +
		"for many years.\n");
	add_item(({"path", "overgrown path"}), "The small path is " +
		"overgrown with soft springy grass, and leads " +
		"around a bend heading out of this sheltered valley.\n");
	add_item(({"flowers", "tiny flowers", "flower", "tiny flower"}),
		"Spanning the colours of the rainbow and beyond, these " +
		"lovely flowers grow beneath the willow, basking " +
		"in the magic of the faeries.\n");
	add_item(({"branches", "green branches"}), "The green branches " +
		"of the willow are covered with slender pointed leaves " +
		"and dancing faeries.\n");
	add_item(({"slender pointed leaves", "slender leaves", 
		"pointed leaves", "leaves"}), "The leaves are a light " +
		"green, waxy and slender. Pointed on both ends, they " +
		"are long and slightly wavy.\n");
	add_item(({"willow", "willow tree", "majestic tree", "tree",
		"majestic willow tree", "majestic willow"}), 
		"It stands as high as a dozen kender standing on " +
		"each other's shoulders. Its branches are covered " +
		"with slender pointed leaves. Faeries flutter around " +
		"it, lounge amidst the flowers below, or slide down " +
		"the branches in play.\n");
	add_item(({"clover", "white flowers"}), "White flowers sprout " +
		"from emerald green clover leaves scattered across the " +
		"ground of this sheltered valley.\n");
	add_item("ground", "The ground is covered with grass, clover " +
		"and flowers.\n");
	add_item(({"grass", "green grass"}), "The grass is soft and " +
		"springy, and grows in abundance in this sheltered " +
		"valley.\n");
	add_item(({"faerie", "faeries", "shimmering aura", "aura",
		"forms", "miniature forms"}),
		"The faeries vary widely in features, yet all appear " +
		"to be the image of perfection. As they see you near " +
		"their tree, several faeries fly up to you and dance " +
		"around your head, giggling and chattering in high " +
		"pitched voices. Perhaps you could find a " +
		"faerie that you like, and befriend it.\n");

	add_exit(KGROOM + "joinroom", "west", 0, 0, 1);

	restore_object(MASTER);
}

public string
format_output(string *output)
{
	int size, i, scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
	string *output2, formatted = "";

	size = sizeof(output);

	if (!size)
	{
		return "";
	}

	output = sort_array(output);

	output2 = ({ output[0] });
	for (i = 1, size = sizeof(output); i < size; i++)
	{
		if (member_array(output[i], output2) == -1)
		{
			output2 += ({ output[i] });
		}
	}

	output = output2;

	scrw = ((scrw >= 40) ? (scrw - 3) : 77);
	formatted += (sprintf("%-*#s\n", scrw, implode(output, "\n")));
	return formatted;
}

public void
leave_inv(object ob, object to)
{
	object finder;

	::leave_inv(ob, to);

	if (finder = present("_faerie_find_object_", ob))
	{
		finder->abort_find();
	}
}

public int
recall_faerie(object who)
{
	int i, size, gender;
	object faerie;
	string name;
	string adj1, adj2, hlength, hcolour, hstyle, etype, fname,
		ecolour, *adorn;
	name = who->query_real_name();

	if (member_array(name, m_indexes(gDetails)) == -1)
	{
		return 0;
	}


	adj1    = gDetails[name][0];
	adj2    = gDetails[name][1];
	hlength = gDetails[name][2];
	hcolour = gDetails[name][3];
	hstyle  = gDetails[name][4];
	etype   = gDetails[name][5];
	ecolour = gDetails[name][6];
	fname   = gDetails[name][7];
	adorn   = gDetails[name][8];
	gender  = gDetails[name][9];	

	faerie = clone_object(FAERIE);
	faerie->faerie_owner(name);
	faerie->faerie_adjs(adj1, adj2);
	faerie->faerie_hair(hlength, hcolour, hstyle);
	faerie->faerie_eyes(etype, ecolour);
	faerie->faerie_name(fname);
	faerie->faerie_gender(gender);

	size = sizeof(adorn);
	for(i = 0; i < size; i++)
	{
		faerie->faerie_adorn(adorn[i]);
	}

	faerie->fly_to_owner();
	return 1;
}

public void
save_faerie(string adj1, string adj2, string hlength, string hcolour, 
  string hstyle, string etype, string ecolour, int gender, string owner)
{
	if (member_array(owner, m_indexes(gDetails)) != -1)
	{
		m_delete(gDetails, owner);
	}

	gDetails += ([ owner: ({adj1,adj2,hlength,hcolour,
		hstyle, etype, ecolour, "unknown", ({}),
		gender }) ]);

	gFoundFriend += ({ owner });
	save_object(MASTER);
}

private int
find_faerie(string str)
{
	int i, size;
	object *oblist, finder;
	string name = this_player()->query_real_name();

	if (member_array(name, gFoundFriend) != -1)
	{
		notify_fail("Abandon your new friend so quickly?\n");
		return 0;
	}
	else if (!strlen(str))
	{
		notify_fail(capitalize(query_verb()) + " a faerie?\n");
		return 0;
	}
	else if (lower_case(str) != "faerie" &&
	  lower_case(str) != "a faerie")
	{
		notify_fail(capitalize(query_verb()) + " a faerie?\n");
		return 0;
	}
	else
	{
		oblist = find_living("faerie", 1);
		size = sizeof(oblist);
		for (i = 0; i < size; i++)
		{
			if (oblist[i]->query_owner() == name)
			{
				oblist[i]->faerie_owner("unknown");
				oblist[i]->fly_away();
			}
		}

		if (member_array(name,
			m_indexes(gDetails)) == -1)
		{
			gDetails += ([ name:({"","","","","","","","",
				({""}),0 }) ]);
		}	

		finder = clone_object(FINDER);
		finder->move(this_player(), 1);
		finder->begin_find(this_player());
		return 1;
	}
}

public void
add_faerie_name(string name, string owner)
{
	gDetails[owner][NAMEP] = name;
	save_object(MASTER);
	return;
}

private int
name_faerie(string str)
{
	int i, size;
	object *faerie_group, faerie;
	string name;

	if (!strlen(str))
	{
		notify_fail("Name your faerie what?\n");
		return 0;
	}
	else if (!parse_command(str, ({}), 
	  "[my] [the] [faerie] [friend] %s", name))
	{
		notify_fail("Name your faerie what?\n");
		return 0;
	}
	else if (!strlen(name))
	{
		notify_fail("Name your faerie what?\n");
		return 0;
	}
	else if (strlen(name) > 11)
	{
		notify_fail(capitalize(name) + " is too long a name.\n");
		return 0;
	}
	else if (SECURITY->query_banished(lower_case(name)))
	{
		notify_fail(capitalize(name) + " has been banished for " +
			"use. Please choose another name.\n");
		return 0;
	}
	else if (SECURITY->query_wiz_level(lower_case(name)))
	{
		notify_fail(capitalize(name) + " has been banished " +
			"for use. Please choose another name.\n");
		return 0;
	}

	faerie_group = (all_inventory(this_player()) + 
		all_inventory(environment(this_player())));
	faerie_group = FILTER_RACE(faerie_group, "faerie");

	if (!sizeof(faerie_group))
	{
		notify_fail("Shouldn't your faerie be present to " +
			"receive a name?\n");
		return 0;
	}
	if (sizeof(faerie_group) > 1)
	{
		for (i = 0, size = sizeof(faerie_group); i < size; i++)
		{
			if (faerie_group[i]->query_owner() == 
			  this_player()->query_real_name())
			{
				faerie = faerie_group[i];
				break;
			}
		}
	}
	else if (faerie_group[0]->query_owner() == 
	  this_player()->query_real_name())
	{
		faerie = faerie_group[0];
	}

	if (!objectp(faerie))
	{
		notify_fail("Shouldn't your faerie be present " +
			"to receive a name?\n");
		return 0;
	}
	else
	{
		faerie->faerie_name(lower_case(name));
		write("You declare that " + LANG_THESHORT(faerie) + 
			" shall be known " +
			"as " + capitalize(name) + " from now on.\n");
		say(QCTNAME(this_player()) + " declares that " +
			LANG_THESHORT(faerie) + " shall be known " +
			"as " + capitalize(name) + " from now on.\n");
		faerie->command("emote looks pleased and smiles.");
		add_faerie_name(lower_case(name), 
			this_player()->query_real_name());
		return 1;
	}
}

public void
add_faerie_adorn(string adorn)
{
	string *adorn_list = gDetails[this_player()->query_real_name()][ADORNP];
	if (member_array(adorn, adorn_list) == -1)
	{
		gDetails[this_player()->query_real_name()][ADORNP] += ({ adorn });
	}
	else
	{
		gDetails[this_player()->query_real_name()][ADORNP] -= ({ adorn });
	}

	save_object(MASTER);
	return;
}

public int
choose_adornment(string str)
{
	int i, size, top, bottom, neck, head, belt, shoes;
	string *adorn_list;
	object *faerie_group, faerie;

	if (!strlen(str))
	{
		write("You don't seem to be very decisive.\n" +
			format_output(gAdornArr) +
			"Which adornment would you like for your faerie? " +
			"Or 'stop'? ");
		input_to(choose_adornment);
		return 1;
	}
	
	str = lower_case(str);

	if (str == "stop")
	{
		notify_fail("You stop looking for adornments.\n");
		return 0;
	}
	if (member_array(str, gAdornArr) == -1)
	{
		write("You don't find anything of that description.\n" +
			format_output(gAdornArr) +
			"Which adornment would you like for your faerie? " +
			"Or 'stop'? ");
		input_to(choose_adornment);
		return 1;
	}

	faerie_group = (all_inventory(this_player()) + 
		all_inventory(environment(this_player())));
	faerie_group = FILTER_RACE(faerie_group, "faerie");

	if (!sizeof(faerie_group))
	{
		notify_fail("Shouldn't your faerie be present?\n");
		return 0;
	}
	if (sizeof(faerie_group) > 1)
	{
		for (i = 0, size = sizeof(faerie_group); i < size; i++)
		{
			if (faerie_group[i]->query_owner() == 
				this_player()->query_real_name())
			{
				faerie = faerie_group[i];
				break;
			}
		}
	}
	else if (faerie_group[0]->query_owner() == 
		this_player()->query_real_name())
	{
		faerie = faerie_group[0];
	}

	if (!objectp(faerie))
	{
		notify_fail("Shouldn't your faerie be present?\n");
		return 0;
	}

	adorn_list = gDetails[this_player()->query_real_name()][ADORNP];
	size = sizeof(adorn_list);
	for (i = 0; i < size; i++)
	{
		if (member_array(adorn_list[i], TOP) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, TOP) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
		if (member_array(adorn_list[i], BOTTOM) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, BOTTOM) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
		if (member_array(adorn_list[i], HEAD) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, HEAD) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
		if (member_array(adorn_list[i], NECK) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, NECK) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
		if (member_array(adorn_list[i], SHOES) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, SHOES) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
		if (member_array(adorn_list[i], BELT) != -1 &&
		  str != adorn_list[i] &&
		  member_array(str, BELT) != -1)
		{
			notify_fail("Your faerie already has " + adorn_list[i] +
				" for that spot.\n");
			return 0;
		}
	}

	faerie->faerie_adorn(str);
	write(capitalize(LANG_THESHORT(faerie)) + " smiles " +
		"in delight as you change " +
		faerie->query_objective() + " wardrobe.\n");
	add_faerie_adorn(str);
	return 1;
}

private int
adorn_faerie(string str)
{
	if (!strlen(str))
	{
		notify_fail("Choose adornment?\n");
		return 0;
	}
	
	str = lower_case(str);

	if (str == "adornments" ||
	  str == "clothing" ||
	  str == "adornment")
	{
		write("You find several pieces of clothing and " +
			"adornments hanging on a nearby bush.\n" +
			format_output(gAdornArr) +
			"Which piece would you like to add or remove? " +
			"Or 'stop'? ");
		input_to(choose_adornment);
		return 1;
	}
	return 1;
}

public void
init()
{
	::init();

	add_action(find_faerie, "befriend");
	add_action(find_faerie, "find");
	add_action(name_faerie, "name");
	add_action(adorn_faerie, "choose");
}

