/*
 * /std/book.c
 *
 * A general book with many pages. You have to open the book and turn it to
 * the right page in order to read it.
 *
 */

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "guild.h"

#define TITLE_OBJ (THIS_DIR+"s_c_titles")

/*
 * Prototype
 */
varargs void
read_book_at_page(int page, string verb);


int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 15;
string  gPage;

void
set_book_is_private(int i){ book_is_private = i; }


/*
 * Function name: create_book
 * Description:   creates a default book
 *                change it to make your own book
 */
public void
create_book()
{
  set_short("old leather book");
  set_long("An old book with leather binding. It has simple title:\n\n"+
           "            The Army of Angmar\n\n"+
           "It is chained to the wall to prevent you from stealing it.\n"+
           "@@opened_at_page@@");
  add_adj(({"old", "leather"}));

  add_item("chain", "A strong iron chain capable of preventing "+
                    "you from stealing the book.\n");

  add_prop(OBJ_M_NO_GET, "You can't take this book! Chain doesn't let you.\n");
}

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
    add_name("book");
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    create_book();
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

    add_action("read_scroll", "close");
    add_action("read_scroll", "open");
    add_action("read_scroll", "turn");
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
        write("The "+short(this_player())+" is already open.\n");
    return;
    }

    what_page = 1;

    write("You open the " + short(this_player()) + " at page " +
    LANG_WNUM(what_page) + ".\n");
    say(QCTNAME(this_player()) + " opens the " + QSHORT(this_object()) + ".\n");

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
        write("The " + short(this_player()) + "is already closed.\n");
        return;
    }

    write("You close the " + short(this_player()) + ".\n");
    say(QCTNAME(this_player()) + " closes the " + QSHORT(this_object()) + ".\n");

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
       write("But the "+short(this_player())+" is closed.\n");
    return;
    }

    appr_num = LANG_NUMW(gPage);
    if (appr_num > 0 && appr_num < maxm_page + 1)
    {
        what_page = appr_num;

        say(QCTNAME(this_player())+" turns the "+short()+" to page "+
        LANG_WNUM(what_page) + ".\n");
        write("You turn the " + short() + " to page " +
        LANG_WNUM(what_page) + ".\n");
        return;
    }

    if (gPage == "forward" || gPage == "")
    {
        if (maxm_page < what_page + 1)
        {
            write("You have reached the last page of the " +
            short(this_player()) + ".\n");
            return;
    }
        what_page += 1;
        if (maxm_page == what_page)
        {
           say(QCTNAME(this_player())+" turns the "+short()+
                " to the last page.\n");
            write("You turn the "+short()+" to the last page.\n");
        }
        else
        {
          say(QCTNAME(this_player())+" turns the "+short()+
                  " to page "+LANG_WNUM(what_page)+".\n");
          write("You turn the "+short()+
                  " to page "+LANG_WNUM(what_page)+".\n");
        }
        return;
    }
    else if (gPage == "backward" || gPage == "back")
    {
        if (what_page == 1)
        {
            write("You cannot turn the " + short() +
                  " below the first page.\n");
            return;
        }
        what_page -= 1;
        say(QCTNAME(this_player())+" turns the "+short()+
                  " to page "+LANG_WNUM(what_page)+".\n");
        write("You turn the " + short() +
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

    if (!str)
    return ::read_scroll(what);

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
           write("The "+short(this_player())+" is closed.\n");
        return;
    }
    say(QCTNAME(this_player()) + " reads the " + QSHORT(this_object()) +
        ".\n");
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
"       This is a book about Angmar's army.\n"+
"       ***********************************\n\n\n"+
"It contains a brief history (stolen from some poor historian)\n"+
"and some other topics. At the end is the register of members.\n\n"+
"Please use this book with care because it is not likely that anyone\n"+
"will ever write new one after this one is destroyed (there is bigger\n"+
"chance that we will steal another book from somewhere else).\n");
      break;
    case 2:
      write("\n"+
"History of Angmar's army.\n"+
"*************************\n"+
"\n"+
"After the downfall of Numenor in the middle of the Second Age,\n"+
"the Faithful Numenoreans came to the Middle-earth.  They settled\n"+
"there, founding the two Kingdoms of the Exiles: Gondor and Arnor.\n"+
"\n"+
"But Sauron was not dead for good.\n"+
"He returned to Mordor, and gathered his armies of orcs and trolls.\n"+
"Soon they were ravaging Rhovanion and Eriador, only stopped by\n"+
"the Dunedain and the Elves.\n"+
"\n"+
"This was the Last Alliance, the last time when Elves and Men stood\n"+
"together in the war against the Evil One.\n"+
"They were strong, and they beat Sauron's armies back into Mordor, \n"+
"after a big battle on the plains south of Greenwood. The plains were\n"+
"later known as the Dagorlad, - the Battle Plains. The Alliance \n"+
"besieged Sauron at Barad-Dur, and after several years they killed\n"+
"him.\n"+
"\n"+
"This was the end of the Second Age, and the beginning of the Third.\n");
      break;
    case 3:
      write("\n"+
"Before the War, Sauron had forged the Rings of Power. \n"+
"He had given nine to human nobles, seven to dwarven fathers, \n"+
"three to elven princes, and kept one to himself, the One Ring.\n"+
"The nine humans were enslaved, and became the Nazgul.\n"+
"\n"+
"After a thousand years in the void, Sauron returned and he settled\n"+
"in Dol Guldur, but did not make it known who he was. His Nazgul \n"+
"returned with him, and he sent them on missions across the continent,\n"+
"to spread his power, and prepare his return. From Dol Guldur, his evil\n"+
"power spread into Greenwood, which became known as Mirkwood thereafter.\n"+
"And he hated the Numenoreans who had killed him - the Gondorians and\n"+
"Arnoreans.\n"+
"\n"+
"He sent the chief of the Nazgul north, to the mountains north and east\n"+
"of Arnor. They say his name was Angmar, and that was the name of his \n"+
"kingdom there. Angmar gathered great armies of orcs and trolls. He also\n"+
"hired human agents with purpose of making chaos inside Arnor and gaining\n"+
"control there. Soon Arnor was split into three smaller kingdoms by internal\n"+
"strife, and soon after, the first of the three fell under Angmar.\n");
      break;
    case 4:
      write("\n"+
"For many hundred years, the armies of Angmar made war unto Arnor.\n"+
"Rhudaur was the first part to fall, it is today known as the Trollshaws.\n"+
"Then a plague killed most of the population in Cardolan, the southern\n"+
"parts of Arnor.\n"+
"\n"+
"From year 1700 of the Third Age, Angmar only had to war against Arthedain,\n"+
"the last remaining part of Arnor. It is the area today known as the Shire.\n"+
"At the final stages of the war, Fornost and Annuminas were destroyed, the\n"+
"chief cities of Arnor, north in the Shire.\n"+
"\n"+
"The King of Gondor brought the Army of Gondor north to aid Arnor, and\n"+
"together they destroyed the Angmar army. But the realm of Arnor was so \n"+
"destroyed, that it was never rebuilt. The remnant Dunedain of Arnor \n"+
"settled in hiding, and became the Rangers of the North. Their task \n"+
"remained to protect the lost realm of Arnor from the remnants of the \n"+
"army of Angmar.\n"+
"\n"+
"The chief Nazgul, the Witch-king fled south after the defeat, but the\n"+
"remains of his army were left back to harass the population of ancient \n"+
"Arnor. Instead of the human settlements, the small hobbits came and\n"+
"settled the area...\n");
      break;
    case 5:
      write("\n"+
"Comments to history:\n"+
"********************\n"+
"\n"+
"Basic fact to bear in mind is that this history wasn't written by us!\n"+
"We disagree with it in many points, but it is good enough to give you\n"+
"basic idea of the purpose of our army.\n"+
"Yes! We are army!!! Not only some remnants!\n"+
"We are waiting for return of Angmar - our chief captain and king.\n"+
"The land around will tremble under our boots when we will march\n"+
"once again under his command.\n"+
"We will kill every elf, every Ranger in revenge for what they did in\n"+
"the past!\n"+
"\n"+
"Every human and dwarf who can see the real power will join goblins, orcs\n"+
"and trolls in our army! There is no place for anyone else in our lines!\n");
      break;
    case 6:
      write("\n"+
"What do we offer to loyal warriors?\n"+
"***********************************\n"+
"\n"+
"For a small 13% tax (9% for layman soldiers) we give you the chance\n"+
"to stay on the right side when the final war breaks out.\n"+
"\n"+
"In addition to this we teach many skills in our training hall\n"+
"(layman soldiers to a little bit lower levels in some skills).\n"+
"\n"+
"Our preference is on using shield and club. We teach two special\n"+
"skills. One helps you to defend yourself better when using a shield\n"+
"and the other one teaches you how to properly smash your enemy with\n"+
"a club.\n"+
"\n"+
"Members can do 'help shield and club' for more information.\n"+
"\n    **** Note that shield is not working right now ****\n"+
"\n");
      break;
    case 7:
      write("\n"+
"Punishments\n"+
"***********\n"+
"\n"+
"Beware the wraith of the king Angmar. Most of all he hates traitors\n"+
"and has no mercy with them. The least he will do to you for leaving\n"+
"the army or repetitive killing of members of his army is that he will\n"+
"send bunch of strong warriors with clubs to beat your stupidity out of\n"+
"your head. And you should be aware that after thorough work on your head\n"+
"it will most likely forget not only the name of its holder but also all\n"+
"other sort of things it used to know. Hence don't be surprised if you\n"+
"can't remember skills you knew before the curing took place. Naturally\n"+
"'skills' here mean just any skills and not only ones related to the\n"+
"Army. The curing has also some impact on your physical state so apart"+
"from forgetting things you can also feel weaker, with broken health and"+
"somehow clumsier. Not to mention that you may forget how to count to ten\n"+
"and suddenly be afraid of every mouse running in your way.\n"+
"But you do not have to be afraid any of these things... All you have to do\n"+
"is to obey orders and show respect to your superiors.\n"+
"\n");
      break;
    case 8:
      write("\n"+
"Organization of the Army\n"+
"************************\n"+
"\n"+
"Every member has given title according to his position in the Army.\n"+
"The title consists of an adjective and a rank in the army. The rank is\n"+
"what determines your position. Immediately after joining your rank is\n"+
"Servant. After short trial period you become full member with the rank\n"+
"Footman. From now on it depends only on your behaviour, experience and\n"+
"skills what rank will you achieve. Actual ranking system is described\n"+
"on the next page.\n"+
"The adjective is related to your general knowledge of the world\n"+
"and probably also how are you known in the world. Here is the list\n"+
"of all adjectives in increasing order:\n\n"+
break_string(COMPOSITE_WORDS(ADJ_LIST), 60, 5)+
"\n");
      break;
    case 9:
      write("\n"+
"The ranking system of Angmar's Army:\n"+
"************************************\n"+
"\n"+
"Army has fixed structure and so there is only fixed number of positions\n"+
"for every rank. This number depends on the number of members with lower\n"+
"rank. Note that there is always at least one position available.\n"+
"If you want to reach some rank you must fulfill two conditions:\n"+
"    1.  You must be 'good' enough to qualify for the position\n"+
"    2.  You must be better than others who qualify for the position.\n"+
"From time to time every member is reconsidered and ranks are assigned\n"+
"according to your current position in the army. So you might find\n"+
"yourself demoted while someone else got promoted. Hope this will keep\n"+
"the competitive spirit up which in turn will help to build up better\n"+
"and stronger army.\n"+
"\n"+
"Number of positions available:\n"+
"******************************\n"+
"\n"+
"   Footman:            any number\n"+
"   Standard Bearer:    1 position for every  2 lower members\n"+
"   Corporal:           1 position for every  5 lower members\n"+
"   Sergeant:           1 position for every  9 lower members\n"+
"   Warrant Officer:    1 position for every 15 lower members\n"+
"   Lieutenant:         1 position for every 24 lower members\n"+
"   Captain:            1 position\n"+
"\n");
      break;
    case 10:
      write("\n"+
"Discipline, Council and Punishments...\n"+
"**************************************\n"+
"\n"+
"In order to maintain the discipline in the army there is a set of\n"+
"punishments to fit every possible level of misbehaving. These are:\n"+
"      1. Ban from training for 2 weeks\n"+
"      2. Lowering effectivity of specials for 10 days + above\n"+
"      3. Disallowing specials for 1 week + above\n"+
"      4. Beating on the head (loosing skills) + above\n"+
"      5. Extermination\n"+
"      6. Rejecting from Army + beating on the head\n"+
"There is also elected a council that has the final word on the\n"+
"punishments. Councilmembers are elected by all soldiers. However votes\n"+
"are weighted according to the rank and here are exact weights:\n"+
"                Footman         - 2\n"+
"                Standard Bearer - 3\n"+
"                Corporal        - 4\n"+
"                Sergeant        - 5\n"+
"                Warrant Officer - 6\n"+
"                Lieutenant      - 7\n"+
"                Captain         - 8\n"+
"In council can be any soldier with rank below Lieutenant. Only Captain\n"+
"Lieutenants and councilmember can start election for the position in\n"+
"council. This cannot be done sooner than one month after last election.\n");
      break;
    case 11:
      write("\n"+
"Voting on punishments:\n"+
"**********************\n"+
"\n"+
"Suggest a punishment can only Captain, Lieutenant or councilmember.\n"+
"Soldier cannot be suggested for same punishment sooner than one month\n"+
"after the last suggestion for this punishment. He can be suggested for\n"+
"different punishment tough. After the suggestion there is exactly one\n"+
"week for voting on it.\n"+
"\n"+
"Who can vote on punishment:\n"+
"      punishment no. 1: Council + Lieutenants and higher\n"+
"      punishment no. 2: Council + Warrant Officers and higher\n"+
"      punishment no. 3: Council + Sergeants and higher\n"+
"      punishment no. 4: Council + Corporals and higher\n"+
"      punishment no. 5 and 6: Council + Standard Bearers and higher\n"+
"\n"+
"Deciding on punishment:\n"+
"Votes are equal. Majority of votes gives the result but if voted less than\n"+
"50% of soldiers allowed to vote or in case of tie the votes of council are\n"+
"the only ones counted. No vote from councilmember in this case counts as\n"+
"vote against.\n"+
"\n");
      break;
    case 12:
      write("\n"+
"Register of the members of Angmar's army:\n"+
"*****************************************\n"+
"\n"+
"Captain:\n"+
"********\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Captain")) :
"  ----")+
"\n\n"+
"Lieutenants:\n"+
"************\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Lieutenant")) :
"  ----")+
"\n\n"+
"Warrant Officers:\n"+
"*****************\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Warrant Officer")) :
"  ----")+
"\n");
      break;
    case 13:
      write("\n"+
"Sergeants:\n"+
"**********\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Sergeant")) :
"  ----")+
"\n\n"+
"Corporals:\n"+
"**********\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Corporal")) :
"  ----")+
"\n\n"+
"Standard Bearers:\n"+
"*****************\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Standard Bearer")) :
"  ----")+
"\n");
      break;
    case 14:
      write("\n"+
"Footmen:\n"+
"********\n\n"+
(book_is_private ?
make_string_from_list(TITLE_OBJ->query_players_with_title("Footman")) :
"  ----")+
"\n");
      break;
    default:
      write("This page is empty.\n");
  }
}
