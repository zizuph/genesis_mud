/**********************************************************************
 * - house.c                                                        - *
 * - Eil-Galaith Join House room                                    - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "../guild.h"

inherit GUILD_ROOM;
inherit SCROLL;

#include "seated2.c"
#include "fireplace.c"

string
read_plaque(void)
{
	return(
	"list houses         = To list the Houses of Eil-Galaith.\n"+
	"list <house name>   = To list members of a House.\n"+
	"choose <house name> = To join a house.\n"+
	"request mantle      = To obtain a new mantle.\n"+
	"leave house         = To leave your present House.\n"+
	"list                = List current guilds you are affiliated "+
	"with.\n");
}

/*
 * The room itself.
 */
public void
create_guild_room()
{
	setuid(); seteuid(getuid());
	
	set_short("Hall of Houses");
	set_long("   You are standing in a Grand Hall that is filled "+
	"with large elaborate tapestries that adorn the marble walls. "+
	"A large fireplace rests in the east wall and you notice a "+
	"golden plaque placed along the mantle. ");
	add_item(({"plaque", "gold plaque", "golden plaque"}),
	"The plaque is made of gold and engraved with these words.\n"+
	"@@read_plaque@@");
	add_cmd_item("plaque", "read", read_plaque);
	add_item(({"fireplace"}),
	"The fireplace is lit with a nice warm glowing fire.\n");
	add_item(({"mantle"}),
	"The mantle is large and made for the same marble the walls "+
	"and flooring is made from. A golden plaque is placed along "+
	"the front.\n");
	add_item(({"fire"}),
	"The fire dances with golden light which fills the hall with "+
	"warmth and peace.\n");
	add_item(({"tapestries"}),
	"The tapestries are large and elaborately crafted by "+
	"skilled elven hands. Silken threads are woven in various "+
	"patterns in each. There are twelve tapestries in total and "+
	"you should be able to examine each one a bit closer.\n");
	add_item(({"tapestry"}),
	"Which tapestry did you want to look at? The first one "+
	"perhaps?\n");
	add_item(({"first tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"prietess healing a young warrior while wearing the silken "+
	"colours of turquoise and copper. At the bottom right corner "+
	"you see the name written in elven script, 'Ailia'.\n");
	add_item(({"second tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"alchemist mixing potions while wearing the silken colours of "+
	"sapphire and gold. At the bottom right corner you see the name "+
	"written in elven script, 'Driliau'.\n");
	add_item(({"third tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf standing "+
	"with his hands spread wide in an obvious fashion of telling a "+
	"tale to onlookers and he's wearing the silken colours of yellow "+
	"and blue. At the bottom right corner you see the name written "+
	"in elven script, 'Eilaith'.\n");
	add_item(({"fourth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf tending "+
	"soil in a small garden while wearing the silken colours of "+
	"green and silver. At the bottom right corner you see the name "+
	"written in elven script, 'Ellilith'.\n");
	add_item(({"fifth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"herbalist picking herbs and studying them while wearing the "+
	"silken colours of emerald and gold. At the bottom right corner "+
	"you see the name written in elven script, 'Jilaith'.\n");
	add_item(({"sixth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf engaged "+
	"in a battle wearing only shields and kicking his foe across the "+
	"battlefield while wearing the silken colours of sapphire and "+
	"silver. At the bottom right corner you see the name written in "+
	"elven script, 'Khilarith'.\n");
	add_item(({"seventh tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf holding "+
	"many scrolls and engaged in the art study while wearing the "+
	"silken colours of jade and silver. At the bottom right corner "+
	"you see the name written in elven script, 'Quillith'.\n");
	add_item(({"eighth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"merchant buying and selling his wares in a large square while "+
	"wearing the silken colours of white and blue. At the bottom "+
	"right corner you see the name written in elven script, "+
	"'Silith'.\n");
	add_item(({"ninth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf forging "+
	"a sword while wearing the silken colours of silver and black. "+
	"At the bottom right corner you see the name written in elven "+
	"script, 'Sillaith'.\n");
	add_item(({"tenth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"magician standing alone looking at a miniature world within "+
	"his hands and wearing the silken colours of red and black. At "+
	"the bottom right corner you see the name written in elven "+
	"script, 'Uluith'.\n");
	add_item(({"eleventh tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elf "+
	"wandering distant lands while wearing the silken colours of "+
	"gold and green. At the bottom right corner you see the name "+
	"written in elven script, 'Wylith'.\n");
	add_item(({"twelfth tapestry"}),
	"This tapestry is simply breath taking. The workmanship has been "+
	"elaborately done. There is an image depicted of an elven "+
	"warrior proudly slaying his foe while wearing the silken "+
	"colours of red and gold. At the bottom right corner you see "+
	"the name written in elven script, 'Xelith'.\n");
	add_item(({"hall", "grand hall", "room", "area"}),query_long);
	add_item(({"chair","chairs"}), seat_desc);
	add_my_desc(seat_desc, this_object());
	add_prop(ROOM_I_INSIDE, 1);
	add_exit("join", "down");
	add_fail("auto", "You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");  
}

/*
 * List the available houses, for convenience.
 */
public int
list(string str)
{
	if (!strlen(str))
	{
		if (str = this_player()->list_major_guilds())
		write("You are a member of the following guilds.\n" + str);
		else
		write("You are not a member of any important guilds.\n");
		return 1;
	}
	str = capitalize(lower_case(str));
	if (lower_case(str) == "houses")
	{
		return print_scroll(sort_array(m_indexes(HOUSES)),
		"These are the available houses of the " + GUILD_NAME);
	}
	if (member_array(str, m_indexes(HOUSES)) == -1)
	{
		write("That is not a House of the " + GUILD_NAME + ".\n");
		return 1;
	}
	else
	{
		int i;
		string *lst;
		mixed tmp = ([]) + SERVER->query_house(str);
		tmp = m_indexes(tmp) - ({ HOUSE_CLRS });
		i = sizeof(tmp);
		lst = ({});
		while(--i >= 0)
		{
			if(!wildmatch("*jr", tmp[i]) &&
			!SECURITY->query_wiz_level(tmp[i]))
			lst += ({tmp[i]});
		}
		if (!sizeof(lst))
		{
			write("The House " + str + " is currently "+
			"empty and in need of a claimant.\n");
			return 1;
		}
		lst = sort_array(map(lst, capitalize));
		return print_scroll(lst, "The following "+
		"" + GUILD_NAME + " belong to the House " + str);
	}
}

/*
 * Naughty elf lost their mantle, bad.. baaaad elfie...
 */
public int
request(string str)
{
	object mantle;
	if (str != "mantle")
	{
		NF("Request what? A mantle maybe?\n");
		return 0;
	}
	if (!IS_MEMBER(TP))
	{
		write("The " + GUILD_NAME + " do not grant requests "+
		"to non-members.\n");
		return 1;
	}
	if (objectp(mantle = present(OBJECT_ID, TP)) &&
	(!mantle->query_prop(OBJ_I_BROKEN)))
	{
		write("You don't need another mantle.\n");
		return 1;
	}
	if (mantle)
	mantle->remove_object();
	clone_object(OBJECT)->move(TP, 1);
	write("A young elf enters, hands you a new mantle, "+
	"then leaves.\n");
	say (QCTNAME(TP) + " is given a new mantle by a young elf.\n");
	return 1;
}

public int
choose_house(string str)
{
	string *tmp, name;
	/* Not a member, go away. */
	if (!IS_MEMBER(this_player()))
	{
		return 0;
	}
	/* Input would be helpful. */
	if (!strlen(str))
	{
		notify_fail("Choose what? A house maybe?\n");
		return 0;
	}
	name = this_player()->query_real_name();
	/* Stoopid elfie, your already in a house. */
	if (SERVER->query_house(name))
	{
		write("You already belong to a house.\n");
		return 1;
	}
	str = capitalize(lower_case(str));
	
	/* Are we asking to join a real house? */
	tmp = SERVER->query_house("all");
	if (member_array(str, tmp) == -1)
	{
		write("No such house exists, try again.\n");
		return 1;
	}
	/* Rut-roh! An error.. ickyness */
	if (!SERVER->add_to_house(name, str, name))
	{
		write("An error has prevented you from claiming "+
		"that house, please make a bug report.\n");
		return 1;
	}
	write("You choose the House " + str + " as your own.\n"+
	"A servant of the Houses fetches your new mantle "+
	"and places it upon your shoulders, taking the old "+
	"one away with him.\n");
	say(QCTNAME(this_player()) + " has chosen the House "+
	"" + str + " as their own.\n");
	
	/* In case we don't have one */
	if (!present(OBJECT_ID, this_player()))
	{
		clone_object(OBJECT)->move(this_player());
	}
	
	/* This resets the player's mantle with house colours */
	present(OBJECT_ID, this_player())->init();
	write_file(LOG + "members",
	ctime(time()) + " " + capitalize(this_player()->query_real_name()) +
	" (age = " + (this_player()->query_age() / 43200) +
	", avg = " + this_player()->query_average_stat() +
	") joined house " + str + ".\n");
	return 1;
}

/* Leave a household. */
public int
leave_house(string str)
{
	string house, name = this_player()->query_real_name();
	if (!IS_MEMBER(this_player()) || !(house = SERVER->query_house(name)))
	{
		return 0;
	}
	str = lower_case(str);
	if (str != "my house" && str != "house" &&
        str != lower_case("house " + house))
        {
		return notify_fail("Leave what, your House?");
	}
	if (!SERVER->remove_from_house(name, name))
	{
		write("An error occured preventing your leaving.\n"+
		"Please make a bug report.\n");
		return 1;
	}
	write("You leave the House " + house + " and turn in your "+
	"mantle for your old one.\n");
	say(QCTNAME(this_player()) + " has left the House "+
	"" + house + ".\n");
	
	/* reinitialize colours of the mantle */
	present(OBJECT_ID, this_player())->init();
	write_file(LOG + "members",
	ctime(time()) + " " +
	capitalize(this_player()->query_real_name()) +
	" (age = " + (this_player()->query_age() / 43200) +
	", avg = " + this_player()->query_average_stat() +
	") left house " + house + ".\n");
	return 1;
}

public void
init()
{
	::init();
	init_seat();
	init_fire();
	add_action(list, "list");
	add_action(request, "request");
	add_action(leave_house, "leave");
	add_action(choose_house, "choose");

}
