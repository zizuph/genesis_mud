/*
 * /d/Faerun/guilds/black_flame/obj/bf_book.c
 *
 * Nerull 2022
 */

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "../guild.h"

inherit "/std/scroll";

#define SIGN_ID  ({"instructions"})
#define TO this_object()
#define TP this_player()

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 9; /* how many pages in book */
string  gPage;

void
set_book_is_private(int i){ book_is_private = i; }

string
opened_at_page()
{
    if(book_is_closed) return "The book is closed.\n";
    return "It is opened to page "+LANG_WNUM(what_page)+".\n";
}


/*
 * Function name: create_scroll
 * Description:   creates the general object
 * Arguments:
 */
nomask void
create_scroll()
{
    set_short("black book floating in the air");
    set_name("book");
    add_name("book");
    add_name("Zealot book");
    set_long("This is a large book bound in black leather. It looks "
    +"well read and is floating in the air before you. There are "
    +"instructions next to the book.\n\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"black"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"@@try_get");
	add_prop(OBJ_I_NO_STEAL,"@@try_get");

    add_cmd_item(SIGN_ID, "read", "@@instructions@@");
}


int
instructions(string str)
{
    write(
        "\t.------------------------------------------------------.\n" +
        "\t|                                                      |\n" +
        "\t|   These are the commands for the book:               |\n" +
        "\t|   <open book>          - Open the book               |\n" +
        "\t|   <close book>         - Closes the book             |\n" +
        "\t|   <read book> or       - Read the current page       |\n" +
        "\t|   <read page>                                        |\n" +
        "\t|   <turn page> or       - Turn to next page           |\n" +
        "\t|   <turn page forward>                                |\n" +
        "\t|   <turn page backward> - Turn to previous page       |\n" +
        "\t|   <turn page [num]>    - Turn to page number [num]   |\n" +
        "\t|                                                      |\n" +
        "\t'------------------------------------------------------'\n\n");
    return 1;
}


int
try_get()
{
    write("You don't dare to take the book.\n");
    
    return 1;
}


/*
 * Function name: read_scroll
 * Description:   We need some special stuff for the turn page command
 *        The turn page has the following syntax
 *          turn page - turn forward one page
 *          turn page forward/[backward, back] - turn one page
 *          in the appropriate direction
 *          turn book to/at page <num> - turn to page <num>
 *          where <num> is a string like one, two, eight,
 *          not an integer like 7.
 */
static int
read_scroll(string str)
{
    string where, what;
    if (!str) return ::read_scroll(what);

    if (str == "page")
    {
        gPage = "forward";
        what = "book";
    }
    else if (parse_command(str, ({}), "'page' [to] %w", where))
    {
        gPage = where;
        what = "book";
    }
    else if (!parse_command(str, ({}), "%s 'at' / 'to' 'page' %w", what, 
    where))
    {
        gPage = "";
        what = str;
    }
    else
        gPage = where;
    return ::read_scroll(what);
}


/*
 * Function name: init
 * Description:   initialise the commands
 * Arguments:
 */
void
init()
{
    ::init();
    add_action(read_scroll, "close");
    add_action(read_scroll, "open");
    add_action(read_scroll, "turn");
}


/*
 * Function name: open_me
 * Description:   opens the book (at page one!)
 */
void
open_me()
{
    if (!book_is_closed)
    {
        write("The "+short(TP)+" is already open.\n");
        return;
    }
    what_page = 1;
    write("You open the " + short(TP) + " to page " +
    LANG_WNUM(what_page) + ".\n");
    say(QCTNAME(TP) + " opens the " + QSHORT(TO) + ".\n");
    book_is_closed = 0;
}


/*
 * Function name: close_me
 * Description:   closes the book again
 */
void
close_me()
{
    if (book_is_closed)
    {
        write("The " + short(TP) + " is already closed.\n");
        return;
    }
    write("You close the " + short(TP) + ".\n");
    say(QCTNAME(TP) + " closes the " + QSHORT(TO) + ".\n");
    what_page = 1;
    book_is_closed = 1;
}


/*
 * Function name: turn_me
 * Description:   turn the book to the next page
 */
void
turn_me()
{
    int appr_num;

    gPage = previous_object()->query_gPage();
    if (book_is_closed)
    {
        write("But the "+short(TP)+" is closed.\n");
        return;
    }
    appr_num = LANG_NUMW(gPage);
    if (appr_num > 0 && appr_num < maxm_page + 1)
    {
        what_page = appr_num;
        say(QCTNAME(TP)+" turns the "+QSHORT(TO)+" to page "+
            LANG_WNUM(what_page) + ".\n");
        write("You turn the " + short(TP) + " to page " +
              LANG_WNUM(what_page) + ".\n");
        return;
    }

    if (gPage == "forward" || gPage == "")
    {
        if (maxm_page < what_page + 1)
        {
            write("You have reached the last page of the " +
            short(TP) + ".\n");
            return;
        }
        what_page += 1;
        if (maxm_page == what_page)
        {
            say(QCTNAME(TP)+" turns the "+QSHORT(TO)+
                " to the last page.\n");
            write("You turn the "+short(TP)+" to the last page.\n");
        }
        else
        {
            say(QCTNAME(TP)+" turns the "+QSHORT(TO)+
                " to page "+LANG_WNUM(what_page)+".\n");
            write("You turn the "+short(TP)+
                  " to page "+LANG_WNUM(what_page)+".\n");
        }
        return;
    }
    else if (gPage == "backward" || gPage == "backwards"|| gPage == "back" )
    {
        if (what_page == 1)
        {
            write("You cannot turn the " + short(TP) +
                  " below the first page.\n");
            return;
        }
        what_page -= 1;
        say(QCTNAME(TP)+" turns the "+QSHORT(TO)+
            " to page "+LANG_WNUM(what_page)+".\n");
        write("You turn the " + short(TP) +
              " to page " + LANG_WNUM(what_page) + ".\n");
        return;
    }
    else
    {
        write("You may turn the page 'forward' or 'backward'.\n");
        return;
    }
}


/*
 * Function name: read_it
 * Description:   If player wanted to do anything to this book we end up here.
 * Arguments:     verb - The verb the player had used
 */
void
read_it(string verb)
{
    switch (verb)
    {
        case "read":
        case "mread":
            if (book_is_closed)
            {
                write("The "+short(TP)+" is closed.\n");
                break;
            }
            say(QCTNAME(TP)+" reads the "+QSHORT(TO)+".\n");
            read_book_at_page(what_page, verb); break;
        case "turn":
            turn_me(); break;
        case "open":
            open_me(); break;
        case "close":
            close_me(); break;
    }
}


/*
 * Function name: query_gPage
 * Description:   Ask what page info the player gave.
 * Returns:   The same string the player gave
 */
string
query_gPage()
{
    return gPage;
}


string
make_string_from_list(string *names)
{
    int i, s = sizeof(names);
    string text = "";

    sort_array(names);

    if(!s) return "  ----";
    if(find_player(names[0])) text += "*";
    text += capitalize(names[0]);
    for(i = 1; i < s-1; i++)
    {
        if(find_player(names[i])) text += ", *";
        else text += ", ";
        text += capitalize(names[i]);
    }
    if(s > 1)
    {
        if(find_player(names[s-1])) text += " and *";
        else text += " and ";
        text += capitalize(names[s-1]);
    }
    return break_string(text, 60, 5);
}


/*
 * Function name: read_book_at_page
 * Description:   should be redefined in your book. is called from read_me
 * Arguments:     which - read the book at which page
 *        verb  - If the player wanted to read it, or mread it.
 *            To mread something, you can look how the scoll.c does
 *            it in read_it() if needed.
 */
varargs void
read_book_at_page(int which, string verb)
{
    int i;
    string list, *names;

    switch(which)
    {
        case 1:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 1  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |          I N D E X                                      |\n"+
        "    |          ---------                                      |\n"+
        "    |          1           Index, this page                   |\n"+
        "    |          2..3        Kossuth                            |\n"+
        "    |          4..5        Black Flame Zealots                |\n"+
        "    |          6..7        Skills & Abilities                 |\n"+
        "    |          8           Joining                            |\n"+
        "    |          9           Leaving                            |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
         "\n");
        break;              
               
        case 2:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 2  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Kossuth                                              |\n"+
        "    |    -------                                              |\n"+
        "    |    Kossuth, the Fire Lord is the master of the element  |\n"+
		"    |    of Fire, the greatest of the Elements. Through his   |\n"+
		"    |    blessing and purification the world will rise to a   |\n"+
		"    |    new order, after being cleansed from impurity by his |\n"+
		"    |    holy fire.                                           |\n"+
		"    |                                                         |\n"+ 
        "    |    His blessings will be bestowed upon the faithful.    |\n"+ 
		"    |    Theirs will be the wealth, knowledge and power, in   |\n"+ 
		"    |    this world and the next.                             |\n"+ 
		"    |                                                         |\n"+
        "    |    Blessed be Kossuth, the Fire Lord, who will grant    |\n"+ 
		"    |    us the power to purify the world through the fire of |\n"+ 
		"    |    our belief and conviction, thus saving it from the   |\n"+ 
        "    |    corruption and impurities that are so rampant        |\n"+ 
		"    |    in the world today.                                  |\n"+ 
        "    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
	    break; 

        case 3:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 3  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Blessed be the Order of the Black Flame, and the     |\n"+
		"    |    Zealots who act as the hand of Kossuth, exerting his |\n"+
		"    |    will in this world.                                  |\n"+
        "    |                                                         |\n"+
        "    |    Blessed be the Zealots of the Order of the           |\n"+
		"    |    Black Flame, who Guide others to Kossuth's fire so   |\n"+
		"    |    that he may reforge all life into its essential form.|\n"+
		"    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
	    break; 

        case 4:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 4  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Black Flame Zealots                                  |\n"+
        "    |    -------------------                                  |\n"+
        "    |    The Order of the Black Flame enforces the will of    |\n"+
		"    |    Kossuth in this realm. In doing the bidding of your  |\n"+
		"    |    elders in the Order, you serve Kossuth and help      |\n"+
		"    |    prepare the world to receive the purifying fire of   |\n"+
		"    |    Kossuth.                                             |\n"+
        "    |                                                         |\n"+
        "    |    The Order is hierarchical in the meaning that those  |\n"+
		"    |    who have reached a higher terrace of enlightenment   |\n"+
		"    |    have come closer to total purification and           |\n"+
        "    |    understanding of the will of Kossuth, and are worthy |\n"+
		"    |    of your service.                                     |\n"+
        "    |                                                         |\n"+
        "    |    Through purification and service, the Zealots work   |\n"+
		"    |    to bring themselves and the world closer to          |\n"+
		"    |    Kossuth's fire so that the ultimate purification     |\n"+
        "    |    of life may take place.                              |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
	    break; 
		
		case 5:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 5  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    The Order of the Black Flame has smoldered like      |\n"+
		"    |    embers long enough. It is time to fan the flames     |\n"+
		"    |    and rebuild the Order stronger than ever, for        |\n"+
		"    |    Kossuth still lives, and through him we will be      |\n"+
		"    |    reforged in our ultimate form.                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
	    break; 

        case 6:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 6  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Skills & Abilities                                   |\n"+
        "    |    ------------------                                   |\n"+
        "    |    The Black Flame Zealots base their teachings on      |\n"+
		"    |    ancient documents found in the Temple of Kossuth in  |\n"+
		"    |    Proskur. While the Order of the Black Flame has not  |\n"+
		"    |    been seen for a long time, they have existed. Like   |\n"+
		"    |    embers in smoldering peat waiting to light the fire  |\n"+
		"    |    anew, the Order have waited, and now is the time.    |\n"+
        "    |                                                         |\n"+
        "    |    The Order will teach you of alchemical wonders that  |\n"+
		"    |    help enhance yourself and your weapons, to better    |\n"+
		"    |    serve Kossuth in this world. The higher terrace of   |\n"+
		"    |    enlightenment you reach, the more miracles of        |\n"+
		"    |    alchemy you will witness.                            |\n"+
        "    |                                                         |\n"+
        "    |    We only take those who seek purification and know    |\n"+
		"    |    how to fight. Through the enlightenment and          |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
         "\n");
	    break; 				  

        case 7:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 7  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    purification, you will be reforged by Kossuth to     |\n"+
    	"    |    burn away your impurities and enhance your           |\n"+
		"    |    potential.                                           |\n"+
        "    |                                                         |\n"+
        "    |    Although traditionally the Order of the Black Flame  |\n"+
		"    |    used only knives, we have adapted the teachings to   |\n"+
		"    |    suit whatever style of fighting you already know.    |\n"+
        "    |                                                         |\n"+
        "    |    Magic users are welcome to pledge themselves, but be |\n"+
		"    |    warned that the powers granted may be of less benefit|\n"+
		"    |    to you.                                              |\n"+
		"    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
        break;

        case 8:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 8  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Joining                                              |\n"+
        "    |    -------                                              |\n"+
        "    |    Since you are reading this you are already purified. |\n"+
        "    |    Now remains the last step -                          |\n"+
		"    |    <pledge fealty to the Order of the Black Flame>.     |\n"+
        "    |                                                         |\n"+
        "    |    By doing that, you may partake of the knowledge and  |\n"+
		"    |    power of the Order of the Black Flame and count      |\n"+
		"    |    yourself a Zealot.                                   |\n"+
        "    |                                                         |\n"+
        "    |    When you have pledged yourself to the order, you     |\n"+
		"    |    can <bfhelp> to get help on the Order of the         |\n"+
		"    |    Black Flame.                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
	    break; 				  

        case 9:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 9  |\n"+
        "    |                                                         |\n"+
        "    |   O R D E R    O F    T H E    B L A C K    F L A M E   |\n"+
        "    |                                                         |\n"+
        "    |    Leaving                                              |\n"+
        "    |    -------                                              |\n"+
        "    |    Leaving the Order of the Black Flame is as easy as   |\n"+
		"    |    it is foolish. You simply need to                    |\n"+
		"    |    <renounce the Order of the Black Flame> to show your |\n"+
        "    |    commitment to abandoning the path of enlightenment   |\n"+
		"    |    that Kossuth so graciously provides.                 |\n"+
        "    |                                                         |\n"+
        "    |    Be Warned that not only the Order of the Black Flame |\n"+
		"    |    may take offense at this action, but you are also    |\n"+
		"    |    spitting in the face of the Lord of the Flame        |\n"+
        "    |    himself. Expect the consequences to be dire.         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
		"    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
		break; 				  

        default:
            write("This page is empty.\n");
            return 0;
        break;
    }
}
