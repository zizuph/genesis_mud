// OBJECT:  gingerbread dispenser

    /* Calia Domain

    HISTORY

    [2001-12-23] Created by Uhclem from
        [C:\CALIA\YULEWARE\GINGER\DISPENSE.DOC].

    [2002-01-05] Uhclem added December/January chat changes.

    [2002-01-09] Uhclem added punishment code in response to players who
        repeatedly log out and in to receive large numbers of cookies.

    PURPOSE

    This object is deployed in the Gelan bakery during the Yule season.  Its
    function is to cause the baker to hand out a free gingerbread cookie to
    each customer that enters the shop.  The general rule is to only dispense
    one cookie per customer per day, so this object maintains a list of people
    who have received cookies.  As always, there are exceptions to the rule:
    the baker is far too polite to give a cookie to one person in a group and
    not another, so if several people enter the bakery at once (teamed or not),
    all will get a cookie if any of them is eligible (that is, not already on
    the list).  The baker's memory is also a little dodgy (thanks to Maniac for
    introducing me to that term), so entries will be deleted from the list at
    random. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <language.h>
#include <composite.h>
#include "defs.h"

// GLOBAL VARIABLES

int Dispense_Pending = 0;
int *Cookie_List = ({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
object *Recipients = ({});     /*  players who have received cookies  */
string *Recipient_Names = ({});  /*  needed for logout/login check  */

// FUNCTIONS

// Function:  reset_dispenser()

/*

Purpose:  clears arrays so that returning players can get more cookies; called
by room's reset function.

Arguments:  none

Returns:  nothing

*/

void
reset_dispenser()

{

    Recipients = ({});
    Recipient_Names = ({});

}

// Function:  dispense_cookies()

/*

Purpose:  check for eligibilty and give cookies as appropriate.

Arguments:  room, object representing the location of a new construction site

Returns:  nothing

*/

void
dispense_cookies()

{

    int cookie_selector;
    int i;
    int j;
    int k;
    string current_month = explode(ctime(time()), " ")[1];
    object room = environment();
    object cookie;
    object *everyone = ({});
    object *eligible = ({});
    object baker = present("donut", environment());

    Dispense_Pending = 0;

    /*
     *  If the baker, named Donut, is not present, abort the routine.  He'll 
     *  come back with the next room reset; in the interim, no cookies!    
     */

    if (!baker)

    {

        return;

    }

    /*
     *  The baker needs a few extra lines of dialogue to let players in on the 
     *  gingerbread quest.  Check to see if he's gotten his cues.    
     */

    if (!baker->query_prop(CALIA_GINGERBREAD_CHAT))

    {

        /*
         *  Most yule treats in Calia are deployed during a two-week period 
         *  centered on Christmas Day.  Because I want players to have plenty
         *  of opportunities to complete the gingerbread quest, the cookies are
         *  available for an entire month, roughly December 17 - January 16.
         *  The chat changes a bit from December to January.    
         */

        if (current_month == "Dec")

        {

            baker->add_act("say People love my gingerbread cookies" +
                " during yule season, but as soon as it's over" +
                " they forget them. Funny thing - so do I!");

            baker->add_ask(({"yule", "yule season", "season"}),
                "say It must be yule season now because I've" +
                " begun making gingerbread cookies!", 1);

        }

        else

        {

            baker->add_act("say It's not really yule season any" +
                " more, but I still have plenty of gingerbread cookies!");

            baker->add_ask(({"yule", "yule season", "season"}),
                "say I suppose I celebrate yule season longer" +
                " than anyone else around here - well, other" +
                " than people who like to play the" +
                " gingerbread game.", 1);

        }

        baker->add_act("say We used to play a game with gingerbread" +
            " cookies when I was a child, but I forget how it goes.");

        baker->add_ask(({"game", "play", "gingerbread game"}),
            "say It was a silly game. We played it in the Calian" +
            " Inn, although the innkeeper wasn't very" +
            " happy about it.", 1);

        baker->add_ask(({"gingerbread",
            "cookie", "gingerbread cookie",
            "biscuit", "gingerbread biscuit",
            "cookies", "gingerbread cookies",
            "biscuits", "gingerbread biscuits"}),
            "say Didn't I just give you one? I'm sure I've" +
            " given one to everybody who's visited the shop today." +
            " Or were you asking about the gingerbread game?", 1);

        baker->add_ask(({"calian inn", "Calian Inn", "inn"}),
            "say It's just a little ways north of here.", 1);

        baker->add_ask(({"innkeeper", "happy", "rules", "win", "winning"}),
            "say I don't really remember the rules or how to win the game," +
            " but I do recall that we always managed to get" +
            " a lot of gingerbread on the floor. The innkeeper" +
            " didn't care much for all the sweeping she had to do.", 1);

        baker->add_prop(CALIA_GINGERBREAD_CHAT, 1);

    }

    everyone = FILTER_PLAYERS(all_inventory(room));

    /*
     *  To be eligible to receive a cookie, a player must be visible and must 
     *  not currently be holding a cookie.    
     */

    eligible = FILTER_CAN_SEE(everyone, baker);
    i = sizeof(eligible);
    j = 0;

    while (j < i)

    {

        if (present("_calia_gingerbread_cookie", eligible[j]))

        {

            eligible[j] = room;

        }

        j += 1;

    }

    eligible -= ({room});

    /*
     *  If at least one eligible person is not already on the Recipients list, 
     *  then all eligible players get a cookie.    
     */

    if (sizeof(eligible - Recipients))

    {

        if (sizeof(eligible) == 1)

        {

            tell_room(room, QCTNAME(baker) + " says: " +
                ({
                "Here's a special yule treat for my favorite customer",
                "I have a little yule gift just for you",
                "I baked this especially for you - happy yule",
                "You're just in time for today's yule treat",
                "You can't celebrate yule season without a cookie"
                })[random(5)] + "!\n");

        }

        else

        {

            tell_room(room, QCTNAME(baker) + " says: " +
                ({
                "Here are some little yule treats for you;" +
                " they're not very filling, so don't let them" +
                " stop you from buying anything",
                "It's yule season - free cookies for everyone",
                "Last year's haggis wasn't very popular, so" +
                " this year I'm giving out yule cookies instead",
                "These little gifts are my way of wishing you" +
                " a happy yule",
                "Everyone gets a cookie - it's an old" +
                " yule tradition here"
                })[random(5)] + "!\n");

        }

        while (sizeof(eligible))

        {

            cookie_selector = Cookie_List[sizeof(Recipients) % 16];
            cookie = clone_object(GINGERBREAD_COOKIE + cookie_selector);
            cookie->move(eligible[0]);

            tell_room(room,
                "The baker gives " + QTNAME(eligible[0]) +
                " " + cookie->short() + ".\n",
                ({eligible[0]}));

            eligible[0]->catch_msg("The baker gives you " +
                cookie->short() + ".\n");

            Recipients += ({eligible[0]});
            Recipient_Names += ({eligible[0]->query_real_name()});
            eligible -= ({eligible[0]});

        }

        /*
         *  Randomize the cookie selection and degrade the baker's memory just 
         *  a bit.    
         */

        i = random(sizeof(Cookie_List));
        j = random(sizeof(Cookie_List));
        k = Cookie_List[i];
        Cookie_List[i] = Cookie_List[j];
        Cookie_List[j] = k;

        /*
         *  The faster gingerbread is dispensed, the faster the baker forgets 
         *  who he's already given it to.    
         */

        if (!random(10) &&
            sizeof(Recipients) > 1 &&
            sizeof(Recipient_Names) > 1)

        {

            Recipients -= ({Recipients[random(sizeof(Recipients))]});
            Recipient_Names = Recipient_Names[1..sizeof(Recipient_Names) - 1];

        }

    }

    Recipients -= ({room});

}

