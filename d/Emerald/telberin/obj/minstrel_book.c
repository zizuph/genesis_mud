/*
 * Book in the entry room of the Telberin Minstrel Guild
 * -- Arman, December 2019
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>

/*
 * Prototype
 */
varargs void read_book_at_page(int page, string verb);

int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 5;
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
    set_short("lectern with a leather-bound book upon it");
    set_name("book");
    add_name("minstrel_book");
    add_adj("leather-bound");
    set_long("A leather-bound book sits open upon the lectern near " +
             "the entry of the Minstrel's Guild.\n" +
             "@@opened_at_page@@");

    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_NO_GET,"The book cannot be taken from the lectern.\n");

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
        write("The leather-bound book is already open.\n");
        return;
    }
    what_page = 1;
    write("You open the leather-bound book at page " +
    LANG_WNUM(what_page) + ".\n");
    say(QCTNAME(this_player()) + " opens the leather-bound book.\n");
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
        write("The leather-bound book is already closed.\n");
        return;
    }
    write("You close the leather-bound book.\n");
    say(QCTNAME(this_player()) + " closes the leather-bound book.\n");
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
        write("But the leather-bound book is closed.\n");
        return;
    }
    appr_num = LANG_NUMW(gPage);
    if (appr_num > 0 && appr_num < maxm_page + 1)
    {
        what_page = appr_num;
        say(QCTNAME(this_player())+" turns the leather-bound book to page "+
            LANG_WNUM(what_page) + ".\n");
        write("You turn the leather-bound book to page " +
              LANG_WNUM(what_page) + ".\n");
        return;
    }

    if (gPage == "forward" || gPage == "")
    {
        if (maxm_page < what_page + 1)
        {
            write("You have reached the last page of the leather-bound book.\n");
            return;
        }
        what_page += 1;
        if (maxm_page == what_page)
        {
            say(QCTNAME(this_player())+" turns the leather-bound book"+
                " to the last page.\n");
            write("You turn the leather-bound book to the last page.\n");
        }
        else
        {
            say(QCTNAME(this_player())+" turns the leather-bound book"+
                " to page "+LANG_WNUM(what_page)+".\n");
            write("You turn the leather-bound book"+
                  " to page "+LANG_WNUM(what_page)+".\n");
        }
        return;
    }
    else if (gPage == "backward" || gPage == "back")
    {
        if (what_page == 1)
        {
            write("You cannot turn the " + short(this_player()) +
                  " below the first page.\n");
            return;
        }
        what_page -= 1;
        say(QCTNAME(this_player())+" turns the leather-bound book"+
            " to page "+LANG_WNUM(what_page)+".\n");
        write("You turn the leather-bound book" + 
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
                write("The leather-bound book is closed.\n");
                break;
            }
            say(QCTNAME(this_player())+" reads the leather-bound book.\n");
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
    write("                       The Minstrel's Guild of Telberin\n"+
          "                              General Information\n\n"+
          "         Welcome distinguished performers!  . . . . . . . . . 2\n"+
          "         The Outer Halls - In tribute to the Lost Muses . . 3-5\n\n"+
          "                                     Page 1\n");
    break;


    case 2:
    write(
"                     Welcome distinguished performers!\n\n"+
"    The Masters of the Bardic college of Telberin welcome all visiting\n"+
"    distinguishedperformers to the Halls of the Minstrel's Guild!\n\n"+
"    Please respect that access to the Inner Halls and broader school\n"+
"    campus is strictly restricted to those who have been accepted as\n"+
"    Bards of Telan-Ri.\n\n"+
"    Feel welcome to engage with our journeyman Bards and expert \n"+    
"    instrument repairers, as well as seek musical inspiration.\n\n"+
"                                     Page 2\n"+
    "\n");
    break;

    case 3:
    write(
"        The Outer Halls - In tribute to the Lost Muses\n\n"+
"    In the days of ancient lore, the muses who brought joy to \n"+
"    the world were known as Melete, Mneme, and Aoide which \n"+
"    loosely translates to Practice, Memory, and Song. Music \n"+
"    was very beautiful and very uniform. Its sole purpose was\n"+
"    to enlighten and please the listener. Through the ages, \n"+
"    while styles have progressed, musics main purpose has never\n"+
"    changed.\n\n"+
"    At the end of the days of ancient lore, nine muses came to\n"+
"    the land bringing with them the different styles of music -\n"+
"    being epic, historic, lyric, comedic, tragic, lively,\n"+
"    heartfelt, sacred, and mystic. This music was created using\n"+
"    the diatonic scale to fill the land with joy.\n\n"+
"                                     Page 3\n"+
       "\n");
    break;

    case 4:
    write("\n\n"+
"    A century later music changed when Thamyris, known as the\n"+
"    greatest minstrel in the land, started creating songs with\n"+
"    the root note being the second note of the diatonic scale.\n"+
"    This Dorian scale led to the next revolution of music.\n"+
"    From this came songs of darkness and sadness, songs of Power,\n"+
"    music entwined with spellcraft.\n\n"+
"    The nine muses cultivated this style, to the anger of Telan-Ri.\n"+
"    His wrath was swift. Five of the muses - whether destroyed or \n"+
"    banished - were never seen again.\n\n"+
"    The four remaining muses fled our lands with their followers\n"+
"    in an exodus to an old land of shadows, bordering the \n"+
"    subterranean lands where Val-Shoreil's influence remains \n"+
"    strong. In that land the power of the muses faded and much of \n"+
"    the lore about their songs of Power was forgotten.\n\n"+
"                                     Page 4\n"+
    "\n");
    break;

    case 5:
    write(

"    The Minstrel's Guild in Telberin is the final custodian of the\n"+
"    musical lore of the muses, with access restricted to those who\n"+
"    have progressed to be acknowedged as Master Bards of Telan-Ri.\n\n"+
"    Visiting lay Minstrels may seek training in these halls from\n"+
"    journeyman Bards in language skills and spellcraft, the latter\n"+
"    training enhancing the effectiveness of known songs of Power.\n\n"+
"    It has also been known for visiting Minstrels who perform to\n"+
"    the statues of the lost muses standing in this hall to receive\n"+
"    epiphanies on songs of power long lost.\n\n"+
"                                     Page 5\n"+
    "\n");
    break;

    default:
    write("This page is empty.\n");
    return 0;
    break;
    }
//  return 1;
}
