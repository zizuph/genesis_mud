// OBJECT:  gelan_tree

    /*

    Calia Domain

    HISTORY

    [04/12/23] Created by Uhclem from [C:\CALIA\YULEWARE\GELAN_TR.DOC].

    PURPOSE

    A Christmas decoration for Gelan.  It is covered with glowing ornaments
    that are actually tiny flasks of magic elixirs.  Players can acquire
    seasonal variations on standard emotes by drinking combinations of
    elixirs.  By special request, a few black ribbons are available.  They can
    be used to tie around guelphes (dispensed by palace_tree) so that they may
    be sent (via gopheroo) as gifts.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

// GLOBAL VARIABLES

object *Tree_Items = ({});    /* Inventory of this tree minus ribbons.     */
int Num_Flasks = 6;           /* Limits the number of varieties of flasks. */
int Ribbon_Count = 0;         /* Number of ribbons dispensed.              */

// FUNCTIONS

// Function:  take_item(item_text)

/*

Purpose:  take something from the tree.

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
                " what from the " + short() + "?\n");

        }

        return 0;

    }

    /*
     *  Players can take as many as they want of whatever they want from this 
     *  tree, although they can only take one item at a time.  This is the
     *  first time I've devised such an accommodating dispenser.  Holding too
     *  many flasks, however, can be a problem all by itself; see flask code
     *  for details.  A new flask is cloned for the player and configured with
     *  the same attributes as the one he chose from the tree so that the
     *  tree's inventory never diminishes.    
     */

    item_short = item->short();

    n = member_array(item, Tree_Items);
    item = clone_object(explode(file_name(item), "#")[0]);
    item->configure_flask(item_short);

    item->move(tp);

    write("You " + query_verb() +
        " " + LANG_ADDART(item->short()) +
        " from the " + short() + ".\n");

    say(QCTNAME(tp) + " " + query_verb() +
        "s " + LANG_ADDART(item->short()) +
        " from the " + short() + ".\n");

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
            "       Happy Yule from Raspatoon, who is not responsible\n" +
            "      for death or dismemberment (accidental or otherwise)\n" +
            "      resulting from use of, contact with, or proximity to\n" +
            "     this tree, the decorations for which he admits to have\n" +
            "                 had some small hand in making.\n\n");

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

    object ribbon;

    if (tree && wildmatch("*tree", tree))

    {

        write("You shake the " + short() + ".\n");
        say(QCTNAME(this_player()) + " shakes the " + short() + ".\n");

        tell_room(environment(),
            "The " + query_adj(1)[2] + " tree " +
            ({"wriggles", "slithers", "writhes"})[random(3)] + " " +
            ({
            "as if trying to escape from its stand",
            "in an alarmingly reptilian manner",
            "lithely in its stand, more like a rubber plant than" +
            " a " + query_adj(1)[2] + " tree"
            })[random(3)] +
            " and the luminous ornaments " +
            ({
            "seem to merge briefly in a swirl of multifarious" +
            " blends of their colors",
            "whirl about with such energy that they" +
            " momentarily appear to separate from the tree and" +
            " then regoup on the branches like a swarm of bees" +
            " returning to its hive",
            "suddenly blink out all at once, only to" +
            " gradually resume glowing at their previous intensity"
            })[random(3)] +
            ".\n");

        if (!random(Ribbon_Count))

        {

            ribbon = clone_object(YULEWARE + "ribbon_black");
            ribbon->move(environment());
            Ribbon_Count += 1;

            tell_room(environment(), "A " + ribbon->short() +
                " falls from the " + short() + ".\n");

        }

        return 1;

    }

    else

    {

        notify_fail("Shake what - the tree?\n");
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

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     * VARIABLES   
     */

    /*
     *  There are nine different hues for the flasks.  Because each hue 
     *  represents a different numeric value that's used to compute the effects
     *  of combinations of elixirs, the contents of this list should not be
     *  changed.    
     */

    string *adjs = ({"lustrous", "burnished", "vivid", "frosted", "faceted",
        "glossy", "pale", "sparkling", "translucent"});

    string *colors = ({"purple", "blue", "aquamarine", "green", "yellow-green",
        "yellow", "orange", "red", "pink"});

    string *flasks = ({});

    string color_word;
    string text = "The tree is covered with ";
    object item;
    int l = 0;
    int m = 0;
    int n = 0;

    setuid();
    seteuid(getuid());

    /*
     *  RANDOMIZE ARRAYS    
     */

    l = sizeof(adjs);

    for (m = 0; m < 10; m += 1)

    {

        /*
         *  Subtracting and adding an array element in one statement moves it 
         *  to the last position in the array (only works if there are no
         *  duplicate elements).    
         */

        n = random(l);
        adjs = adjs - ({adjs[n]}) + ({adjs[n]});

        n = random(l);
        colors = colors - ({colors[n]}) + ({colors[n]});

    }

    /*
     *  DESCRIPTION    
     */

    set_name("tree");
    add_adj(({"gaily decorated", "little"}));
    add_adj(({"fir", "spruce", "pine"})[random(3)]);

    set_short(implode(query_adj(1), " ") +
        " tree covered with glowing ornaments");

    set_long("The " + implode(query_adj(1), " ") +
        " is covered with countless luminous ornaments, so" +
        " many that their combined glow seems to envelope the" +
        " tree in a swirling multicolored cloud. Although" +
        " the tree radiates heat as well as light, it's" +
        " a beckoning warmth that you instinctively recognize" +
        " as innocuous and welcoming. A sturdy wooden stand" +
        " holds the tree securely in an upright position.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_M_NO_GET, "The glow surrounding the tree seems" +
        " to make it inexplicably slippery; no matter how you" +
        " try, you can't seem to get a grip on it!\n");

    add_prop(OBJ_I_WEIGHT,  5000);
    add_prop(OBJ_I_VOLUME, 15000);
    add_prop(OBJ_I_VALUE, 100);

    /*
     *  ITEMS    
     */

    m = Num_Flasks - 1;

    for (n = 0; n < Num_Flasks; n += 1)

    {

        item = clone_object(FLASKS + "flask");
        item->configure_flask(adjs[n] + " " + colors[n]);
        item->move(STORAGE_ROOM);
        Tree_Items += ({item});

        add_item(({colors[n] + " ornament", colors[n] + " ornaments",
            adjs[n] + " ornament", adjs[n] + " ornaments",
            colors[n] + " flask", colors[n] + " flasks",
            adjs[n] + " flasks", adjs[n] + " flasks",
            adjs[n] + " " + colors[n] + " ornament",
            adjs[n] + " " + colors[n] + " ornaments",
            adjs[n] + " " + colors[n] + " flask",
            adjs[n] + " " + colors[n] + " flasks"}), item->long());

        if (n == m)

        {

            text += "and " + item->short() + "s.\n";

            add_item(({"ornament", "ornaments",
                "luminous ornament", "luminous ornaments",
                "ornament on tree", "ornaments on tree",
                "ornament on " + query_adj(1)[1] + " tree",
                "ornaments on " + query_adj(1)[1] + " tree",
                "luminous ornament on " + query_adj(1)[1] + " tree",
                "luminous ornaments on " + query_adj(1)[1] + " tree",}),
                text);

        }

        else

        {

            text += item->short() + "s, ";

        }

    }

    add_item(({"glow", "enigmatic glow",
        "color", "colors", "myriad colors"}),
        "An enigmatic glow emanates from the tree itself" +
        " and illuminates the fruits and ribbons," +
        " cheerfully reflecting their myriad colors.\n");

    add_item(({"stand", "wooden stand", "sturdy wooden stand"}),
        "The stand is simple in design but well crafted so" +
        " that there's no danger of the tree falling over. A" +
        " small brass plaque is attached that is easy to read by" +
        " the light of the ornaments.\n");

    add_item(({"plaque", "brass plaque"}),
        "The brass is well polished to reflect the glow of" +
        " the ornaments.\n");

}
