// OBJECT:  wrapped guelph

    /* Calia Domain

    HISTORY

    [2004-12-23] Created from [C:\CALIA\YULEWARE\FRUITS\WRAPPED_.DOC] by
    Uhclem.

    PURPOSE

    This is an unpleasant gift consisting of a guelph wrapped with a ragged
    black bow.  The player may "address" the gift to another player.  Once
    addressed, the gift cannot be taken by anyone other than the recipient, the
    giver, or the Calian delivery npc (delivery service is optional). */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include "defs.h"

#define FILTER_MY_GIFTS(x) \
    filter(all_inventory(environment()), &operator(==)(x) @ &->to_whom())

// GLOBAL VARIABLES

string Gift_To;   /*  recipient's name (lowercase)  */
string Gift_From; /*  sender's name (lowercase)     */

// FUNCTIONS

// Function:  query_recover()

/*

Purpose:  prevent this object from ever being recovered since it must be
configured by the object which clones it to be of any use.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  to_whom()

/*

Purpose:  identify the person to whom this gift is addressed.

Arguments:  none.

Returns:  string containing the addressee's name (lowercase),
0 if the gift is not yet addressed.

*/

string
to_whom()

{

    return Gift_To;

}

// Function:  from_whom()

/*

Purpose:  identify the person who sent this gift.

Arguments:  none.

Returns:  string containing the sender's name (lowercase),
0 if the gift is not yet addressed.

*/

string
from_whom()

{

    return Gift_From;

}

// Function:  dont_take_me()

/*

Purpose:  if this gift has been addressed to someone, prevent anyone but the
recipient, sender, or the Great Gift Gopheroo from taking it.

Arguments:  none.

Returns:  string or 0.

*/

string
dont_take_me()

{

    string who_takes = this_player()->query_real_name();

    if (who_takes == Gift_To || who_takes == "gifteroo")

    {

        return 0;

    }

    else

    {

        return "This is " + capitalize(Gift_To) + "'s gift." +
            " If there are any here for you, 'take gifts'" +
            " will get them for you.\n";

    }

}

// Function:  take_gifts(my_gifts)

/*

Purpose:  let a player take all of his gifts without disturbing any gifts for
others that may be in the same room.

Arguments:  string indicating what the player is trying to take.

Returns:  0/1.

*/

int
take_gifts(string gifts)

{

    object tp = this_player();
    object *gift_array;
    object this_gift;
    string *gift_name_array = ({});
    int gift_count;
    int n;

    /*
     *  If the player tried to get a specific gift, let the OBJ_M_NO_GET 
     *  property handle the request.  Also ignore the command if this gift is
     *  not in the same room with the player.    
     */

    if (sizeof(explode(gifts, " ") - ({"a", "the", "gift", "gifts"})) ||
        environment() != environment(tp))

    {

        return 0;

    }

    /*
     *  Player has asked for "gift" or "gifts"; scan the area and give him one 
     *  or all of the gifts addressed to him (if any).    
     */

    gift_array = FILTER_MY_GIFTS(tp->query_real_name());
    gift_count = sizeof(gift_array);

    if (gift_count)

    {

        if (wildmatch("*gift", gifts))  /*  Player only asked for one gift  */

        {

            gift_count = 1;

        }

        for (n = 0; n < gift_count; n += 1)

        {

            gift_array[n]->move(tp);

        }

        if (gift_count == 1)

        {

            write("You take " + LANG_ADDART(gift_array[0]->short()) + ".\n");

            say(QCTNAME(tp) +
                " takes " + LANG_ADDART(gift_array[0]->short()) + ".\n");

        }

        else

        {

            write("You take " + COMPOSITE_DEAD(gift_array) + ".\n");
            say(QCTNAME(tp) + " takes " + COMPOSITE_DEAD(gift_array) + ".\n");

        }

    }

    else

    {

        write("Sorry, there aren't any gifts here addressed to you.\n");

    }

    return 1;

}

// Function:  address_gift(to_name)

/*

Purpose:  address this gift from this_player() to another.

Arguments:  array containing the recipient's name.

Returns:  0/1.

*/

int
address_gift(string to_name)

