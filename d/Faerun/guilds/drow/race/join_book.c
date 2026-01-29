/*
 * Join book of the Drow
 * It is based on the Noldor join book, which is based on 
 * the book of the original Army of Angmar by Milan
 * -- Finwe, November 2015
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
int     maxm_page = 15;
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
    set_short("leather book chained to a wall");
    set_name("book");
    add_name("book");
    add_name("Drow book");
    set_long("This is a large book chained to a wall. It is bound in leather from the skin of goblins. The book looks well read as the leather is smooth from constant use. Next to the book is a sign.\n\n" +
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
        "    |       T H E   D R O W   R A C I A L   G U I L D         |\n"+
        "    |                                                         |\n"+
        "    |  Drow Guild                                             |\n"+
        "    |  ----------                                             |\n"+
        "    |    * About the Drow. . . . . . . . . . . . . . . .  2   |\n"+
        "    |    * History of the Drow . . . . . . . . . . . . .  3   |\n"+
        "    |    * Joining the Drow. . . . . . . . . . . . . . .  4   |\n"+
        "    |    * Leaving the Drow. . . . . . . . . . . . . . .  5   |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities                                           |\n"+
        "    |  ------------                                           |\n"+
        "    |    * Eilistraee. . . . . . . . . . . . . . . . . .  6   |\n"+
        "    |    * Ghaunadaur. . . . . . . . . . . . . . . . . .  7   |\n"+
        "    |    * Kiaransalee . . . . . . . . . . . . . . . . .  8   |\n"+
        "    |    * Lolth . . . . . . . . . . . . . . . . . . . .  9   |\n"+
        "    |    * Selvetarm . . . . . . . . . . . . . . . . . . 10   |\n"+
        "    |    * Vhaeraun  . . . . . . . . . . . . . . . . . . 11   |\n"+
        "    |                                                         |\n"+
        "    |  Drow Cities and Houses                                 |\n"+
        "    |  ----------------------                                 |\n"+
        "    |    * Ched Nesan, Arkhenneld and Zauvirr. . . . . . 12   |\n"+
        "    |    * Menzoberranzan,                                    |\n"+
        "    |      Duskryn, Srune'lett, and Horlbar. . . . . . . 13   |\n"+
        "    |    * Sshamath, Khalazza, T'orgh and Vyllsha. . . . 14   |\n"+
        "    |    * Thal'katkhact, Eveningsky and Sweetkiller . . 15   |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;

    case 2:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 2  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Guild - About the Drow                            |\n"+
        "    |  ---------------------------                            |\n"+
        "    |  We are descended from dark-skinned subrace of the      |\n"+
        "    |  faeries. When Lolth enlightened us and showed us       |\n"+
        "    |  power unimagined, we followed her and worshiped her.   |\n"+
        "    |  At that time, the evil deities of the faeries cursed   |\n"+
        "    |  us. It was to no avail for by that time, we were free  |\n"+
        "    |  and protected by Lolth herself.                        |\n"+
        "    |                                                         |\n"+
        "    |  True Drow are dark-skinned and have stark white or     |\n"+
        "    |  pale yellow hair. Our eyes are often pale lilac,       |\n"+
        "    |  silver, pink, or blue colored. We follow Lolth and     |\n"+
        "    |  seek to find her favor in all things. There are other  |\n"+
        "    |  gods and goddesses that we worship, but they are of    |\n"+
        "    |  less important than Lolth. There are other Drow who    |\n"+
        "    |  have fallen out of favor with Lolth. These same Drow   |\n"+
        "    |  often worship evil deities and are not tolerated by    |\n"+
        "    |  the true followers of the Spider Queen.                |\n"+
        "    |                                                         |\n"+
        "    |  Drow society is ruled by Matron Mothers, female Drow   |\n"+
        "    |  who have found favor with the Spider Queen. Those      |\n"+
        "    |  females who find favor in their eyes are elevated to   |\n"+
        "    |  positions of power. Male Drow are worthless and good   |\n"+
        "    |  for little more than breeding and fighting. They are   |\n"+
        "    |  weak-minded and can easily be twisted to the desires   |\n"+
        "    |  of Lolth.                                              |\n"+
        "    |                                                         |\n"+
        "    |  Drow are fierce warriors. Those who doubt this meet    |\n"+
        "    |  their doom at the end of our weapons, and few live to  |\n"+
        "    |  tell about it. We are skilled weapon users, but are    |\n"+
        "    |  often more proficient in bows and arrows or swords.    |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 3:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 3  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Guild - History of the Drow                       |\n"+
        "    |  --------------------------------                       |\n"+
        "    |  In ages past, Drow walked on the surface of the world. |\n"+
        "    |  We walked beside the pale-skinned elves we called the  |\n"+
        "    |  faeries. At that time, we and the faeries were their   |\n"+
        "    |  friends and even called them our kin. We did not know  |\n"+
        "    |  that they were actually evil creatures and the embodi- |\n"+
        "    |  ment of all that is vile and deceitful. We found this  |\n"+
        "    |  out the hard way when the faeries began to hunt and    |\n"+
        "    |  kill us for no reason.                                 |\n"+
        "    |                                                         |\n"+
        "    |  The faeries turned on us and began to slay our         |\n"+
        "    |  children and our elders for no reason. They chased us  |\n"+
        "    |  across the surface without mercy. We always tried to   |\n"+
        "    |  reason with them, for all we wanted was to be left in  |\n"+
        "    |  peace. The faeries would not listen. They slew us with |\n"+
        "    |  swords and arrows. At our darkest hour, we found the   |\n"+
        "    |  Spider Queen!                                          |\n"+
        "    |                                                         |\n"+
        "    |  She showed took us and helped us fight off our         |\n"+
        "    |  enemies. It was she who led us to the Underdark, our   |\n"+
        "    |  Paradise. With her help, we were able to destroy our   |\n"+
        "    |  enemies. We learned how to be conquerers and           |\n"+
        "    |  possessors of all we desire. Never will we be down-    |\n"+
        "    |  trodden by our enemies. We have strength and the power |\n"+
        "    |  to pay back those who destroyed us.                    |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;
    case 4:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 4  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Guild - Joining the Drow                          |\n"+
        "    |  -----------------------------                          |\n"+
        "    |  Any elf of any alignment may embrace the worship of    |\n"+
        "    |  gods of the drow. They welcome all who desire to       |\n"+
        "    |  follow them. They grant their loyal worshippers skills |\n"+
        "    |  to defeat their enemies. If you decide this is what    |\n"+
        "    |  you want, be warned there are demands that must be     |\n"+
        "    |  met.                                                   |\n"+
        "    |                                                         |\n"+
        "    |  Before joining, an elf must be a Great Adventurer or   |\n"+
        "    |  older. All drow must belong to a house. Those females  |\n"+
        "    |  who find favor with their deity may become a Matron    |\n"+
        "    |  Mother. Within the house, the Matron Mother rules      |\n"+
        "    |  completely. All in her house are subject to her whims. |\n"+
        "    |                                                         |\n"+
        "    |  When you join, you must declare which city you are     |\n"+
        "    |  from and which deity you follow.                       |\n"+
        "    |                                                         |\n"+
        "    |  Before joining, be sure you are willing to commit your |\n"+
        "    |  life to the drow. They are ruthless and unforgiving if |\n"+
        "    |  you later forsake them, but won't take your life. To   |\n"+
        "    |  join, type <djoin drow>.                               |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;
    case 5:
        write("\n\n"+
        "     _________________________________________________________\n"+
        "    |                                                 Page 5  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Guild - Leaving the Drow                          |\n"+
        "    |  -----------------------------                          |\n"+
        "    |  Any elf who turns their back and leaves the drow       |\n"+
        "    |  becomes an outlaw in the eyes of Lolth. They are not   |\n"+
        "    |  tolerated less the faeries lose all benefits of a      |\n"+
        "    |  drow are barred from returning. If you choose to re-   |\n"+
        "    |  turn, you must seek the favor of Lolth again. This     |\n"+
        "    |  will take time as she is an unforgiving goddess. When  |\n"+
        "    |  she deems you are worthy, you will be permitted to     |\n"+
        "    |  return.                                                |\n"+
        "    |                                                         |\n"+
        "    |  If you still desire to leave, you must sever all ties  |\n"+
        "    |  to your house. When that is completed, you must        |\n"+
        "    |  <dbetray drow>.                                        |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
    break;
    case 6:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 6  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Eilistraee                              |\n"+
        "    |  -------------------------                              |\n"+
        "    |  Eilistraee is the goddess of the good drow. Also known |\n"+
        "    |  as The Dark Maiden and Lady of the Dance, she is the   |\n"+
        "    |  Matron goddess of all the drow that wish to return to  |\n"+
        "    |  the surface. Eilistraee was not exiled from Arvandor,  |\n"+
        "    |  but volunteered to leave as she believed she would be  |\n"+
        "    |  needed. She still harbours hope that some, if not all, |\n"+
        "    |  of the drow will turn their back on evil.              |\n"+
        "    |                                                         |\n"+
        "    |  Eilistraee's trademarks are song and beauty. Her sym-  |\n"+
        "    |  bol is that of a nude, long-haired female drow dancing |\n"+
        "    |  with a silver bastard sword in front of a full moon.   |\n"+
        "    |  Not much is known about her except that she is quick   |\n"+
        "    |  to anger over the evil that most drow do.              |\n"+
        "    |                                                         |\n"+
        "    |  Those who follow Eilistraee are females and expected   |\n"+
        "    |  to further the cause of beauty and song. They are en-  |\n"+
        "    |  couraged to carry one of their goddess's favored       |\n"+
        "    |  instruments: the horn, flute, or harp. Their lot in    |\n"+
        "    |  life is to persuade drow to return to the surface      |\n"+
        "    |  world and work to improve surface relations.           |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 7:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 7  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Ghaunadaur                              |\n"+
        "    |  -------------------------                              |\n"+
        "    |  Ghaunaduar is a lesser known drow deity. He is known   |\n"+
        "    |  as That Which Lurks, and the Elder Eye. He is alo un-  |\n"+
        "    |  predictable and when he appears, he is seen as a       |\n"+
        "    |  purplish ooze with tentacles. The followers of Ghaun-  |\n"+
        "    |  aduar are mostly drow that have fallen from the grace  |\n"+
        "    |  of Lolth or are sub-intelligent monsters.              |\n"+
        "    |                                                         |\n"+
        "    |  The symbol of Ghaunaduar is a purplish eye on purple,  |\n"+
        "    |  violet and black circles.                              |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 8:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 8  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Kiaransalee                             |\n"+
        "    |  --------------------------                             |\n"+
        "    |  Kiaransalee is the overlord of the undead. Known as    |\n"+
        "    |  The Lady of the Dead, the Revenancer, the Vengeful     |\n"+
        "    |  Banshee, she chafes at the rule of Lolth and seeks to  |\n"+
        "    |  rival Lolth in power and ultimately reign as the       |\n"+
        "    |  supreme Goddess over all drow.                         |\n"+
        "    |                                                         |\n"+
        "    |  Most clerics to Kiaransalee practice necromancy and    |\n"+
        "    |  perform a handful of minor devotions to her every      |\n"+
        "    |  month. There is also one single annual holy day, known |\n"+
        "    |  as the Graverending, which is celebrated each Mid-     |\n"+
        "    |  winter Eve.                                            |\n"+
        "    |                                                         |\n"+
        "    |  Her symbol is a female drow hand wearing silver rings. |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 9:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 9  |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Lolth                                   |\n"+
        "    |  --------------------                                   |\n"+
        "    |  Lolth, the Spider Queen, is cruel and malicious. The   |\n"+
        "    |  only person in her world is herself. She is constantly |\n"+
        "    |  plotting to keep her loyal minions in a state of tur-  |\n"+
        "    |  moil. This way she can find the strongest and most     |\n"+
        "    |  cunning of her followers to serve her. Drow, being     |\n"+
        "    |  brought up under this religion, are all but perfectly  |\n"+
        "    |  suited to this arrangement. With the drow instinc-     |\n"+
        "    |  tive distrust and wit, all but the wiliest of oppo-    |\n"+
        "    |  nents will be thrown into disarray. Seeing that Lolth  |\n"+
        "    |  is the goddess of chaos, this seems all but fitting.   |\n"+
        "    |                                                         |\n"+
        "    |  The main object of affection among Lolth worshippers   |\n"+
        "    |  is the spider. It is an offence punishable by death to |\n"+
        "    |  kill or even maim one. Lolth is most frequently found  |\n"+
        "    |  in the form of giant black widow spider. This form can |\n"+
        "    |  be changed to an extremely beautiful drow female.      |\n"+
        "    |  These two forms can also be combined to produce a      |\n"+
        "    |  giant spider with a lovely female drow head. In any    |\n"+
        "    |  form, Lolth is a presence to be feared.                |\n"+
        "    |                                                         |\n"+
        "    |  The vast majority of clergy to Lolth are women. The    |\n"+
        "    |  Spider Queen favours those of her own gender, and she  |\n"+
        "    |  encourages her followers to view males as lesser       |\n"+
        "    |  beings. The priestesses of Lolth are the only subjects |\n"+
        "    |  of Lolth to hold any real power in drow society. If a  |\n"+
        "    |  priestess of any rank says to do something there       |\n"+
        "    |  better not be any hesitation. Punishment for disobe-   |\n"+
        "    |  dience is usually swift and destructive. A priestess   |\n"+
        "    |  has the feeling that they are the judge, jury and      |\n"+
        "    |  executioner of the society at their feet, and the      |\n"+
        "    |  power given to her by Lolth as justification for any   |\n"+
        "    |  action that she may take. A priestess's sole purpose   |\n"+
        "    |  in life is to weed out the weak and sanctify the       |\n"+
        "    |  strong.                                                |\n"+
        "    |                                                         |\n"+
        "    |  Lolth is known by many titles. Some of them are Queen  |\n"+
        "    |  of Spiders, Queen of the Demonweb Pits, Demon Queen of |\n"+
        "    |  Spiders, Demon Queen of the Abyss, Weaver of Chaos,    |\n"+
        "    |  Dark Mother of All Drow, and Lady of Spiders.          |\n"+
        "    |                                                         |\n"+
        "    |  Her symbol is a black spider with female drow head     |\n"+
        "    |  hanging from a spider web.                             |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 10:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 10 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Selvetarm                               |\n"+
        "    |  ------------------------                               |\n"+
        "    |  Selvetarm is the embodiment of the drow passion for    |\n"+
        "    |  prowess in fighting, and the champion of Lolth. Known  |\n"+
        "    |  as Champion of Lolth or the Spider that Waits, he is   |\n"+
        "    |  cruel and malicious by nature, and cares only for      |\n"+
        "    |  battle and destruction. The Champion of Lolth harbours |\n"+
        "    |  a deep hatred for all living things, including his     |\n"+
        "    |  dominating mistress, and the only beauty he can appre- |\n"+
        "    |  ciate is a well-honed and deadly fighting style.       |\n"+
        "    |                                                         |\n"+
        "    |  Selvetarm's faithful are expected to observe the rit-  |\n"+
        "    |  uals of Lolth, as directed by her clerics. Selvetarm   |\n"+
        "    |  does expect all who take up arms in his name to cry    |\n"+
        "    |  out his name in the bloodlust of battle as they        |\n"+
        "    |  deliver the killing blow to a foe.                     |\n"+
        "    |                                                         |\n"+
        "    |  His Symbol is a spider on a crossed sword and mace.    |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;

    case 11:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 11 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Deities - Vhaeraun                                |\n"+
        "    |  -----------------------                                |\n"+
        "    |  Vhaeraun is the god of thievery and the furthering of  |\n"+
        "    |  drow power on the surface world. He is also the patron |\n"+
        "    |  deity of drow males, teaching a heresy (according to   |\n"+
        "    |  Lolth) that drow males are the equals of drow females. |\n"+
        "    |  Vhaeraun is haughty and proud, like all drow deities   |\n"+
        "    |  and is known as the Masked Lord and the Masked God of  |\n"+
        "    |  Night. He favours underhanded means and treachery to   |\n"+
        "    |  achieve his goals.                                     |\n"+
        "    |                                                         |\n"+
        "    |  His priesthood is exclusively male, and priests usu-   |\n"+
        "    |  ally hide their true vocation in drow communities.     |\n"+
        "    |  Vhaeraun is passively opposed to Lolth and wishes to   |\n"+
        "    |  reunite the elven people. He considers all elves to be |\n"+
        "    |  superior to all other races, however, and wishes only  |\n"+
        "    |  to have elves dominate all other races. Vhaeraun's     |\n"+
        "    |  loyalty is to all elves, but primarily the drow race.  |\n"+
        "    |  He would like to see the surface elves serving as the  |\n"+
        "    |  enforcers of the 'true masters', the drow, who would   |\n"+
        "    |  rule from the depths of the earth.                     |\n"+
        "    |                                                         |\n"+
        "    |  In the Night Above, nights of the new moon are consid- |\n"+
        "    |  ered sacred to clerics of Vhaeraun. Midwinter Night is |\n"+
        "    |  known to Vhaeraun's followers as the Masked Lord's     |\n"+
        "    |  Embrace and is their annual holy day.                  |\n"+
        "    |                                                         |\n"+
        "    |  His symbol is a pair of black glass lenses that peer   |\n"+
        "    |  from behind a mask.                                    |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 12:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 12 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Cities and Houses - Ched Nesan                    |\n"+
        "    |  -----------------------------------                    |\n"+
        "    |  The City of Shimmering Webs is said to have a popu-    |\n"+
        "    |  lation of 30,000 drow and 70,000 slaves of other       |\n"+
        "    |  races. However the source of these quotes has seri-    |\n"+
        "    |  ously overestimated the population of other more well  |\n"+
        "    |  known cites, and the true population is probably con-  |\n"+
        "    |  siderably less.                                        |\n"+
        "    |                                                         |\n"+
        "    |  Ched Nasad was founded by House Nasadra of primitive   |\n"+
        "    |  Menzoberranzan, and by other refugees from Golothaer.  |\n"+
        "    |  This city also lives according to the Way of Lolth,    |\n"+
        "    |  and is pledged to remain friendly with Menzoberranzan. |\n"+
        "    |  It is located in the North (under High Gap and the     |\n"+
        "    |  Grey Peak Mountains) in a huge mile high cavern.       |\n"+
        "    |                                                         |\n"+
        "    |  The cavern is crisscrossed with spider's webs that     |\n"+
        "    |  have been magically calcified. These webs sparkle and  |\n"+
        "    |  shimmer in the lights, both magical and natural. The   |\n"+
        "    |  city is built on these platforms, and individual       |\n"+
        "    |  dwellings have the appearance of great cocoons.        |\n"+
        "    |                                                         |\n"+
        "    |  This is another matriarchal city, ruled by a council   |\n"+
        "    |  of the Matron Mothers from the twelve highest ranking  |\n"+
        "    |  houses. However House Nasadra holds sway over the      |\n"+
        "    |  other houses. The worship of Lolth dominates here, and |\n"+
        "    |  the government is similar to that of Menzoberranzan.   |\n"+
        "    |                                                         |\n"+
        "    |  Houses of Ched Nasad are Arkhenneld and Zauvirr.       |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 13:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 13 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Cites and Houses - Menzoberranzan                 |\n"+
        "    |  --------------------------------------                 |\n"+
        "    |  The most famous (or infamous) of the drow cities has a |\n"+
        "    |  population of some 11,000 drow and, of course, count-  |\n"+
        "    |  less spiders. There are at least 20,000 slaves (in-    |\n"+
        "    |  cluding bugbears, goblins, ogres, ogrillons, orcs,     |\n"+
        "    |  minotaurs, quaggoths, and trolls, and kobolds).        |\n"+
        "    |                                                         |\n"+
        "    |  Menzoberranzan lies north of the Evermoors and under   |\n"+
        "    |  the River Subrin, not too far from Mithral Hall. It is |\n"+
        "    |  some 3 miles under the surface in a vast cavern, orig- |\n"+
        "    |  inally a spiders lair. The cavern is shaped rather     |\n"+
        "    |  like an arrowhead and is two miles wide at the         |\n"+
        "    |  broadest point. The dwarves named it Araurilcaurak     |\n"+
        "    |  (Great Pillar Cavern) and the drow still use this      |\n"+
        "    |  name.                                                  |\n"+
        "    |                                                         |\n"+
        "    |  The city was founded by Menzobarra, a high priestess   |\n"+
        "    |  of Lolth, who led group of refugees out from war torn  |\n"+
        "    |  Golothaer. The founding of the great city was marked   |\n"+
        "    |  by blood and strife. At first there were battles       |\n"+
        "    |  against dwarves and beholders. Later fighting broke    |\n"+
        "    |  out between the four houses who follow Lolth, and a    |\n"+
        "    |  fifth house who did not. This house was driven out and |\n"+
        "    |  since then the worship of Lolth has reigned supreme. A |\n"+
        "    |  steady influx of refugees from various areas affected  |\n"+
        "    |  by strife meant Menzoberranzan grew and prospered.     |\n"+
        "    |                                                         |\n"+
        "    |  The worship of Lolth remains the primary religion of   |\n"+
        "    |  Menzoberranzan. The Spider Goddess is known as Lolth   |\n"+
        "    |  throughout the city. Vhaeraun is also worshiped here.  |\n"+
        "    |  The priestesses of Lolth dominate this matriarchal     |\n"+
        "    |  society. Although the power lies in theory  with the   |\n"+
        "    |  ruling council formed of the Matron Mothers of the     |\n"+
        "    |  eight highest ranking noble houses. In fact the Matron |\n"+
        "    |  Mothers of the noble houses are really secondary       |\n"+
        "    |  powers to the rule of the Spider Queen.                |\n"+
        "    |                                                         |\n"+
        "    |  It is a beautiful city--full of magnificent statuary,  |\n"+
        "    |  bright lights and alien but breathtaking buildings.    |\n"+
        "    |  Most of the rock formations on the floor of the cavern |\n"+
        "    |  have been carved into gorgeous castles of stone.       |\n"+
        "    |  Thousands of stalactites reach down from the high      |\n"+
        "    |  roof. However underneath this beauty lies a city that  |\n"+
        "    |  is said by many to be chaotic and violent, and to      |\n"+
        "    |  reflect the cold hearts of the drow. What is certain   |\n"+
        "    |  is that the city can be a deadly trap for outsiders.   |\n"+
        "    |  The architecture mimics the weaving of spiders, and    |\n"+
        "    |  also mimics the many deadly traps to be found within   |\n"+
        "    |  a spider's lair.                                       |\n"+
        "    |                                                         |\n"+
        "    |  The city's major trades are in tasty fungi, spell      |\n"+
        "    |  scrolls, riding lizards, wine and potable water.       |\n"+
        "    |                                                         |\n"+
        "    |  Houses of Menzobarranzan are Fey-Branche, Mizzrym,     |\n"+
        "    |  and Xorlarrin.                                         |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 14:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 14 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Cities and Houses - Sshamath                      |\n"+
        "    |  ---------------------------------                      |\n"+
        "    |  Sshamath is also known as the City of Dark Weavings.   |\n"+
        "    |  Itis probably the largest of the drow cities with some |\n"+
        "    |  45,000 inhabitants. Of these 42,000 are drow; around   |\n"+
        "    |  1,000 or so are other Dark Elves and the remainder are |\n"+
        "    |  a mixture of slaves, emissaries, traders, undead and   |\n"+
        "    |  conjured creatures. It is a truly cosmopolitan city    |\n"+
        "    |  welcoming any who come to trade--regardless of race or |\n"+
        "    |  creed.                                                 |\n"+
        "    |                                                         |\n"+
        "    |  Sshamath lies under the Far Hills, east of Scornubel.  |\n"+
        "    |  It is largely built in a single main cavern. This      |\n"+
        "    |  cavern has literally thousands of stalagmites and      |\n"+
        "    |  stalactites reaching between roof and floor, and       |\n"+
        "    |  numerous other rock formations and these create a      |\n"+
        "    |  dense three dimensional web of rock.                   |\n"+
        "    |                                                         |\n"+
        "    |  It is almost impossible to gain a clear line of sight  |\n"+
        "    |  for any distance. The rock formations have been        |\n"+
        "    |  sculpted and reshaped with magic into spirally towers  |\n"+
        "    |  and other dwellings. Travel between these is by        |\n"+
        "    |  magical means, or by the slender and delicate bridges. |\n"+
        "    |  There are permanent Faerie Fire type spells in the     |\n"+
        "    |  cavern walls and these provide a beautiful light.      |\n"+
        "    |                                                         |\n"+
        "    |  Unlike most other drow cities, Sshamath is not a       |\n"+
        "    |  matriarchy, rather it is dominated by male wizards.    |\n"+
        "    |  The reasons behind this are historical. The city was   |\n"+
        "    |  founded in -4,973 DR by followers of Lolth. Around two |\n"+
        "    |  thousand years later the region lost its faerzess (the |\n"+
        "    |  under dark radiation so important to drow magic). For  |\n"+
        "    |  some 300 years before this there had been an unusually |\n"+
        "    |  high number of males born. Thus the cities male mages  |\n"+
        "    |  were increasing in number as the female priestesses    |\n"+
        "    |  were declining.                                        |\n"+
        "    |                                                         |\n"+
        "    |  Clerics of Ghaunaduar and Vhaeraun, and more recently  |\n"+
        "    |  Kiaransalee have positions as minor city officials.    |\n"+
        "    |  The greatest power lies in the hands of the high       |\n"+
        "    |  ranking male wizards.                                  |\n"+
        "    |                                                         |\n"+
        "    |  Sshamath is now an important trading city. It is       |\n"+
        "    |  especially renowned for its traffic in magic           |\n"+
        "    |  artifacts, and dominates Underdark trade in these      |\n"+
        "    |  items.                                                 |\n"+
        "    |                                                         |\n"+
        "    |  Houses of Sshamath are Khalazza, T'orgh, and Vyllshan. |\n"+
        "    |_________________________________________________________|\n"+
        "\n");
        break;
    case 15:
        write("\n\n"+
        "     __________________________________________________________\n"+
        "    |                                                 Page 15 |\n"+
        "    |                                                         |\n"+
        "    |  Drow Cities and Houses - Thal'katkhact                 |\n"+
        "    |  --------------------------------------                 |\n"+
        "    |  Thal'katkhact is the city for the non-evil drow.       |\n"+
        "    |  Eilistraee has remained allied to both the Seldarine   |\n"+
        "    |  and the drow pantheon in hopes that she can return     |\n"+
        "    |  the Dark elves to the surface, and back from the       |\n"+
        "    |  worship of evil.                                       |\n"+
        "    |                                                         |\n"+
        "    |  Ever since the drow were banished to their dark        |\n"+
        "    |  caverns there have been small numbers who have         |\n"+
        "    |  shunned the worship of evil gods, and as followers of  |\n"+
        "    |  Eilistraee they have returned to the surface, in small |\n"+
        "    |  communities around temples to the good goddess. These  |\n"+
        "    |  communities are almost always small, and sadly mostly  |\n"+
        "    |  short lived. Exceptions to this are the city of        |\n"+
        "    |  Thal'kathact in the drow forest.                       |\n"+
        "    |                                                         |\n"+
        "    |  Houses of the Thal'kathact are Eveningstar and         |\n"+
        "    |  Sweetkiller.                                           |\n"+
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
