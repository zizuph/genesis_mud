/*
 * /d/Gondor/common/dunedain/obj/join_book.c
 * Updated guild book for Dunedain
 * -- Finwe, January 2018
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Faerun/defs.h"

inherit "/std/scroll";

#define SIGN_ID  ({"sign"})

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 10;
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
    set_short("leather book sitting on a pedestal");
    set_name("book");
    add_name("book");
    add_name("Dunedain book");
    set_long("This is a large leather bound book. It looks well read as " +
        "the leather is smooth from constant use. Next to the book is a " +
        "sign.\n\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"leather"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"@@try_get");

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

int
try_get()
{
    write("The book cannot be taken. It sits on the pedestal.\n");
    say(QCTNAME(TP)+" tries to take the book from the pedestal but fails.\n", TP);
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
        "     __________________________________________________________\n"+
        "    |                                                 Page 1  |\n"+
        "    |                                                         |\n"+
        "    |     T H E   B O O K   O F   T H E   D U N E D A I N     |\n"+
        "    |                                                         |\n"+
        "    |  Rules of the Dunedain . . . . . . . . . . . . . . 2    |\n"+
        "    |                                                         |\n"+
        "    |  History of the Houses of the Dunedain . . . . . . 4    |\n"+
        "    |                                                         |\n"+
        "    |  Lords and Ladies of the Dunedain. . . . . . . . . 6    |\n"+
        "    |                                                         |\n"+
        "    |  Joining a House of the Dunedain . . . . . . . . . 7    |\n"+
        "    |                                                         |\n"+
        "    |  Skills of the Dunedain. . . . . . . . . . . . . . 9    |\n"+  
        "    |                                                         |\n"+
        "    |  Leaving a House of the Dunedain . . . . . . . .  10   |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 2:
       write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 2  |\n"+
        "    |                                                         |\n"+
        "    |  Rules of the of the Dunedain                           |\n"+
        "    |  ----------------------------                           |\n"+
        "    |  There are twelve Houses of the Dunedain. Every House   |\n"+
        "    |  can have a Lord or a Lady if there is a member of the  |\n"+
        "    |  House that proves worthy. The Lord or the Lady can     |\n"+
        "    |  adopt new members and admit them thus into the House.  |\n"+
        "    |  They can also expel members of their House that have   |\n"+
        "    |  proven not to be worthy, at the Lord or Lady's sole    |\n"+
        "    |  descretion.                                            |\n"+
        "    |                                                         |\n"+
        "    |  The members of the Houses of the Dunedain have to      |\n"+
        "    |  swear an oath of fealty to the Lord or the Lady of the |\n"+
        "    |  House. If the House receives a new Lord or Lady, every |\n"+
        "    |  Dunadan of the House will automatically become vassel  |\n"+
        "    |  to the new Lord or Lady. If the Dunadan is not able or |\n"+
        "    |  willing to fulfill their duties to the House and its   |\n"+
        "    |  its Lord or Lady, the Dunadan will have to renounce    |\n"+
        "    |  the House.                                             |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 3:
       write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 3  |\n"+
        "    |                                                         |\n"+
        "    |  Every Dunadan may use the Armoury, the Train Hall,     |\n"+
        "    |  the Post Office, and the Library of the Dunedain.      |\n"+
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
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 4:
       write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 4  |\n"+
        "    |                                                         |\n"+
        "    |  History of the Houses of the Dunedain                  |\n"+
        "    |  -------------------------------------                  |\n"+
        "    |  The members of the Houses of the Dunedain value lore   |\n"+
        "    |  and knowledge above all else. In highest regard they   |\n"+
        "    |  hold knowledge of the history of Arda and Middle-earth,|\n"+
        "    |  as they consider it as one of their most noble duties  |\n"+
        "    |  to collect and preserve the tales relating the history |\n"+
        "    |  of their people.                                       |\n"+
        "    |                                                         |\n"+
        "    |  The Houses of the Dunedain are the repository of much  |\n"+
        "    |  knowledge that cannot be found anywhere else in the    |\n"+
        "    |  world. The members of the Houses are expected to be    |\n"+
        "    |  familiar with the history of Arda, the Ainulindale     |\n"+
        "    |  including the Tales of the Elder Days and the War of   |\n"+
        "    |  the Silmarilli, and the accounts of Numenor and the    |\n"+
        "    |  Third Age.                                             |\n"+
        "    |                                                         |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 5:
       write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 5  |\n"+
        "    |                                                         |\n"+
        "    |  The status of a Dunadan in the Houses is determined    |\n"+
        "    |  by their experience and knowledge. A Dunadan that      |\n"+
        "    |  wishes to increase their status in the Houses can try  |\n"+
        "    |  to advance in the Chamber of Knowledge, located west   |\n"+
        "    |  of the Chamber of the Houses. But they must pass a     |\n"+
        "    |  test to do so. The higher the status, the more diffi-  |\n"+
        "    |  cult will be the questions to be answered. And only    |\n"+
        "    |  the truly learned will ever gain sufficient status     |\n"+
        "    |  to be eligible to become Lord or Lady of their House.  |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;
    case 6:
       write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 6  |\n"+
        "    |                                                         |\n"+
        "    |  Lords and Ladies of the Houses of the Dunedain         |\n"+
        "    |  ----------------------------------------------         |\n"+
        "    |  Any member of a House of the Dunedain can advance to   |\n"+
        "    |  the position of Lord or Lady of their house, if the    |\n"+
        "    |  Dunadan has reached sufficient status among the Dune-  |\n"+
        "    |  dain, and if there are no other active Dunadan already |\n"+
        "    |  holding the position.                                  |\n"+
        "    |                                                         |\n"+
        "    |  If a house has a Lord or a Lady, a human can only join |\n"+
        "    |  that house if they are adopted into the House by the   |\n"+
        "    |  Lord or the Lady.                                      |\n"+
        "    |                                                         |\n"+
        "    |  The Lord or the Lady of a House will lose the rank if  |\n"+
        "    |  they resign in this room, if they are absent for a     |\n"+
        "    |  prolonged period of time, or another member of the     |\n"+
        "    |  House tries to advance to the position of Lord or      |\n"+
        "    |  Lady.                                                  |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;
        case 7:
           write("\n\n"+
            "     __________________________________________________________\n"+
            "    |                                                 Page 7  |\n"+
            "    |                                                         |\n"+
            "    |  Joining a House of the Dunedain                        |\n"+
            "    |  -------------------------------                        |\n"+
            "    |  If the House has a Lord or a Lady, only the Lord or    |\n"+
            "    |  the Lady can receive new members into the House. Any   |\n"+
            "    |  human who wishes to join the House has to 'apply' for  |\n"+
            "    |  membership in the House in this room in the presence   |\n"+
            "    |  of the Lord or the Lady of the House.                  |\n"+
            "    |                                                         |\n"+
            "    |  The Lord or the Lady can then offer to 'adopt' the     |\n"+
            "    |  applicant, asking him or her to swear the oath of      |\n"+
            "    |  fealty. After the applicant has sworn the oath and the |\n"+
            "    |  Lord or the Lady has replied with the correspoding     |\n"+
            "    |  oath as liege lord, the Lord or the Lady receives      |\n"+
            "    |  the applicant into their House.                        |\n"+
            "    |                                                         |\n"+
            "    |  If a House has neither Lord nor Lady, every human may  |\n"+
            "    |  'enter' the House by declaring their wish to do so,    |\n"+
            "    |_________________________________________________________|\n"+
            "\n");
        break;


        case 8:
           write("\n\n"+
            "     __________________________________________________________\n"+
            "    |                                                 Page 8  |\n"+
            "    |                                                         |\n"+
            "    |  provided that a member of the House or a Lord or a     |\n"+
            "    |  Lady of the Dunedain has vouched for them. Everyone    |\n"+
            "    |  entering a House without a Lord and a Lady must be     |\n"+
            "    |  aware, that once the House receives a Lord or a Lady,  |\n"+
            "    |  the members are required to follow the Lord or the     |\n"+
            "    |  Lady as faithful vasalls, as if they had sworn an oath |\n"+
            "    |  of fealty. If they are unwilling or unable to do so,   |\n"+
            "    |  they will have to renounce the House.                  |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |_________________________________________________________|\n"+
            "\n");
        break;

        case 9:
           write("\n\n"+
            "     __________________________________________________________\n"+
            "    |                                                 Page 9  |\n"+
            "    |                                                         |\n"+
            "    |  Skills of the Duneddain                                |\n"+
            "    |  -----------------------                                |\n"+
            "    |  The skills of the Dunedain are many. They can learn    |\n"+
            "    |  the following skills up to Superior Journeyman:        |\n"+
            "    |                                                         |\n"+
            "    |      > Awareness                                        |\n"+
            "    |      > Axes                                             |\n"+
            "    |      > Climbing                                         |\n"+
            "    |      > Herbalism                                        |\n"+
            "    |      > Languages                                        |\n"+
            "    |      > Spellcraft                                       |\n"+
            "    |      > Trading                                          |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |                                                         |\n"+
            "    |_________________________________________________________|\n"+
            "\n");
        break;

        case 10:
           write("\n\n"+
            "     __________________________________________________________\n"+
            "    |                                                 Page 10 |\n"+
            "    |                                                         |\n"+
            "    |  Leaving a House of the Dunedain                        |\n"+
            "    |  -------------------------------                        |\n"+
            "    |  Any Dunadan who is unwilling or unable to fulfill his  |\n"+
            "    |  duties as liege man or liege woman of the Lord or the  |\n"+
            "    |  Lady of the House of the Dunedain to which he or she   |\n"+
            "    |  belongs has to declare this by renouncing the House.   |\n"+
            "    |  This action will remove them not only from their own   |\n"+
            "    |  House, but also from the the ranks of the Dunedain.    |\n"+
            "    |                                                         |\n"+
            "    |  A Lord or a Lady of a House may expel at their discre- |\n"+
            "    |  tion, any member of their House.                       |\n"+
            "    |                                                         |\n"+
            "    |  A Lord or a Lady of a House of the Dunedain may re-    |\n"+
            "    |  lease a Dunadan of their House from service. This will |\n"+
            "    |  not end membership of the Dunadan in the House, but it |\n"+
            "    |  will enable the Dunadan to be adopted into another     |\n"+
            "    |  House ofthe Dunedain.                                  |\n"+
            "    |_________________________________________________________|\n"+
            "\n");
        break;
        case 11:
           write("\n\n"+
            "     __________________________________________________________\n"+
            "    |                                                 Page 11 |\n"+
            "    |                                                         |\n"+
            "    |  Only humans can belong to the Houses of the Dunedain.  |\n"+
            "    |  If by magic, wizardry, or by corruption through the    |\n"+
            "    |  power of the Evil One a Dunadan is turned into a being |\n"+
            "    |  that is not human anymore, that being will be removed  |\n"+
            "    |  from the Houses of the Dunedain.                       |\n"+
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
            "    |_________________________________________________________|\n"+
            "\n");
        break;

        default:
            write("This page is empty.\n");
            return 0;
        break;
    }
//  return 1;
}
