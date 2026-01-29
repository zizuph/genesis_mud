// OBJECT:  inn object

    /* Calia Domain

    HISTORY

    [2001-12-23] Created by Uhclem from
        [C:\CALIA\YULEWARE\GINGER\INN_OBJE.DOC].

    PURPOSE

    This object is deployed in the the Calian Inn in Gelan during the Yule
    season.  It adds a few question-and-answer combinations to the innkeeper's
    usual dialogue and then removes itself from the game.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include "defs.h"

// FUNCTIONS

// Function:  add_gingerbread_chat()

/*

Purpose:  adds some dialog to the innkeeper.

Arguments:  none.

Returns:  nothing.

*/

void
add_gingerbread_chat()

{

    object innkeeper = present("orgulas", environment());

    if (innkeeper && !innkeeper->query_prop(CALIA_GINGERBREAD_CHAT))

    {

        innkeeper->add_ask(({"yule", "yule season", "season",
            "donut", "Domut", "baker", "gingerbread", "cookies",
            "gingerbread cookies", "biscuits", "gingerbread biscuits"}),
            "say Ah, Donut the baker is making those" +
            " gingerbread cookies again, isn't he? The" +
            " gingerbread isn't bad, but I've had quite" +
            " enough of that game - far too messy.", 1);

        innkeeper->add_ask(({"messy", "too messy",
            "mess", "piece", "pieces"}),
            "say My goodness, what a mess they made! People" +
            " would leave gingerbread everywhere, and guess who had to" +
            " sweep it up afterwards - me, of course. Sometimes" +
            " it seemed like hundreds of pieces.", 1);

        innkeeper->add_ask(({"game", "gingerbread game"}),
            "say Oh, it's not much of a game, although it did waste" +
            " a lot of people's time - time that they could" +
            " have spent drinking my fine wine! You simply had to" +
            " find and eat the gingerbread emperor, and Donut" +
            " doesn't even make that cookie any more.", 1);

        innkeeper->add_ask(({"emperor", "gingerbread emperor",
            "winning", "win", "win game", "reward", "rewarding"}),
            "say Well, strictly speaking, all you need to do" +
            " is eat the gingerbread emperor to win, but for" +
            " those who played the game - and I was never one, mind" +
            " you - it was always most rewarding if you could" +
            " collect all his different gingerbread subjects first" +
            " and then eat the emperor.", 1);

        innkeeper->add_ask(({"subjects", "gingerbread subjects",
            "emperor's subjects", "how many", "kinds", "different kinds"}),
            "say The emperor's subjects are the other cookies, of course." +
            " There aren't as many as there once were. Donut only" +
            " makes half as many different kinds as he did before." +
            " Sometimes you do see some of the others, but I" +
            " don't know where to get them.", 1);

        innkeeper->add_ask(({"collect", "cookie", "more cookies"}),
            "say As I recall, you need a lot of different cookies" +
            " to play the gingerbread game, but Donut usually only" +
            " gives one to a customer. But maybe you have" +
            " some friends who would help you collect them.", 1);

        innkeeper->add_ask(({"find", "find emperor",
            "find gingerbread emperor", "eat emperor",
            "eat gingerbread emperor"}),
            "say Ah, well that's the trick, isn't it? You" +
            " won't find the emperor just by searching. If" +
            " you're determined to play - and I can't" +
            " imagine why anyone would - you have to start" +
            " by collecting his subjects. You can't have" +
            " a gingerbread emperor without a gingerbread empire!", 1);

        innkeeper->add_ask(({"where", "play", "play game", "collect",
            "collecting", "collect subjects", "collecting subjects",
            "collecting his subjects", "collect gingerbread subjects",
            "collecting gingerbread subjects", "play gingerbread game",
            "empire", "gingerbread empire"}),
            "say Anywhere but here! The last thing I need" +
            " is people leaving gingerbread cookies all over" +
            " my nice clean floor.", 1);

        innkeeper->add_prop(CALIA_GINGERBREAD_CHAT, 1);

    }

    remove_object();

}

// OBJECT DEFINITION

void
create_object()

{

    set_long("This object gives the innkeeper some" +
        " handy answers to yule-related questions.\n");

    set_no_show();  /*  object is invisible to mortals  */
    set_short("inn_object");
    set_name("_gingerbread_inn_object");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

    add_prop(OBJ_M_NO_GET, "Do not attempt to move this object." +
        " It belongs in the Calian Inn.\n");

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

    set_alarm(1.0, 0.0, add_gingerbread_chat);

}
