/*
 *      /d/Gondor/common/dunedain/obj/guild_book.c
 *
 *      Copyright (c) 1995, 1997 by Christian Markus
 *      Based on the dunedain join book
 *      Modified by Finwe, August 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

//#include "/d/Gondor/defs.h"
//#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"
#include "/d/Shire/sys/defs.h"
#include "../noldor.h"


int     read_chapter(string str);
string  read_index();

public void
create_object()
{
    set_short("book of scrolls on a pedestal");
    set_name("book");
    add_name("scrolls");
    add_name("noldor book");
    set_long("The large book of scrolls is made of leather and " +
        "parchments, bound by mithril bands. It lies open.\n" + 
        read_index());
    add_prop(OBJ_I_NO_GET,"@@try_get");
    add_prop(OBJ_I_LIGHT,1);
}

int
try_get()
{
    write("The book of scrolls is is secured to the pedastal " +
        "and cannot be taken.\n");
    say(QCTNAME(TP)+" tries to take the book from the pedestal, " +
	    "but fails.\n", TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(read_chapter, "read");
}

string
read_index()
{
    return
        "The book is open. Beautiful script fills the page. " +
        "Written in the finest lettering of the Noldor you see " +
        "written:\n\n " +
		"Index of the Noldor Guild\n" +
		"    1. History of the Noldor\n" +
		"    2. Rules and Joining the Noldor\n" +
		"    3. Leaving the Noldor\n" +
		"\n\n";
}

string
read_history()
{
    return "\n\n" +
	    "History of the Noldor\n" +
		"---------------------\n\n" +
"The Noldor are a great family of the Elves. We are the Second Kindred and are well known for our heroic battles and defeats. Noldor is Quenya for 'knowledge' which describes well our nature. Above all else, we desire knowledge more than anything.\n\n"+

"Our greatest creation was the making of the Silmarilli. These gems shined with the light of the Two Trees and eventually became our bane, causing much bloodshed and discontent through the many ages.\n\n"+

"During the Ages of Twilight, the dwarves fashioned the city-fortress of Menegroth for Thingol and his Maia, Melian. Through the Age, the city prospered with the works of the dwarves and elves. The dwarves fashioned a crown to hold a Silmarili and ather than give the crown to Thingol, the dwarves demanded payment to which we refused. "+
"Ultimately, Thingol was slain and the dwarves sacked the beautiful city. Since then we have never trusted the dwarves, knowing their selfishness brought the fall of that great city.\n\n"+

"Our talents are many and are excellent craftspeople. We excel in the art of carving stone and making gems, working metal, learning, inventing languages and scripts, and other beautiful arts. Our ability to carve beautiful gems and shape metal into works of art. We once set aside our animosity for a time with the dwarves during the Second Age.\n\n"+

"During the Second Age Celebrimbor came out of Lindon and foundeded a kingdom at the foot of the Misty mountains near the dwarf-realm of Hadhod, or Khazad-dum as the dwarves call it. This kingdom was home for the Gwaith-i-Mirdain, the greatest jewel and and elven-smiths. It was here that the Dark One came to the " + 
"Gwaith-i-Mirdain, disguised as a teacher, and taught them many things. When the Dark One was revealed, he slew many of our kindred and those that remained, retreated to Imladris with Elrond, leaving behind our fair city, which the dwarves later sacked. For their actions, we despise the dwarves forever.\n\n"+

"Imladris is now one of the last refuges of our fair people. It is here that we reside and enjoy peace and prosperity. Nontheless, we continue to keep an eye on the Shadow tht grows from the East and prepare for what that might bring.\n\n";
}

string
read_join()
{
    return "\n\n" +
	    "Rules and Joining the Noldor\n" +
		"----------------------------\n\n" +
		"As a racial guild, the Noldor have limited abilities and skills. In order to provide these abilities and skills, the Noldor charge its members a low fee. They also have guidelines that members must follow if they are to remain known as Noldor.\n\n" +

		" > All members must remain elf. If by chance you are deceived by\n"+
        "   the Dark One and lose your elven heritage, you will be\n"+
        "   expelled from the guild. \n" +
		" > Players must be agreeable before joining, and Noldo who don't\n" +
        "   remain agreeable will be expelled.\n"+
		" > Those members who remain asleep for too long may awake to find\n" +
        "   themselves no longer counted as Noldor.\n" +
        " > Noldo who kill the good creations and defenders of Arda may be\n"+
        "   expelled, never allowed to join again.\n"+
        "\n"+
		"Even though the valley is large, the guild can only permit a small number of elves to be counted as Noldor. If you believe you can follow these guildelines, you may declare your race as a Noldor. If there is room within the walls, you will be permitted to join, otherwise you will have to try again at another time.\n\n";
}

string
read_leave()
{
    return "\n\n" +
	    "Leaving the Noldor\n" +
		"------------------\n\n" +
		"If there comes a time that you wish to leave the Noldor voluntarily, simply return here and you may abandon the Noldor. You may rejoin at a later date if there is room in the guild. Repeated leaving and joining may anger the elves, and result in a permanent banishment from the guild.\n\n" +
		"Additionally, breaking any of the guidelines above will force you from the guild.\n\n";
}


int
read_chapter(string str)
{
    if (!str)
        return 0;

    str = LOW(str);

    switch (str)
    {
        case "book":
            write(read_index());
            say(QCTNAME(TP)+" reads the index page of the large brown book.\n",TP);
            break;
        case "rules":
		case "chapter 1":
		case "1":
        case "history":
		case "history of the noldor":
            write(read_history());
            say(QCTNAME(TP)+" turns a page and reads about the " +
                "history of the Noldor.\n",TP);
            break;
		case "2":
		case "chapter 2":
		case "join":
        case "joining":
        case "joining the noldor":
        case "rules":
		case "rules of the noldor":
		case "rules and joining the noldor":
            write(read_join());
            say(QCTNAME(TP)+" turns a page and reads the rules " +
                "and how to join the Noldor.\n",TP);
            break;
		case "3":
		case "chapter 3":
		case "leave":
        case "leaving":
        case "leaving the noldor":
            write(read_leave());
            say(QCTNAME(TP)+" turns a page and reads about how " +
                "to leave the Noldor.\n",TP);
            break;
		default:
            NF("There is no such chapter!\n");
            return 0;
            break;
    }

    return 1;
}