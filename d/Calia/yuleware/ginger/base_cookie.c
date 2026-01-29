// OBJECT:  gingerbread cookie (base)

    /* Calia Domain

    HISTORY

    [2001-12-17] Created by Uhclem from [C:\CALIA\YULEWARE\GINGER\COOKIE.DOC].
    [2002-01-08] Uhclem rewrote the original file, cookie.c, into this base
    object [C:\CALIA\YULEWARE\GINGER\BASE_COO.DOC] to remedy heap splitting and
    merging problems caused by std/food's handling of a single file with
    variable descriptions.
    [2010-12-17] Lavellan - No more "giving" the special cookies to containers.


    PURPOSE

    A Yule treat distributed in Gelan.  It has no player-controlled function
    other than to be eaten like any other food; however, if multiple
    gingerbread men are left alone in a room for some time, they may get
    restless (see Holiday Room for details).

    This is a base object only and should never be cloned.  The cookie files
    (cookie1.c - cookie32.c) inherit this object. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <cmdparse.h>
#include <files.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include <composite.h>
#include "defs.h"

// GLOBAL VARIABLES

int Cookie_Type;
string Figure;
string Smell_Text;

// FUNCTIONS

// Function:  is_calian_gingerbread()

/*

Purpose:  identifies this object as genuine Calian gingerbread - your guarantee
of quality!

Arguments:  none.

Returns:  int, Cookie_Type, 1-32.

*/

int
is_calian_gingerbread()

{

    return Cookie_Type;

}

// Function:  query_recover()

/*

Purpose:  sorry, cookies are not recoverable through the usual process; they
are so freely available, we need Armageddon to sweep them out of the game from
time to time.  More importantly, the recovery process cannot properly handle
the configuration requirements.  The special cookies do have their own recovery
process which allows a player to continue pursuing the quest in the face of
multiple crashes, bugs, and other brouhaha; it's in the Calia Holiday Room.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  special_effect(num)

/*

Purpose:  effect called when this object is eaten.

Arguments:  number of cookies consumed.

Returns:  nothing.

*/

void
special_effect(int num)

