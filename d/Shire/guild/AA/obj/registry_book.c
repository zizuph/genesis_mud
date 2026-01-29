/*
 * Angmar Army Registry
 * Varian - May, 2020
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "../guild.h"

inherit "/std/scroll";

#define SIGN_ID  ({"marker"})

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 17;
string  gPage;


void
set_book_is_private(int i){ book_is_private = i; }

string
opened_at_page()
{
    if(book_is_closed) return "";
    return "It is opened to page number "+LANG_WNUM(what_page)+".\n";
}

/*
 * Function name: create_scroll
 * Description:   creates the general object
 * Arguments:
 */
nomask void
create_scroll()
{
    set_short("niche in the wall with a small, brown book");
    set_long("The small brown book appears to be a registry of all members " +
        "in the Army of Angmar.\n\n"+
        "@@opened_at_page@@");
    add_name(({"book", "niche"}));
    add_adj(({"small", "brown"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_M_NO_GET, "The book should not be removed from the " +
        "niche!\n");
    add_item("niche", 
        "There is a niche in the stone wall here, just the perfect " +
        "size for holding a small book.\n");

    add_cmd_item(SIGN_ID, "read", "@@sign@@");

}
int
sign(string str)
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
        write("The " + short(TP) + "is closed.\n");
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
        write("Do you want to turn the page 'forward' or 'backward'?\n");
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
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 1  |\n" +
"    |                                                                   |\n" +
"    |                T H E   A R M Y   O F   A N G M A R                |\n" +
"    |                                                                   |\n" +
"    |  Register of the Army of Angmar. . . . .. . . . . . . . . . .  2  |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");

            break;

        case 2:
            write("\n"+
"Register of the members of Army of Angmar.\n"+

"******************************************\n"+
"\n"+
"Captain:\n"+
"********\n\n   >>>"+AA_COUNCIL_OBJ->query_captain()+
"<<<\n\n"+
"\n" +
"Lieutenants:\n" +
"************\n\n   >>" + AA_RANKS_OBJ->query_players_with_rank_no(5) +
"<<\n\n" +
/*"Master Sergeants:\n"+
"*****************\n\n"+
(book_is_private ?
make_string_from_list((AA_RANKS_OBJ->query_players_with_rank_no(5)) ||
(AA_RANKS_OBJ->query_players_with_rank_no(6))) :
"  ----")+*/
"\n");
            break;
        case 3:
            write("\n"+
"Sergeants:\n"+
"**********\n\n"+
(book_is_private ?
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(4)) :
"  ----")+
"\n\n"+
"Corporals:\n"+
"**********\n\n"+
(book_is_private ?
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(3)) :
"  ----")+
"\n\n"+
"Lance Corporals:\n"+  
"*****************\n\n"+
(book_is_private ?
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(2)) :
"  ----")+
"\n");
            break;
        case 4:
            write("\n"+
"Standard Bearers:\n"+ 
"********\n\n"+
(book_is_private ?
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(1)) :
"  ----")+
"\n\n" +
"Footmen:\n" +
"**********\n\n" +
(book_is_private ?
make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(0)) :
    "  ----") +
"\n");
            break;

        default:

            write("This page is empty.\n");
    }
}