/*
 * Join book of the Blacksmiths Guild
 * Based on the Book of Angmar Army by Milan
 * -- Finwe, June 2001
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Shire/smiths/smiths.h"
#include "/d/Shire/sys/defs.h"



/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 8;
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
    set_short("brown book");
    set_name("brown book");
    add_name("smith_join");
    set_long("This very large book is bound in brown leather. " +
        "Golden letters written on the cover tell you that this " +
        "book concerns the rules and history of the Blacksmiths guild.\n" +
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"brown"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"The book cannot be taken.\n");

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
    write("                        The Blacksmiths Guild\n"+
          "                         General Information\n\n"+
          "         A Brief History of Blacksmithing in Middle-Earth . . 2\n"+
          "         A Brief History of the Blacksmiths Guild . . . . . . 3\n"+
          "         Skills Taught in the Blacksmiths Guild . . . . . . . 4\n"+
          "         Abilities Learned in the Blacksmiths Guild . . . . . 5\n"+
          "         Taxation of the Blacksmiths Guild. . . . . . . . . . 6\n"+
          "         Joining the Blacksmiths Guild. . . . . . . . . . . . 7\n"+
          "         Leaving the Blacksmiths Guild. . . . . . . . . . . . 8\n\n"+
          "                                     Page 1\n");
    break;


    case 2:
    write(
"          A Brief History of Blacksmithing in Middle-Earth\n\n"+
"    It is widely known and accepted that the first blackmiths in \n"+
"    Middle-Earth are the dwarves. The dwarves--according to their own\n"+
"    mythologies--were created by Aule, the god of smithcraft and\n"+
"    stoneworking. It is true, indeed, that the dwarves were the first\n"+
"    in Middle-Earth to forge blades and armours and in some concerns\n"+
"    the dwarves of old has not been rivaled by any other race--not\n"+
"    even elves--in their craft.\n\n"+
"    The elves who came from the Undying Lands long ago--the Noldor\n"+
"    they are named--brought with them great knowledge in the craft\n"+
"    of forging. Many of the greatest perished during the long wars\n"+
"    with the dark powers. The elves used their powers mostly to\n"+
"    imbue their items with strange powers (magic items as other\n"+
"    would call them). However, the dwarves spent generations finding\n"+
"    and developing the best alloys and shapes for their items.\n\n"+
"                                     Page 2\n"+
    "\n");
    break;

    case 3:
    write(
"              A Brief History of the Blacksmiths Guild\n\n"+
"    The Blacksmiths guild was founded by the dwarf Tranin who came passed\n"+
"    through Bree more than two hundred years ago. He found many people\n"+
"    were interested in his profession. Tranin made a small blacksmith\n"+
"    shop here. Soon, hopeful apprentices, both human and dwarven, came\n"+
"    here to learn the skills of smithing. That was the founding of the\n"+
"    Blacksmiths Guild.\n"+
"                                     Page 3\n"+
       "\n");
    break;

    case 4:
    write(
"                                     Skills\n\n"+
"    The following skills related to metal working can be learned here\n"+
"    by a dedicated Blacksmith.\n\n"+

"        * Forging to Superior Craftsman\n"+
"        * Mending non-magical weapons to Superior Craftsman\n"+
"        * Mending non-magical armours to Superior Craftsman\n\n"+

"    The following skills relating to a Blacksmith's ability to\n"+
"    determine the worth of his creations are also taught.\n\n"+

"        * Appraising objects to Superior Craftsman\n"+
"        * Appraising values to Superior Craftsman\n"+
"        * Trading to Superior Craftsman\n\n"+

"    Only when a Blacksmith knows how to use a weapon effectively can he\n"+
"    hope to forge one with appropriate qualities. As such the following\n"+
"    weapon skills are taught here.\n\n"+

"        * Sword to Superior Journeyman\n"+
"        * Axe to Superior Journeyman\n"+
"        * Club to Superior Journeyman\n"+
"        * Knife to Superior Craftsman\n\n"+  
"                                     Page 4\n"+
    "\n");
    break;

    case 5:
    write(

"                                   Abilities\n\n"+
"    As many Blacksmiths believe, he who is best equipped stands the best\n"+
"    chance of survival during times of danger. To this end, a Blacksmith\n"+
"    will learn the ability to distinguish the relative quality of\n"+
"    items. No longer will he wonder if it is best to use a rusty\n"+
"    longsword compared to a new shortsword. Eventually a Blacksmith, with\n"+
"    a keen eye and years of experience, will have no trouble selecting\n"+
"    the best quality weapon and armour from a large assortment of choices.\n\n"+
"    A razor-sharp edge may be a Blackmith's best friend during any encounter\n"+
"    he stumbles into. While the common man takes his weapon to his local\n"+
"    blacksmith to pay for it to be sharpened, a Blacksmith can do this job\n"+
"    himself in the Forge for free. Also, while travelling, a Blackmith will\n"+
"    learn to find certain rocks that allow him to sharpen his weapon\n"+
"    right there. The need to travel to the nearest town for this service\n"+
"    is alleviated for a Blacksmith.\n"+
"                                     Page 5\n"+
    "\n");
    break;

    case 6:
    write(
"                                      Tax\n\n"+
"    The Blacksmiths Guild tax is slight. Guild members will be notified " +
"    prior to any changes of the tax rate.\n"+
"                                     Page 6\n"+
    "\n");
    break;

    case 7:
    write(
"                     Joining the Blacksmiths Guild\n\n"+
"    Prospective members of the layman Blacksmiths Guild must complete an\n"+
"    apprentice project to prove their worth before joining. Bores, the\n"+ 
"    resident Master Blacksmith, will be the sole judge of a prospective\n"+
"    member's merit. Further questions regarding joining should be\n"+
"    directed towards him.\n"+
"                                     Page 7\n"+
    "\n");
    break;

    case 8:
    write(
"                     Leaving the Blacksmiths Guild\n\n"+
"    It is widely acknowledged the life of a Blacksmith is a hard road to\n"+
"    travel. For those who no longer have the desire to be a part of\n"+
"    this guild, for whatever reason, the option to leave it is\n"+
"    available at no penalty. Type <leave guild> here and all ties with\n"+
"    this guild will be severed.\n"+
"                                     Page 8\n"+
    "\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
