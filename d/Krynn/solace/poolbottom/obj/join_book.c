/*
 * Join book of the SoHM in Poolbottom
 * Based on the Book of Angmar Army by Milan
 * -- Arman, Feb 2016
 */

#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Krynn/solace/poolbottom/local.h"
#include "/d/Krynn/guilds/sohm/defs.h"



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
    set_short("lectern with a leather-bound book upon it stands near the twin doors");
    set_name("book");
    add_name("sohm_join");
    add_adj("leather-bound");
    set_long("A leather-bound book sits open upon the lectern near " +
             "the twin doors at the southern end of the " +
             "great hall. It provides instructions on how to join - " +
             "or leave - the school of High Magic.\n" +
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
    write("                       The School of High Magic\n"+
          "                         General Information\n\n"+
          "         A summary of the origins of magic in Krynn . . . . . 2\n"+
          "         The persecution of magic and the Cataclysm . . . . . 3\n"+
          "         Early life of a wizard, and the Test . . . . . . . . 5\n"+
          "         Magi training at Poolbottom. . . . . . . . . . . . . 6\n"+
          "         Joining the School of High Magic . . . . . . . . . . 7\n"+
          "         Leaving the School of High Magic . . . . . . . . . . 8\n\n"+
          "                                     Page 1\n");
    break;


    case 2:
    write(
"          A summary of the origins of magic in Krynn\n\n"+
"    At the end of the Age of Starbirth after the destructive\n"+
"    All Saints War between the Gods that devastated the lands\n"+
"    of Krynn, each family of gods agreed to nevermore make\n"+
"    war upon Krynn, sealing this pact through the creation of\n"+
"    three blood-siblings who would bless the world by their\n"+
"    creation. The blessing from these children of the gods \n"+
"    was magic.\n\n"+    
"    To Paladine and Mishakal was born a son of light, Solinari,\n"+
"    who gained domination over quiet and constructive magic.\n\n"+
"    From Gilean's majestic and beautiful thoughts sprang forth\n"+
"    a daughter of Neutrality, Lunitari, who gained domination\n"+
"    over illusion and reshaping magic.\n\n"+    
"    And last, from Takhisis and Sargonnas, came a brother of\n"+
"    darkness, Nuitari, who gained domain over commanding and\n"+
"    destructive magic.\n\n"+   
"    Bound by the common bond of magic, these three looked about\n"+ 
"    the face of Krynn and loved it greatly. Thus they did not \n"+
"    join their fellow gods in the heavens, but stayed close to \n"+
"    the world. They revolved about it, teaching those who would\n"+
"    follow their ways the Foundations of Wizardry and granting \n"+
"    them their powers.\n\n"+   
"    From these followers the three Orders of High Sorcery were \n"+
"    formed. Solinari the god of Good magic founded the Order\n"+
"    of the White Robes; Lunitari the god of Neutral magic\n"+
"    founded the Order of the Red Robes; and Nuitari the god of\n"+
"    Evil magic founded the Order of the Black Robes.\n\n"+
"                                     Page 2\n"+
    "\n");
    break;

    case 3:
    write(
"          The persecution of magic and the Cataclysm\n\n"+
"    The end of the Third Dragon War  - when the Knight of\n"+
"    Solamnia Huma Dragonbane banished the Queen of Darkness, \n"+
"    Takhisis, to the Infernal Realms of the Abyss - heralded \n"+
"    the beginning of a golden age for the lands of Krynn. \n\n"+
"    Nearly 200 years of peaceful coexistence followed, until\n"+
"    the rise of Istar and the determination of successive\n"+
"    Kingpriests of Istar to rid the world of 'evil'.\n\n"+
"    Evil was proclaimed to be an affront to gods and mortals\n"+
"    and needed to be destroyed. A rigid list of evil acts\n"+
"    was created, of which top of that list was wizardry.\n\n"+
"    Priests of Istar roused mobs of citizens to fear and\n"+
"    revile magic, stirring them to attack the towers of\n"+
"    High Sorcery across the realms. When rioting mobs\n"+
"    approached two of the towers, the mages of the towers\n"+
"    knew that the artifacts and spells contained within\n"+
"    would be disastrous in the hands of the uninitiated.\n"+
"    Unleashing the powers of the artifacts these mages\n"+
"    destroyed the towers and themselves, devastating the\n"+
"    countryside.\n\n"+
"                                     Page 3\n"+
       "\n");
    break;

    case 4:
    write("\n\n"+
"    The Kingpriest, fearing what would happen if the magic\n"+
"    stored in the towers at the great cities of Palanthas\n"+
"    and Istar were released, made a pact with the wizards.\n\n"+
"    They were offered safe passage to exile in a faraway \n"+
"    land if they left the remaining towers undestroyed. \n"+
"    The mages agreed, removing themselves to the the Tower\n"+
"    of Wayreth in far Qualinesti.\n\n"+
"    Soon after the Kingpriest in his arrogance tried to\n"+
"    elevate himself to godhood, resulting in the full\n"+
"    wrath of the gods. The sky burned and a fiery mountain\n"+
"    fell from the heavens. Istar was destroyed and the\n"+
"    lands of Krynn broken - beginning an Age of Darkness.\n"+
"    The gods withdrew from the world, with the exception of\n"+
"    the three gods of magic.\n\n"+
"    Krynn became a place of distrust and hatred, with every\n"+
"    fallen race blaming others for the world's pain.\n\n"+
"    Mages withdrew and largely went in to hiding for over\n"+
"    300 years. Only now has the distrust and hatred for \n"+
"    magic diminished to a point where once again\n"+
"    schools of magic can open their doors to students.\n\n"+
"                                     Page 4\n"+
    "\n");
    break;

    case 5:
    write(

"             Early life of a wizard, and the \n" +
"                   Test of High Sorcery\n\n"+
"    All who wish to join an Order of Wizardry must first \n"+
"    begin their training studying at a school of High \n"+
"    Magic or under the tutelage of a willing Archmage. \n\n"+
"    Wizards involved in such tutelage may make use of \n"+
"    their magic without declaring allegiance to an Order or \n"+
"    loyalty to the Conclave of Wizards who rule the Orders \n"+
"    of High Sorcery. \n\n"+
"    There is no obligation for one who studies at a school \n"+
"    of High Magic to join an Order of High Sorcery. \n"+
"    However those who wish to expand their mastership of  \n"+
"    their spell skills, gain access to powerful advanced \n"+
"    spells or enhance their capacity to cast greater spells \n"+
"    can only do so by becoming a Wizard of High Sorcery. \n\n"+
"    Once a student of High Magic progresses to the rank of \n"+
"    Aspirant, they will be ready to take the Test of High \n"+
"    Sorcery. \n\n"+
"    While one may be ready as an Aspirant for the Test, it \n"+
"    should be noted that the Test is by invitation only from \n"+
"    the Conclave of Wizards.\n\n" +
"    The Test of High Sorcery measures a wizard's magical \n"+
"    abilities. Each Aspirant's test differs, designed \n"+
"    exclusively to measure strengths and weaknesses and  \n"+
"    their understanding of the Foundations of Wizardry. \n\n"+ 
"    In all Tests failure means death. With greater power  \n"+
"    comes greater responsibility, and the Orders take this \n"+
"    very seriously. \n\n"+
"                                     Page 5\n"+
    "\n");
    break;

    case 6:
    write(
"                 Magi training at Poolbottom\n\n"+
"    Poolbottom is a private school of High Magic, sponsored \n"+
"    by the Orders of High Sorcery based in the Tower of  \n"+
"    Wayreth that can be found - if it wants to be found -  \n"+
"    in the Qualinesti forest south of Haven. \n\n"+
"    At Poolbottom you begin your life as an apprentice, \n"+
"    learning the fundamentals of magic that will be the \n"+
"    cornerstone of your career as a wizard. \n\n"+
"    The school will teach you the six arcane spell forms -\n"+
"    transmutation, illusion, divination, enchantment \n"+
"    conjuration, and abjuration, as well as the four primary \n"+
"    elemental spell skills - fire, earth, air, and water. \n\n"+
"    You will also be be able to take advanced training in \n"+
"    an arcane form and an element, allowing you to specialise \n"+
"    towards a path of mastery for spells of a specific \n"+
"    type. \n\n"+
"    You will also be taught skills in herbalism and alchemy. \n\n"+
"    Poolbottom will also teach you some functional spells, \n"+
"    although do not expect spells of wonder and power to \n"+
"    be handed to you on a platter. Magic is jealously guarded \n"+
"    by wizards. You will find your spellbook being filled \n"+
"    more by your own study and adventuring than by the \n"+
"    tutors of this school. \n\n"+
"                                     Page 6\n"+
    "\n");
    break;

    case 7:
    write(
"                 Joining the School of High Magic\n\n"+
"    The school of High Magic is an occupational guild that \n"+
"    accepts humans, elves, half-elves, gnomes, and even \n"+
"    the curious race of hobbits in to its halls. \n\n"+
"    The races of dwarves, kender, goblinoids, minotaurs \n"+
"    and ogres are not accepted here. Any member unfortunate \n"+
"    enough to find themselves transformed in to such a  \n"+
"    race will be expelled. \n\n"+
"    The nature of magic is unforgiving, so the school will \n" +
"    only train those of wanderer mortal rank or higher.\n\n" +
"    Members are expected to act with civility within the \n"+ 
"    walls of the school. Violence and theft against fellow \n"+
"    members is not accepted within the school, and will \n" +
"    result in expulsion. \n\n"+
"    Outside the walls of the school you can act as you  \n"+
"    please, however misuse of magic may bring the wrath of \n"+
"    the Orders of High Sorcery, resulting in you being \n"+
"    declared 'Renegade' and forcibly hunted. \n\n"+
"    There are no other requirements to join. Simply \n"+
"    <enroll in school of high magic>. \n\n"+
"                                     Page 7\n"+
    "\n");
    break;

    case 8:
    write(
"               Leaving the School of High Magic\n\n"+
"    Those who no longer wish to be a student of High Magic \n"+
"    can leave with no penalty beyond the loss of all the \n"+
"    spells they have scribed in their spellbook. \n\n"+
"    Simply <burn school of high magic spellbook>. This \n"+
"    can be done anywhere, and you do not need to return \n"+
"    to the school to leave. \n\n"+
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