{

    object *palace_trees;
    object secure_master;
    object tp = this_player();
    string *long_text_array;
    string gift_record;
    int n;

    if (environment() != tp)

    {

        return 0;

    }

    if (!to_name)

    {

        notify_fail("Address the gift to whom?\n");
        return 0;

    }

    if (Gift_To)

    {

        notify_fail("The gift is already addressed" +
            " to " + capitalize(Gift_To) + "\n");

        return 0;

    }

    /*
     *  Get rid of capitals and any extraneous text such as the word "to".    
     */

    to_name =
        lower_case(explode(to_name, " ")[sizeof(explode(to_name, " ")) - 1]);

    if (to_name == tp->query_real_name())

    {

        write("What, address the gift to yourself?" +
            " Surely you want to get rid of this, and quickly!\n");

    }

    else

    {

        secure_master = find_object("/secure/master");

        if (tp->query_met(to_name) || tp->query_wiz_level())

        {

            /*
             *  The palace tree keeps a list of who has sent what kind of gifts 
             *  to whom.  If for any reason the tree has disappeared, clone
             *  one!    
             */

            palace_trees = object_clones(find_object(PALACE_TREE));

            if (!sizeof(palace_trees))

            {

                palace_trees = ({clone_object(PALACE_TREE)});

            }

            /*
             *  Unlike fruits, which are available in unlimited supply, there 
             *  is no restriction on the number of rare guelphes that any
             *  player may send to anyone else.  Guelphes are, in fact, most
             *  amusing (or horrifying) when eaten in large quantities.    
             */

            Gift_To = to_name;
            Gift_From = tp->query_real_name();
            long_text_array = explode(long(), ".");
            n = sizeof(long_text_array);

            long_text_array[n-2] = " This gift is addressed" +
                " to " + capitalize(Gift_To) +
                " from " + capitalize(Gift_From);

            set_long(implode(long_text_array, "."));
            add_prop(OBJ_M_NO_GET, "@@dont_take_me@@");

            write("The " + short() + " is magically inscribed:" +
                " to " + capitalize(Gift_To) +
                " from " + capitalize(Gift_From) + ".\n");

            say(QCTNAME(tp) +
                " addresses " + LANG_ADDART(short()) +
                " to " + capitalize(Gift_To) + ".\n");

        }

        else

        {

            write("You don't know anybody named " + capitalize(to_name) +
                ".\n");

        }

    }

    return 1;

}

// Function:  untie_bow(bow)

/*

Purpose:  untie the bow to get the guelph inside.

Arguments:  string containing 'bow'.

Returns:  0/1.

*/

int
untie_bow(string bow)

{

    object tp = this_player();
    object ribbon;
    object guelph;

    if (environment() != tp)

    {

        return 0;

    }

    /*
     *  Return 0 if the last word typed isn't "bow".    
     */

    if (!bow || !wildmatch("*bow", bow))

    {

        notify_fail("Untie what - the bow?\n");
        return 0;

    }

    ribbon = clone_object(YULEWARE + "ribbon_black");
    ribbon->move(tp);

    guelph = clone_object(FRUITS + "guelph");
    guelph->move(tp);

    write("You untie the crude bow on the " + short() +
        " to reveal the " + guelph->short() + " inside.\n");

    say(QCTNAME(tp) + " unties the crude bow on the " + short() +
        " to reveal the " + guelph->short() + " inside.\n");

    remove_object();
    return 1;

}

// Function:  hook_smelled()

/*

Purpose:  add truly atrocious smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The " + short() + " exudes " +
        ({
        "an irritating",
        "a revolting",
        "an acrid",
        "a nauseating",
        "a disgusting"
        })[random(5)] +
        " stench of " +
        ({
        "fresh vomit",
        "assorted entrails",
        "aged beef offal",
        "mildew",
        "bat droppings"
        })[random(5)] +
         " with " +
        ({
        "a subtle undercurrent",
        "a hint of",
        "a nearly imperceptible suggestion",
        "just a touch",
        "faint traces",
        "a vague suggestion",
        "an indistinct yet provocative insinuation"
        })[random(7)] +
        " of " +
        ({
        "yak sweat",
        "overturned outhouse",
        "ogre's armpit",
        "haggis",
        "pus"
        })[random(5)] +

        ".\n");

}

// Function:  init()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    object tp = this_player();

    ::init();

    add_action(untie_bow, "untie");
    add_action(take_gifts, "take");
    add_action(take_gifts, "get");

    if (!Gift_To)

    {

        add_action(address_gift, "address");

    }

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("gift");
    add_adj(({"dull", "gray"}));
    set_short("dull gray gift with a crude black bow");
    set_pshort("dull gray gifts with crude black bows");

    set_long("This gift - if indeed it deserves to be so called" +
        " - is prickly and smelly and unpleasant to behold. Yet" +
        " if you want, you can untie the bow and see what's inside.\n");

    add_item(({"bow", "black bow", "crude black bow", "ribbon"}),
        "Seriously, someone didn't put much time or effort" +
        " into wrapping this gift. The ribbon is crudely tied" +
        " into what may pass for a bow on a dark night in a" +
        " windstorm, and the ribbon from which it's made looks" +
        " like it was abruptly torn from the hide of something" +
        " that may shortly come back to collect it. You may not" +
        " want to be around when it does!\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_I_VOLUME, 121);
    add_prop(OBJ_I_NO_STEAL, 1);

    setuid();  /*  "uid" settings required for cloning fruit and ribbons. */
    seteuid(getuid());

}
