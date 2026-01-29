/*
 * /d/Faerun/guilds/warlocks/obj/patron_book.c
 *
 * Nerull 2018
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
int     maxm_page = 8; /* how many pages in book */
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
    set_short("leather book floating in the air");
    set_name("book");
    add_name("book");
    add_name("Patron book");
    set_long("This is a large book bound in rich leather. It looks "
    +"well read and is floating in the air before you. There are "
    +"instructions next to the book.\n\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"leather"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"@@try_get");

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
    write("The book cannot be taken. It is secured to the lectern.\n");
    
    say(QCTNAME(TP)+" tries to take the book from the lecturn but fails.\n", TP);
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
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |          I N D E X                                      |\n"+
        "    |          ---------                                      |\n"+
        "    |          1           Index, this page                   |\n"+
        "    |          2..3        Forewords, about Warlocks          |\n"+
        "    |          4           Patrons                            |\n"+
        "    |          5           Charms                             |\n"+
        "    |          6           Rituals                            |\n"+
        "    |          7           Pact Magic                         |\n"+
        "    |          8           Restrictions & Leaving             |\n"+
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
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |          --= By the Whispess, Covenmaster =--           |\n"+
        "    |                                                         |\n"+
        "    |    F O R E W O R D S                                    |\n"+
        "    |    -----------------                                    |\n"+
        "    |    Philosophers and dreamers alike has often            |\n"+
        "    |    been labeled as mad, dangerous and crazy, often      |\n"+
        "    |    cast aside from the society and even hunted and      |\n"+
        "    |    killed, some burned alive at the stake. But for      |\n"+
        "    |    what and why? Simply for being 'different'? Fear of  |\n"+
        "    |    the unknown? We think it's a product of ignorant     |\n"+
        "    |    superstitions and dogmatic views of religious        |\n"+
        "    |    fanatics, but we are seekers of the knowledge that   |\n"+
        "    |    lies beyond the veil of what the common man          |\n"+
        "    |    can reach and understand. For such priviliege, we    |\n"+
        "    |    will perform necessary acts deemed too gruesome for  |\n"+
        "    |    most, but like mother nature, we shall kill,         |\n"+
        "    |    sacrifice and maim indiscriminately for own cause.   |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
        break;  
        
        

        case 3:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 3  |\n"+
        "    |                                                         |\n"+
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |    F O R E W O R D S  -  C O N T I N U E D              |\n"+
        "    |    ---------------------------------------              |\n"+
        "    |    Through bonds made with powerful entities of         |\n"+
        "    |    supernatural power, we harness magical energies      |\n"+
        "    |    that is both subtle and spectacular in the eyes of   |\n"+
        "    |    others. As a direct consequence, for the secret      |\n"+
        "    |    powers given to us by them, we must also give, for   |\n"+
        "    |    no such knowledge comes freely. In time, every       |\n"+
        "    |    warlock will know what the bond truly means, and the |\n"+
        "    |    heavy toll it carries with it.                       |\n"+
        "    |                                                         |\n"+
        "    |    By the pact forged between you and me, you will      |\n"+
        "    |    initially be a servant in my coven. In time, unless  |\n"+
        "    |    you flee in terror from this place or end up boiling |\n"+
        "    |    in my cauldron, you may one day ascend as a Warlock, |\n"+
        "    |    bonded to an entity even more powerful than myself.  |\n"+
        "    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
        break;       

        case 4:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 4  |\n"+
        "    |                                                         |\n"+
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   P A T R O N S                                         |\n"+
        "    |   -------------                                         |\n"+
        "    |   The supernatural entitites served by warlocks in      |\n"+
        "    |   the coven are initially a secret, and will only be    |\n"+
        "    |   revealed to worthy servants when they see             |\n"+
        "    |   fit. Meanwhile, heed the whispers, heed the calls,    |\n"+
        "    |   let them guide you to your..                          |\n"+
        "    |                                                         |\n"+
        "    |                     ..Destiny.                          |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   Warlocks may also 'abandon patron' if they wish       |\n"+
        "    |   to, but it comes with a heavy penalty. Be Warned!     |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
        break;               
        

        case 5:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 5  |\n"+
        "    |                                                         |\n"+
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   C H A R M S                                           |\n"+
        "    |   -----------                                           |\n"+
        "    |   Some gifts given by the patrons require a certain     |\n"+
        "    |   magical charm in order to function. The charms are    |\n"+
        "    |   created by a combination of components listed in      |\n"+
        "    |   'wahelp charms', and must be 'flared' in order for    |\n"+
        "    |   the warlock to be infused with magical energies       |\n"+
        "    |   required to use some of the gifts.                    |\n"+
        "    |                                                         |\n"+
        "    |   A charm may infuse the warlock with enough power to   |\n"+
        "    |   use a gift several times.                             |\n"+
        "    |                                                         |\n"+
        "    |   Not all gifts require the magical infusion of         |\n"+
        "    |   a charm.                                              |\n"+
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
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   R I T U A L S                                         |\n"+  
        "    |   -------------                                         |\n"+  
        "    |   The importance of the rituals are crucial. Warlocks   |\n"+
        "    |   who serve a particular patron can expect demands      |\n"+
        "    |   of rituals rather regulary. The bond means you must   |\n"+
        "    |   give something back to your patron..a part of         |\n"+
        "    |   yourself, for the access to the knowledge and the     |\n"+
        "    |   gifts given.                                          |\n"+
        "    |                                                         |\n"+
        "    |   In this world or the next, nothing is truly free.     |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    +---------------------------------------------------------+\n"+
        "\n");
        break;                   


        case 7:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 7  |\n"+
        "    |                                                         |\n"+
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   P A C T   M A G I C                                   |\n"+
        "    |   -------------------                                   |\n"+
        "    |   Warlocks who have served their patron well may be     |\n"+
        "    |   given the opportunity select a specialized gift       |\n"+
        "    |   of their choosing. For a price, the selection of      |\n"+   
        "    |   these gifts may be nullified, opening the chance      |\n"+
        "    |   for selecting them again.                             |\n"+
        "    |                                                         |\n"+
        "    |   These particular gifts are only available at the      |\n"+  
        "    |   special location for each entity, on a time of        |\n"+
        "    |   their choosing.                                       |\n"+
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
        "    |                   W A R L O C K S                       |\n"+
        "    |                                                         |\n"+
        "    |                                                         |\n"+
        "    |   R E S T R I C T I O N S   &   L E A V I N G           |\n"+
        "    |   -------------------------------------------           |\n"+
        "    |   The patrons do not care about petty mortal            |\n"+
        "    |   definitions of 'good' and 'evil'. Whenever a          |\n"+
        "    |   Solamnian knight or a cannibalistic orc from          |\n"+
        "    |   Mordor performs an action or a ritual that is         |\n"+
        "    |   deemed unethical or evil by the eyes of man,          |\n"+
        "    |   the patrons receive what is rightfully theirs         |\n"+
        "    |   regardless.                                           |\n"+
        "    |                                                         |\n"+
        "    |   Leaving carries no immediate penalty for a member,    |\n"+
        "    |   except for a period of time that he|she can't         |\n"+
        "    |   immediately rejoin. Joining my coven also requires    |\n"+
        "    |   a certain size. A member may 'break the pact' at the  |\n"+
        "    |   entrance in order to tuck tail and flee my coven.     |\n"+
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
