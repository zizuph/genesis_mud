
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "../sindar_racial.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/scroll";

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 7;
string  gPage;

void
set_book_is_private(int i){ book_is_private = i; }

string
opened_at_page()
{
    if(book_is_closed) return "";
    return "It is opened at page number "+LANG_WNUM(what_page)+".\n";
}

/*
 * Function name: create_scroll
 * Description:   creates the general object
 * Arguments:
 */
nomask void
create_scroll()
{
    set_short("leather book on the pedestal");
    set_name("book");
    add_name("book");
    add_name("sindar book");
    set_long("This is a large leatherbound book full of parchments. " +
        "The book is bound with mithril bands and secured to the " +
        "pedestal.\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"leather"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"@@try_get");

}

int
try_get()
{
    write("The book is secured to the pedestal and cannot be " +
        "taken.\n");
    say(QCTNAME(TP)+" tries to take the book from the pedestal, " +
	    "but fails.\n", TP);
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
    else if (!parse_command(str, ({}), "%s 'at' / 'to' 'page' %w", what, where))
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
    write("You open the " + short(TP) + " at page " +
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
        write("The " + short(TP) + "is already closed.\n");
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
    else if (gPage == "backward" || gPage == "back")
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
    "    _________________________________________________________________\n"+
    "    :                                                  Page 1        |\n"+
    "    :                                                                |\n"+
    "    :        I N D E X   O F   T H E   S I N D A R   G U I L D       |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;

    case 2:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page  2  |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;
	case 3:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page 3   |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
	break;

    case 4:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page 4   |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;

    case 5:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page 5   |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;

    case 6:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page 6   |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;

    case 7:
    write("\n\n"+
    "     ________________________________________________________________\n"+
    "    :                                                       Page 7   |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :________________________________________________________________|\n"+
    "\n\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
