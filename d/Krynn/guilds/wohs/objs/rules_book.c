/*
 * WoHS rule and guidelines book
 * -- Arman, June 2017
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

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
    set_short("lectern with a leather-bound book upon it");
    set_name("book");
    add_name("wohs_rules");
    add_adj("leather-bound");
    set_long("A leather-bound book sits upon a lectern in the " +
        "corner of the waiting room. It contains the ruminations of " +
        "the Master of the Tower of Wayreth and Head on the Conclave " +
        "of Wizards, the mighty archmage Par-Salian.\n" +
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
        say(QCTNAME(this_player())+" turns the leather-bound book to " +
            "page " + LANG_WNUM(what_page) + ".\n");
        write("You turn the leather-bound book to page " +
              LANG_WNUM(what_page) + ".\n");
        return;
    }

    if (gPage == "forward" || gPage == "")
    {
        if (maxm_page < what_page + 1)
        {
            write("You have reached the last page of the leather-bound " +
                "book.\n");
            return;
        }
        what_page += 1;
        if (maxm_page == what_page)
        {
            say(QCTNAME(this_player())+" turns the leather-bound book" +
                " to the last page.\n");
            write("You turn the leather-bound book to the last page.\n");
        }
        else
        {
            say(QCTNAME(this_player()) + " turns the leather-bound book" +
                " to page "+LANG_WNUM(what_page) + ".\n");
            write("You turn the leather-bound book" +
                  " to page "+LANG_WNUM(what_page) + ".\n");
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
    write("\n\n\n" +
       "                       The ruminations of Par-Salian,\n"+
       "                       Head of the Conclave of Wizards,\n"+
       "                       Master of the Tower of Wayreth,\n"+
       "                   Archmage of the Order of the White Robes.\n\n\n\n"+
       "      For the aspiring Wizard, this summary will provide you with an\n"+
       "      understanding of the rules of the Order as well as guidelines\n"+
       "      of expected behaviour. This is not only to manage your expectations\n"+
       "      prior to joining an Order, but also potentially provide guidance that\n" +
       "      ultimately saves your life when sitting the Test of High Sorcery.\n\n"+
       "                                     Page 1\n"+
       "\n");
    break;


    case 2:
    write(
"         The rules of the Wizards of High Sorcery\n\n"+
"   .----------------------------------------------------.\n"+
"  |   1:   All Wizards must support and uphold the      |\n"+
"  |        Foundation of Magic at all times.            |\n"+
"  +-----------------------------------------------------+\n"+
"  |   2:   All Wizards must obey the directions of      |\n"+
"  |        the Conclave and their Order.                |\n"+
"  +-----------------------------------------------------+\n"+
"  |   3:   No outsiders are allowed to learn the        |\n"+
"  |        secrets of the Orders.                       |\n"+
"  +-----------------------------------------------------+\n"+
"  |   4:   All Wizard must report any Renegade          |\n"+
"  |        activity they discover.                      |\n"+
"  +-----------------------------------------------------+\n"+
"  |   5:   Altering the forces of creation and the      |\n"+
"  |        very fabric of magic is expressly forbidden  |\n"+
"  |        unless permission is granted by the          |\n"+
"  |        Conclave to do so.                           |\n"+
"  '-----------------------------------------------------'\n\n\n"+
"                                     Page 2\n"+
    "\n");
    break;

    case 3:
    write(
"               THE FOUNDATIONS OF MAGIC\n\n"+
"   The Foundation of Magic is the Divine Mandate that guides\n"+
" our work within the Towers of High Sorcery:\n\n"+
"   .----------------------------------------------------.\n"+
"  |                 Law of Solinari                     |\n"+
"  |   All Wizards are brothers and sisters in their     |\n"+
"  |   Order. All Orders are brothers and sisters in     |\n"+
"  |   the Art.                                          |\n"+
"  +-----------------------------------------------------+\n"+
"  |                 Law of Lunitari                     |\n"+
"  |   The places of High Sorcery are held in common,    |\n"+
"  |   and no sorcery is to be used there in anger       |\n"+
"  |   against fellow Wizards.                           |\n"+
"  +-----------------------------------------------------+\n"+
"  |                  Law of Nuitari                     |\n"+
"  |   The World beyond the walls of the Towers may      |\n"+
"  |   bring brother against sister, and Order against   |\n"+
"  |   Order, but such is the way of the universe.       |\n"+
"  '-----------------------------------------------------'\n\n"+
"   With the Foundation of Magic to guide our work, the rules\n"+
" of our organization are kept relatively simple, and we are\n"+
" free to perform our primary duties, which are:\n"+
"  A)  We teach and study magic, as well as protect\n"+
"      magic and the wizards who practice magic within\n"+
"      the Towers of High Sorcery;\n"+
"  B)  We seek out and help those that have the gift of\n"+
"      magic and show willingness to take the Test;\n"+
"  C)  We protect Krynn against the dangerous and\n"+
"      uncontrolled magic used by Renegade Mages.\n\n"+
"   As you learn to understand the Divine Mandate, you will\n"+
" see clearly how well the rules have been created to aid us\n"+
" in these tasks. However, situations are certain to arise,\n"+
" where it is wise to have a set of guidelines to help.\n\n"+
"                                     Page 3\n"+
       "\n");
    break;

    case 4:
    write("\n"+
"   Listed below, you will find some example circumstances and\n"+
" guidance on how they should be solved. The cases mostly cover\n"+
" player-player (or guild-guild) interactions, because those\n"+
" are the ones that are likely to cause any problems for our\n"+
" guild.\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: The Foundation of Magic is the guiding  |\n"+
"  |   principles in our work to master magic. With this |\n"+
"  |   in mind, the Law of Nuitari explains how we, as   |\n"+
"  |   individuals, pursue magic in different ways, some |\n"+
"  |   with more moral obligations than others. In this  |\n"+
"  |   pursuit of magic, we may at times find each other |\n"+
"  |   on opposing sides of a conflict.                  |\n"+
"  +-----------------------------------------------------+\n"+
"  |  GUIDELINE: The Law of Nuitari is not going to be   |\n"+
"  |   anyone's carte blanche to do whatever they like   |\n"+
"  |   outside the Towers of High Sorcery. If your mis-  |\n"+
"  |   sion in an area is of a personal nature, you      |\n"+
"  |   should never interfere with Wizards who are wor-  |\n"+
"  |   king to recover magic, or any Wizards on a mis-   |\n"+
"  |   sion given by the Conclave or any of the Orders.  |\n"+
"  +-----------------------------------------------------+\n"+
"  |  GUIDELINE: As an extension of this precept, you    |\n"+
"  |   should never ignore a call for aid from a fellow  |\n"+
"  |   Wizard, unless your prior obligations prevent you |\n"+
"  |   from doing so. Such duties could include an       |\n"+
"  |   urgent mission given to you by the Conclave or    |\n"+
"  |   the head of your Order.                           |\n"+
"  '-----------------------------------------------------'\n\n"+
"   Please note: If you are on an urgent mission to recover\n"+
" magic: be it parchments; items; or components, you are enti-\n"+
" rely free to challenge the presence of any Wizard who enters\n"+
" the area; in such situations, you negotiate the outcome with\n"+
" the other Wizard on the spot.\n\n"+
"   These negotiations may, of course, vary depending on the\n"+
" moral persuasions of the two Wizards in question, and may\n"+
" result in any number of possible outcomes, ranging from\n"+
" cooperation to conflict.\n\n"+
"   Remember that you might not always be the strongest Wizard,\n"+
" and a wise Wizard is often one who avoids a battle, maybe by\n"+
" offering something in return for cooperation.\n\n"+
"   If you are the most powerful Wizard in the confrontation,\n"+
" you would be wise to offer your cooperation and wisdom, rather\n"+
" than to seek a conflict with your fellow Wizards, particularly\n"+
" when said Wizards are significantly less experienced than\n"+
" you.\n"+
"                                     Page 4\n"+
    "\n");
    break;

    case 5:
    write("\n\n"+ 
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: A Wizards first loyalty is always to    |\n"+
"  |   Magic, and by extension that means the Conclave   |\n"+
"  |   first and foremost, secondly to the brothers and  |\n"+
"  |   sisters of his or her Order and thirdly towards   |\n"+
"  |   all Wizards of High Sorcery. All other personal   |\n"+
"  |   loyalties must come after this.                   |\n"+
"  +-----------------------------------------------------+\n"+
"  |  GUIDELINE: If an emergency threatens one or more   |\n"+
"  |   Orders of the Wizards of High Sorcery, we will    |\n"+
"  |   answer this crisis as a united guild.             |\n"+
"  '-----------------------------------------------------'\n\n"+
"   Example situation: Let us assume that the Knights of Solamnia\n"+
" declare war against the Black Order. In this case, the Conclave\n"+
" will unite and defend the Wizards who are under threat. Sending\n"+
" a clear message to the Knights of our intent to stand strong\n"+
" and united against their attacks will show the Knights that they\n"+
" cannot divide us into parts for their own benefit. It is not our\n"+
" way to leave fellow Wizards behind.\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: Threats against individual Wizards are  |\n"+
"  |   handled by the Conclave, or by the Order if the   |\n"+
"  |   Conclave decides not to take action. In most      |\n"+
"  |   cases, the Conclave will not take action unless   |\n"+
"  |   the threat is deemed to be unprovoked, exaggera-  |\n"+
"  |   ted or prolonged or if magic, in general, will be |\n"+
"  |   threatened as well.                               |\n"+
"  '-----------------------------------------------------'\n\n"+
"   Please note: An exaggerated threat might be when a person\n"+
" of great experience assaults our less experienced Wizards, or\n"+
" when a group or guild attempts to kill a single Wizard.\n\n"+
"                                     Page 5\n"+
    "\n");
    break;

    case 6:
    write("\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: Any emergency that threatens to desta-  |\n"+
"  |   bilize the balance on Ansalon will be dealt with  |\n"+
"  |   according to the decisions of the Conclave, or if |\n"+
"  |   Conclave decides not to take action, the will of  |\n"+
"  |   an individual Order (or individual Wizards, if    |\n"+
"  |   the Orders allows it).                            |\n"+
"  '-----------------------------------------------------'\n\n"+
"   For example, the Blue Dragon Army (BDA) declares war against\n"+
" the Knights of Solamnia (Knights). The Conclave might decide\n"+
" to let it pass because it doesn't concern us directly, and\n"+
" it does not threaten magic or wizards in general. But the\n"+
" Black Order decides to allow individual wizards to aid the\n"+
" BDA in their war.\n\n"+
"   This situation is acceptable, as long as there is no threat\n"+
" to magic itself on Ansalon. If at any point during this war,\n"+
" magic is threatened (or the Conclave decides), the Wizards of\n"+
" High Sorcery will unite again and face this new threat\n"+
" together, thus ignoring all alliances that may have existed\n"+
" during this example war.\n\n"+
"   To continue the example: A White Robed Wizard decides to\n"+
" aid the Knights in a single daring raid against the town of\n"+
" Sanction, and in their haste or anger, the BDA choose to\n"+
" declare war against all White Robed Wizards. This new situa-\n"+
" tion will be re-examined by the Conclave, as a threat towards\n"+
" any Order within our organization may be seen as a threat\n"+
" towards our entire guild.\n\n"+
"   Please note: While the Conclave may unite the guild against\n"+
" an emergency, it must remain clear, that if the Conclave\n"+
" discovers evidence that any Wizards or Orders are involved in\n"+
" the instigation of the emergency, these Wizards will be held\n"+
" accountable for their actions before the Conclave. It is not\n"+
" our mission to start wars on Ansalon, or elsewhere within these\n"+
" Realms.\n\n"+
"   Please note: It goes against everything we stand for if we\n"+
" find ourselves in a situation where two Orders face each other\n"+
" as enemies in a war, but according to the Foundation of Magic,\n"+
" it is not expressly forbidden. If this happens, the Conclave\n"+
" must take careful note of the situation as often as possible\n"+
" and be ready to pull everyone out of the conflict. Our mission\n"+
" is not to eradicate each other in a conflict that does not\n"+
" concern us directly.\n"+
"                                     Page 6\n"+
    "\n");
    break;

    case 7:
    write("\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: Any other situation involving a Wizard, |\n"+
"  |   that does not include any other Wizards of High   |\n"+
"  |   Sorcery or magic in general, may be handled as    |\n"+
"  |   the Wizard wishes, according to his or her ideals |\n"+
"  |   and morals, unless orders from the Conclave or    |\n"+
"  |   his or her Order has determined otherwise.        |\n"+
"  '-----------------------------------------------------'\n"+
"   As an example, if two opposing factions from another Realm\n"+
" go against each other, any Wizard may fight whomever they\n"+
" choose, as long as it does not affect the Wizards of High\n"+
" Sorcery as a whole by doing so.\n\n"+
"   This example should also show that all wizards must think\n"+
" carefully before creating a situation where Wizards of High\n"+
" Sorcery may be forced to react to a threat against the entire\n"+
" guild.\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: When a Wizard breaks any of the five    |\n"+
"  |   rules, or violates the principles on which the    |\n"+
"  |   Foundation of Magic is based, by knowingly and    |\n"+
"  |   willingly putting magic or fellow Wizards in      |\n"+
"  |   harm's way for personal gain, said Wizard risks   |\n"+
"  |   becoming an outcast from the Towers of High       |\n"+
"  |   Sorcery; a Renegade Mage.                         |\n"+
"  '-----------------------------------------------------'\n\n"+
"   Please note: The highest and most severe punishment that\n"+
" can be given to any Wizard of High Sorcery is to cast the\n"+
" Wizard out from the Towers of High Sorcery as a Renegade. \n"+
" Renegades Mages are the bane of our guild; these wayward\n"+
" individuals have chosen to deny the rules that guide our\n"+
" work on Ansalon, and by doing so, they threaten to destabi-\n"+
" lize everything we stand for in the Towers of High Sorcery.\n"+
"                                     Page 7\n"+
    "\n");
    break;

    case 8:
    write("\n\n"+
"   Renegades have denied following the few and simple rules\n"+
" of our organization for purely personal gains, and they must\n"+
" be brought to justice one way or the other, before they\n"+
" destroy what we stand for.\n\n"+
"  .----------------------------------------------------.\n"+
"  |  GUIDELINE: Should you ever find yourself in a      |\n"+
"  |   situation, where your allies or enemies uses the  |\n"+
"  |   skills of a Renegade Wizard, then you should      |\n"+
"  |   always, as soon as possible, report the actions   |\n"+
"  |   taken by the Renegade to the Conclave of Wizards. |\n"+
"  +-----------------------------------------------------+\n"+
"  |  GUIDELINE: If you face a Renegade in your travels, |\n"+
"  |   you are in your right mind to challenge the Rene- |\n"+
"  |   gade to return with you to the Towers of High     |\n"+
"  |   Sorcery, bringing the Renegade to face any char-  |\n"+
"  |   ges against him or her. You are allowed to attack |\n"+
"  |   the Renegade if the conflict escalates, or if the |\n"+
"  |   Renegade refuses your challenge.                  |\n"+
"  +-----------------------------------------------------+\n"+
"  |  GUIDELINE: You must never lend aid to any Renegade |\n"+
"  |   or anyone employing a Renegade, under any         |\n"+
"  |   circumstances, unless the Conclave has given      |\n"+
"  |   permission.                                       |\n"+
"  '-----------------------------------------------------'\n\n"+
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
