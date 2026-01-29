/*
 * Matron's room for Drow Guild
 * By Finwe, May 2006
 */

#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "/d/Faerun/defs.h"
#define "/d/Faerun/guilds/drow/drow.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <const.h>
#include <macros.h>
#include <mail.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";

#define FLAG_CITY     1
#define FLAG_HOUSE    2
#define FLAG_DEITY    4
#define FLAG_DONE     8

#define PROP_CITY   "_temp_s_drow_from_city"
#define PROP_DEITY  "_temp_as_drow_deity"
#define PROP_HOUSE  "_temp_s_drow_claimed_house"
#define PROP_HOUSES "_temp_as_drow_claimable_houses"
#define SECONDS     86400
#define DAYS        30
//#define MORE(x)    this_player()->more(read_file(x, 2))

//inherit (P_FAERUN_STD + "faerun_room");

public void more_city(void);
public void more_deity(void);
private string *gods = ({});
private mapping cities = ([]);
//int banish_time = SECONDS * DAYS;
int banish_time = 300;


private void
create_drow_room()
{
    setuid();
    seteuid(getuid());

    set_short("Entrance Cave");
    set_long(short() + ". This is a cave that was carved out of the mountain and has been enlarged. The walls are decorated with carvings, and a large spider adorns the floor. Fungi grow on the walls and provide some light to the cave. A large book has been chained to a wall.\n");

    add_item(({"plaque"}),
        "It is large and made of bone-white material. The plaque " +
        "has symbols and writing on it which you can read.\n");
    add_cmd_item(({"plaque"}),
        "read", "@@scroll_toc@@");

    add_item("fungi",
        "The fungi are orange, red, and blue colored. They grow in cracks and crevices on the wall and provide some light to thw cave.\n");

    room_add_object("/d/Faerun/guilds/drow/race/join_book");
/*
    add_item(({"fifth scroll", "5th scroll", "eilistraee", "eilistraee scroll"}),
        "It is a large plaque made of bone-bone white material. At " +
        "the top of the plaque you see the image of a full size, nude " +
        "drow. She has long hair and is dancing with a silver bastard " +
        "sword before a full moon. Below the symbol is some writing.\n");
    add_cmd_item(({"fifth scroll", "5th scroll", "eilistraee", "eilistraee scroll"}),
        "read", "@@eilistraee@@");

    add_item(({"sixth scroll", "6th scroll", "ghaunaduar", "ghaunaduar scroll"}),
        "It is a large plaque made of bone-bone white material. At the " +
        "top of the plaque you see the image of a purplish eye on purple, " +
        "violet and black circles. Underneath the symbol is some writing.\n");
    add_cmd_item(({"sixth scroll", "6th scroll", "ghaunaduar", "ghaunaduar scroll"}), 
        "read", "@@ghaunaduar@@");

    add_item(({"seventh scroll", "7th scroll", "kiaransalee", "kiaransalee scroll"}),
        "It is a large plaque made of bone-bone white material. At the " +
        "top of the plaque you see the image of a full size, female " +
        "drow hand wearing silver rings. There is some writing under " +
        "the symbol.\n");
    add_cmd_item(({"seventh scroll", "7th scroll", "kiaransalee", "kiaransalee scroll"}),
        "read", "@@kiaransalee@@");

    add_item(({"eighth scroll", "8th scroll", "lolth", "lolth scroll"}),
        "It is a large plaque made of bone-bone white material. At the " +
        "top of the plaque you see the image of a large, black spider " +
        "with a female drow head hanging from a spider web. Below the " +
        "symbol is some writing to read.\n");
    add_cmd_item(({"eighth scroll", "8th scroll", "lolth", "lolth scroll"}),
        "read", "@@lolth@@");

    add_item(({"ninth scroll", "9th scroll", "selvetarm", "selvetarm scroll"}),
        "It is a large plaque made of bone-bone white material. At the " +
        "top of the plaque you see the image of a large spider on a " +
        "crossed sword and mace. There is some writing under the symbol.\n");
    add_cmd_item(({"ninth scroll", "9th scroll", "selvetarm", "selvetarm scroll"}),
        "read", "@@selvetarm@@");

    add_item(({"tenth scroll", "10th scroll", "vhaeraun", "vhaeraun scroll"}),
        "It is a large plaque made of bone-bone white material. At the " +
        "top of the plaque you see the image of a pair of black glass " +
        "lenses peering from behind a mask. Under the symbol is some " +
        "writing you may read.\n");
    add_cmd_item(({"tenth scroll", "10th scroll", "vhaeraun", "vhaeraun scroll"}),
        "read", "@@vhaeraun@@");
*/    
    add_exit("board_pub", "north");
    add_exit("admin", "south");
    add_exit("board_pri", "west");
    add_exit("", "northeast");
}

