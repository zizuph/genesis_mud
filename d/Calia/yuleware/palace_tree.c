// OBJECT:  palace_tree

    /*

    Calia Domain

    HISTORY

    [1999-12-02] Created by Uhclem from [C:\CALIA\YULEWARE\PALACE_T.DOC].
    [2002/12/19] Uhclem added storage_keep_out room; never ever go in there.

    PURPOSE

    A Christmas decoration (and gift dispenser) for Calia palace.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

#define FILTER_BY_SHORT(x) \
    filter(deep_inventory(this_player()), &operator(==)(x) @ &->short())

// GLOBAL VARIABLES

object *Tree_Items = ({});    /* Inventory of this tree minus guelphes.   */
object Gifteroo;              /* He delivers the gifts.                   */
string *Gift_Records = ({});  /* Keeps list of addressed gifts.           */
int Num_fruits = 5;           /* Limits the number of varieties of fruit. */
int Guelph_Count = 0;         /* Number of guelphes dispensed.            */

// FUNCTIONS

// Function:  take_item(item_text)

/*

Purpose:  take a fruit or ribbon from the tree.

Arguments:  string specifying which item (can only take one at a time).

Returns:  0/1

*/

int
take_item(string item_text)

    {

    object tp = this_player();
    object *tp_inventory;
    object item;
    object tree;
    string item_short;
    int n;

    if (!parse_command(item_text, Tree_Items + ({this_object()}),
        " %o 'from' %o ", item, tree))

        {

        if (tree == this_object())

            {

            notify_fail(capitalize(query_verb()) +
                " what from the " + query_adj() +
                " " + query_name() + "?\n");

            }

        return 0;

        }

    /*  At this point we know that the player has identified an item that is
        available.  We don't let him have more than one of any unique object;
        that is, if he has a red apple and a yellow ribbon, he can take a green
        apple or blue ribbon but not another red apple or yellow ribbon.
        Note that query_short() is used to generate the messages rather than
        short(); this is to avoid problems associated with processing text
        generated from either a heap or an individual object.  */

    item_short = item->short();

    tp_inventory = FILTER_BY_SHORT(item_short);

    if (sizeof(tp_inventory))

        {

        if (environment(tp_inventory[0]) == tp)

            {

            write ("You already have " +
                LANG_ADDART(item->query_short()) + ".\n");

            }

        else

            {

            write ("You already have " +
                LANG_ADDART(item->query_short()) +
                " (look in your " +
                environment(tp_inventory[0])->short() + ").\n");

            }

        }

    else

        {

        n = member_array(item, Tree_Items);
        item = clone_object(explode(file_name(item), "#")[0]);

        if (item->query_name() == "ribbon")

            {

            item->configure_ribbon(Tree_Items[n]->query_ribbon_config());

            }

        else

            {

            item->configure_fruit(Tree_Items[n]->query_fruit_config());

            }

        item->move(tp);

        write("You " + query_verb() +
            " " + LANG_ADDART(item->query_short()) +
            " from the " + query_adj() + " " + query_name() + ".\n");

        say(QCTNAME(tp) + " " + query_verb() +
            "s " + LANG_ADDART(item->query_short()) +
            " from the " + query_adj() + " " + query_name() + ".\n");

        }

    return 1;

    }

// Function:  read_plaque(plaque)

/*

Purpose:  read the brass plaque.

Arguments:  string containing 'plaque'.

Returns:  0/1

*/

int
read_plaque(string plaque)

    {

    if (plaque && wildmatch("*plaque", plaque))

        {

        write ("\n" +
            "          Gifts which have been addressed may be dropped\n" +
            "             here for pickup by the delivery service.\n" +
            "          Addressed gifts dropped in other locations may\n" +
            "               only be retrieved by the addressees.\n\n" +
            "           Note: Armageddon eats all undelivered gifts.\n\n");

        return 1;

        }

    else

        {

        notify_fail("Read what - the plaque?\n");
        return 0;

        }

    }

// Function:  shake_tree(tree)

/*

Purpose:  shake the tree.

Arguments:  string containing 'tree'.

Returns:  0/1

*/

