/*
 * /d/Faerun/guilds/fire_knives/obj/fireknives_book.c
 *
 * Nerull 2019
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
    set_short("small leather book on a simple iron book stand");
    set_name("book");
    add_name("book");
    add_name("Fireknives book");
    set_long("This is a small book bound in rich leather. It "
    +"sits on top of a simple iron book stand. There are "
    +"instructions next to the book.\n\n" +
        "@@opened_at_page@@");
        
    add_name("book");
    add_adj(({"leather"}));
    book_is_closed = 1;
    what_page = 1;
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 200);
    
    add_prop(OBJ_I_NO_GET,"The small leather book is "
    +"tethered to the simple iron book stand. You don't dare "
    +"to remove it.\n");
    
    add_prop(OBJ_I_NO_STEAL,"The small leather book is "
    +"tethered to the simple iron book stand. You don't dare "
    +"to remove it.\n");

    add_cmd_item(SIGN_ID, "read", "@@instructions@@");
}


int
instructions(string str)
{
    write(
        "\t.------------------------------------------------------.\n" +
        "\t|                                                      |\n" +
        "\t|   These are the commands for the leather book:       |\n" +
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
        "  ____________________________________________________________\n"+
        " |                                                    Page 1  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |          I N D E X                                         |\n"+
        " |          ---------                                         |\n"+
        " |          1           Index, this page                      |\n"+
        " |          2..3        About the Brotherhood                 |\n"+
        " |          4           Rules                                 |\n"+
        " |          5           The Elders                            |\n"+
        " |          6           Contracting                           |\n"+
        " |          7           Ranks                                 |\n"+
        " |          8           Restrictions & Leaving                |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                           ___                              |\n"+                     
        " |                   $      |___|           $                 |\n"+
        " |           $   $           | |        $      $              |\n"+
        " |                     __    | |    __                        |\n"+
        " |            $       |  |___|_|___|  |                       |\n"+
        " |              $  $  |_______________|     $                 |\n"+
        " |                     $    | | |    $  $   $                 |\n"+
        " |             $        $$  | | |  $$     $                   |\n"+
        " |                  $   $$$ | | | $$$       $                 |\n"+
        " |                $     $$$$| | |$$$$     $                   |\n"+
        " |                 $$$    $$$$$$$$$ _  $$$                    |\n"+
        " |                  $$$$$  $$$$$$$  $$$$$                     |\n"+
        " |                    $$$$$$$$$$$$$$$$$                       |\n"+
        " |                       $$$$$$$$$$$                          |\n"+
        " |                          $$$$$                             |\n"+      
        " |                           $$$                              |\n"+
        " |                            $                               |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n");
        break;                     
        
        
        case 2:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 2  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |       A B O U T   T H E   B R O T H E R H O O D            |\n"+
        " |       -----------------------------------------            |\n"+
        " |  The Brotherhood of Assassins, also known as the           |\n"+
        " |  Fire Knives, was originally a band operating under        |\n"+
        " |  Lord Tagreth Cormaeril, the Grandfather of Assassins.     |\n"+
        " |  Unlike the popular opinion of a murderer, they were       |\n"+
        " |  never mere mercenaries honing their skills to earn a      |\n"+
        " |  coin or two, but rather highly educated and               |\n"+
        " |  cold-blooded nobles who understood the inner workings of  |\n"+
        " |  a civil society and the need for the removal, by any      |\n"+
        " |  means necessary, of pawns in the way of kings.            |\n"+
        " |                                                            |\n"+
        " |  As it once was, the world again has become of an          |\n"+
        " |  unstable nature where stability is desired, and been      |\n"+
        " |  condemned by stagnation where progress is required. When  |\n"+
        " |  the wheel does not turn, water cannot flow, and where     |\n"+
        " |  the wind blows too fast, nothing can be built. It         |\n"+
        " |  falls to us today in this reemergence of the              |\n"+
        " |  Brotherhood to be the means for greater ends, the         |\n"+
        " |  facilitators of the return of balance, and the ones       |\n"+
        " |  who carry out the judgements of fate.                     |\n"+
        " |                                                            |\n"+
        " |  An assassin understands the difference between service    |\n"+
        " |  and servitude, offering the former and being anathema     |\n"+
        " |  to the latter. Where other men follow truths, leaders,    |\n"+
        " |  causes, filling themselves of a false grandeur,           |\n"+
        " |  we recognize the hypocrisy of living creatures who        |\n"+
        " |  work for naught but themselves and would go as far as     |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n"); 
        break;        
                              
        case 3:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 3  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |       A B O U T   T H E   B R O T H E R H O O D            |\n"+
        " |       -----------------------------------------            |\n"+                                
        " |  keeping the sun from rising if it meant they'd reign      |\n"+
        " |  in darkness. We recognize a life for what it is: a        |\n"+
        " |  mission for the grand plan, which when unequal to         |\n"+
        " |  the task must be removed so that a new one can take       |\n"+
        " |  its place and push the wheel along.                       |\n"+
        " |                                                            |\n"+
        " |  As every life, ours also has a mission, and we will       |\n"+
        " |  either fulfill it or perish. What unites us is purpose    |\n"+
        " |  and complete dedication to this our mission. For the      |\n"+
        " |  sake of our mission, we will be the hand that pushes      |\n"+
        " |  the pawn away from table in others', so long as their     |\n"+
        " |  mission is worthy, and this in turn will always be        |\n"+
        " |  easily recognizable by the only truth there exists in     |\n"+
        " |  this world of smokes and mirrors: power of                |\n"+
        " |  acquisition... Coin.                                      |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+        
        " |                                                            |\n"+       
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+    
        " |                                                            |\n"+    
        " |                                                            |\n"+    
        " |                                                            |\n"+    
        " |                                                            |\n"+    
        " |                                                            |\n"+     
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  
               
        case 4:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 4  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                  T H E   C O U N C I L                     |\n"+
        " |                  ---------------------                     |\n"+  
        " |                                                            |\n"+
        " |  The Elder (unknown) - Role and purpose                    |\n"+
        " |  --------------------------------------                    |\n"+
        " |  The Elder is the leader of the Council of Elders,         |\n"+
        " |  responsible for the overall direction of this chapter     |\n"+
        " |  of the Fire Knives. While not normally involved in day    |\n"+
        " |  to day activity the Elder can if necessary step in and    |\n"+
        " |  take care of the roles of other absent Elders.            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |  The Inquisitor - Role and purpose                         |\n"+
        " |  ---------------------------------                         |\n"+
        " |  The Inquisitor is the primary teacher of this chapter     |\n"+
        " |  of the Fire Knives and responsible for the education      |\n"+
        " |  of new trainees. He also serves as the face of the        |\n"+
        " |  Fire Knives to people outside the guild, assigning        |\n"+
        " |  envoys if necessary.                                      |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |  The Fist - Role and purpose                               |\n"+
        " |  ---------------------------                               |\n"+
        " |  The Fist is the primary disciplinarian of the chapter     |\n"+
        " |  as well as the primary enforcer when dealing with         |\n"+
        " |  declared enemies. He also takes part in the education     |\n"+
        " |  of trainees.                                              |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  
        
        case 5:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 5  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                  T H E   M E M B E R S                     |\n"+
        " |                  ---------------------                     |\n"+  
        " |                                                            |\n"+
        " |  What we are looking for in prospects for the              |\n"+
        " |  Brotherhood is loyalty. Loyalty to the Brotherhood,       |\n"+
        " |  the principles we adhere to and to your                   |\n"+
        " |  comrades-in-arms. What we want are team players, those    |\n"+
        " |  concerned with the betterment of us all, not just         |\n"+
        " |  themselves. We want those who trust us with molding       |\n"+
        " |  them into efficient killers.                              |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+        
        " |                                                            |\n"+
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+        
        " |                                                            |\n"+    
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+       
        " |                                                            |\n"+         
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  
        
        case 6:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 6  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                       R A N K S                            |\n"+
        " |                       ---------                            |\n"+  
        " |                                                            |\n"+
        " |  Ranks in the Brotherhood is completely based on merit     |\n"+
        " |  and promotion, and with higher rank you gain access to    |\n"+
        " |  more special training. Higher rank however does not       |\n"+
        " |  set you above other members, it merely shows you have     |\n"+
        " |   been working hard or perhaps been with us for a longer   |\n"+
        " |  time. In the end all members are equal.                   |\n"+
        " |                                                            |\n"+
        " |  Trainee Ranks:                   Member Ranks:            |\n"+       
        " |  --------------                   --------------           |\n"+
        " |  Accomplished Candidate Inhumer   Bringer of Endless Night |\n"+     
        " |  Surviving Candidate Inhumer      Ender of Dreams          |\n"+
        " |  Beginning Candidate Inhumer      Fearsome Asp             |\n"+
        " |  Initiate of the Third Level      Fatal Wish               |\n"+
        " |  Initiate of the Second Level     Poisoned Mist            |\n"+
        " |  Initiate of the First Level      Whisper of Steel         |\n"+
        " |  Postulant                        Glint in the Moonlight   |\n"+
        " |                                   Whispering Scythe        |\n"+
        " |                                   Venom Barb               |\n"+
        " |                                   Silent Shade             |\n"+
        " |                                   Endless Twilight         |\n"+
        " |                                   Deadly Breeze            |\n"+
        " |                                   Midnight Shade           |\n"+
        " |                                   Light Tread              |\n"+
        " |                                   Quiet Touch              |\n"+
        " |                                   Black Orchid             |\n"+
        " |                                   Keen Stiletto            |\n"+
        " |                                   Dark Shadow              |\n"+
        " |                                   Stealthy Dart            |\n"+
        " |                                   Lurker in the Shadows    |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  
         
        case 7:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 7  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                     T R A I N I N G                        |\n"+
        " |                     ---------------                        |\n"+  
        " |                                                            |\n"+
        " |  As a trainee you will be taught the finest combat         |\n"+
        " |  techniques the realms can offer, but we will also         |\n"+
        " |  teach you how to be the member of a team. You will        |\n"+
        " |  live and breathe for the team, and the team will live     |\n"+
        " |  and breathe for you. Your failures are theirs and         |\n"+
        " |  their success is yours. Alone we are strong, but          |\n"+
        " |  together we are invincible. And a team is never           |\n"+
        " |  stronger than its weakest link.                           |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                    C O N T R A C T S                       |\n"+
        " |                    -----------------                       |\n"+  
        " |                                                            |\n"+
        " |  The Council of Elders will make contracts available as    |\n"+
        " |  supply and demand ebb and flow. They negotiate with       |\n"+
        " |  customers that will remain anonymous to you and make      |\n"+
        " |  the contracts available when an agreement has been        |\n"+
        " |  struck. You may then gather a team and give the target    |\n"+
        " |  of the contract the gift of a swift death.                |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  

        case 8:
        write("\n\n"+
        "  ____________________________________________________________\n"+
        " |                                                    Page 8  |\n"+
        " |                                                            |\n"+
        " |                  F I R E    K N I V E S                    |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                        R U L E S                           |\n"+
        " |                        ---------                           |\n"+  
        " |                                                            |\n"+
        " |  1.                                                        |\n"+
        " |    Once you join the Brotherhood, you join for life.       |\n"+
        " |    You also swear to keep the secrets you learn in your    |\n"+
        " |    training. Under no circumstance will you share any      |\n"+
        " |    information you are privy to without the explicit       |\n"+
        " |    permission of the Council of Elders.                    |\n"+
        " |                                                            |\n"+
        " |  2.                                                        |\n"+
        " |    You will never kill someone without the permission      |\n"+
        " |    of the Council of Elders. If you are attacked you       |\n"+
        " |    walk away and gather the information you can about      |\n"+
        " |    the assailant and present it to the Elders. If you      |\n"+
        " |    are harassed you let them and present the evidence      |\n"+
        " |    to the Elders. The Elders decide who has earned a       |\n"+
        " |    death mark, not you.                                    |\n"+
        " |                                                            |\n"+
        " |  3.                                                        |\n"+
        " |    You are a part of a greater system. Help keep our       |\n"+
        " |    racks filled and our herbalist supplied with the        |\n"+
        " |    components we need.                                     |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+     
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " |                                                            |\n"+
        " +------------------------------------------------------------+\n"+
        "\n");
        break;  
        
        default:
            write("This page is empty.\n");
            return 0;
        break;
    }
}
