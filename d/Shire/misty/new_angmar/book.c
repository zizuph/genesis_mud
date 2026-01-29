/*
 * /std/book.c
 *
 * A general book with many pages. You have to open the book and turn it to
 * the right page in order to read it.
 *
 */

#pragma save_binary

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "../local.h"

#define TITLE_OBJ (NEW_ANGMAR + "s_c_titles")
#define ADJ_LIST ({"Fresh","Insecure","Young","Training","Legionary", \
                   "Proud","Elder","Experienced","Dangerous","Notorious", \
                   "Cruel","Infamous","Bestial","Feared","Legendary",  \
                   "Mythical"})

/*
 * Prototype
 */
varargs void
read_book_at_page(int page, string verb);


int     book_is_private;
int     book_is_closed;
int     what_page;
int     maxm_page = 20;
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
           "It is ripped and torn. The book looks like it could probably be read if treated with care.\n"+
           "@@opened_at_page@@");
  add_adj(({"old", "leather"}));

  add_prop(OBJ_M_NO_GET, "It is too valuable to steal.\n");
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
      write("\n"+
"       This is a book about Army of Angmar\n"+
"       ===================================\n"+
"\n"+
"\n"+
"History of Army of Angmar ........................  2\n"+
"What we offer to loyal warriors .................. 10\n"+
"Punishments for traitors ......................... 11\n"+
"Organization of Army of Angmar ................... 12\n"+
"The ranking system of Army of Angmar ............. 13\n"+
"Number of positions available .................... 14\n"+
"Council .......................................... 15\n"+
"Discipline and Punishments ....................... 16\n"+
"Voting on Punishments ............................ 17\n"+
"Register of the members of Army of Angmar ........ 18\n\n");
      break;
    case 2:
      write("\n"+
"History of Army of Angmar\n"+
"=========================\n"+
"\n"+
"The history of the army is a long and bloody one. It begins in the year "+
"1500 of the second age when the elven smiths of Eregion, under the "+
"tutelage of our Dark Lord reached the height of their skills and began "+
"the forging of the rings of power. Celebrimbor, the leader of the elven "+
"smiths, was jealous of Dark Lords knowledge and skills, and after "+
"learning all that he could from our lord, betrayed his mentor with foul "+
"lies and innuendo. The other elves, weak in mind as well as body, failed "+
"to see that Celebrimbor was motivated by hatred and spite and were "+
"deceived. As a result, in the year 1693 the war between elves and "+
"Dark Lord began and ever since that time our lord has continued in his "+
"attempts to restore the order in the world.\n\n");
      break;
    case 3:
      write("\n"+
"Dark Lord, in his achieved, "+
"and to this end made a gift of rings to nine of the greatest Numenoreans. "+
"The rings allowed these selected Numenoreans to transcend their mortality "+
"(the curse of the Valar!) and opened their eyes to the truth of things. "+
"These nine, now known as the Nazgul, began spreading the word amongst "+
"the other Numenoreans in the hope that the truth would finally be heard. "+
"Unfortunately, many of the Numenoreans refused to listen, placing their "+
"fear-instilled faith in the Valar, who had oppressed and used them for "+
"so many years, rather than face the prospect of freedom under our lord. "+
"Dark Lord despaired in the realisation that these unbelievers were "+
"a blight, a disease that would undermine his struggle for order if "+
"given the chance and hence he petitioned the king of Numenor to remove "+
"them. The king, sensing the honesty in Dark Lord, agreed- banishing "+
"the unbelievers to Middle Earth where they formed the realms of Arnor "+
"and Gondor.\n");
      break;
    case 4:
      write("\n"+
"With the word spreading, the men of Numenor thought they might finally "+
"throw off the yoke of slavery that the Valar had cast about their neck "+
"and in the year 3319 sailed to Aman in the hopes of coming to some "+
"peaceful agreement with their masters. This was to no avail for the "+
"Valar were ever as treacherous as their minions and destroyed the brave "+
"men of Numenor before they had uttered a word. Dark Lord returned to "+
"Mordor with a heavy heart, realising that both the elves and the "+
"traitors of Numenor were beyond redemption and that Middle Earth's "+
"only chance for peace and freedom was their complete destruction. To "+
"this end, he gathered his armies of orcs and trolls and swept the "+
"gondorian army out of Ithilien. Unfortunately, the combined might of "+
"elves and men was too much and in the year 3434, our Lord's army was "+
"defeated at Dagorlad ('Battle-plain'), just north of the gates of "+
"Mordor. The alliance besieged Dark Lord at Barad-dur and after several "+
"years of bitter fighting, cruelly slew his physical form. "+
"Here ends the Second Age.\n");
      break;
    case 5:
      write("\n"+
"After a thousand years in the void, the Dark Lord returned and settled "+
"in Dol-Guldur, sending his Nazgul on missions across the continent to "+
"spread his power and prepare for his return. The mightiest of the Nazgul "+
"was sent North and formed the Kingdom of Angmar, gathering great armies "+
"of orcs and trolls to do his that of his master; the cleansing of "+
"Middle-Earth. The Witch-king, as captain of Angmar, sent many human "+
"agents and dark priests to infiltrate Arnor and as a result of their "+
"skillful manipulation, Arnor soon split into three smaller kingdoms. "+
"Rhudaur, one of these kingdoms, was the first to submit to the Army of "+
"Angmar, allowing them to liberate the Rhudaric Hillmen who had long been "+
"slaves of the evil Dunedain. In the year 1637, a great plague killed the "+
"majority of Dunedain in Carlodan, the southern kingdom in Arnor, "+
"resulting in the majority of its remaining people abandoning their "+
"homeland and leaving only Arthedain for the Army of Angmar to war "+
"against.\n");
      break;
    case 6:
      write("\n"+
"In 1973, the Witch-king threw the full might of Angmar against "+
"Arthedain and after a brief struggle, the final kingdom of Arnor "+
"collapsed in ruin. Thus the North was liberated by the Angmar army's "+
"force of arms. Unfortunately, it was not to remain so. In 1975, the "+
"Gondorian army marched North and, together with elves from Rivendell "+
"and Lindon, attacked the Angmarian troops. Despite the overwhelming "+
"numbers of aggressors, the Army of Angmar fought bravely and the result "+
"of the battle was long in doubt until, at acrucial time, the Witch-king "+
"deserted his troops and fled. The Gondorians, with their spirits "+
"uplifted, forced the Army of Angmar to retreat in bad order with "+
"huge attrition. After the defeat, the remnants of the Army of Angmar "+
"gathered in the Misty Mountains and with heavy hearts, brooded over "+
"what could have been.\n");
      break;
    case 7:
      write("\n"+
"Little is known about the Army until the year 2060 of the third age, "+
"when Dark Lord returned to Dol Guldur and sent northa new captain for "+
"the Army. This second captain was a mighty child of Numenor named "+
"Morgrond ('black-club' in common tongue) as a sign of respect for his "+
"mastery of fighting with clubs. Other than his combat prowess, he was "+
"renowned for being unfailingly loyal to the Dark Lord and Dark Lord only "+
"(which led to him being called, 'The club of Dark Lord' in some circles). "+
"Unlike the Nazgul, he had not needed a ring of power to show him the "+
"truth and righteousness inherent in Dark Lords great scheme- he had "+
"known it all along. Morgrond had no difficulty in regathering the Army "+
"of Angmar for most still believed in Dark Lords cause and could not help "+
"but admire their new captain whose belief epitomised their own. In the "+
"year 2063, the newly reformed army marched over the Men-i-Naugrim to "+
"Rhun and there built a fortress which they inhabited for the next 400 "+
"years. The army grew both in strength and numbers, achieving under "+
"Morgrond, unsurpassed mastery with the club- the only weapon the army "+
"has used since this time.\n");
      break;
    case 8:
      write("\n"+
"In the year 2460, the Dark Lord returned to Dol Guldur and took the "+
"newly revitalised army with him. In the year 2510, Balchoth army "+
"ordered by Dark Lord launched an assault against the Dunedain. "+
"Morgrond with a small part of Army of Angmar joined them in order to "+
"observe the progress and report results to the Dark Lord. The Balchoth "+
"were defeated on the field of Celebrant when the Gondorian Army received "+
"support from Eorl the Young and his cursed Eothed. Morgrond, while "+
"fighting in a desperate rear guard action, was slain but his bravery "+
"allowed the soldiers of Army of Angmar to retreat to Dol Guldur and "+
"report the anihilation of Balchoth to the Dark Lord. He then appointed "+
"a third Captain for the army known as Belturma ('Strong Shield'), who "+
"taught thearmy advanced defensive techniques involving the use of the "+
"shield, as well as various strategies for close-formation fighting. "+
"Under the orders of the new captain, the Angmar army went in search "+
"of Eorl. With the help of Dunlendings and Hillmen from the southern "+
"Misty Mountains they found him in the year 2545 on the Wold. With the "+
"fire of retribution burning hot in their hearts, they wreaked their "+
"vengeance on Eorl's troops and smashed Eorl to his death.\n");
      break;
    case 9:
      write("\n"+
"In the year 2941, Dark Lord was forced to abandon the home he had made "+
"in Dol Guldur by the foul machinations of the White Council. Before "+
"leaving, he ordered the Army of Angmar to head west to the Misty "+
"Mountains in order to protect the misty passes from incursion and "+
"harry the followers of the Valar. The journey undertaken by the army "+
"was a difficult one and many men were lost both to the treacherous "+
"mountain passes and skirmishes with the cowardly elves of Lorien. By "+
"far the greatest loss was Belturma, who at the age of 512 died a "+
"natural death and was buried on the slopes of the Misty Mountains. "+
"So it was that the Angmarim arrived at their current location, once "+
"more proudly raising the banners of the Dark Lord in the North.\n");
      break;
    case 10:
      write("\n"+
"What We Offer To Loyal Warriors\n"+
"===============================\n"+
"\n"+
"For a small 17% tax (10% for layman soldiers) we give you the chance "+
"to stay on the right side when the final war breaks out.\n"+
"\n"+
"In addition to this we teach many skills in our training hall "+
"(layman soldiers to a little bit lower levels in some skills).\n"+
"\n"+
"Our preference is on using shield and club. We teach two special "+
"skills. One helps you to defend yourself better when using a shield "+
"and the other one teaches you how to properly smash your enemy with "+
"a club.\n"+
"\n"+
"Members can do 'help angmar' for more information.\n"+
"\n");
      break;
    case 11:
      write("\n"+
"Punishments for Traitors\n"+
"========================\n"+
"\n"+
"Beware the wrath of Dark Lord. Most of all he hates traitors "+
"and has no mercy with them. The least he will do to you for leaving "+
"the army or repetitive killing of members of his army is that he will "+
"send bunch of strong warriors with clubs to beat your stupidity out of "+
"your head. And you should be aware that after thorough work on your head "+
"it will most likely forget not only the name of its holder but also all "+
"other sort of things it used to know. Hence don't be surprised if you "+
"can't remember skills you knew before the curing took place. Naturally "+
"'skills' here mean just any skills and not only ones related to the "+
"Army. The curing has also some impact on your physical state so apart "+
"from forgetting things you can also feel weaker, with broken health and "+
"somehow clumsier. Not to mention that you may forget how to count to ten "+
"and suddenly be afraid of every mouse running in your way. "+
"But you do not have to be afraid any of these things... All you have to do "+
"is to obey orders and show respect to your superiors.\n");
      break;
    case 12:
      write("\n"+
"Organization of Army of Angmar\n"+
"==============================\n"+
"\n"+
"Every member has given title according to his position in the Army. "+
"The title consists of an adjective and a rank in the army. The rank is "+
"what determines your position. Immediately after joining your rank is "+
"Servant. After short trial period you become full member with the rank "+
"Footman. From now on it depends only on your behaviour, experience and "+
"skills what rank will you achieve. Actual ranking system is described "+
"on the next page.\n"+
"The adjective is related to your general knowledge of the world "+
"and probably also how are you known in the world. Here is the list "+
"of all adjectives in increasing order:\n\n"+
break_string(COMPOSITE_WORDS(ADJ_LIST), 70, 5)+
"\n");
      break;
    case 13:
      write("\n"+
"The Ranking System of Army of Angmar\n"+
"====================================\n"+
"\n"+
"The Army has a fixed structure and so there is only fixed number of positions "+
"for every rank. This number depends on the number of members with lower "+
"rank. Note that there is always at least one position available. "+
"If you want to reach some rank you must fulfill two conditions:\n"+
"    1.  You must be 'good' enough to qualify for the position\n"+
"    2.  You must be better than others who qualify for the position.\n"+
"From time to time every member is reconsidered and ranks are assigned "+
"according to your current position in the army. So you might find "+
"yourself demoted while someone else got promoted. Hope this will keep "+
"the competitive spirit up which in turn will help to build up better "+
"and stronger army.\n");
      break;
    case 14:
      write("\n"+
"Number of Positions Available\n"+
"=============================\n"+
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
    case 15:
      write("\n"+
"Council\n"+
"=======\n"+
"\n"+
"There is elected a council that has the final word on the "+
"punishments. Councilmembers are elected by all soldiers. However votes "+
"are weighted according to the rank and here are exact weights:\n"+
"                Footman         - 2\n"+
"                Standard Bearer - 3\n"+
"                Corporal        - 4\n"+
"                Sergeant        - 5\n"+
"                Warrant Officer - 6\n"+
"                Lieutenant      - 7\n"+
"                Captain         - 8\n"+
"In council can be any soldier with rank below Lieutenant. Only Captain "+
"Lieutenants and councilmember can start election for the position in "+
"council. This cannot be done sooner than one month after last election.\n");
      break;
    case 16:
      write("\n"+
"Discipline and Punishments\n"+
"==========================\n"+
"\n"+
"In order to maintain the discipline in the army there is a set of "+
"punishments to fit every possible level of misbehaving. These are:\n"+
"      1. Ban from training for 2 weeks\n"+
"      2. Lowering effectivity of specials for 10 days + above\n"+
"      3. Disallowing specials for 1 week + above\n"+
"      4. Beating on the head (losing skills) + above\n"+
"      5. Extermination\n"+
"      6. Rejecting from Army + beating on the head\n");
      break;
    case 17:
      write("\n"+
"Voting on Punishments\n"+
"=====================\n"+
"\n"+
"Suggest a punishment can only Captain, Lieutenant or councilmember. "+
"Soldier cannot be suggested for same punishment sooner than one month "+
"after the last suggestion for this punishment. He can be suggested for "+
"different punishment tough. After the suggestion there is exactly one "+
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
"Votes are equal. Majority of votes gives the result but if voted less than "+
"30% of soldiers allowed to vote or in case of tie the votes of council are "+
"the only ones counted. No vote from councilmember in this case counts as "+
"vote against.\n");
      break;
    case 18:
      write("\n"+
"Register of the members of Army of Angmar\n"+
"=========================================\n\n"+
"Captain\n"+
"-------\n"+
"Denethor\n\n"+

"Lieutenants\n"+
"-----------\n"+
"Gector, Jakle, Reficul, Skulker\n\n"+

"Warrant Officers\n"+
"----------------\n"+
"Carpus, Hawk, Lazarus, Newton, Smokey, Ulath\n\n"+

"Sergeants\n"+
"---------\n"+
"Bloodlust, Bogart, Emper, Javert, Karpath, Krangh, Manowar, Morg, " +
"Ragul, Vlady\n\n"+

"Corporals\n"+
"----------\n"+
"Aaz, Astra, Bildor, Dazalarian, Deproelius, Dethraine, Flingbang, " +
"Hendrix, Jar, Locklear, Morti, Nanja, Per, Stryder, Talbot\n\n"+

"Standard Bearers\n"+
"----------------\n"+
"Chmee, Dolmarth, Elliot, Fidi, Frajola, Funky, Geb, Hades, Halb, " +
"Janice, Kayt, Kysler, Maren, Mickey, Mortimor, Nixon, Purple, Radha, " +
"Rhunt, Stern, Talis, Twolf, Ugelplect, Vgi, Zeus\n\n"+

"Footmen\n"+
"-------\n"+
"Avathar, Bebop, Bign, Bloodfang, Bueradin, Cabral, Caldin, Catherine, " +
"Cerlion, Daryoon, Doughboy, Drakman, Duh, Dundurs, Dunhough, Eleron, " +
"Elysia, Fzoul, Gallahan, Gargayle, Ghazg, Gnarf, Gozer, Gram, Gruff, " +
"Guard, Hoax, Holiday, Ishnacht, Java, Khali, Laurel, Lubu, Lynxx, " +
"Mantis, Mars, Metallica, Moridin, Morncki, Oloth, Pippilotta, Pirvan, " +
"Sartan, Sin, Skarsnik, Spider, Thurin, Tinkel, Tovos, Tweed, Uriel, " +
"Whisper, Woj, Zeppelin\n\n"+

"Former Members\n"+
"--------------\n"+
"Monika, Mysterion, Necros, Nogg, Raffe, Rage, Rahvin, Spider, Tubs, Uhlrag\n\n"+
"\n");
      break;
    default:
      write("This page is empty.\n");
  }
}