int
shake_tree(string tree)

    {

    object guelph;

    if (tree && wildmatch("*tree", tree))

        {

        write("You shake the " + short() + ".\n");
        say(QCTNAME(this_player()) + " shakes the " + short() + ".\n");

        tell_room(environment(),
            "The fruits and ribbons " +
            ({
            "sparkle and shimmer as they reflect the glow of" +
            " the tree itself",
            "swing wildly among the swaying branches",
            "bob and wheel, flashing their vivid colors as they duck" +
            " in and out of the tree",
            "oscillate, pendulate, even vacillate as the" +
            " tree's rocking sets them into motion",
            "gyrate in response to the movement of the tree but" +
            " do not fall off"
            })[random(5)] + ".\n");

        if (!random(Guelph_Count))

            {

            guelph = clone_object(FRUITS + "guelph");
            guelph->move(environment());
            Guelph_Count += 1;

            tell_room(environment(), "A " + guelph->query_short() +
                " falls from the " + short() + "! It must" +
                " have been put in there " +
                ({
                "by someone who does not approve of yule celebrations",
                "by a kroug infiltrator",
                "as a practical joke",
                "as part of a diabolical anti-yule plot",
                "by mistake",
                })[random(5)] + ".\n");

            }

        return 1;

        }

    else

        {

        notify_fail("Shake what - the tree?\n");
        return 0;

        }

    }

// Function:  add_gift_record(record)

/*

Purpose:  add a record to the addressed gift list.

Arguments:  string specifying who addressed what to whom.

Returns:  nothing

*/

void
add_gift_record(string record)

    {

    Gift_Records += ({record});

    /*  Reset the guelph dispensing routine after every 100 gifts are
        adressed.  */

    if (!(sizeof(Gift_Records) % 100))

        {

        Guelph_Count = 0;

        }

    }

// Function:  check_gift_record(record)

/*

Purpose:  see if a specific person has already addressed a gift with a specific
description to a specific recipient.

Arguments:  a specific string in the form
    "<Sender> <giftcolor> + <bowcolor> -> <Recipient>".

Returns:  1 if such a gift has already been addressed, 0 if not.

*/

int
check_gift_record(string record)

    {

    if (member_array(record, Gift_Records) != -1)

        {

        return 1;

        }

    else

        {

        return 0;

        }

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

    ::init();
    add_action(shake_tree, "shake");
    add_action(take_item, "take");
    add_action(take_item, "get");
    add_action(read_plaque, "read");

    if (!objectp(Gifteroo))

        {

        Gifteroo = clone_object(YULEWARE + "gifteroo");
        Gifteroo->move(environment());
        Gifteroo->start_delivery(this_object(), environment());

        tell_room(environment(),
            capitalize(LANG_ADDART(Gifteroo->short())) +
            " wanders in, peering around curiously" +
            " and sniffing eveything.\n");

        }

    }

// OBJECT DEFINITION