{

    object *cookies;
    object tp = this_player();
    object holiday_room;
    string tp_pronoun = tp->query_pronoun();
    string tp_objective = tp->query_objective();
    string tp_possessive = tp->query_possessive();
    string tp_race = tp->query_race_name();
    string quest_text = "";
    int cookie_object_count;
    int quest_xp;
    int n;

    holiday_room = find_object(HOLIDAY_ROOM);

    if (!holiday_room)

    {

        holiday_room = call_other(HOLIDAY_ROOM, "this_object");

    }

    /*
     *  Eating the emperor completes the Gingerbread Quest, and it is the only 
     *  required element of this quest.  Acquiring the emperor cookie is a bit
     *  of work, but in the true spirit of the yule season, it's possible for a
     *  big player to get the cookie and simply give it to a smaller friend.
     *  Acquiring each of the emperor's subjects, the other 31 cookies, is
     *  equivalent to completing a separate little quest, and the experience
     *  acquired is proportional to the number of subjects held at the time the
     *  emperor is eaten, and assembling the complete set of subjects is worth
     *  extra points.

     *  The player will "eat" all cookies in his inventory when he completes
     *  the quest, but we can't be sure he has room for any of them but the
     *  emperor (this routine is only called when the emperor is successfully
     *  eaten.  Therefore, all other cookies are removed with the remove_object
     *  function, and the player gets quest xp rather than the nutritional
     *  value, which is meager anyway.    
     */

    if (Figure == "emperor")

    {

        if (tp->test_bit("Calia",
            GINGERBREAD_QUEST_GROUP, GINGERBREAD_QUEST_BIT))

        {

            /*
             *  Player has completed the quest before; considering the amount 
            of work that goes into getting the emperor cookie, I don't expect
            to see this routine used often.  */

            say("As " + QTNAME(tp) + " prepares to" +
                " stuff the gingerbread emperor into " + tp_possessive +
                " mouth, the emperor suddenly comes to life" +
                " and exclaims: it's quite the stout " + tp_race +
                " who can stomach more than one emperor!\n");

            write("As you prepare to stuff the gingerbread" +
                " emperor into your mouth, he suddenly comes" +
                " to life and exclaims: it's quite the stout " + tp_race +
                " who can stomach more than one emperor!\n");

            holiday_room->remove_quest_cookie(tp->query_real_name(),
                Cookie_Type);

            log_file("gingerbread_quest",
                ctime(time()) + " " + tp->query_name() +
                " gets no experience.\n");

        }

        else

        {

            /*
             *  What's important is the number of different cookies rather than 
             *  the count of any one kind, so all we need is a count of objects
             *  rather than the heap sizes.  The xp formula is 800 points for
             *  completing the quest plus 100 points per cookie, including the
             *  emperor, which adds up to a maximum of 4,000, and a 1,000 point
             *  bonus is added for having the complete set.    
             */

            cookies = filter(all_inventory(tp), &->is_calian_gingerbread());

            cookie_object_count = sizeof(cookies);

            /*
             *  Once I have the count, I remove the emperor from the array for 
             *  text formatting; the system will provide the "eat" message for
             *  the emperor, but I will process all the others.    
             */

            cookies -= ({this_object()});

            if (cookie_object_count == 32)

            {

                quest_xp = 5000;

            }

            else

            {

                quest_xp = cookie_object_count * 100 + 800;

            }

            if (cookie_object_count == 1)

            {

                /*
                 *  A player ate the emperor without having any of his 
                 *  subjects!  Obviously, somebody wasn't paying attention.    
                 */

                say("As " + QTNAME(tp) + " prepares to" +
                    " stuff the gingerbread emperor into " +
                    tp_possessive +
                    " mouth, the emperor suddenly comes to life" +
                    " and sneers: Only one cookie? A paltry feast" +
                    " indeed, and an ignominous end" +
                    " for a gingerbread emperor!\n");

                write("As you prepare to" +
                    " stuff the gingerbread emperor into your" +
                    " mouth, the emperor suddenly comes to life" +
                    " and sneers: Only one cookie? A paltry feast" +
                    " indeed, and an ignominous end" +
                    " for a gingerbread emperor!\n");

                write("You feel a little more experienced.\n");

            }

            else

            {

                if (cookie_object_count == 2 && cookies[0]->num_heap() == 1)

                {

                    /*
                     *  Only one subject for the emperor to command?  Better 
                     *  than none, I suppose, but still not much compared to
                     *  what's available.    
                     */

                    quest_text = cookies[0]->query_short();

                    say("As " + QTNAME(tp) + " prepares to" +
                        " stuff the gingerbread emperor into " +
                        tp_possessive +
                        " mouth, the emperor suddenly comes to life" +
                        " and says: Come with me, " + quest_text +
                        ", let not your emperor quit" +
                        " this realm unattended!\n" +
                        "The " + quest_text + " joins hands with" +
                        " the emperor and leads the way!\n" +
                        QCTNAME(tp) + " eats the " + quest_text +
                        " unexpectedly.\n");

                    write("As you prepare to" +
                        " stuff the gingerbread emperor into your" +
                        " mouth, the emperor suddenly comes to life" +
                        " and says: Come with me, " + quest_text +
                        ", let not your emperor quit" +
                        " this realm unattended!\n" +
                        "The " + quest_text + " joins hands with" +
                        " the emperor and leads the way!\n" +
                        "You eat the " + quest_text + " unexpectedly.\n");

                    cookies[0]->remove_object();

                    write("You feel a little more experienced.\n");

                }

                else

                {

                    say("As " + QTNAME(tp) + " prepares to" +
                        " stuff the gingerbread emperor into " +
                        tp_possessive +
                        " mouth, the emperor suddenly comes to life" +
                        " and exclaims: Where I go, so also go my" +
                        " subjects! Arise, ye gingerfolk," +
                        " and come with me!\n");

                    write("As you prepare to" +
                        " stuff the gingerbread emperor into your" +
                        " mouth, the emperor suddenly comes to life" +
                        " and exclaims: Where I go, so also go my" +
                        " subjects! Arise, ye gingerfolk," +
                        " and come with me!\n");

                    quest_text = COMPOSITE_DEAD(cookies);

                    say(capitalize(quest_text) + " join hands and" +
                        " frolic toward " + QTNAME(tp) + "'s mouth" +
                        " in a merry dance as they sing an old Calian" +
                        " yule cookie carol:\n\n" +
                        "    Life is merry and short when you're" +
                        " made of dough,\n" +
                        "    So into the " + tp_race +
                        " we go, we go,\n" +
                        "    Into the " + tp_race + " we go!\n\n" +
                        QTNAME(tp) + " suddenly," +
                        " unexpectedly, cheerfully," +
                        " perhaps even wantonly lets them cavort up " +
                        tp_possessive + " arms and into " +
                        tp_possessive + " gaping maw, and in" +
                        " quick succession " + tp_pronoun +
                        " eats " + quest_text + ".\n");

                    write(capitalize(quest_text) + " join hands and" +
                        " frolic toward your mouth" +
                        " in a merry dance as they sing an old Calian" +
                        " yule cookie carol:\n\n" +
                        "    Life is merry and short when you're" +
                        " made of dough,\n" +
                        "    So into the " + tp_race +
                        " we go, we go,\n" +
                        "    Into the " + tp_race + " we go!\n\n" +
                        "You suddenly find yourself" +
                        " unexpectedly, cheerfully," +
                        " perhaps even wantonly letting them cavort up" +
                        " your arms and into your gaping maw, and" +
                        " in quick succession you eat " + quest_text + ".\n");

                    n = sizeof(filter(cookies, &->remove_object()));

                    write("You feel more experienced!\n");

                }

            }

            /*
             *  Make sure we don't give the player more xp than he already 
             *  possesses, one of the key rules in designing a quest.    
             */

            quest_xp = min(quest_xp, tp->query_exp());

            tp->set_bit(GINGERBREAD_QUEST_GROUP, GINGERBREAD_QUEST_BIT);
            tp->add_exp(quest_xp);

            log_file("gingerbread_quest", ctime(time()) +
                " " + tp->query_name() +
                " solved with " + cookie_object_count +
                " cookies (" + quest_xp + "xp).\n");

            holiday_room->remove_quest_player(tp->query_real_name());

        }

    }

    else

    {

        /*
         *  Yes, if the player eats one of the special cookies, the recovery 
         *  record for that type of cookie is removed from the Holiday Room
         *  even if he has a dozen more.  The special cookies are for questing,
         *  not eating!    
         */

        holiday_room->remove_quest_cookie(tp->query_real_name(), Cookie_Type);

    }

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The gingerbread " + Figure + " " +
        ({"exudes an aroma",
        "reveals the scent",
        "smells"})[random(3)] +
        " of " + Smell_Text + " as well as freshly baked gingerbread.\n");

}

