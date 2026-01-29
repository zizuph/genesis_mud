// OBJECT:  wrapped fruit

    /* Calia Domain

    HISTORY

    [1999-12-23] Created from [C:\CALIA\YULEWARE\FRUITS\WRAPPED.DOC] by Uhclem.
    [2001-12-29] Uhclem corrected code exempting wizards from having to know
    the people to whom they address gifts.

    PURPOSE

    This is a glazed fruit tied up with a bow.  It is made by a player who
    takes a fruit and a ribbon from the yule tree in Calia palace and ties one
    around the other.  The player may "address" the gift to another player.
    Once addressed, the gift cannot be taken by anyone other than the
    recipient, the giver, or the Calian delivery npc (delivery service is
    optional). */

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

string Hue;       /*  glaze color                   */
string Glaze;     /*  glaze taste & smell           */
string Fruit;     /*  what kind of fruit            */
string Color;     /*  bow color                     */
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

    if (!gifts)
    {
        return 0;
    }
    
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
            " That's hardly the right attitude!\n");

    }

    else

    {

        secure_master = find_object("/secure/master");

        if (tp->query_met(to_name) || tp->query_wiz_level())

        {

            if (secure_master->exist_player(to_name))

            {

                /*
                 *  The palace tree keeps a list of who has sent what kind of 
                 *  gifts to whom.  If for any reason the tree has disappeared,
                 *  clone one!    
                 */

                palace_trees = object_clones(find_object(PALACE_TREE));

                if (!sizeof(palace_trees))

                {

                    palace_trees = ({clone_object(PALACE_TREE)});

                }

                /*
                 *  Mortals cannot address two identical gifts to a single 
                 *  recipient in the same day; wizards may address any number
                 *  of gifts to anyone they please.    
                 */

                gift_record = tp->query_name() +
                    ", " +
                    implode(explode(short(), " ") -
                    ({"gift", "with", "a", "bow"}), " ") +
                    ", " + capitalize(to_name);

                if (!palace_trees[0]->check_gift_record(gift_record) ||
                    tp->query_wiz_level())

                {

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

                    palace_trees[0]->add_gift_record(gift_record);

                }

                else

                {

                    write("You've already addressed " +
                        LANG_ADDART(Hue) + " gift with " +
                        LANG_ADDART(Color) + " bow to " +
                        capitalize(to_name) + " today; you don't" +
                        " want to give the same gift to" +
                        " the same person again!\n");

                }

            }

            else

            {

                /*
                 *  Prevent players from addressing gifts to NPCs or wizards 
                 *  from addressing gifts to nonexistent characters.    
                 */

                write("Address the gift to " + capitalize(to_name) +
                    "? Sorry, there's no such name on the" +
                    " official delivery list.\n");

            }

        }

        else

        {

            write("You don't know anybody named " + capitalize(to_name) +
                ".\n");

        }

    }

    return 1;

}

// Function:  configure_gift(*hue_glaze_fruit_color)

/*

Purpose:  specify the physical attributes of this object.

Arguments:  array containing four strings.

Returns:  nothing.

*/

void
configure_gift(string *hue_glaze_fruit_color)

{

    Hue = hue_glaze_fruit_color[0];
    Glaze = hue_glaze_fruit_color[1];
    Fruit = hue_glaze_fruit_color[2];
    Color = hue_glaze_fruit_color[3];

    set_short(Hue + " gift with a " + Color + " bow");
    set_pshort(Hue + " gifts with " + Color + " bows");
    add_adj(explode(Hue, " "));

    set_long("This is a traditional Calian delicacy," +
        " a shell of " + Hue + " glaze just translucent enough for you" +
        " to see the peeled " + Fruit + " inside, and it has" +
        " an unusual (for " + LANG_ADDART(Fruit) + ") but appetizing" +
        " smell. A " + Color + " bow is tied on top;" +
        " you can simply untie it when you want to" +
        " eat the " + Fruit + ". You may address this" +
        " gift to someone you know; if you do, you can safely" +
        " leave it somewhere for the recipient to find" +
        " or arrange to have it delivered.\n");

    add_item(({"peeled " + Fruit, Fruit}),
        "You can't see much detail through the glaze," +
        " but it looks delicious.\n");

    add_item(({"bow", "top"}),
        "You can untie the bow if you want to eat the " + Fruit + ".\n");

}

// Function:  untie_bow(bow)

/*

Purpose:  untie the bow to get the fruit inside.

Arguments:  string containing 'bow'.

Returns:  0/1.

*/

int
untie_bow(string bow)

{

    object tp = this_player();
    object item;

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

    write("You untie the " + Color + " bow on the " + Hue +
        " gift to reveal the glazed " + Fruit + " inside.\n");

    say(QCTNAME(tp) + " unties the " + Color +
        " bow on the " + Hue +
        " gift to reveal the glazed " + Fruit + " inside.\n");

    item = clone_object(YULEWARE + "ribbon");
    item->configure_ribbon(Color);
    item->move(tp);

    item = clone_object(FRUITS + Fruit);
    item->configure_fruit(({Hue, Glaze, Fruit}));
    item->move(tp);

    remove_object();
    return 1;

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

    write("The " + short() + " exudes " +
        ({
        "an enticing",
        "a sensuous",
        "an alluring",
        "a savory",
        "a stimulating"
        })[random(5)] +
        " aroma of " + Glaze + " with " +
        ({
        "a subtle undercurrent",
        "a hint of",
        "a nearly imperceptible suggestion",
        "just a touch",
        "faint traces",
        "a vague suggestion",
        "an indistinct yet provocative insinuation"
        })[random(7)] +
        " of " + Fruit + ".\n");

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
    set_short("fruit with a bow tied on top");

    set_long("This fruit is full of bugs! Seriously, something" +
        " has gone wrong if you see this description. Please" +
        " file a bug report.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_I_VOLUME, 121);
    add_prop(OBJ_I_NO_STEAL, 1);

    setuid();  /*  "uid" settings required for cloning fruit and ribbons. */
    seteuid(getuid());

}
