/*
 * Join room for Drow Racial
 * By Finwe, May 2006
 * banish time set to 5 seconds for testing purposes.
 */
 
 /* Edited by Leia 8/16/2010
 *  Changes documented where they occurred.
 */

#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "/d/Faerun/defs.h"
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
#define MORE(x) this_player()->more(read_file(x,2))
#define UDARK_DIR   "/d/Faerun/underdark/dark_dom/rooms/"
#define MIN_SIZE    75      /* GA size */

//inherit (P_FAERUN_STD + "faerun_room");

public void more_city(void);
public void more_deity(void);
private string *gods = ({});
private mapping cities = ([]);
// changed to 1 day.
int banish_time = SECONDS * 1;
// banish time 30 days
// int banish_time = SECONDS * DAYS;
// int banish_time = 5;


private void
create_drow_room()
{
    object board;

    setuid();
    seteuid(getuid());

    set_short("Entrance Cave");
    set_long(short() + ". This is a cave that was carved out of the " +
        "mountain and has been enlarged. The walls are decorated with " +
        "carvings, and a large spider adorns the floor. Fungi grow on " +
        "the walls and provide some light to the cave. A large book " +
        "has been chained to a wall.\n");

    room_add_object("/d/Faerun/guilds/drow/race/join_book");

if (!objectp(board))
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name(BOARD_PU_DIR);
        board->move(this_object());
    }

    add_item(({"board", "large board"}),
        "It's a large piece of stone. It is ornately carved and set " +
        "against a wall. Notes are attached to it for anyone to read. " +
        "The board is limned in faerie fire, which makes it glow in " +
        "the cave.\n");
/*
    add_item(({"bookcase", "bookshelf"}),
        "The bookcase has several shelves and decorated with spider web " +
        "designs. Many scrolls are neatly stacked on the shelves.\n");
*/
    add_item(({"spider"}),
        "The spider is life-like and decorates the floor. It's black " +
        "with a the head of a female drow hanging from a spider web.\n");
/*    
    add_item(({"plaque"}),
        "It is large and made of bone-white material. The plaque " +
        "has symbols and writing on it which you can read.\n");
    add_item(({"scrolls"}),
        "They are large rolls of parchments. They look well read and " +
        "contain information about the drow. The scrolls are neatly " +
        "stacked on the bookshelf. Next to the book shelf is a plaque.\n");
    add_item(({"parchments", "parchment"}),
        "They are skins prepared as a material on which to write on. " +
        "The parchments are wrapped around poles that make up the scrolls.\n");
    add_item(({"dowels", "poles"}),
        "They are intricately carved and wrapped with parchment. The " +
        "poles make up the handles of the scrolls.\n");
    add_cmd_item(({"plaque"}),
        "read", "@@scroll_toc@@");
*/
//join scrolls
/*
    add_item(({"1st scroll", "first scroll", "about scroll", "about", 
            "2nd scroll", "second scroll", "history scroll", "history", 
            "3rd scroll", "third scroll", "joining scroll", "joining", 
            "4th scroll", "fourth scroll", "leaving scroll", "leaving"}),
        "The scroll is large and rolled up on the shelf. It looks well " +
        "read with some frayed edges. It belongs to the group of scrolls " +
        "describing the drow.\n");
    add_cmd_item(({"1st scroll", "first scroll", "about scroll", "about"}), 
        "read", "@@read_scroll1@@");
    add_cmd_item(({"2nd scroll", "second scroll", "history scroll", "history"}), 
        "read", "@@read_scroll2@@");
    add_cmd_item(({"3rd scroll", "third scroll", "joining scroll", "joining"}), 
        "read", "@@read_scroll3@@");
    add_cmd_item(({"4th scroll", "fourth scroll", "leaving scroll", "leaving"}), 
        "read", "@@read_scroll4@@");

// deity scrolls
    add_item(({"5th scroll", "fifth scroll", "eilistraee scroll", "eilistraee", 
            "6th scroll", "sixth scroll", "ghaunadaur scroll", "ghaunadaur", 
            "7th scroll", "seventh scroll", "kiaransalee scroll", "kiaransalee", 
            "8th scroll", "eighth scroll", "lolth scroll", "lolth", 
            "9th scroll", "nineth scroll", "selvetarm scroll", "selvetarm", 
            "10th scroll", "tenth scroll", "vhaeraun scroll", "vhaeraun"}), 
        "The scroll is large and rolled up on the shelf. It looks well " +
        "read with some frayed edges. It belongs to the group of scrolls " +
        "that describe the drow deities.\n");

    add_cmd_item(({"5th scroll", "fifth scroll", "eilistraee scroll", "eilistraee"}), 
        "read", "@@read_scroll5@@");
    add_cmd_item(({"6th scroll", "sixth scroll", "ghaunadaur scroll", "ghaunadaur"}), 
        "read", "@@read_scroll6@@");  
    add_cmd_item(({"7th scroll", "seventh scroll", "kiaransalee scroll", "kiaransalee"}), 
        "read", "@@read_scroll7@@");
    add_cmd_item(({"8th scroll", "eighth scroll", "lolth scroll", "lolth"}),
        "read", "@@read_scroll8@@");
    add_cmd_item(({"9th scroll", "nineth scroll", "selvetarm scroll", "selvetarm"}), 
        "read", "@@read_scroll9@@");
    add_cmd_item(({"10th scroll", "tenth scroll", "vhaeraun scroll", "vhaeraun"}),
        "read", "@@read_scroll10@@");

// City scrolls
    add_item(({"11th scroll", "eleventh scroll", "ched nasad scroll", "ched nasad",
            "12th scroll", "twelfth scroll", "menzoberranzan scroll",
                "menzoberranzan",  
            "13th scroll", "thirteenth scroll", "sshamath scroll", "sshamath", 
            "14th scroll", "fourteenth scroll", "thal'katkhact scroll"}), 
        "The scroll is large and rolled up on the shelf. It looks well " +
        "read with some frayed edges. It belongs to the group of scrolls " +
        "drow cities and houses.\n");
    add_cmd_item(({"11th scroll", "eleventh scroll", "ched nasad scroll", "ched nasad"}),
        "read", "@@read_scroll11@@");
    add_cmd_item(({"12th scroll", "twelfth scroll", "menzoberranzan scroll",
            "menzoberranzan"}),
        "read", "@@read_scroll12@@");
    add_cmd_item(({"13th scroll", "thirteenth scroll", "sshamath scroll", "sshamath"}),
        "read", "@@read_scroll13@@");
    add_cmd_item(({"14th scroll", "fourteenth scroll", "thal'katkhact scroll", "thal'katkhact"}),
        "read", "@@read_scroll14@@");
*/
    add_exit("shop", "north");
    add_exit("board_pri", "east", "@@check_member@@");
    add_exit(UDARK_DIR + "tu39", "west");