// Function:  init()

/*

Purpose:  called by system when object enters a player's inventory; used here
to invoke dispense_cookies function whenever a player comes into the bakery.

Arguments:  none

Returns:  nothing

*/

void
init()

{

    mapping recovery = ([]);
    object tp = this_player();
    object cookie;

    object *cookies_held =
        filter(deep_inventory(tp), &->is_calian_gingerbread());

    object *cookies_recovered;
    string tp_name = tp->query_real_name();
    int *cookie_inventory = ({});

    ::init();

    /*
     *  You can't drop a special cookie, nor can it be stolen.  The only way to 
     *  get rid of one is to eat it, give it to another player, or complete the
     *  quest.  Any of these actions removes the cookie from the recovery
     *  list.  Therefore, if there's a cookie on the player's list which is not
     *  in his inventory, it must have been lost in a reboot or destroyed by a
     *  bug and will be replaced.    
     */

    if (interactive(tp))

    {

        recovery = restore_map(GINGERBREAD_MAP_FILE);

        if (recovery[tp_name])

        {

            cookies_recovered = ({});
            cookie_inventory = ({}) + recovery[tp_name];

            while (sizeof(cookie_inventory))

            {

                if (!sizeof(filter(cookies_held,
                    &operator(==)(cookie_inventory[0]) @
                    &->is_calian_gingerbread())))

                {

                    cookie = clone_object(GINGERBREAD_COOKIE +
                        cookie_inventory[0]);

                    cookie->move(tp);
                    cookies_recovered += ({cookie});

                }

                cookie_inventory -= ({cookie_inventory[0]});

            }

            if (sizeof(cookies_recovered))

            {

                say("A little green and red spotted frog" +
                    " comes galloping up to " + QTNAME(tp) +
                    ", hands " + tp->query_objective() +
                    " " + COMPOSITE_DEAD(cookies_recovered) +
                    ", and then speeds away!\n");

                write("A little green and red spotted frog" +
                    " comes galloping up to you, hands you " +
                    COMPOSITE_DEAD(cookies_recovered) +
                    ", and then speeds away!\n");

            }
        }

        if (!Dispense_Pending)

        {

            set_alarm(2.0, 0.0, dispense_cookies);
            Dispense_Pending = 1;

        }

        /*
         *  The dark side of Yule:  Punishment!    
         */

        /*
         *  The following test is true if the player has received more than one 
         *  cookie (as indicated by Recipient_Names), is not currently holding
         *  a cookie, and does not appear on the Recipients list.  This
         *  condition occurs when a player logs out after receiving a cookie
         *  and then quickly returns to the bakery.  I'll let a player log out
         *  and in once and get an extra cookie, since this may simply be
         *  normal activity, but twice is intentional abuse of gingerbread.    
         */

        if (member_array(tp, Recipients) == -1 &&
            !present("_calia_gingerbread_cookie", tp) &&
            (sizeof(Recipient_Names) -
            sizeof(Recipient_Names - ({tp_name}))) > 1)

        {

            cookie = clone_object(GINGERBREAD_PUNISHMENT);
            cookie->move(tp);
            Recipients += ({tp});

        }

    }

}

// OBJECT DEFINITION

void
create_object()

{

    set_long("This object causes the baker to give out free" +
        " cookies during the yule season. The process is" +
        " automatic; there are no functions that you can control.\n");

    set_no_show();  /*  object is invisible to mortals  */
    set_short("gingerbread dispenser");
    set_name("_calia_gingerbread_dispenser");
    add_name("dispenser");
    set_adj("gingerbread");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

    add_prop(OBJ_M_NO_GET, "Do not attempt to move this object." +
        " It belongs in the Gelan bakery.\n");

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

}
