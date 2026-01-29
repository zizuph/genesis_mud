/*
 * Join book of the Wild Elves
 * Based on the Book of Angmar Army by Milan
 * -- Finwe, June 2001
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "../wrunner_defs.h"
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
    set_short("golden book floating in the air");
    set_name("book");
    add_name("book");
    add_name("wild elves book");
    set_long("This is a golden book floating in the air.  It is " +
        "large and made with silver pages. Across the pages are " +
        "flowing elven lettering. The lettering is written in " +
        "the common tongue so that anyone may read it.\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"golden"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"The book floats in the air and moves away from your " +
        "clumsy grasp. It cannot be taken.\n");

}

/*
int
try_get()
{
    write("The book floats in the air and moves away from your " +
        "clumsy grasp.\n");
    say(QCTNAME(TP)+" tries to take the floating book but fails. " +
        "The book moves away.\n", TP);
    return 1;
}
*/

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
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |        I N D E X   O F   T H E   W I L D   E L V E S           |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |       History of the Wild Elves . . . . . . . . . . 2          |\n"+
    "    |                                                                |\n"+
    "    |       Rules and Joining the Wild Elves. . . . . . . 5          |\n"+
    "    |                                                                |\n"+
    "    |       Leaving the Wild Elves. . . . . . . . . . . . 7          |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                         Page 1                                 |\n"+    
    "    |________________________________________________________________|\n"+
    "\n");
    break;


    case 2:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |        H I S T O R Y   O F   T H E   W I L D   E L V E S       |\n"+
    "    |                                                                |\n"+
    "    |  During the turmoil of the Wars, the elves remained neutral,   |\n"+
    "    |  prefering to live their lives quietly. They had spent         |\n"+
    "    |  centuries as scholars and knew that war brought only          |\n"+
    "    |  destruction to all it touched. At the same time, they saw     |\n"+
    "    |  that the conflict of the wizards would have profound effects  |\n"+
    "    |  on the world. Still they remained out of the wars, observing  |\n"+
    "    |  and waiting.                                                  |\n"+
    "    |                                                                |\n"+
    "    |  Unknown to but a few, a wizard sought the strength of the     |\n"+
    "    |  elves, for she knew they would sway many races to follow her. |\n"+
    "    |  She knew they would never do so knowingly, therefore she      |\n"+
    "    |  sought to deceive them by offering the elves a portion of her |\n"+
    "    |  power, hoping their greed would overcome their rational       |\n"+
    "    |  thinking.                                                     |\n"+
    "    |                                                                |\n"+    
    "    |                                                                |\n"+
    "    |                                                                |\n"+    
    "    |                         Page 2                                 |\n"+    
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    case 3:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |  Many were powerful nobles who were enthralled at the thought  |\n"+
    "    |  of increasing their powers and blindly joined her. Soon after |\n"+
    "    |  that, she came disguised and offered to aid the elves with    |\n"+
    "    |  the promise of strength, knowledge, and power--all things     |\n"+
    "    |  elves sought after. Many elves saw immediately through the    |\n"+
    "    |  Wizard's deceit and set out to destroy her. They became known |\n"+
    "    |  as the Wildrunners.                                           |\n"+
    "    |                                                                |\n"+
    "    |  Others, however, accepted and joined her. They became the     |\n"+
    "    |  Deathstalkers and were charged with protecting the Wizard.    |\n"+
    "    |  This began the War of Conflicts. This war was to have a far   |\n"+
    "    |  greater impact on the elves than any other war the elves were |\n"+
    "    |  involved in. The War of Conflicts effectively split the elven |\n"+
    "    |  nation.                                                       |\n"+
    "    |                                                                |\n"+
    "    |  The Wildrunners, those who rejected the Wizard, began to      |\n"+
    "    |  systematically exterminate the Deathstalkers or drive them    |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                         Page 3                                 |\n"+
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    case 4:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |  away. This went on for a time until the Wildrunners realized  |\n"+
    "    |  they had unknowingly followed the path of the Wizard.         |\n"+
    "    |                                                                |\n"+
    "    |  Now, the elves live apart from each other so as to not ignite |\n"+
    "    |  past grievances. Now the two groups tolerate each other,      |\n"+
    "    |  though with a great deal of mutual distrust.                  |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                         Page 4                                 |\n"+
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    case 5:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |  R U L E S  A N D  J O I N I N G   T H E   W I L D   E L V E S |\n"+
    "    |                                                                |\n"+
    "    |  The Wild Elves are a powerful race. They have extended some   |\n"+
    "    |  of their skills and abilities to those who join them. The     |\n"+
    "    |  guild charge its members a low fee to have these skills and   |\n"+
    "    |  abilities. They have very few rules that all guildmembers     |\n"+
    "    |  must follow.                                                  |\n"+
    "    |                                                                |\n"+
    "    |    * All members must remain elf. If by chance you die and     |\n"+
    "    |      change races, you will be expelled from the guild.        |\n"+
    "    |                                                                |\n"+
    "    |    * Half-elves are not permitted to join. They are considered |\n"+
    "    |      an abomination in the eyes of the Wild Elves and are      |\n"+
    "    |      tolerated less than the lowest elf. Yet they are suffered |\n"+
    "    |      to live since they have still have a small part of elf    |\n"+
    "    |      in them.                                                  |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+    
    "    |                         Page 5                                 |\n"+    
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    case 6:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |  Those who wish to join the Wild Elves may do so. Simply       |\n"+
    "    |  <declare wild elves> and you will join the guild.             |\n"+
    "    |                                                                |\n"+
    "    |  If you accidentally lose your ring, return here and <request  |\n"+
    "    |  ring>. You will get a replacement ring.                       |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                         Page 6                                 |\n"+
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    case 7:
    write(
    "     ________________________________________________________________\n"+
    "    |                                                                |\n"+
    "    |          L E A V I N G   T H E   W I L D   E L V E S           |\n"+
    "    |                                                                |\n"+
    "    |  If there comes a time when you want to leave the Wild Elves,  |\n"+
    "    |  all you have to do is return here and <abandon wild elves>.   |\n"+
    "    |  You will be forced to give up your ring, lose your abilities  |\n"+
    "    |  and skills you have learned, and no longer be a member of the |\n"+
    "    |  guild.                                                        |\n"+
    "    |                                                                |\n"+
    "    |  If you die and change races, you will be forcibly removed     |\n"+
    "    |  from the guild.                                               |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                                                                |\n"+
    "    |                         Page 7                                 |\n"+
    "    |________________________________________________________________|\n"+
    "\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
