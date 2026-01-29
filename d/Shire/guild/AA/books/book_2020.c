/*
 * Book of Angmar Army
 * by Milan
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
    set_short("old leather book");
    set_long("This is an old leather book. It is made from the skins of " +
        "enemies and looks well worn. Across the front of the book is " +
        "the title:\n\n"+
        "            The Army of Angmar\n\n"+
         "The book is connected to the wall by a heavy chain, preventing " +
        "anyone from stealing it. Next to the book is a marker.\n\n"+
        "@@opened_at_page@@");
    add_name("book");
    add_adj(({"old", "leather"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_M_NO_GET, "You can't take this book! It has been chained " +
        "to the wall.\n");
    add_item("chain", 
        "It is made from heavy links. It is strong and connects the old " +
        "leather book to the wall, preventing it from being stolen.\n");

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
"    |  History of the Army of Angmar. . . . . . . . . . . . . . . .  2  |\n" +
"    |                                                                   |\n" +
"    |  What We Offer Loyal Soldiers . . . . . . . . . . . . . . . .  9  |\n" +
"    |                                                                   |\n" +
"    |  Organization of the Army of Angmar . . . . . . . . . . . . . 10  |\n" +
"    |                                                                   |\n" +
"    |  The Ranking System of the Army of Angmar . . . . . . . . . . 11  |\n" +
"    |                                                                   |\n" +
"    |  Number of Positions Available. . . . . . . . . . . . . . . . 12  |\n" +
"    |                                                                   |\n" +
"    |  Council. . . . . . . . . . . . . . . . . . . . . . . . . . . 13  |\n" +
"    |                                                                   |\n" +
"    |  Punishment for Traitors. . . . . . . . . . . . . . . . . . . 14  |\n" +
"    |                                                                   |\n" +
"    |  Discipline and Punishments . . . . . . . . . . . . . . . . . 15  |\n" +
"    |                                                                   |\n" +
"    |  Voting on Punishments. . . . . . . . . . . . . . . . . . . . 16  |\n" +
"    |                                                                   |\n" +
"    |  Deciding on Punishments. . . . . . . . . . . . . . . . . . . 17  |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 2:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 2 |\n" +
"    |                                                                   |\n" +
"    |  The History of the Army of Angmar                                |\n" +
"    |  *********************************                                |\n" +
"    |                                                                   |\n" +
"    |  The history of the Army is a long and bloody one. It began in    |\n" +
"    |  the year 1500 of the Second Age when the elven smiths of Eregion,|\n" +
"    |  under the tutelage of our Dark Lord, reached the height of their |\n" +
"    |  skills and began forging the Rings of Power. Celebrimbor, the    |\n" +
"    |  leader of the elven smiths, was jealous of the Dark Lord's       |\n" +
"    |  knowledge and skills. After learning all that he could from our  |\n" +
"    |  lord, he betrayed his mentor with foul lies and innuendo. The    |\n" +
"    |  other elves, weak in mind as well as body, failed to see that    |\n" +
"    |  Celebrimbor was motivated by hatred and spite, and were deceived.|\n" +
"    |  As a result, in the year 1693 the war between elves and the Dark |\n" +
"    |  Lord began, and ever since that time, our lord has continued in  |\n" +
"    |  his attempts to restore the order in the world.                  |\n" +
"    |                                                                   |\n" +
"    |  The Dark Lord wished to appeal to the worthy among the race of   |\n" +
"    |  Men, and to this end, made a gift of rings to nine of the great- |\n" +
"    |  est Numenoreans. The rings allowed these selected Numenoreans to |\n" +
"    |  transcend their mortality (the curse of the Valar!), and opened  |\n" +
"    |  their eyes to the truth of things.                               |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 3:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 3 |\n" +
"    |                                                                   |\n" +
"    |  These nine, now known as the Nazgul, began spreading the word    |\n" +
"    |  amongst the other Numenoreans in the hope that the truth would   |\n" +
"    |  finally be heard. Unfortunately, many of the Numenoreans refused |\n" +
"    |  to listen. Rather than face the prospect of freedom under our    |\n" +
"    |  lord, they placed their fear-instilled faith in the Valar, who   |\n" +
"    |  had oppressed and used them for so many years. The Dark Lord     |\n" +
"    |  despaired in the realization that these unbelievers were a       |\n" +
"    |  blight, a disease that would undermine his struggle for order    |\n" +
"    |  if given the chance. So, he petitioned the king of Numenor to    |\n" +
"    |  remove them. The king, sensing the honesty in the Dark Lord,     |\n" +
"    |  agreed. He banished the unbelievers to Middle Earth. There they  |\n" +
"    |  formed the realms of Arnor and Gondor.                           |\n" +
"    |                                                                   |\n" +
"    |  With the word spreading, the men of Numenor thought they might   |\n" +
"    |  finally throw off the yoke of slavery the Valar had cast about   |\n" +
"    |  their neck. In the year 3319, they sailed to Aman in the hopes   |\n" +
"    |  of coming to some peaceful agreement with their masters. This    |\n" +
"    |  was to no avail, for the Valar were ever as treacherous as their |\n" +
"    |  minions, and destroyed the brave men of Numenor before they had  |\n" +
"    |  uttered a word.                                                  |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 4:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 4 |\n" +
"    |                                                                   |\n" +
"    |  The Dark Lord returned to Mordor with a heavy heart. He realized |\n" +
"    |  that both the elves and the traitors of Numenor were beyond      |\n" +
"    |  redemption, and that Middle-earth's only chance for peace and    |\n" +
"    |  freedom was their complete destruction. Therefore, he gathered   |\n" +
"    |  his armies of orcs and trolls, and swept the Gondorian army out  |\n" +
"    |  of Ithilien. Unfortunately, the combined might of elves and men  |\n" +
"    |  were too much, and in the year 3434, our Lord's army was de-     |\n" +
"    |  feated at Dagorlad, or the Battle-Plain, just north of the gates |\n" +
"    |  of Mordor. The Alliance besieged the Dark Lord at Barad-dur, and |\n" +
"    |  after several years of bitter fighting, they cruelly slew his    |\n" +
"    |  physical form. Thus ended the Second Age.                        |\n" +
"    |                                                                   |\n" +
"    |  After a thousand years in the Void, the Dark Lord returned and   |\n" +
"    |  settled in Dol Guldur, sending his Nazgul on missions across the |\n" +
"    |  land to spread his power and prepare for his return. The         |\n" +
"    |  mightiest of the Nazgul was sent North and formed the Kingdom    |\n" +
"    |  of Angmar, gathering great armies of orcs and trolls to do the   |\n" +
"    |  will of his master, that is, the cleansing of Middle-Earth. The  |\n" +
"    |  Witch-king, as captain of Angmar, sent many human agents and     |\n" +
"    |  dark priests to infiltrate Arnor. As a result of their skillful  |\n" +
"    |  manipulations, Arnor soon split into three smaller kingdoms.     |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 5:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 5 |\n" +
"    |                                                                   |\n" +
"    |  Rhudaur, the western kingdom, was one of these kingdoms and the  |\n" +
"    |  first to submit to the Army of Angmar. This allowed them to      |\n" +
"    |  liberate the Rhudaric Hillmen who had long been slaves of the    |\n" +
"    |  evil Dunedain. In the year 1637, a great plague killed the       |\n" +
"    |  majority of Dunedain in Carlodan, the southern kingdom in Arnor. |\n" +
"    |  This resulted in the majority of its remaining people to abandon |\n" +
"    |  their homeland, leaving only Arthedain, the western kingdom, for |\n" +
"    |  the Army of Angmar to war against.                               |\n" +
"    |                                                                   |\n" +
"    |  In 1973, the Witch-king threw the full might of Angmar against   |\n" +
"    |  Arthedain and after a brief struggle, the final kingdom of Arnor |\n" +
"    |  collapsed in ruin. Thus the North was liberated by the Angmar    |\n" +
"    |  army's force of arms. Unfortunately, it was not to remain so.    |\n" +
"    |                                                                   |\n" +
"    |  In 1975, the Gondorian army marched north, and together with     |\n" +
"    |  elves from Rivendell and Lindon, attacked the Angmarian troops.  |\n" +
"    |  Despite the overwhelming numbers of aggressors, the Army of      |\n" +
"    |  Angmar fought bravely and the result of the battle was long in   |\n" +
"    |  doubt until, at acrucial time, the Witch-king deserted his       |\n" +
"    |  troops and fled. The Gondorians, with their spirits uplifted,    |\n" +
"    |  forced the Army of Angmar to retreat in bad order with huge      |\n" +
"    |  attrition. After the defeat, the remnants of the Army of Angmar  |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 6:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 6 |\n" +
"    |                                                                   |\n" +
"    |  gathered in the Misty Mountains and with heavy hearts, brooded   |\n" +
"    |  over what could have been.                                       |\n" +
"    |                                                                   |\n" +
"    |  Little is known about the Army until the year 2060 of the Third  |\n" +
"    |  Age, when the Dark Lord returned to Dol Guldur and sent north a  |\n" +
"    |  new captain for the Army. This second captain was a mighty child |\n" +
"    |  of Numenor named Morgrond, or Black-Club in the common tongue.   |\n" +
"    |  He was named this as a sign of respect for his mastery of        |\n" +
"    |  fighting with clubs.                                             |\n" +
"    |                                                                   |\n" +
"    |  Besides his combat prowess, Morgrond was renowned for being      |\n" +
"    |  unfailingly loyal to the Dark Lord. Morgrond's loyalty to the    |\n" +
"    |  Dark Lord only led him to be called, The Club of the Dark Lord,  |\n" +
"    |  in some circles. Unlike the Nazgul, he didn't need a ring of     |\n" +
"    |  power to show him the truth and greatness inherent in the Dark   |\n" +
"    |  Lord's great scheme--Morgrond had known it all along.            |\n" +
"    |                                                                   |\n" +
"    |  Morgrond had no difficulty in regathering the Army of Angmar,    |\n" +
"    |  for most still believed in the Dark Lord's cause and could not   |\n" +
"    |  help but admire their new captain whose belief epitomised their  |\n" +
"    |  own. In the year 2063, the newly reformed army marched over the  |\n" +
"    |  Men-i-Naugrim to Rhun and there built a fortress which they      |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 7:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 7 |\n" +
"    |                                                                   |\n" +
"    |  inhabited for the next 400 years. The Army grew both in strength |\n" +
"    |  and numbers, achieving under Morgrond, an unsurpassed mastery    |\n" +
"    |  with the club--the only weapon the army has used since this time.|\n" +
"    |                                                                   |\n" +
"    |  In the year 2460, the Dark Lord returned to Dol Guldur and took  |\n" +
"    |  the newly revitalised army with him. In the year 2510, the       |\n" +
"    |  Balchoth Army, ordered by the Dark Lord, launched an assault     |\n" +
"    |  against the Dunedain. Morgrond, with a small part of the Army of |\n" +
"    |  Angmar, joined them in order to observe the progress and report  |\n" +
"    |  the results to the Dark Lord. The Balchoth were defeated on the  |\n" +
"    |  Field of Celebrant, when the Gondorian Army received support     |\n" +
"    |  from Eorl the Young and his cursed Eothed.                       |\n" +
"    |                                                                   |\n" +
"    |  Morgrond, while fighting in a desperate rear guard action, was   |\n" +
"    |  slain. His bravery allowed the soldiers of the Army of Angmar to |\n" +
"    |  retreat to Dol Guldur and report the anihilation of the Balchoth |\n" +
"    |  to the Dark Lord. The Dark Lord then appointed a third Captain   |\n" +
"    |  for the army known as Belturma, also known as, Strong shield. He |\n" +
"    |  taught the Army advanced defensive techniques involving the use  |\n" +
"    |  of the shield, as well as various strategies for close formation |\n" +
"    |  fighting. Under the orders of the new captain, the Army went     |\n" +
"    |  in search of Eorl.                                               |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 8:
            write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 8 |\n" +
"    |                                                                   |\n" +
"    |  With the help of Dunlendings and Hillmen from the southern Misty |\n" +
"    |  Mountains, they found him in the year 2545 on the Wold. With     |\n" +
"    |  the fire of retribution burning hot in their hearts, they        |\n" +
"    |  wreaked their vengeance on Eorl's troops and smashed Eorl to     |\n" +
"    |  his death.                                                       |\n" +
"    |                                                                   |\n" +
"    |  In the year 2941, the Dark Lord was forced to abandon the home   |\n" +
"    |  he had made in Dol Guldur by the foul machinations of the White  |\n" +
"    |  Council. Before leaving, he ordered the Army of Angmar to head   |\n" +
"    |  west to the Misty Mountains in order to protect the mountain     |\n" +
"    |  passes from incursion and harry the followers of the Valar.      |\n" +
"    |                                                                   |\n" +
"    |  The journey undertaken by the Army was a difficult one, and      |\n" +
"    |  many men were lost both to the treacherous mountain passes and   |\n" +
"    |  skirmishes with the cowardly elves of Lorien. By far the         |\n" +
"    |  greatest loss was Belturma, who at the age of 512, died a        |\n" +
"    |  natural death and was buried on the slopes of the Misty          |\n" +
"    |  Mountains. So it was that the Angmarim arrived at their current  |\n" +
"    |  location, once more proudly raising the banners of the Dark      |\n" +
"    |  Lord in the North.                                               |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 9:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                            Page 9 |\n" +
"    |                                                                   |\n" +
"    |  What We Offer Loyal Soldiers                                     |\n" +
"    |  ****************************                                     |\n" +
"    |                                                                   |\n" +
"    |  As a soldier in the Army of Angmar, we give you the chance to    |\n" +
"    |  stay on the right side when the final war breaks out.            |\n" +
"    |                                                                   |\n" +
"    |  In addition to this, we teach many skills in our training hall.  |\n" +
"    |  Layman soldiers train to  lower levels in some skills. In addi-  |\n" +
"    |  tion, all soldiers pay tax to be a member. Layman soldier's tax  |\n" +
"    |  is a little lower                                                |\n" +
"    |                                                                   |\n" +
"    |  A soldier's is using shield and club. We teach two special       |\n" +
"    |  skills. One helps you to defend yourself better when using a     |\n" +
"    |  shield and the other one teaches you how to properly smash your  |\n" +
"    |  enemies with a club.                                             |\n" +
"    |                                                                   |\n" +
"    |  Members can do 'help angmar' for more information.               |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 10:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 10 |\n" +
"    |                                                                   |\n" +
"    |  Organization of the Army of Angmar                               |\n" +
"    |  **********************************                               |\n" +
"    |                                                                   |\n" +
"    |  Every member has given title according to their position in the  |\n" +
"    |  Army. The title consists of an adjective and a rank. The rank    |\n" +
"    |  determines your position in the Army. Immediately after joining, |\n" +
"    |  you are a Servant. After short trial period, you become a full   |\n" +
"    |  member with the rank of a Footman. From then on, your behaviour, |\n" +
"    |  experience, and skills determine your rank. the actual ranking   |\n" +
"    |  system is described on the next page.                            |\n" +
"    |                                                                   |\n" +
"    |  The adjective is related to your general knowledge of the world  |\n" +
"    |  and also how are you known in the world. Here is the list of all |\n" +
"    |  adjectives, in increasing order:                                 |\n" +
"    |                                                                   |\n" +
"    |      * Fresh, Insecure, Young, Training                           |\n" +
"    |      * Proud, Legionary, Experienced, Elder                       |\n" +
"    |      * Dangerous, Cruel, Notorious, Infamous                      |\n" +
"    |      * Bestial, Feared, Formidable, Dreadful                      |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 11:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 11 |\n" +
"    |                                                                   |\n" +
"    |  The Ranking System of the Army of Angmar                         |\n" +
"    |  ****************************************                         |\n" +
"    |                                                                   |\n" +
"    |  The Army of Angmar has a fixed structure, and so there is only a |\n" +
"    |  fixed number of positions for every rank. This number depends on |\n" +
"    |  the number of members with a lower rank. Note that there is      |\n" +
"    |  always at least one position available. If you want to reach a   |\n" +
"    |  new rank, you must fulfill two conditions:                       |\n" +
"    |                                                                   |\n" +
"    |      1.  You must be good enough to qualify for the position      |\n" +
"    |      2.  You must be better than others who qualify for the       |\n" +
"    |          position                                                 |\n" +
"    |                                                                   |\n" +
"    |  From time to time, every member is reconsidered and ranks are    |\n" +
"    |  assigned according to their current position in the Army. This   |\n" +
"    |  means you might find yourself demoted while someone else got     |\n" +
"    |  promoted. Hope this will keep the competitive spirit up which in |\n" +
"    |  turn will help to build up better and stronger army.             |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 12:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 12 |\n" +
"    |                                                                   |\n" +
"    |  Number of Positions Available                                    |\n" +
"    |  *****************************                                    |\n" +
"    |                                                                   |\n" +
"    |  Footman . . . . . . . . . any number                             |\n" +
"    |  Standard Bearer . . . . . 1 position for every  2 lower members  |\n" +
"    |  Corporal. . . . . . . . . 1 position for every  5 lower members  |\n" +
"    |  Sergeant. . . . . . . . . 1 position for every  9 lower members  |\n" +
"    |  Warrant Officer . . . . . 1 position for every 15 lower members  |\n" +
"    |  Lieutenant. . . . . . . . 1 position for every 24 lower members  |\n" +
"    |  Captain . . . . . . . . . 1 position                             |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 13:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 13 |\n" +
"    |                                                                   |\n" +
"    |  Council                                                          |\n" +
"    |  *******                                                          |\n" +
"    |                                                                   |\n" +
"    |  There is elected a council that has the final word on all        |\n" +
"    |  punishments. Council members are elected by all soldiers. How-   |\n" +
"    |  ever, votes are weighted according to the soldier's rank. Here   |\n" +
"    |  are the exact weights:                                           |\n" +
"    |                                                                   |\n" +
"    |        Rank                Weight                                 |\n" +
"    |        --------------------------                                 |\n" +
"    |        Footman. . . . . . .  2                                    |\n" +
"    |        Standard Bearer. . .  3                                    |\n" +
"    |        Corporal . . . . . .  4                                    |\n" +
"    |        Sergeant . . . . . .  5                                    |\n" +
"    |        Warrant Officer. . .  6                                    |\n" +
"    |        Lieutenant . . . . .  7                                    |\n" +
"    |        Captain. . . . . . .  8                                    |\n" +
"    |                                                                   |\n" +
"    |  Any soldier below the rank of a Lieutenant can be in the         |\n" +
"    |  Council. Only the Captain, Lieutenants, and a council member can |\n" +
"    |  start an election for a position in council. This cannot be done |\n" +
"    |  sooner than one month after last election.                       |\n" +
"    |___________________________________________________________________|\n\n");

            break;
        case 14:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 14 |\n" +
"    |                                                                   |\n" +
"    |  Punishments for Traitors                                         |\n" +
"    |  ************************                                         |\n" +
"    |                                                                   |\n" +
"    |  Beware the wrath of the Dark Lord. Most of all, he hates traitors|\n" +
"    |  and has no mercy for them. The least he will do to you for       |\n" +
"    |  leaving the army, or repetitive killing of members of his army,  |\n" +
"    |  is send a bunch of strong warriors with clubs to beat your       |\n" +
"    |  stupidity out of your head. And be aware that after a thorough   |\n" +
"    |  beating on your head, it will most likely forget not only your   |\n" +
"    |  name, but many other things. Don't be surprised if you can't     |\n" +
"    |  remember skills you knew before the beating took place.          |\n" +
"    |                                                                   |\n" +
"    |  Naturally 'skills' means not only skills related to the Army.    |\n" +
"    |  The curing has also some impact on your physical state. So,      |\n" +
"    |  apart from forgetting things, you will also feel weaker, with    |\n" +
"    |  broken health and be somehow clumsier. Not to mention, you may   |\n" +
"    |  forget how to count to ten and suddenly be afraid of every       |\n" +
"    |  mouse running your way. The Dark Lord will not tolerate solders  |\n" +
"    |  who do not stay under his sway. If you venture to much from his  |\n" +
"    |  darkness, he will abandon you and banish you from his Army. You  |\n" +
"    |  have been warned.                                                |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 15:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 15 |\n" +
"    |                                                                   |\n" +
"    |  Discipline and Punishments                                       |\n" +
"    |  **************************                                       |\n" +
"    |                                                                   |\n" +
"    |  In order to maintain the discipline in the Army, there is a set  |\n" +
"    |  of punishments to fit every possible level of misbehaving.       |\n" +
"    |  These are:                                                       |\n" +
"    |                                                                   |\n" +
"    |      1. Ban from training for 2 weeks                             |\n" +
"    |      2. Lowering effectiveness of specials for 10 days + above    |\n" +
"    |      3. Blocking specials for 1 week + above                      |\n" +
"    |      4. Beating on the head (losing skills) + above               |\n" +
"    |      5. Extermination                                             |\n" +
"    |      6. Being booted from the Army + beating on the head          |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 16:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 16 |\n" +
"    |                                                                   |\n" +
"    |  Voting on Punishments                                            |\n" +
"    |  *********************                                            |\n" +
"    |                                                                   |\n" +
"    |  Suggesting a punishment can only be done by the Captain,         |\n" +
"    |  Lieutenant or a council member. A soldier cannot be recommended  |\n" +
"    |  for the same punishment twice within a one month period, but he  |\n" +
"    |  can be recommended for a different punishment. After the         |\n" +
"    |  recommendation is made, there is exactly one week to vote on it. |\n" +
"    |                                                                   |\n" +
"    |  Who can vote on punishments?                                     |\n" +
"    |                                                                   |\n" +
"    |      Punishment  #1: Council, Lieutenants, and higher             |\n" +
"    |      Punishment  #2: Council, Warrant Officers, and higher        |\n" +
"    |      Punishment  #3: Council, Sergeants, and higher               |\n" +
"    |      Punishment  #4: Council, Corporals, and higher               |\n" +
"    |      Punishments #5 & 6: Council, Standard Bearers, and higher    |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
        case 17:
        write("\n"+
"     ___________________________________________________________________\n" +
"    |                                                           Page 17 |\n" +
"    |                                                                   |\n" +
"    |  Deciding on Punishments                                          |\n" +
"    |  ***********************                                          |\n" +
"    |                                                                   |\n" +
"    |  All votes have equal weight and the majority wins. If fewer than |\n" +
"    |  30% of soldiers vote or if there is a tie, then only council     |\n" +
"    |  member votes will be counted. A council member who does not cast |\n" +
"    |  a vote will be considered to have voted against.                 |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |                                                                   |\n" +
"    |___________________________________________________________________|\n\n");
            break;
/*
        case 17:

            break;
        case 18:
            write("\n"+
"Register of the members of Army of Angmar.\n"+
"******************************************\n"+
"\n"+
"Captain:\n"+
"********\n\n   >>>"+AA_COUNCIL_OBJ->query_captain()+
"<<<\n\n"+
"\n" +
"Lieutenants:\n" +
"************\n\n   >>" + AA_COUNCIL_OBJ->query_lieutenant() +
"<<\n\n" +
//"Master Sergeants:\n"+
//"************\n\n"+
//(book_is_private ?
//make_string_from_list(AA_RANKS_OBJ->query_players_with_rank_no(6)) :
//"  ----")+
//"\n\n"+
"Master Sergeants:\n"+
"*****************\n\n"+
(book_is_private ?
make_string_from_list((AA_RANKS_OBJ->query_players_with_rank_no(5)) || (AA_RANKS_OBJ->query_players_with_rank_no(6))) :
"  ----")+
"\n");
            break;
        case 19:
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
        case 20:
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
*/
        default:
            write("This page is empty.\n");
    }
}