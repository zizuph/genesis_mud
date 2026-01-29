/*
 * Help Pamphlet for Bree steeds
 * -- Finwe, May 2005
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"

inherit "/std/scroll";

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);
public int do_tear(string str);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 18;
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
    set_short("leather pamplet");
    set_name("book");
    add_name("pamphlet");
    add_adj(({"small", "leather"}));
    set_short("small leather pamphlet");
    set_long("This is a small leather pamphlet. It is distributed by " +
        "the stablemaster when steeds are rented from him. The cover is " +
        "made from soft leather and embossed with an image of a stately " +
        "steed. Bound inside the pamphlet is a sheaf of crisp parchments. " +
        "You may also <tear pamphlet> to get rid of it.\n" +
        "@@opened_at_page@@");

    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_M_NO_STEAL,"The " + short() + " may not be taken.");
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
        what = "pamphlet";
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
    add_action(do_tear, "tear");
}


public int
do_tear(string str)
{
    if (stringp(str))
    {
        write("You tear up the " + short() + " several times and throw it away.\n");
        this_object()->remove_object();
        return 1;
    }
    write ("Tear what? The " + short() + "?\n");
    return 1;
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
    return text;
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
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Table of Contents                           |\n"+
    "    |  ------------------------------------------  |\n"+
    "    |  Introduction. . . . . . . . . . . . . .  2  |\n"+
    "    |  Commands. . . . . . . . . . . . . . . .  4  |\n"+
    "    |  Riding Your Steed . . . . . . . . . . .  4  |\n"+
    "    |  Leading Your Steed. . . . . . . . . . .  5  |\n"+
    "    |  Autodismount and Automount. . . . . . .  7  |\n"+
    "    |  Boarding Ships. . . . . . . . . . . . .  9  |\n"+
    "    |  Galloping or Trotting . . . . . . . . . 10  |\n"+
    "    |  Feeding and Watering Your Steed . . . . 11  |\n"+
    "    |  Using the Bree Saddlebags . . . . . . . 13  |\n"+
    "    |  Horse Behaviour . . . . . . . . . . . . 16  |\n"+
    "    |  Emotes. . . . . . . . . . . . . . . . . 17  |\n"+
    "    |  Index . . . . . . . . . . . . . . . . . 18  |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                   Page 1                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");    
    break;

    case 2:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Introduction                                |\n"+
    "    |  ------------                                |\n"+
    "    |  Thank you for renting a Bree steed. Our     |\n"+
    "    |  steeds are high quality Rohan-bred animals  |\n"+
    "    |  With proper understanding of how to use and |\n"+
    "    |  take care of your steed we know you will    |\n"+
    "    |  have a most pleasurable riding experience.  |\n"+
    "    |                                              |\n"+
    "    |  The term steed is used throughout this      |\n"+
    "    |  pamphlet. It can be replaced with 'horse'   |\n"+
    "    |  or 'pony' in any of the commands.           |\n"+
    "    |                                              |\n"+
    "    |  Your new steed understands several com-     |\n"+
    "    |  mands, and can do several emotes, control-  |\n"+
    "    |  led by you.                                 |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                   Page 2                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
    break;
	case 3:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Introduction, cont.                         |\n"+
    "    |  -------------------                         |\n"+
    "    |  Your steed will have a different set of     |\n"+
    "    |  commands and emotes, depending on whether   |\n"+
    "    |  you are leading or riding the steed.        |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                   Page 3                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
	break;

    case 4:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Commands                                    |\n"+
    "    |  --------                                    |\n"+
    "    |  Below are the commands available to steed   |\n"+
    "    |  users.                                      |\n"+
    "    |                                              |\n"+
    "    |  Riding Your Steed                           |\n"+
    "    |  -----------------                           |\n"+
    "    |  To ride your steed you need to mount it     |\n"+
    "    |  first, otherwise you will lead it wherever  |\n"+
    "    |  you go. To do that, simply:                 |\n"+
    "    |      'mount' or 'mount <steed>'              |\n"+
    "    |                                              |\n"+
    "    |  There will be some places you can't take    |\n"+
    "    |  your steed. In those cases, you will have   |\n"+
    "    |  dismount. This is done by:                  |\n"+
    "    |      'dismount' or 'dismount <steed>'        |\n"+
    "    |                                              |\n"+
    "    |                   Page 4                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
    break;

    case 5:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Leading Your Steed                          |\n"+
    "    |  ------------------                          |\n"+
    "    |  When you can't ride your steed, you may     |\n"+
    "    |  lead it instead. The command is:            |\n"+
    "    |      'lead' or 'lead <stead>'                |\n"+
    "    |                                              |\n"+
    "    |  Conversely, you may stop leading the animal |\n"+
    "    |  with:                                       |\n"+
    "    |      'unlead' or 'unlead <stead>'            |\n"+
    "    |                                              |\n"+
    "    |  If you are leading your steed, may also:    |\n"+
    "    |      'mount <steed>'                         |\n"+
    "    |                                              |\n"+
    "    |  This will make you unlead the animal and    |\n"+
    "    |  mount it.                                   |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                   Page 5                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
    break;

    case 6:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  Leading Your Steed, cont.                   |\n"+
    "    |  -------------------------                   |\n"+
    "    |  In general you will want to stay mounted,   |\n"+
    "    |  as opposed to leading your steed, in most   |\n"+
    "    |  situations. Your steed is not very fond of  |\n"+
    "    |  water, so you must be mounted to cross      |\n"+
    "    |  rivers.                                     |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                                              |\n"+
    "    |                   Page 6                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
    break;

    case 7:
    write("\n\n"+
    "    +----------------------------------------------+\n"+
    "    |      B R E E   S T E E D ' S   I N F O       |\n"+
    "    |                                              |\n"+
    "    |  'autodismount' and 'automount'              |\n"+
    "    |  ------------------------------              |\n"+
    "    |  These two commands will force you to auto-  |\n"+
    "    |  matically mount or dismount your steed when |\n"+
    "    |  necessary. They act as switches that can be |\n"+
    "    |  turned off or on. The commands are useful   |\n"+
    "    |  when you go into rooms that allow steeds in |\n"+
    "    |  in them or return outside.                  |\n"+
    "    |                                              |\n"+
    "    |  Some indoor rooms allow steeds but you have |\n"+
    "    |  to be leading, not mounted. To automatic-   |\n"+
    "    |  ally dismount and lead your stead, type:    |\n"+
    "    |      'autodismount'                          |\n"+
    "    |                                              |\n"+
    "    |  When you return outside, you can automati-  |\n"+
    "    |  cally mount your steed again. To do this,   |\n"+
    "    |                                              |\n"+
    "    |                   Page 7                     |\n"+
    "    +----------------------------------------------+\n"+
    "\n\n");
    break;

    
    case 8:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  'autodismount' and 'automount', cont.       |\n"+
        "    |  -------------------------------------       |\n"+
        "    |  When you return outside, you can automati-  |\n"+
        "    |  cally mount your steed again. To do this,   |\n"+
        "    |  the command may be turned on this way:      |\n"+
        "    |      'automount'                             |\n"+
        "    |                                              |\n"+
        "    |  Some indoor rooms do not allow steeds at    |\n"+
        "    |  all and autodismount will not help you.     |\n"+
        "    |  You will have to manually dismount or       |\n"+
        "    |  unlead your horse.                           |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 8                     |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 9:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Boarding Ships                              |\n"+
        "    |  --------------                              |\n"+
        "    |  When you board a ship, you can't be leading |\n"+
        "    |  your steed, but must be mounted. Steeds are |\n"+
        "    |  skitterish on water so they cannot be led   |\n"+
        "    |  onto a ships.                               |\n"+
        "    |                                              |\n"+
        "    |  Your steed does not ride for free, except   |\n"+
        "    |  on the Circle Line. To make boarding and    |\n"+
        "    |  purchasing tickets easier, use the          |\n"+
        "    |  command:                                    |\n"+
        "    |      'hboard'                                |\n"+
        "    |                                              |\n"+
        "    |  This will allow you to buy a ticket for     |\n"+
        "    |  yourself and steed.                         |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 9                     |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 10:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Boarding Ships, cont.                       |\n"+
        "    |  ---------------------                       |\n"+
        "    |  Disembarking a ship with your steed works   |\n"+
        "    |  the same way. Simply:                       |\n"+
        "    |      'disembark' or 'leave ship'.            |\n"+
        "    |                                              |\n"+
        "    |  Galloping or Trotting                       |\n"+
        "    |  ---------------------                       |\n"+
        "    |  You can make your horse gallop or trot as   |\n"+
        "    |  you travel. This command may be turned on   |\n"+
        "    |  or off. When it is on, the steed will       |\n"+
        "    |  gallop, when off, the animal will trot. The |\n"+
        "    |  command is:                                 |\n"+
        "    |      'hgallop on/off'                        |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 10                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 11:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Feeding and Watering Your Steed             |\n"+
        "    |  -------------------------------             |\n"+
        "    |  Horses and ponies are hearty eaters, and    |\n"+
        "    |  enjoys a lot of different foods. When you   |\n"+
        "    |  get the animal, it will be fully fed and    |\n"+
        "    |  watered. However, as it travels with you,   |\n"+
        "    |  it will need to be fed and watered. To see  |\n"+
        "    |  how hungry and thirsty it is, you may:      |\n"+
        "    |       'hglance'                              |\n"+
        "    |                                              |\n"+
        "    |  This will give you a relative idea of if    |\n"+
        "    |  the steed needs to be taken care of or not. |\n"+
        "    |                                              |\n"+
        "    |  Your animal likes all kinds of foods, but   |\n"+
        "    |  its favorites are apples, sugar cubes, hay, |\n"+
        "    |  and oats. All of these may be purchased in  |\n"+
        "    |                                              |\n"+
        "    |                   Page 11                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;

    
    case 12:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Feeding and Watering Your Steed, cont.      |\n"+
        "    |  --------------------------------------      |\n"+
        "    |  in the stables and taken with you to feed   |\n"+
        "    |  the aninal in your travels. To feed your    |\n"+
        "    |  horse or pony, just do this:                |\n"+
        "    |      'feed <steed> with <food>'              |\n"+
        "    |                                              |\n"+
        "    |  Your animal will get thirsty, too, and to   |\n"+
        "    |  make it drink, this is what you do:         |\n"+
        "    |      'hdrink from <water source>'            |\n"+
        "    |                                              |\n"+
        "    |  Luckily, horses and ponies can drink almost |\n"+
        "    |  anywhere you can. This means if you can     |\n"+
        "    |  drink water in the room, so can your steed. |\n"+
        "    |                                              |\n"+
        "    |  There is a trough in the stable to water    |\n"+
        "    |  your steed with before leaving.             |\n"+
        "    |                   Page 12                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 13:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Using the Bree Saddlebags                   |\n"+
        "    |  -------------------------                   |\n"+
        "    |  Your new steed isn't just your best         |\n"+
        "    |  friend. Its also a fantastic pack animal.   |\n"+
        "    |  With the saddlebags in the Bree Tack Shop,  |\n"+
        "    |  you can carry quite a load on your steed.   |\n"+
        "    |  The saddlebag also doubles as a regular     |\n"+
        "    |  pack. Below are the commands necessary to   |\n"+
        "    |  use the saddlebags.                         |\n"+
        "    |                                              |\n"+
        "    |  WARNING: Be sure you empty the contents     |\n"+
        "    |  of your saddlebag before stabling the       |\n"+
        "    |  steed. The stablehands at Bree are not      |\n"+
        "    |  responsible for any lost or forgotten       |\n"+
        "    |  saddlebags, or its contents, when steeds    |\n"+
        "    |  are returned.                               |\n"+
        "    |                                              |\n"+
        "    |                   Page 13                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 14:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Using the Bree Saddlebags, cont.            |\n"+
        "    |  --------------------------------            |\n"+
        "    |  After purchasing a saddlebag you'll want    |\n"+
        "    |  to put it on your steed. Here's how:        |\n"+
        "    |      'strap saddlebag on steed'              |\n"+
        "    |                                              |\n"+
        "    |  To fill your saddlebag with whatever is     |\n"+
        "    |  in your inventory, you need to do this:     |\n"+
        "    |      'fill saddlebag on steed'               |\n"+
        "    |                                              |\n"+
        "    |  To empty the contents of the saddlebag,     |\n"+
        "    |  simply do this:                             |\n"+
        "    |      'empty saddlebag on steed'              |\n"+
        "    |                                              |\n"+
        "    |  To close your saddlebag on the steed:       |\n"+
        "    |      'close saddlebag on steed'              |\n"+
        "    |                                              |\n"+
        "    |                   Page 14                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 15:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Using the Bree Saddlebags, cont.            |\n"+
        "    |  --------------------------------            |\n"+
        "    |  To open your saddlebag on the steed:        |\n"+
        "    |      'open saddlebag on steed'               |\n"+
        "    |                                              |\n"+
        "    |  To take the saddlebag off your steed:       |\n"+
        "    |      'unstrap saddlebag on steed'            |\n"+
        "    |                                              |\n"+
        "    |  To view the contents of your saddlebag:     |\n"+
        "    |      'hpack'                                 |\n"+
        "    |                                              |\n"+
        "    |  Only the person riding the steed can see    |\n"+
        "    |  the contents of the saddlebag, and that's   |\n"+
        "    |  often the owner of the steed.               |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 15                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 16:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    | Horse Behavior                               |\n"+
        "    | --------------                               |\n"+
        "    | You can set how friendly your animal is      |\n"+
        "    | towards others. The command can be turned    |\n"+
        "    | off or on this way:                          |\n"+
        "    |     'hnice on/off'                           |\n"+
        "    |                                              |\n"+
        "    | When your horse or pony is nice, it will     |\n"+
        "    | be kind to others. When it is not, it will   |\n"+
        "    | bite and nip people when it is touched.      |\n"+
        "    |                                              |\n"+
        "    | Bree Stables is not be held responsible      |\n"+
        "    | if your steed bites someone. Use this        |\n"+
        "    | command at your own risk.                    |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 16                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 17:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Emotes                                      |\n"+
        "    |  ------                                      |\n"+
        "    |  You can have your steed easily express it-  |\n"+
        "    |  self. Below are the available emotes for    |\n"+
        "    |  your steed.                                 |\n"+
        "    |                                              |\n"+
        "    |  hsnort                                      |\n"+
        "    |  hscrape <adverb>                            |\n"+
        "    |  hnuzzle <player>                            |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 17                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 18:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |  Index                                       |\n"+
        "    |  -----                                       |\n"+
        "    |  Listed below is an index of the commands    |\n"+
        "    |  available with your steed.                  |\n"+
        "    |                                              |\n"+
        "    |  autodismount, 7    hnice, 15                |\n"+
        "    |  automount, 8       hnuzzle <player>, 17     |\n"+
        "    |  close, 14          hpack, 15                |\n"+
        "    |  dismount, 4        hscrape <adverb>, 17     |\n"+
        "    |  empty, 14          hsnort, 17               |\n"+
        "    |  feed, 12           lead, 5                  |\n"+
        "    |  fill, 14           mount, 4                 |\n"+
        "    |  hboard, 9          strap, 14                |\n"+
        "    |  hdrink, 12         unlead, 5                |\n"+
        "    |  hgallop, 10        unstrap, 15              |\n"+
        "    |  hglance, 11                                 |\n"+
        "    |                                              |\n"+
        "    |                   Page 18                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 19:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 19                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;
    
    case 20:
        write("\n\n"+
        "    +----------------------------------------------+\n"+
        "    |      B R E E   S T E E D ' S   I N F O       |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                                              |\n"+
        "    |                   Page 20                    |\n"+
        "    +----------------------------------------------+\n"+
        "\n\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