// Function:  cookie_or_biscuit()

/*

Purpose:  to amuse and/or annoy players; it identifies this object as a cookie
to most races but as a biscuit to hobbits.

Arguments:  none.

Returns:  string, "cookie" or "biscuit".

*/

string
cookie_or_biscuit()

{

    if (this_player()->query_race() == "hobbit")

    {

        return "biscuit";

    }

    else

    {

        return "cookie";

    }

}

// Function:  do_not_drop()

/*

Purpose:  prevents the dropping of this object if it's one of the valuable
special figures but allows the player to give it to someone else.  This routine
is only activated for special cookies (types 17-32).

Arguments:  none.

Returns:  0 if the transfer is allowed, string if not.

*/

mixed
do_not_drop()

{

    if (query_verb() == "give")

    {

        return 0;

    }

    else

    {

        return "The gingerbread " + Figure + " is far too rare" +
            " and valuable to be carelessly dropped or" +
            " put just anywhere!\n";

    }

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment; used
here to deploy the gingerbread_builder object when more than one gingerbread
man is left in a room.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    int room_type;
    object holiday_room;

    ::enter_env(ob_to, ob_from);

    /*
     *  This test makes sure that we don't generate runtime errors when the 
     *  object is moved around by any wizard commands or system functions,
     *  especially the split and merge heap routines.    
     */

    if (!ob_to)

    {

        return;

    }

    holiday_room = find_object(HOLIDAY_ROOM);

    if (!holiday_room)

    {

        holiday_room = call_other(HOLIDAY_ROOM, "this_object");

    }



    /*
     *  For the construction process to start, the environment must be a room, 
     *  must be dry, and must allow magic.    
     */

    room_type = ob_to->query_prop(ROOM_I_TYPE);

    if (ob_to->query_prop(ROOM_I_IS)
        &&
        !(room_type == ROOM_IN_WATER || room_type == ROOM_UNDER_WATER)
        &&
        !ob_to->query_prop(ROOM_M_NO_MAGIC))

    {

        holiday_room->add_location(ob_to);

    }

    /*
     *  If the cookie is one of the special types (17-32) and is entering a 
     *  player's inventory, it is a valuable quest object and will be
     *  remembered by the Holiday Room for recovery in the event of a crash or
     *  reboot (cookies are recovered in the bakery).  When the cookie leaves a
     *  player's inventory, it is removed from the room's memory.  Regular
     *  cookies, freely available in large quantities, are never recovered.

     *  Just a reminder:  cookie types are numbered 1-32, but the arrays that
     *  define them have elements 0-31, so we always use the raw number when
     *  recording the cookie type and subtract 1 when the cookie is
     *  configured.    
     */

    if (Cookie_Type >= 17)

    {

        if (interactive(ob_to))

        {

            holiday_room->add_quest_cookie(ob_to->query_real_name(),
                Cookie_Type);

        }

        /*
         *  In the spirit of the season, we only remove a cookie from the 
         *  recovery list if it is eaten or given away.  We also check to see
         *  if the player losing the cookie has any more of the same kind left
         *  in his inventory, since this function may be invoked when a player
         *  who has two cookies of the same kind gives one away.  There are
         *  some monsters and traps in Genesis that cause players to lose
         *  inventory by other means, and if that happens just before a crash
         *  or reboot, they'll get their special cookies back, if nothing
         *  else.    
         */

        if (ob_from && interactive(ob_from) &&
            !present("calia_cookie_" + val2str(Cookie_Type), ob_from) &&
            (interactive(ob_to) || query_verb()=="eat"))

        {

            holiday_room->remove_quest_cookie(ob_from->query_real_name(),
                Cookie_Type);

        }

    }

}