/* This removes the temporary props we set on applicants. */
private void
cleanup_props(object who)
{
    gods = ({});
    cities = ([]);
    who->remove_prop(PROP_CITY);
    who->remove_prop(PROP_HOUSE);
    who->remove_prop(PROP_DEITY);
    who->remove_prop(PROP_HOUSES);
}

/* This function does the actual shadow loading and server updates. */
private void
finalize_joining(object who)
{
    object shadow = clone_object(GUILD_SHADOW);

    /* Make sure the shadow loads. */
    if (!objectp(shadow))
    {
	write("How odd, it would appear that your supplications "+
	  "cannot be heard at this time, file a bug report.\n");
	return;
    }

    /* Make sure applicant can join the guild. */
    if (shadow->shadow_me(who, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
	write("How odd, it would appear that your supplications "+
	  "cannot be heard at this time, file a bug report.\n");
	cleanup_props(who);
	return;
    }

    /* Clear the racial guild stat. */
    who->clear_guild_stat(SS_RACE);

    /* Initialize member into guild server. */
    GSERVER->add_member(who);

    /* Set the city the applicant has chosen. */
    GSERVER->set_member_city(who, who->query_prop(PROP_CITY));

    /* Set the deity the applicant has chosen. */
    GSERVER->set_member_deity(who, who->query_prop(PROP_DEITY));

    /* Claim the House if appropriate to do so. */
    if (who->query_prop(PROP_HOUSE) &&
	!GSERVER->claim_house(who,
	    who->query_prop(PROP_HOUSE),
	    who->query_prop(PROP_CITY)))
    {
	write("The House you chose has already been "+
	    "claimed, you shall have to choose anew.\n");
    }

    /* Update info in shadow for titles and whatnot. */
    who->update_member_info_race();

    /* Print a message. */
    tell_room(TO, QCTNAME(who) + " joins the Drow race!\n", who, who);
    write("\nYou are now a full fledged member of the Drow race!\n\n");

    /* Clear the props. */
    cleanup_props(who);
}

/* This is a menu-based system where the applicant must choose
 * the necessary bits to join the guild. */
private void
process_applicant(string str, int flag)
{
    /* See if the player wants to abort. */
    if (str == "quit" || str == "~q")
    {
	write("You have chosen to abort the joining process.\n");
	cleanup_props(TI);
	return;
    }

    /* Check our joining status. */
    switch(flag)
    {
    /* Initial phase, must choose a city to be from. */
    case FLAG_CITY:
	if (!m_sizeof(cities))
	    cities = DROW_CITIES;

	if (!strlen(str))
	{
	    write("\nWell, well, well...A potential Drow!\n" +
	    "You must first choose your city of heritage.\n\n" +
	    "You may append the name with a '?' for help, ie 'Ched Nasad?',\n" +
	    "or enter 'quit' to abort the process at any time.\n\n" +
	    "Choose one of the following cities:\n");
	    write(sprintf("%-#75s\n\nYour choice: ",
		implode(m_indices(cities), "\n")));
	    input_to(&process_applicant(, flag));
	}
	else
	{
	    if (str[-1..] == "?" && cities[str[..-2]])
	    {
		/* Applicant requested help on a city. */
		TI->more(read_file(sprintf("%scities/%s", GUILD_HELP,
			cities[str[..-2]][1])), 0, more_city);
	    }
	    else if (cities[str])
	    {
		/* Player has chosen a city. */
		TI->add_prop(PROP_CITY, str);
		write("Ahhh...you have chosen the city of "+ str +
		    ", an excellent choice!\n\n");

		/* Move to next step. */
		if (TI->query_gender() == G_FEMALE)
		    process_applicant("", FLAG_HOUSE);
		else
		    process_applicant("", FLAG_DEITY);
	    }
	    else
	    {
		/* Invalid City name. */
		write("\nThat is not the name of a proper Drow city.\n" +
		    "You must enter the name exactly as presented.\n\n" +
		    "Try again, or enter 'quit' to abort.\n\n");
		write("Choose one of the following cities:\n");
		write(sprintf("%-#75s\n\nYour choice: ",
		    implode(m_indices(cities), "\n")));
		input_to(&process_applicant(, flag));
	    }
	}
	break;
    /* Femme-only phase, claim a House from their city if it's available. */
    case FLAG_HOUSE:
	if (!strlen(str))
	{
	    string *avail, city;

	    /* See what houses are available. */
	    city = TI->query_prop(PROP_CITY);
	    avail = cities[city][0];
	    avail -= GSERVER->query_houses(city);

	    if (sizeof(avail))
	    {
		/* There are Claimable Houses, present the offer. */
		TI->add_prop(PROP_HOUSES, avail);
		write("As a potential Drow female, you have the Honour " +
		    "of choosing whether or not to claim a Noble House "+
		    "from your chosen city.\n\nClaim one of the following: "+
		    " (or 'none' to forfeit this opportunity)\n");
		write(sprintf("%-#75s\n\nYour choice: ", implode(avail, "\n")));
		input_to(&process_applicant(, flag));
	    }
	    else
	    {
		/* No houses are Claimable, skip to next step. */
		process_applicant("", FLAG_DEITY);
	    }
	}
	else
	{
	    if (str == "none")
	    {
		/* Didn't want to claim a House. */
		write("You shall remain Houseless for now.\n\n");
		process_applicant("", FLAG_DEITY);
	    }
	    else if (member_array(str, TI->query_prop(PROP_HOUSES)) == -1)
	    {
		/* Not the name of an available House. */
		write("There is no such House available to claim. "+
		    "Be sure you enter it exactly as presented.\n"+
		    "Try again, or enter 'quit' to abort.\n\n");
		write("Claim one of the following: "+
		    "(or 'none' to forfeit this opportunity)\n");
		write(sprintf("%-#75s\n\nYour choice: ",
			implode(TI->query_prop(PROP_HOUSES), "\n")));
		input_to(&process_applicant(, flag));
	    }
	    else
	    {
		/* Applicant has laid their claim on a House. */
		TI->add_prop(PROP_HOUSE, str);
		write("I see you have aspirations for House "+ str +
		    ", very impressive!\n\n");
		process_applicant("", FLAG_DEITY);
	    }
	}
	break;
    /* Here the supplicant chooses a Drow deity to follow. */
    case FLAG_DEITY:
	if (!strlen(str))
	{

	    write("This is the final stage where you must now choose the deity " +
            "in which you shall devote your life as a Drow.\n" +
            "You may append the name with a '?' for help, ie 'Lolth?', \n" +
            "or enter 'quit' to abort the process at any time.\n\n" +
            "Choose one of the following deities:\n\n");
	    write(sprintf("%-#75s\n\nYour choice: ", implode(gods, "\n")));
	    input_to(&process_applicant(, flag));
	}
	else
	{
	    str = capitalize(str);

	    if (str[-1..] == "?" && IN_ARRAY(str[..-2], gods))
	    {
		/* Applicant requested help on a deity. */
		TI->more(read_file(sprintf("%sdeities/%s", GUILD_HELP,
			str[..-2])), 0, more_deity);
	    }
	    else if (!IN_ARRAY(str, gods))
	    {
		write("That was not the name of a Drow deity, choose "+
		    "again from the following:\n\n");

		write(sprintf("%-#75s\n\nYour choice: ", implode(gods, "\n")));
		input_to(&process_applicant(, flag));
	    }
	    else
	    {
		/* Player has chosen a city. */
		TI->add_prop(PROP_DEITY, ({ str }));
		write("Ahhh...you have chosen to worship "+ str +
		    ", an interesting choice.\n\n");

		/* Move to next step. */
		process_applicant("", FLAG_DONE);
	    }
	}
	break;
    /* The final step, before they become a member. */	
    case FLAG_DONE:
	if (str == "commit myself")
	{
	    finalize_joining(TI);
	}
	else
	{
	    write("This is your last chance to rethink your decision.\n");
	    write("If you are ready to join the Drow race, then "+
		"enter the phrase 'commit myself'.  Otherwise enter "+
		"'quit' to abort the process.\n");
	    write("Thy choice? ");
	    input_to(&process_applicant(, flag));
	}
	break;
    /* Try to catch errors. */
    default:
	cleanup_props(TI);
	write("A serious error has occured, make a bugreport!\n");
	break;
    }
}

/* This is just a helper function for when the player
 * requests info on a City, just dumps them back into
 * the application process. */
public void
more_city(void)
{
    write("\nChoose one of the following cities:\n");
    write(sprintf("%-#75s\n\nYour choice: ",
	    implode(m_indices(cities), "\n")));
    input_to(&process_applicant(, FLAG_CITY));
}

public void
more_deity(void)
{
    write("\nChoose one of the following deities:\n");
    write(sprintf("%-#75s\n\nYour choice: ", implode(gods, "\n")));
    input_to(&process_applicant(, FLAG_DEITY));
}

/* This is the JOIN command, does a couple basic checks
 * then kicks off the menu system. */
public int
f_djoin(string str)
{
    if (str != "drow")
    {
	notify_fail("Syntax:  djoin drow\n");
	return 0;
    }

    if (TI->query_race_name() != "elf")
    {
	write("Non-elves need not apply.\n");
	return 1;
    }

    if (TI->query_guild_name_race() == GUILD_NAME)
    {
	write("But you are a member of the guild already!\n");
	return 1;
    }

    if ((time() - GSERVER->query_banished(TI)) < banish_time)
    {
        write("You have not waited long enough to prove yourself worthy " +
        "to rejoin the Drow.\n");


	return 1;
    }

    gods = sort_array(get_dir(GUILD_HELP + "deities/"));
    process_applicant("", FLAG_CITY);
    return 1;
}

/* The LEAVE guild command. */
public int
f_dbetray(string str)
{
    object obj;

    if (str != "drow")
    {
	notify_fail("dbetray drow, perhaps?\n");
	return 0;
    }

    /* Make sure we are a member first. */
    if (TI->query_guild_name_race() != GUILD_NAME)
    {
	write("You have to be a member before you can quit.\n");
	return 1;
    }

    /* Save us a headache. */
    if (GSERVER->query_member(TI, HOUSE_MEMBER))
    {
	write("You cannot leave the Drow while belonging to a House.\n");
	return 1;
    }

    /* Print a message */
    say(QCTNAME(TI) + " leaves the racial Drow!\n");
    write("You leave the racial Drow!\n");

    /* Remove shadow. (it does all the work) */
    TI->remove_guild_race_drow(TI);

    return 1;
}

/* Add commands into the room. */
public void
init(void)
{
    ::init();

    add_action(   f_djoin, "djoin"   );
    add_action( f_dbetray, "dbetray" );
}


string scroll_toc()
{
    return "\n\nOn the plaque you read:\n\n" +
    "+------------------------------------------+\n" +
    "|                                          |\n" +
    "|  To learn more about the Drow, you must  |\n" +
    "|  read the book that is chained to the    |\n" +
    "|  wall.                                   |\n" +
    "|                                          |\n" +
    "+------------------------------------------+\n" +
    "\n";
}
/*

int scroll5()
{
    MORE(DEITY_DIR + "eilistraee"; 
    return 1;
}

int scroll6()
{
    MORE(DEITY_DIR + "ghaunaduar"; 
    return 1;
}

int scroll7()
{
    MORE(DEITY_DIR + "kiaransalee"; 
    return 1;
}

int scroll8()
{
    MORE(DEITY_DIR + "lolth"; 
    return 1;
}

int scroll9()
{
    MORE(DEITY_DIR + "selvetarm"; 
    return 1;
}

int scroll10()
{
    MORE(DEITY_DIR + "vhaeraun"; 
    return 1;
}
*/
