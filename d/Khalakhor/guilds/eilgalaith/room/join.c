/**********************************************************************
 * - join.c                                                         - *
 * - Created by Tomas, Damaris and Lucius September 2000            - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 * - Allowed humans and elves to join. (Gorboth, July 2011)         - *
 * - Humans can only join as half-elf - Lavellan 2011/07/26         - *
 * - Added better syntax information so make it easier to           - *
 *   to join, also fixed capitalization problem with the            - *
 *   joining syntax. (Cherek, April 2019)                           - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit GUILD_ROOM;
inherit SCROLL;

#define LOG_SIZE      25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))


void
create_guild_room()
{
	string scroll;
	
	set_short("Joining Room");
	set_long("   You are standing in the join room of the "+
	"Eil-Galaith. This room has been decorated simply, but is "+
	"quite elegant. Two of the walls have been adorned with "+
	"bright-coloured tapestries. There is a small table with a "+
	"chair before you.\n");
	add_item(({"room", "area"}), query_long);
	add_item(({"table", "small table", "wooden table", "wood table"}),
	"The table is small in size and made from a dark wood. "+
	"Two scrolls have been placed on top. One scroll is for you to "+
	"read, the other is with quill and an inkwell next to it.\n");
	add_item(({"ink", "inkwell"}),
	"The inkwell is filled with dark ink.\n");
	add_item(({"quill"}),
	"The quill has been placed next to a scroll with an inkwell.\n");
	add_item(({"chair", "wooden chair", "wood chair", "small chair"}),
	"The chair is placed with the table and is small and made "+
	"from a dark wood.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from a mysterious white marble with "+
	"a spiral of black intertwining in seamless patterns, and "+
	"adorned with two tapestries.\n");
	add_item(({"tapestries", "tapestry"}),
	"The tapestries are elegantly woven with silken threads. The "+
	"colours are bright and give dimension to the patterns in the "+
	"tapestries.\n");
	add_item(({"pattern", "patterns"}),
	"The patterns of the tapestries form what appear to be maps "+
	"of Khalakhor.\n");
	add_item(({"map", "maps"}),
	"The maps in the tapestries are only generalized locations "+
	"of Khalakhor, but they have elven flair in their depictions of "+
	"the areas.\n");
	add_item(({"depiction", "depictions"}),
	"The depictions in the map definitely have elven flair and "+
	"style.\n");
	add_item(({"join room", "room"}),
	"This is the join room of the Eil-Galaith. "+
	"This room has been decorated simple but is quite elegant. "+
	"Two of the walls have been decorated with bright coluored "+
	"tapestries. There is a small table with a chair before you.\n");
	
    scroll = "Here you can do the following:\n" +
    "<list surnames>             =  For a list of acceptable surnames.\n"+
    "<choose 'surname'>          =  To join the Eil-Galaith.\n" +
    "<choose 'surname' half-elf> =  To join the Eil-Galaith and become "+
    "half-elven.\n" +
    "<request mantle>            =  To obtain a new mantle.\n"+
    "<leave guild>               =  Leave the Eil-Galaith.\n" +
    "<list>                      =  List current guilds you are affiliated "+
    "with.\n\n"+
    "Elves and humans may join this guild. Elves can decide if they want "+
    "to become half-elven or not when joining, while humans can only join as "+
    "half-elves. To join, use one of the commands listed above, replacing "+
    "'surname' with your chosen surname. For example: <choose Ailia> or "+
    "<choose Ailia half-elf>.\n";
    

        add_item("scroll",scroll);
        add_cmd_item(({"scroll", "the scroll"}), "read", scroll);
        add_prop(ROOM_I_INSIDE, 1);
        add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
        add_prop(ROOM_M_NO_ATTACK, 1);
        clone_here(NPC + "junil")->move(this_object());
        add_exit("entrance", "west");
        add_exit("house", "up");
}


/*
 * Function name: log_guild
 * Description  : This function logs some actions of members of the guild.
 *                It uses a larger cycle than basically coded.
 * Arguments    : string text - the message to log.
 */
nomask private void
log_guild(string text)
{
	setuid();
	seteuid(getuid());
	if (file_size(GLOG) > LOG_SIZE)
	{
		rename(GLOG, (GLOG + ".old"));
	}
	write_file(GLOG, text);
}

