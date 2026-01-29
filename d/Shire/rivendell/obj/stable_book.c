/*
 * Stable book of the Noldor
 * Based on the Book of Angmar Army by Milan
 * -- Finwe, January 2003
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/scroll";

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 14;
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
    add_name("noldor book");
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
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :              H O R S E   I N S T R U C T I O N S               |\n"+
    "    :                                                                |\n"+
    "    :       Riding and Leading Your Horse . . . . . . . . . . .  2   |\n"+
    "    :       Automount and Autodismount. . . . . . . . . . . . .  4   |\n"+
    "    :       Boarding Ships. . . . . . . . . . . . . . . . . . .  5   |\n"+
    "    :       Horse Behavior. . . . . . . . . . . . . . . . . . .  6   |\n"+
    "    :       Galloping and Trotting. . . . . . . . . . . . . . .  7   |\n"+
    "    :       Emotes. . . . . . . . . . . . . . . . . . . . . . .  7   |\n"+
    "    :       Feeding and Watering Your Horse . . . . . . . . . .  8   |\n"+
    "    :       Sending Your Horse Away or Summoning It . . . . . .  9   |\n"+
    "    :       Using Saddlebags. . . . . . . . . . . . . . . . . . 11   |\n"+
    "    :       Other Notes . . . . . . . . . . . . . . . . . . . . 12   |\n"+
    "    :       Quick List of Commands. . . . . . . . . . . . . . . 13   |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              1                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 2:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Your horse will have a different set of commands and emotes,  |\n"+
    "    :  depending on whether you are leading or riding the horse.     |\n"+
    "    :  Typing 'hhelp' while leading or mounted will give you a list  |\n"+
    "    :  of commands and emotes.                                       |\n"+
    "    :                                                                |\n"+
    "    :  Riding and Leading Your Horse                                 |\n"+
    "    :  -----------------------------                                 |\n"+
    "    :  To mount your horse, simply use:                              |\n"+
    "    :      mount horse                                               |\n"+
    "    :                                                                |\n"+
    "    :  To get off your horse:                                        |\n"+
    "    :      dismount                                                  |\n"+
    "    :  or                                                            |\n"+
    "    :      dismount horse                                            |\n"+
    "    :                                                                |\n"+
    "    :  To lead your horse, use the same format:                      |\n"+
    "    :      lead horse                                                |\n"+
    "    :                                                                |\n"+
    "    :                              2                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;
    
    case 3:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :  Riding and Leading Your Horse, continued                      |\n"+
    "    :  ----------------------------------------                      |\n"+
    "    :  To stop leading your horse:                                   |\n"+
    "    :      unlead horse                                              |\n"+
    "    :                                                                |\n"+
    "    :  If you are leading your horse you may also:                   |\n"+
    "    :      mount horse                                               |\n"+
    "    :                                                                |\n"+
    "    :  This makes you unlead, then mount your horse.                 |\n"+
    "    :                                                                |\n"+
    "    :  In general you will want to stay mounted, as opposed to       |\n"+
    "    :  leading your horse, in most situations. Your horse is not     |\n"+
    "    :  very fond of water, so you must be mounted to cross rivers.   |\n"+
    "    :  In some cases, you may have to unlead your horse, cross the   |\n"+
    "    :  water, then summon your horse. The ford of Bruinen is one     |\n"+
    "    :  such place.                                                   |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              3                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 4:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Automount and Autodismount                                    |\n"+
    "    :  --------------------------                                    |\n"+
    "    :  Some indoor rooms allow horses inside, but you have to be     |\n"+
    "    :  leading, not mounted. In this case, if you have typed         |\n"+
    "    :  <autodismount>, you will dismount your horse and lead it      |\n"+
    "    :  into the room.                                                |\n"+
    "    :                                                                |\n"+
    "    :  If you have 'automount' turned on, you will automatically     |\n"+
    "    :  mount your horse when you lead it back outside.               |\n"+
    "    :                                                                |\n"+
    "    :  Some indoor rooms do not allow horses at all and autodismount |\n"+
    "    :  will not help you. You will have to manually dismount or      |\n"+
    "    :  unlead your horse. One example of this is the ford at the     |\n"+
    "    :  river Bruinen. In this case, simple leave the horse, cross    |\n"+
    "    :  body of water, then summon the horse to you.                  |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              4                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;
    
    case 5:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Boarding Ships                                                |\n"+
    "    :  --------------                                                |\n"+
    "    :  When you board a ship you must be mounted, not leading. The   |\n"+
    "    :  horses don't particularly enjoy water so they won't be led    |\n"+
    "    :  onto a ship.                                                  |\n"+
    "    :                                                                |\n"+
    "    :  Your horse does not ride for free (Except the Circle Line).   |\n"+
    "    :  To make boarding and purchasing tickets easier, you have the  |\n"+
    "    :  <hboard> command. This simply buys two tickets and boards       |\n"+
    "    :  the ship. You must be mounted, not leading when using         |\n"+
    "    :  <hboard>.                                                     |\n"+
    "    :                                                                |\n"+
    "    :  Disembarking a ship with your horse works the same as if you  |\n"+
    "    :  had no horse. Simply <disembark> or <leave ship>.             |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                               5                                |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;
    
    case 6:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Horse Behavior                                                |\n"+
    "    :  --------------                                                |\n"+
    "    :  You can set your horses agressiveness towards others with     |\n"+
    "    :  the hnice command:                                            |\n"+
    "    :                                                                |\n"+
    "    :  To make your horse friendly:                                  |\n"+
    "    :      hnice on                                                  |\n"+
    "    :                                                                |\n"+
    "    :  To make your horse bite people when touched:                  |\n"+
    "    :      hnice off                                                 |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              6                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 7:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Galloping or Trotting                                         |\n"+
    "    :  ---------------------                                         |\n"+
    "    :  You can make your horse gallop or walk.                       |\n"+
    "    :                                                                |\n"+
    "    :  To make your horse gallop:                                    |\n"+
    "    :      hgallop on                                                |\n"+
    "    :                                                                |\n"+
    "    :  To make your horse walk or trot again:                        |\n"+
    "    :      hgallop off                                               |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :  Emotes                                                        |\n"+
    "    :  ------                                                        |\n"+
    "    :  The following emotes can be used when mounted on your horse.  |\n"+
    "    :      hsnort                                                    |\n"+
    "    :      hscrape <adverb>                                          |\n"+
    "    :      hnuzzle <adverb> <player>                                 |\n"+
    "    :                                                                |\n"+
    "    :                              7                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;


    case 8:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Feeding and Watering Your Horse                               |\n"+
    "    :  -------------------------------                               |\n"+
    "    :  A happy horse is a well-fed and watered horse. Your horse is  |\n"+
    "    :  a hearty eater and enjoys hay, oats, apples and of course     |\n"+
    "    :  sugar cubes. To feed your horse, simply:                      |\n"+
    "    :      feed horse with <food>                                    |\n"+
    "    :                                                                |\n"+
    "    :  Example:                                                      |\n"+
    "    :      feed horse with apple                                     |\n"+
    "    :                                                                |\n"+
    "    :  To make your horse drink, simply:                             |\n"+
    "    :      hdrink from <water source>                                |\n"+
    "    :                                                                |\n"+
    "    :  Basically, any room that has a water source that you can      |\n"+
    "    :  drink from, your horse can too. So if you can <drink from     |\n"+
    "    :  river> yourself, you can make your horse drink too with       |\n"+
    "    :  <hdrink from river>.                                          |\n"+
    "    :                                                                |\n"+
    "    :                              8                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 9:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Sending Your Horse Away or Summoning It                       |\n"+
    "    :  ---------------------------------------                       |\n"+
    "    :  When your travels are complete for the day, your horse can    |\n"+
    "    :  be sent back to the stables of Imladris stables on its own.   |\n"+
    "    :  To send your horse home from anywhere, simply tell it:        |\n"+
    "    :      hhome                                                     |\n"+
    "    :                                                                |\n"+
    "    :  Be forewarned that if you lose your horse or someone kills    |\n"+
    "    :  it, you will not be able to rent another until the next       |\n"+
    "    :  Armageddon.                                                   |\n"+
    "    :                                                                |\n"+
    "    :  When you are ready to begin your journies again, or your      |\n"+
    "    :  horse has been grazing, simply say:                           |\n"+
    "    :      nosummon                                                  |\n"+
    "    :                                                                |\n"+
    "    :  This will call your horse from either the stables where it    |\n"+
    "    :  has been resting or where ever it has been grazing.           |\n"+
    "    :                                                                |\n"+
    "    :                              9                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 10:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :  Sending Your Horse Away or Summoning It, continued            |\n"+
    "    :  --------------------------------------------------            |\n"+
    "    :  If you need to send your horse away while you go indoors, or  |\n"+
    "    :  for whatever reason, you may send it to graze by saying:      |\n"+
    "    :      nograze                                                   |\n"+
    "    :                                                                |\n"+
    "    :  You must be dismounted when you send your horse to graze.     |\n"+
    "    :  When you use this command, it will leave your presence right  |\n"+
    "    :  away.                                                         |\n"+
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
    "    :                              10                                 |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 11:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Saddlebag Commands                                            |\n"+
    "    :  ------------------                                            |\n"+
    "    :  Below is a list of available commands for saddlebags sold in  |\n"+
    "    :  Tack Shop.                                                    |\n"+
    "    :                                                                |\n"+
    "    :  strap saddlebag on horse    - put saddlebag on horse          |\n"+
    "    :  unstrap saddlebag on horse  - remove saddlebag                |\n"+
    "    :  fill saddlebag on horse     - put items in saddlebag          |\n"+
    "    :  empty saddlebag on horse    - retrieve items from saddlebag   |\n"+
    "    :  close saddlebag on horse    - closes saddlebag                  |\n"+
    "    :  hpack                       - see contents of saddlebag       |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              11                                |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 12:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Other Notes                                                   |\n"+
    "    :  -----------                                                   |\n"+
    "    :  If you go somewhere where your horse cannot follow, such as   |\n"+
    "    :  indoors, and will be away for some time, be sure to send      |\n"+
    "    :  your horse to graze. You will usually be able to call it      |\n"+
    "    :  back immediately. Horses left to wander have a good chance    |\n"+
    "    :  of running off for good or being killed by enemies.           |\n"+
    "    :                                                                |\n"+
    "    :  You may also use your horse's name instead of <horse> in the  |\n"+
    "    :  appropriate commands.                                         |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                                                                |\n"+
    "    :                              12                                |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    case 13:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :                                                                |\n"+
    "    :  Quick List of Commands                                        |\n"+
    "    :  ----------------------                                        |\n"+
    "    :  mount/dismount horse        - mount and ride or dismount      |\n"+
    "    :                                horse                           |\n"+
    "    :  lead/unlead horse           - lead or stop leading horse      |\n"+
    "    :  hboard                      - buy ship ticket for yourself    |\n"+
    "    :                                and your horse                  |\n"+
    "    :  feed horse with <food>      - feed horse food, including hay, |\n"+
    "    :                                oats, apples, and sugar cubes   |\n"+
    "    :  hdrink from <water source>  - let horse drink from river, etc |\n"+
    "    :  automount on                - automatically mount horse when  |\n"+
    "    :                                you go outdoors                 |\n"+
    "    :  autodismount                - automatically dismount horse    |\n"+
    "    :                                when you go indoors             |\n"+
    "    :  hgallop on                  - turns galloping on              |\n"+
    "    :  hgallop off                 - returns horse to walk or trot   |\n"+
    "    :  hnice on                    - makes horse friendly to others  |\n"+
    "    :  hnice off                   - horse unfriendly to others      |\n"+
    "    :                              13                                |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;
    
    case 14:
    write("\n\n"+
    "    -----------------------------------------------------------------\n"+
    "    :  Quick List of Commands, continued                             |\n"+
    "    :  ---------------------------------                             |\n"+
    "    :  hhome                       - send horse to stables           |\n"+
    "    :  hgraze                      - send horse away to graze        |\n"+
    "    :  nosummon                    - call for horse                  |\n"+
    "    :  hsnort                                                        |\n"+
    "    :  hscrape <adverb>                                              |\n"+
    "    :  hnuzzle <adverb> <player>                                     |\n"+
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
    "    :                                                                |\n"+
    "    :                              14                                |\n"+
    "    :----------------------------------------------------------------|\n"+
    "\n\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