void
create_object()

    {

    /* VARIABLES */

    /*  Hues and glazes are applied to the fruits.  These two arrays are always
        used together, so be sure that they have the same number of elements
        and that these elements match up in a reasonable way.  */

    string *hues = ({"glistening golden", "brilliant silver",
        "sparkling copper", "pastel yellow", "glossy pink",
        "luminous red", "sumptuous purple", "luxuriant indigo",
        "lustrous bronze"});

    string *glazes = ({"wildflower honey", "ginger root",
        "sassafrass extract", "maple sugar", "rose nectar",
        "beet sugar", "distilled strawberry",
        "black grape essence", "molasses"});

    /*  The number and order of elements in the following arrays can be changed
        according to whim.  The colors are applied to ribbons that can be tied
        around the fruits so that they may be given as presents.  */

    string *fruits = ({"pear", "plum", "apple", "nectarine",
        "fig", "orange", "lemon", "lime"});

    string *colors = ({"cheerful bright blue", "striking deep blue",
        "festive bright green", "vivid deep green",
        "vibrant bright red", "noble deep red",
        "sunny bright yellow", "flamboyant deep yellow",
        "radiant pure white"});

    string text;
    object item;
    int m = 0;
    int n = 0;

    setuid();
    seteuid(getuid());

    /*  RANDOMIZE ARRAYS  */

    for (m = 0; m < 10; m += 1)

        {

        /*  Subtracting and adding an array element in one statement moves it
            to the last position in the array (only works if there are no
            duplicate elements).  */

        n = random(sizeof(fruits));
        fruits = fruits - ({fruits[n]}) + ({fruits[n]});

        n = random(sizeof(colors));
        colors = colors - ({colors[n]}) + ({colors[n]});

        /*  hues and glazes are kept in synch so that the flavors are always
            appropriate to the color.  */

        n = random(sizeof(hues));
        hues = hues - ({hues[n]}) + ({hues[n]});
        glazes = glazes - ({glazes[n]}) + ({glazes[n]});

        }

    /*  REDUCE ARRAYS  */

    /*  To prevent people from standing around all day trying to decide what
        fruit to match up with what ribbon, limit the choices with Num_fruits,
        but then just for fun, add a striped ribbon.  */

    hues = hues[1..Num_fruits];
    glazes = glazes[1..Num_fruits];
    fruits = fruits[1..Num_fruits];

    colors = colors[2..Num_fruits] +
        ({
        ({"red and white",
        "red and green",
        "green and white",
        "gold and white",
        "red and gold",
        "green and gold"
        })[random(6)] +
        " striped"});

    /*  DESCRIPTION  */

    set_name("tree");
    add_adj(({"fir", "spruce", "pine", "balsam", "cedar"})[random(5)]);

    set_short(({"magnificent", "grand", "majestic", "opulent",
        "splendid"})[random(5)] + " " + query_adj() +
        " tree festooned with ribbons and glazed fruits");

    set_long("You see no candles or lamps of any kind on the tree," +
        " yet it glows almost as brightly as if it were ablaze," +
        " and the good cheer it spreads through the room warms you" +
        " as well as any hearth. Ribbons and glazed fruits of all" +
        " kinds and colors cover the tree almost entirely." +
        " The tree is supported by a sturdy cast-iron stand, and" +
        " affixed to the stand is a brass plaque that you can read.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_M_NO_GET, "Not this tree! Go cut down and decorate" +
        " one of your own!\n");

    add_prop(OBJ_I_WEIGHT,  50000);
    add_prop(OBJ_I_VOLUME, 150000);
    add_prop(OBJ_I_VALUE, 10000000);

    /*  ITEMS  */

    text = "The tree contains many ";
    m = Num_fruits - 1;

    for (n = 0; n < Num_fruits; n += 1)

        {

        add_item(({fruits[n], hues[n] + " " + fruits[n],
            fruits[n] + "s", hues[n] + " " + fruits[n] + "s"}),
            "All traces of skin, stem, and seed have been removed from" +
            " the " + fruits[n] + "s, and the succulent fruit" +
            " has been enrobed in a " + hues[n] +
            " glaze made from " + glazes[n] + " and other sweets.\n");

        add_item(({colors[n] + " ribbon", colors[n] + " ribbons"}),
            "The ribbons have a shiny satin surface and are the" +
            " prefect size to tie around one of the fruits to" +
            " make an exquisite holiday gift.\n");

        if (n == m)

            {

            text += "and " + hues[n] + " " + fruits[n] + "s.\n";

            add_item(({"fruit", "fruits", "glazed fruit", "glazed fruits",
                "fruit on tree", "fruits on tree",
                "fruit on " + query_adj() + " tree",
                "fruits on " + query_adj() + " tree",
                "glazed fruit on tree", "glazed fruits on tree",
                "glazed fruit on " + query_adj() + " tree",
                "glazed fruits on " + query_adj() + " tree"}),
                text);

            }

        else

            {

            text += hues[n] + " " + fruits[n] + "s, ";

            }

        }

    add_item(({"ribbon", "ribbons",
        "ribbon on tree", "ribbons on tree",
        "ribbon on " + query_adj() + " tree",
        "ribbons on " + query_adj() + " tree"}),
        "The tree contains many " + implode(colors[1..m], " ribbons, ") +
        " ribbons, and " + colors[0] + " ribbons.\n");

    add_item(({"glow", "enigmatic glow",
        "color", "colors", "myriad colors"}),
        "An enigmatic glow emanates from the tree itself" +
        " and illuminates the fruits and ribbons," +
        " cheerfully reflecting their myriad colors.\n");

    add_item(({"stand", "cast-iron stand", "iron", "cast iron"}),
        "The stand is made of cast iron and massive enough" +
        " to easily support such an enormous tree. It bears a" +
        " brass plaque that you can read.\n");

    add_item(({"plaque", "brass plaque"}),
        "The brass is well polished to reflect the glow of" +
        " the tree, yet not so bright that you would have" +
        " any trouble reading it.\n");

    /*  CREATE INVENTORY OF FRUITS AND RIBBONS  */

    m = sizeof(hues);

    for (n = 0; n < m; n += 1)

        {

        item = clone_object(FRUITS + fruits[n]);
        item->move("/d/Calia/yuleware/storage_keep_out");
        item->configure_fruit(({hues[n], glazes[n], fruits[n]}));
        Tree_Items += ({item});

        item = clone_object(YULEWARE + "ribbon");
        item->configure_ribbon(colors[n]);
        Tree_Items += ({item});

        }

    }