int
add_the_shadow()
{
	object sh;
	mixed why;
	/* Clone the shadow */
	setuid();
	seteuid(getuid());
	
	sh = clone_object(SHADOW);
	
	/* See if this member is acceptable */
	if (stringp(why = sh->acceptable_member(TP)))
	{
		write(why);
	}
	else
	{
		/* Try to add the shadow to the player */
		switch (sh->add_race_shadow(TP))
		{
			case 1:
			/* We have successfully shadowed the player,
			 * so we're set */
			
			TP->clear_guild_stat(SS_RACE);
			
			write("You announce your lineage by picking "+
			"up the quill and signing your name on the "+
			"scroll.\nA young elf enters and places a "+
			"mystic vine to the tip of your left ear then "+
			"drapes it along the back of your neck then "+
			"up to your right ear.\nYou feel a tingling in "+
			"the back of your neck and then the young elf "+
			"hands you a soft grey mantle, signifying your "+
			"acceptance into the "+ GUILD_NAME + "!\n");
			say(QCTNAME(TP) + " picks up the quill and "+
			"signs the scroll.\nA young elf enters and "+
			"places a vine to the tip of "+HIS(TP) +" left "+
			"ear then drapes it along the back of "+
			""+HIS(TP) +" neck then up to "+HIS(TP) +" "+
			"right ear. You watch in amazement as it is "+
			"absorbed into "+HIS(TP) +" skin. Then the "+
			"young elf hands "+HIM(TP) +" a soft grey "+
			"mantle, signifying acceptance into the "+
			""+ GUILD_NAME + "!\n");
			
			if (!present(OBJECT_ID, TP))
			{
				clone_object(OBJECT)->move(TP);
			}
			log_file("eil_members", capitalize(TP->query_real_name()) +" "+
			"joined " + ctime(time()) + "\n");
			return 1;
			break;
			case -4:
			/* The player has a race guild already, or one
			 * of his existing guilds has blocked this one. */
			write("Your other guilds don't want you in "+
			"this one!\n");
			break;
			default:
			
			/* Some error in shadowing */
			write("OH NO! now you went and did it! You "+
			"broke the guild! Please <mail aop> and "+
			"report the error.\n");
			break;
		}
	}
	/* We couldn't shadow the player, so remove the shadow */
	sh->remove_shadow();
	return 1;
}

int
add_me(string str)
{
    string *arr;
    int race;
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    arr = explode(str, " ");
    arr[0] = capitalize(arr[0]);
    if ((TP->query_race_name() == "human") &&
        ((sizeof(arr) != 2) || (arr[1] != "half-elf")))
    {
        write("As a human, you may only join as a half-elf.\n");
        return 1;
    }   
    if (!IN_ARRAY(TP->query_race_name(), ({ "elf", "human" }) ))
    {
        write("You are not of the correct race for joining.\n");
        return 1;
    }
    if (TP->query_guild_member("race"))
    {
        write("You still belong to another racial guild.\n");
        return 1;
    }
    if (TP->query_alignment() <= GUILD_MIN_ALIGN)
    {
        write("The " + GUILD_NAME + " seeks elves of good "+
        "and finds your heart unworthy.\n");
        return 1;
    }
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("The " + GUILD_NAME + " appreciate life, not "+
        "death.\nCorpses need not apply.\n");
    return 1;
    }
//    arr = explode(str, " ");
    str = TP->query_real_name();
    if (SERVER->query_member(str))
    {
        write("You are already a member, find something "+
        "more productive to do.\n");
        return 1;
    }
    if ((sizeof(arr) == 2) && (arr[1] == "half-elf"))
        race = 1; 
    if (member_array(arr[0], SURNAMES) == -1)
    {
        write("That is not a valid surname choice, please "+
        "try again.\n");
        return 1;
    }
    if (SERVER->add_member(str, arr[0], race))
    {
        add_the_shadow();
        write("Welcome home.\n"+
        "For assistance type: <eghelp>\n");
    }
    else
    {
        write("You were not able to join, please make a bug "+
        "report.\n");
    }
    return 1;
}


int
leave(string str)
{
	if (str != "guild" &&  str != "the guild")
	{
		NF("Leave what? The guild??\n");
		return 0;
	}
	str = TP->query_real_name();
	if (!SERVER->query_member(str))
	{
		write("You are not a member, how do you propose "+
		"to leave?\n");
		return 1;
	}
	if (!TP->leave_guild_race())
	{
		write("There has been an error, please contact "+
		"a wizard or an aop member.\n");
	}
	else
	{
		say(QCTNAME(TP) + " leaves the " + GUILD_NAME + ".\n");
		log_file("eil_members", capitalize(TP->query_real_name()) +
		" left " + ctime(time()) + "\n");
	}
	return 1;
}

int
list(string str)
{
	if (strlen(str))
	{
		if (str == "surnames")
		{
			return print_scroll(sort_array(SURNAMES),
			"These are the surnames of the " + GUILD_NAME);
		}
		return 0;
	}
	str = TP->list_major_guilds();
	if (str)
	write("You are a member of the following guilds.\n" + str);
	else
	write("You are not a member of any important guilds.\n");
	return 1;
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

void
init()
{
	::init();
	add_action(list, "list");
	add_action(add_me, "choose");
	add_action(leave, "leave");
	add_action(request, "request");
}