//    add_exit("/d/Faerun/common/domain_office", "northeast");
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
	write("How odd. It seems your supplications cannot be heard at " +
        "this time. You need to file a bug report.\n");
	return;
    }

    /* Make sure applicant can join the guild. */
    if (shadow->shadow_me(who, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
	write("How odd. It would appear that your supplications "+
	  "cannot be heard at this time. File a bug report.\n");
	cleanup_props(who);
	return;
    }

    /* Clear the racial guild stat. */
    who->clear_guild_stat(SS_RACE);

    /* Clear their prior departure, as they have rejoined. */
    GSERVER->remove_banished(who);

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
	    "claimed. You shall have to choose a new House.\n");
    }

    /* Update info in shadow for titles and whatnot. */
    who->update_member_info_race();

    /* Print a message. */
    tell_room(TO, QCTNAME(who) + " joins the drow race!\n", who, who);
    write("\nYou are now a full fledged member of the drow race!\n\n");

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
	    write("\nWell, well, well...A potential drow!\n" +
	    "You must first choose your city of heritage.\n\n\n" +
	    "You may append the name with a '?' to learn more about city, " +
        "ie 'Ched Nasad?',\n" +
	    "or enter 'quit' to abort the process at any time.\n\n\n" +
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
		write("\nThat is not the name of a proper drow city.\n" +
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
		write("As a potential drow female, you have the Honour " +
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
            "in which you shall devote your life as a drow.\n\n" +
            "You may append the name with a '?' to learn mor about a deity, ie 'Lolth?', \n" +
            "or enter 'quit' to abort the process at any time.\n\n\n" +
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
		write("That was not the name of a drow deity, choose "+
		    "again from the following:\n\n");

		write(sprintf("%-#75s\n\nYour choice: ", implode(gods, "\n")));
		input_to(&process_applicant(, flag));
	    }
	    else
	    {
		/* Player has chosen a city. */
		TI->add_prop(PROP_DEITY, ({ str }));
		write("Ahhh.. you have chosen to worship "+ str +
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
	    write("If you are ready to join the drow race, then "+
		"enter the phrase 'commit myself'.  Otherwise, enter "+
		"'quit' to abort the process.\n");
	    write("Your choice? ");
	    input_to(&process_applicant(, flag));
	}
	break;
    /* Try to catch errors. */
    default:
	cleanup_props(TI);
	write("A serious error has occured. Please make a bug report!\n");
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

// must be a GA or larger to join.
    if (TI->query_average_stat() < MIN_SIZE)
    {
        write("You are too small to join. Come back when you are larger!\n");
        return 1;
    }

    if (TI->query_guild_name_race() == GUILD_NAME)
    {
	write("But you are a drow already!\n");
	return 1;
    }

//Removed to accomodate drow who wish to switch cities/houses due to alignment changes, etc.
//Didn't make sense not to allow them to do so. Removing the timer was the easiest way to do
//this, however, it might be wise in the future to just write functionality to allow them to
//switch and add the timer back in. -Leia
/*
    if ((time() - GSERVER->query_banished(TI)) < banish_time)
    {
        write("You have not waited long enough to prove yourself worthy " +
        "to rejoin the drow.\n");


	return 1;
    }
*/

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
	write("You cannot leave the drow while belonging to a House.\n");
	return 1;
    }

    /* Print a message */
    say(QCTNAME(TI) + " leaves the racial drow!\n");
    write("You are no longer a drow!\n");

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
"                             +--------------+\n" +
"                      +-----/                \\-----+\n" +
"                 +---/                              \\---+\n" +
"             +--/          D R O W   G U I L D           \\--+\n" +
"+-----------/                                                \\----------+\n" +
"|                                                                       |\n" +
"|  This is the index of the scrolls stacked on the bookcase. You should |\n" +
"|  read them for more information about drow, their deities, and their  |\n" +
"|  cities.                                                              |\n" +
"|                                                                       |\n" +
"|  Drow Guild                        Drow Cities and Houses             |\n" +
"|  ----------                        -----------------------            |\n" +
"|   1. About the Drow                11. Ched Nasad,                    |\n" +
"|   2. History of the Drow               Houses: Arkhenneld and Zauvirr |\n" +
"|   3. Joining the Drow              12. Menzoberranzan                 |\n" +
"|   4. Leaving the Drow                  Houses: Fey-Branche, Mizzrym,  |\n" +
"|                                        and Xorlarrin                  |\n" +
"|  Drow Deities                      13. Sshamath                       |\n" +
"|  ------------                          Houses: Khalazza, T'orgh, and  |\n" +
"|   5. Eilistraee                        Vyllshan                       |\n" +
"|   6. Ghaunadaur                    14. Thal'katkhact                  |\n" +
"|   7. Kiaransalee                       Houses: Eveningsky and         |\n" +
"|   8. Lolth                             Sweetkiller                    |\n" +
"|   9. Selvetarm                                                        |\n" +
"|  10. Vhaeraun                                                         |\n" +
"+-----------------------------------------------------------------------+\n\n\n";
}

// Guild Scrolls
int read_scroll1()
{
    MORE(JOIN_DIR + "about");
    return 1;
}

int read_scroll2()
{
    MORE(JOIN_DIR + "history");
    return 1;
}

int read_scroll3()
{
    MORE(JOIN_DIR + "joining");
    return 1;
}

int read_scroll4()
{
    MORE(JOIN_DIR + "leaving");
    return 1;
}

// Dieties
int read_scroll5()
{
    MORE(DEITY_DIR + "Eilistraee");
    return 1;
}

int read_scroll6()
{
    MORE(DEITY_DIR + "Ghaunadaur");
    return 1;
}

int read_scroll7()
{
    MORE(DEITY_DIR + "Kiaransalee");
    return 1;
}

int read_scroll8()
{
    MORE(DEITY_DIR + "Lolth");
    return 1;
}

int read_scroll9()
{
    MORE(DEITY_DIR + "Selvetarm");
    return 1;
}

int read_scroll10()
{
    MORE(DEITY_DIR + "Vhaeraun");
    return 1;
}

//Cities
int read_scroll11()
{
    MORE(CITIES_DIR + "ched_nasad");
    return 1;
}

int read_scroll12()
{
    MORE(CITIES_DIR + "menzo");
    return 1;
}

int read_scroll13()
{
    MORE(CITIES_DIR + "sshamath");
    return 1;
}

int read_scroll14()
{
    MORE(CITIES_DIR  + "thal_k");
    return 1;
}


int
check_member()
{
   
   object tp = this_player();
   
   if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
      {
      write("Only drow are allowed past this point.\n");
      return 1;
   }
   return 0;
}