// Function:  create_cookie()

/*

Purpose:  provides all the usual services of create_food.  This is a base
object; the individual cookie files contain a create_food function that calls
this function with the required parameter

Arguments:  which_cookie, integer, varies from 1 to 32.

Returns:  nothing.

*/

void
create_cookie(int which_cookie)

{

    /*
     *  DESCRIPTION    
     */

    /*
     *  The first 16 figures are "regular" and are freely distributed as part 
     *  of the Calian Yule celebration.  The second 16 are "special" and only
     *  show up when specifically called for by the object that clones them,
     *  usually the gingerbread building (see building file).

     *  The second set is used only when a gingerbread building is broken.  The
     *  figures that appear are appropriate to the specific building, which can
     *  be one of the following:  hut, shack, bungalow, cabin, cottage, lodge,
     *  house, inn, monastery, cathedral, hamlet, village, town, city, kingdom,
     *  empire.    
     */

    string *figures =
        ({
        "baker preparing a many-layered decorated cake for",
        "blacksmith hammering out ornamental candlesticks to light up",
        "carpenter with a chest of wooden toys for",
        "cook preparing a sumptuous smorgasbord for",
        "dairyman hauling enormous cans of milk and cream for",
        "fishmonger bearing a great load of sea delicacies for",
        "gardener harvesting ripe vegetables for",
        "innkeeper opening his door wide to invite passers-by to",
        "jester singing, dancing, and cavorting in the spirit of",
        "lumberjack hauling a freshly-cut pine tree to",
        "miller balancing great sacks of sugar and flour on his way to",
        "poet diligently scribbling some new rhymes for",
        "potter busily turning out cups and plates for",
        "troubadour entertaining listeners with ballads and carols at",
        "vintner tramping grapes in a immense vat to make wine for",
        "wizard conjuring up magical decorations and treats for",

        // ---------- divider between regular and special figures ----------

        "hermit having a mug of mead with his simple meal in honor of",
        "hunter with a freshly-killed boar slung over his shoulders for",
        "whaler bringing his boat into port just in time for",
        "astrologer drawing charts of good and ill fortune for revelers at",
        "beekeeper ringed by colorful bees as if they were a wreath for",
        "rogue of unsavoury character, tempered somewhat by the spirit of",
        "merchant displaying his special wares on sale for",
        "wench in a tight and low-cut costume serving guests at",
        "abbot indulging in a goodly amount of drink during",
        "bishop conferring his blessing on boughs of holly for",
        "weaver creating an exquisite tapestry inspired by",
        "watchman counting the minutes till he goes off duty and can join",
        "crier proclaiming the beginning of",
        "mayor dressed in a gaudy yet festive frock-coat for",
        "king in majestic robes relishing the rich food and drink of",
        "emperor surrounded by symbols of power, wealth, comfort, and"
        });

    string *decorations =
        ({
        "is white on the baker's hat, nut-brown on her apron, and every" +
        " color of the rainbow on the cake.",
        "is dark chocolate-brown on the blacksmith himself and deep" +
        " indigo on his hammer and anvil; on top of these" +
        " dark colors are splashes of vivid gold, orange," +
        " and red representing sparks and fire.",
        "paints the carpenter in white pants and a red plaid" +
        " shirt; his tools and pile of raw wood are" +
        " caramel-colored, and the finished toys shimmer in a" +
        " myriad of glossy candy colors.",
        "is intricately detailed to show the cook in a white" +
        " hat and apron behind a blazing fire of orange and" +
        " red over which turns a plump honey-colored turkey.",
        "dresses the dairyman in comical, bright yellow" +
        " clothes that contrast garishly with the bright red of" +
        " his cheeks and the deep, brilliant green of his" +
        " heavy milk cans.",
        "on the fishmonger's broad cap and long coat is streaked" +
        " with white as if crusted with sea-salt, and she holds" +
        " a cinnamon-brown basket filled with purple" +
        " whelks, green oysters, yellow mussels, and red scallops.",
        "is shaped into little carrots, peppers," +
        " cauliflowers, tomatoes, and cucumbers, all in" +
        " their proper colors, that nearly hide the gardener" +
        " herself in a bright pink broad-brimmed hat.",
        "surrounding the figure of the innkeeper suggests a warm," +
        " cozy room lit in warm hues by a roaring fire, and his" +
        " rotund shape is wrapped in a white apron bearing the" +
        " multicolored stains of many meals and drinks.",
        "is neatly arranged into a gaudy plaid of green and red" +
        " all over the jester's clothes, punctuated by the" +
        " saffron yellow of the little round bells on his" +
        " cap and shoes.",
        "is cherry-red on the lumberjack's shirt and" +
        " licorice-black on his trousers, and he hauls a mint-green" +
        " tree with a chocolate-brown trunk.",
        "paints a portly but hard-working fellow indeed, red-faced from" +
        " carrying his heavy load of yellow flour-sacks" +
        " and blue sugar-sacks, one of which has sprung a leak" +
        " and leaves a trail of white behind him.",
        "envelopes the poet in a deep purple cloak that is partly" +
        " obscured by her cascade of long, brilliant red hair, and a" +
        " bit of her yellow shirt is visible where the cloak" +
        " has draped itself over the back of her cinnamon-brown chair.",
        "on every cup and plate is a different color and pattern," +
        " as if the potter cannot remember what her customers" +
        " have ordered, and she industriously works on a bright" +
        " white lump of clay that will be her next creation.",
        "that creates the troubadour's clothes is a" +
        " radiant pattern of lemon-yellow and strawberry-red, and" +
        " he plays a nut-brown lute to an audience roughly painted" +
        " in shades of blue, green, and brown.",
        "that forms the grapes, the vat, and the vintner himself is" +
        " a uniform deep purple, suggesting that he's been at" +
        " work for quite some time, but a decorative pattern" +
        " of intricate green holly leaves and red berries" +
        " borders the figures and makes the image quite" +
        " bright and cheery.",
        "depicts in implausibly fine detail a tiny wind-up toy wizard" +
        " in a purple military uniform behind a whirlwind" +
        " of multicolored Yule treats and decorations, and" +
        " in the background are even more extravagantly" +
        " detailed flurries of snowflakes - no two alike!",

        // ---------- divider between regular and special figures ----------

        "is mostly shades of brown, from light caramel on the" +
        " hermit's body to darker cinnamon and chocolate on his" +
        " robe and table, but a gleam of honey-gold lights up his" +
        " face and the mug of mead that he raises in honor" +
        " of the season.",
        "is coffee-colored on the boar's body except for" +
        " its bright white tusks, and while the hunter" +
        " wears a nut-brown grament, he is also festooned" +
        " with bright garlands of green holly leaves" +
        " and red berries.",
        "is deep cherry-red, suggesting the colors of sunset," +
        " around the whaler standing at the wheel of his vessel;" +
        " he is dressed in a bright lemon-yellow coat, and he" +
        " holds a harpoon on which is skewered not any sea-creature" +
        " but a vivid green wreath.",
        "is stretched into fine lines to make a variety" +
        " of obscure (and probably fanciful) astrological symbols" +
        " on both the astrologer's purple cloak and on" +
        " the pale yellow parchment he's holding.",
        "is dotted all over the cookie in little bee figures" +
        " that sparkle like jewels, and in the middle of the" +
        " swarm stands the beekeeper herself, clad from head to foot" +
        " in a bright orange protective cloak and hat.",
        "is mostly dark: coffee-black on the rogue's cloak" +
        " and hat, which obscures his face, and" +
        " vague pattern of chocolate-brown suggests other" +
        " shadowy figures, but in his hand is a gleam of green" +
        " and white, a sprig of mistletoe that is," +
        " perhaps, something this unsavory fellow is not" +
        " beyond putting to unscrupulous use.",
        "forms a deep chocolate-brown frock coat with" +
        " a licorice-black fur collar, as befits a" +
        " prosperous businessman, and surrounding him are the" +
        " wares he's made his fortune with:  mint-green" +
        " bottles of ale, caramel-colored kegs of beer, and" +
        " bundles of tobacco with multicolored labels.",
        "is layered thick and heavy all over, but especially" +
        " in two big dollops where a wench ought to have them," +
        " and a lacy licorice corset keeps it all in place," +
        " but the baker reponsible for this creation didn't forget to" +
        " add a few holly leaves and berries, which are about" +
        " all that comprise the rest of her costume.",
        "flows in a caramel-colored stream from a great mint-green" +
        " mug to the abbot's cherry red lips, which match" +
        " his nose; vanilla icing in little puffs of foam" +
        " dot the abbot's strawberry-pink face," +
        " chocolate-brown robe, and nut-brown sandals.",
        "is bright white on the bishop's robe and mitre" +
        " with hems and decorations of lemon-yellow; he holds a" +
        " bundle of deep green holly boughs in one hand and a" +
        " tall red candle in the other.",
        "icing forms a broad tapestry depicting Yule revelers" +
        " attired in all manner and color of holiday finery," +
        " and the weaver herself is fancifully attired in" +
        " fairy-tale style with a long, flowing gown that" +
        " looks like peach-pink silk and a high, pointed cap of" +
        " the same color from which hangs a gossamer train" +
        " that looks even longer than the tapestry",
        "fills the watchman's lantern with lemon-yellow" +
        " light that cascades over his bright blue cloak, and" +
        " he stands before a nut-brown hourglass, watching the" +
        " last few grains of golden sand count the minutes until the" +
        " end of his watch.",
        "makes a broad, chocolate road down which the crier" +
        " marches in his raspberry-red uniform; he" +
        " holds a cream-colored parchment before him, and" +
        " with his mouth open so wide that he seems ready to" +
        " swallow the parchment whole, he loudly proclaims the" +
        " opening of the Yule season to one and all.",
        "is used to comical effect as the mayor's" +
        " melancholy, thin-lipped face, drawn in pallid white" +
        " icing, contrasts with the festive attire that he" +
        " obviously wears only in deference to his official duties" +
        " during the Yule season.",
        "is thick and velvety as befits a king's attire," +
        " dominated by the colors of wine and whiskey" +
        " and trimmed in honey-gold; the king holds an overflowing" +
        " mug of ale in one hand and what appears to be an entire" +
        " side of beef in the other, and surrounding him are all" +
        " sorts of fish, game, breads, cakes, and drinks.",
        "is polished and dazzling white on the emperor's" +
        " ermine robe; a multi-tiered crown sculpted from" +
        " molten sugar, a masterpiece of the confectioner's" +
        " art, adorns his head, and neatly arrayed around him are" +
        " his orb and sceptre on either side, his coat of arms" +
        " above, and at his feet a pile of jewels, furs," +
        " porcelain, books, armaments, and other ornate" +
        " gifts from his subjects."
        });

    string *smells =
        ({
        "vanilla and hazelnuts",
        "chocolate and orange",
        "cranberry and caramel",
        "honey and orange",
        "lemon and mint",
        "cinnamon and grape",
        "strawberry and nectarine",
        "honey, chocolate, mint, caramel, and a myriad of fruits",
        "cranberry and mint",
        "cherry, licorice, and mint",
        "raspberry and lemon",
        "blueberry and cinnamon",
        "anise, sassafrass, pineapple, watermelon, peach, and apple",
        "lemon and strawberry",
        "fully mature grapes, plump and heavy with sugar",
        ({"lightning", "fireflies", "swamp gas", "moonbeams"})[random(4)] +
        " and " +
        ({"fairy dust", "turpentine", "absinthe", "dragon bones"})[random(4)],

        // ---------- divider between regular and special figures ----------

        "chocolate, caramel, and cinnamon",
        "coffee and hazelnuts",
        "cherry and lemon",
        "grape and lemon",
        "orange and honey",
        "coffee and chocolate",
        "chocolate and licorice",
        "licorice and rum",
        "caramel and mint",
        "vanilla and lemon",
        "peach and vanilla",
        "lemon and walnut",
        "chocolate and raspberry",
        "whisky and pistachio",
        "grape, honey, and oak",
        "vanilla, caramel, and brandy"
        });

    /*
     *  Cookie_Type varies from 1 to 32 and is set by the object file that 
     *  inherits the base cookie.  The arrays that configure the cookie contain
     *  elements numbered from 0 to 31, so subscripts ALWAYS include a -1.    
     */

    Cookie_Type = which_cookie;

    Figure = explode(figures[Cookie_Type - 1], " ")[0];

    set_name(Figure);       /*  first word of description  */
    add_name("cookie");     /*  alternate name for the Yanks  */
    add_name("biscuit");    /*  alternate name for the Brits  */
    add_name("_calia_gingerbread_cookie");
    add_name("calia_cookie_" + val2str(Cookie_Type));
    set_adj("gingerbread");
    set_short("gingerbread " + Figure);

    if (Figure == "blacksmith")

    {

        set_pshort("gingerbread blacksmiths");
        add_pname("blacksmiths");

    }

    if (Figure == "dairyman")

    {

        set_pshort("gingerbread dairymen");
        add_pname("dairymen");

    }

    if (Figure == "watchman")

    {

        set_pshort("gingerbread watchmen");
        add_pname("watchmen");

    }

    if (Figure == "wench")

    {

        set_pshort("gingerbread wenches");
        add_pname("wenches");

    }

    set_long("This is a gingerbread @@cookie_or_biscuit@@" +
        " decorated with multicolored icing that makes it look" +
        " like " + LANG_ADDART(figures[Cookie_Type - 1]) +
        " the Yule feast.\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_NO_STEAL, 1);

    /*
     *  Cookies in the range 17-32 are too valuable to drop.  Under most 
     *  circumstances the no_drop property also prevents giving, but in the
     *  yule season we want to encourage generosity, so the value is computed
     *  by a function that allows the "give" command to separate a mortal from
     *  his cookie.    
     */

    if (Cookie_Type > 16)

    {

        add_prop(OBJ_M_NO_DROP, "@@do_not_drop@@");
        add_prop(OBJ_M_NO_INS, "The gingerbread " + Figure + 
            " is far too rare and valuable to be carelessly dropped or" +
            " put just anywhere!\n");

    }

    /*
     *  Anyone who wastes his time appraising gingerbread men deserves to be 
     *  confused.    
     */

    add_prop(OBJ_I_VALUE, random(5000));

    add_prop(OBJ_M_NO_SELL, "Previously-owned gingerbread, no" +
        " matter how well cared for, has no resale value.\n");

    /*
     *  ITEMS    
     */

    /*
     *  We must make sure that the player can easily look at the icing on the 
     *  cookie of his choice, even though it's faster and generally more fun to
     *  simply "exa icing" and get the descriptions from every cookie in his
     *  inventory at once.    
     */

    add_item(({"icing", "multicolored icing",
        Figure + " icing", Figure + "'s icing", "icing on " + Figure,
        short() + " icing", short() + "'s icing", "icing on " + short()}),
        "On the gingerbread " + Figure +
        " the icing " + decorations[Cookie_Type - 1] + "\n");

    Smell_Text = smells[Cookie_Type - 1];  /* used in hook_smelled function */

    /*
     *  "uid" settings required for cloning.    
     */

    setuid();
    seteuid(getuid());

}
