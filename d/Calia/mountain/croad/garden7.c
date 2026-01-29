// ROOM:  palace garden 7

    /* Calia Domain

    HISTORY

    [96-02-23] Created by Uhclem from [C:\CALIA\MOUNTAIN\CROAD\GARDEN7.DOC].

    PURPOSE

    This is one of 14 garden rooms surrounding Calia palace.  See comments in
    Room 1 for layout details. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "crdefs.h"
#include "cant_plant.c"
#include GARDEN_QUEST

#define CALIA_GARDEN_SITS "_calia_garden_sits_"

// GLOBAL VARIABLES

    /* These adjectives describe the fish in the pond. */

    string *Bunches =
        ({"a","a pair of","several","a few","a small school of","many"});

    string *Adjs =
        ({"tiny","fan-tailed","shiny","slender","sleek","sword-tailed"});

    string *Hues =
        ({"blue","golden","silvery","green","black-and-yellow striped"});

    string *Acts =
        ({"feeding","swimming lazily","circling","gliding","drifting"});

    /* These adjectives describe the flowers.  Each entry in the "flowers"
        array must have a corresponding entry in the FLOWER ITEMS section. */

    string *Brights =
        ({"bright pink","pale yellow","soft peach","delicate lavender"});

    string *Darks =
        ({"midnight blue","fiery crimson","deep purple","vibrant magenta"});

    string *Flowers =
        ({"roses", "irises", "dahlias", "jonquils", "lilies", "moonblooms",
        "fairy-slippers"});

    string Bunch = Bunches[(random(sizeof(Bunches)))];
    string Adj = Adjs[(random(sizeof(Adjs)))];
    string Hue = Hues[(random(sizeof(Hues)))];
    string Act = Acts[(random(sizeof(Acts)))];
    string Bright = Brights[(random(sizeof(Brights)))];
    string Dark = Darks[(random(sizeof(Darks)))];
    string Flower = Flowers[(random(sizeof(Flowers)))];

    /* The following statements extract the last word of the dark color
        description. */

    string *Colortext = explode(Dark, " ");
    string Colorword = Colortext[sizeof(Colortext) - 1];

// FUNCTIONS

// Function:  sit_down

/*

Purpose:  let a player sit on a bench

Arguments:  none

Returns:  0/1

*/

int
sit_down()

    {

    object tp = this_player();
    if(tp->query_prop(CALIA_GARDEN_SITS))

        {

        notify_fail("You have become so relaxed in this " +
            "tranquil environment that you " +
            "forgot you were already sitting!\n");

        return 0;

        }

    else

        {

        write("Ahhh... the curve of the bench feels like " +
            "it was made precisely to fit your " +
            "hindquarters.  You lean back, " +
            "feeling very relaxed and comfortable.\n");

        say(QCTNAME(tp) + " relaxes on one of the benches.\n");
        tp->add_prop(CALIA_GARDEN_SITS, 1);
        tp->add_prop(LIVE_S_EXTRA_SHORT, " resting on a bench");
        return 1;

        }

    }

// Function:  stand_up

/*

Purpose:  let a player rise from a bench

Arguments:  none

Returns:  0/1

*/

int
stand_up()

    {

    object tp = this_player();
    if(tp->query_prop(CALIA_GARDEN_SITS))

        {

        write("You rise from your comfortable seat on the bench.\n");
        say(QCTNAME(tp) + " rises from the bench.\n");
        tp->remove_prop(CALIA_GARDEN_SITS);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
        return 1;

        }

    else

        {
            write("You're not sitting!\n");
            return 1;

        }

    }

// leave_inv

/*

Purpose:  Called by system when room is exited.  Removes "sitting" effect if
player leaves from a sitting position..

Arguments:  object and destination

Returns  :::leave_inv

*/

leave_inv(object obj, object dest)

    {

    if(obj->query_prop(CALIA_GARDEN_SITS))

        {
            write("You rise abruptly from the bench.\n");
            say(QCTNAME(obj) + " rises abruptly from the bench.\n");
            obj->remove_prop(CALIA_GARDEN_SITS);
            obj->remove_prop(LIVE_S_EXTRA_SHORT);

        }

    return ::leave_inv(obj, dest);

    }

// break_bread

/*

Purpose:  If the player has a loaf of bread, break it into chunks that can be
fed to the fish.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
break_bread(string str)

    {

    int i;    /* general-purpose counter */
    object tp = this_player();
    object bread = present("bread", tp);

    /*  Next statement ensures that variable str contains string data to avoid
        type mismatch if player enters "break" with no argument.  */

    if(!stringp(str)) str = " ";

    if(!wildmatch("bread", str))

        {

        write("Break what?\n");
        return 1;

        }

    if(!objectp(bread))

        {

        write("You don't seem to have any bread to break.\n");
        return 1;

        }

    else

        {

        write("You break some bread into small chunks.\n");
        say(QCTNAME(tp) + " breaks some bread into small chunks.\n");

        i = (int) bread->num_heap();

        if(i == 1) bread->remove_object();
        else bread->set_heap_size(i-1);

        bread = clone_object(MOUNTAIN_OBJ + "bread_chunks.c");
        bread->move(tp);
        return 1;

        }

    }

// fill_with_water

/*

Purpose:  Contrary to what you might expect from the name of this function,
players are NOT allowed to fill bottles, glasses, watering cans, etc. from the
fish pond, and the fish themselves will make them aware of this rule if
necessary.  If the player types "fill <object>" for an object which he
possesses, this routine takes over.  Otherwise, a 0 is returned to let the fill
function in the object handle the command.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
fill_with_water(string str)

    {

    object tp = this_player();

    if(!stringp(str)) return 0;    /*  Player just typed "fill".  */

    if(objectp(present(str, tp)))    /*  Player typed "fill <object>".  */

        {

        write("You try to fill your " + str + " with water " +
            "from the fishpond, but an angry " +
            Hue + " fish pops its head out of the water and snarls " +
            "savagely at you!  " +
            "You decide it would be a good idea to get " +
            "your water elsewhere.\n");

        say(QCTNAME(tp) + " tries to fill the " + str +
            " with water from the fishpond but is startled " +
            "by an angry " +  Hue + " fish that " +
            "pops its head out of the water and snarls savagely at " +
            tp->query_objective() + " in defense of its home!\n");

        return 1;

        }

    else return 0;

    }

// feed_fish

/*

Purpose:  feeds bread to fish if it is broken into small chunks with
break_bread() and puts a seed on the ground which anyone may take.  Returns
various messages if player tries to feed something other than bread chunks.

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int

feed_fish(string str)

    {

    int i;    /*  General-purpose counter.  */
    object tp = this_player();
    object seed;
    object havebread = present("bread", tp);
    object havechunks = present("chunks", tp);

    /*  Next statement ensures that variable str contains string data to avoid
        type mismatch if player enters "feed" with no argument.  */

    if(!stringp(str)) str = " ";

    /* Player has to feed "fish".  Doesn't matter if player adds other words.
        */

    if(member_array("fish", explode(str, " ")) < 0)

        {

        write("Whom or what are you trying to feed?\n");
        return 1;

        }

    /* You need "chunks" of bread to feed the fish properly. If you don't have
        any chunks but you do have a loaf of bread, you will feed the whole
        loaf to the fish, but you won't be satisfying the quest requirements.
        */

    if(!objectp(havechunks))

        {

        if(!objectp(havebread))

            {

            write("You don't seem to have anything the " +
                "fish want to eat!\n");

            return 1;

            }

        else

            {

            write("You put a loaf of bread in the water " +
                "for the fish to eat.\n");

            i = (int) havebread->num_heap();

            if(i == 1) havebread->remove_object();
            else havebread->set_heap_size(i-1);

            say(QCTNAME(tp) + " puts a loaf of bread in the " +
            "water for the fish to eat.\n");

            tell_room(this_object(),
            "A large fish grabs the loaf of bread " +
            "and takes it down to the bottom of the " +
            "pond.  Several other " + Adj + " " + Hue +
            " fish circle near the surface, hoping to " +
            "find a few crumbs that may have been left behind.\n");

            write("You suspect that it might have been " +
            "more beneficial to the fish if you had " +
            "broken the bread into pieces before you " +
            "put it in the water.\n");

            say(QCTNAME(tp) + " contemplates loaves and fishes.\n");
            return 1;

            }

        }

    else

        {

        write("You toss the chunks of bread into the fishpond.\n");

        say(QCTNAME(tp) + " tosses some chunks of " +
        "bread into the fishpond.\n");

        i = (int) havechunks->num_heap();

        if(i == 1) havechunks->remove_object();
        else havechunks->set_heap_size(i-1);

        tell_room(this_object(),
        "A school of " + Adj + " " + Hue +
        " fish rushes to the surface of the " +
        "pond.  Their feeding frenzy churns the " +
        "water and splashes the gravel path.  Then, " +
        "just as suddenly, the fish return to the " +
        "depths, and the surface of the pond " +
        "is tranquil once again.\n");

        seed = clone_object(MOUNTAIN_OBJ + "seed");
        seed->set_adj(Colorword);
        seed->set_short("shiny " + Colorword + " seed");
        seed->move(this_object());

        tp->add_prop(CALIA_I_GARDEN_QUEST_STAGE, FED_FISH);
        return 1;

        }

    }

// Function:  put_bread

/*

Purpose:  intercepts a player's attempt to "give bread to fish" or "put bread
in pond" and suggests the correct syntax (feed fish).

Arguments:  string containing text typed by the player.

Returns:  0/1

*/

int
put_bread(string str)

    {

    object tp = this_player();

    /*  Next statement ensures that variable str contains string data to avoid
        type mismatch if player enters "give" with no argument.  */

    if(!stringp(str)) str = " ";

    if(wildmatch("* in pond", str))

        {

        write("The fish are confused.  Are you trying to feed them?\n");
        return 1;

        }

    else if(wildmatch("* to fish", str))

        {

        write("The fish do not accept your gift, " +
            "but they watch you curiously.  " +
            "They look like they are hoping you will feed them.\n");

        return 1;

        }

    /* If the player types a "put" or "give" command without indicating that
        the fish or the pond receives the item being moved, return a 0 so that
        the system will use the standard functions to interpret the action.  */

    else return 0;

    }

// Function:  init

/*

Purpose:  define commands available in this location (called by system when
room is entered)

Arguments:  none

Returns:  nothing

*/

void
init()

    {

    ::init();
    add_action(sit_down, "sit");
    add_action(stand_up, "stand");
    add_action(stand_up, "rise");
    add_action(break_bread, "break");
    add_action(feed_fish, "feed");
    add_action(put_bread, "give");
    add_action(put_bread, "put");
    add_action(fill_with_water, "fill");
    add_action(plant_seed, "plant");    /*  function in "cant_plant.c"  */

    }

// ROOM DEFINITION

void
create_room()

    {

    /* DESCRIPTION */

    set_short("Calia Palace Gardens, north side");

    set_long("This is the center of the garden.  There is " +
        "a circular fish pond here bordered by a gravel " +
        "path.  Around the path are several benches where you " +
        "may sit and relax for a while.  On the outer rim of " +
        "the path, a ring of " + Flower + " ranging in hue from " +
        Bright + " to " + Dark + " partitions the pond area " +
        "from the rest of the garden, and the entire area " +
        "is bathed in light reflected from " +
        "the tall crystalline palace.\n");

    /* EXITS */

    add_exit(CROAD + "garden6", "west", 0);
    add_exit(CROAD + "garden8", "east", 0);

    /* ITEMS */

    add_item(({"garden","gardens"}),
        "You find yourself surrounded by a ring of tall flowers " +
        "which enclose the fish pond.  The flowers provide some " +
        "seclusion for visitors who wish to spend a few quiet " +
        "moments sitting on one of the benches by the pond.\n");

    add_item(({"pond","water"}),
        "You notice some seeds floating on the surface of " +
        "the pond.  A bit below them you can just barely make out " +
        "a fish or two moving about slowly.\n");

    add_item(("fish"),
        "You try to see what's moving about in the pond, " +
        "and you discover that there are " + Bunch + " " + Adj +
        " " + Hue + " fish " + Act + " just below " +
        "the surface of the water.\n");

    add_item(({"seed","seeds"}),
        "There are some " + Colorword + " seeds floating " +
        "almost exactly in the center of the pond, the " +
        "one location in the garden where they're " +
        "out of your reach.\n");

    add_item(({"bench","benches"}),
        "The benches are made from vividly " +
        "colored wood characteristic of lumber cut from " +
        "the forests of East Calia.  Deep blue and violet " +
        "streaks in the grain and a high polish give " +
        "them a somewhat jewel-like finish.\n");

    add_item(({Flower,"flowers","flower"}),
        "The flowers grow unusually high and " +
        "thick, and their fragrance permeates the pond area.  " +
        "While most are a lovely shade of " + Bright + ", and " +
        "a number of them somewhat darker hues, one of the " + Flower +
        ", majestically robed in intense " + Colorword +
        ", commands your attention.\n");

    add_item(({"path","gravel"}),
        "The gravel path encircles the pond and cuts through " +
        "the ring of flowers, leading east and west to " +
        "other parts of the garden.\n");

    add_item(("plaque"),
        "\n" +
        "       HELP PRESERVE CALIA'S FLORAL TREASURES!\n" +
        "     This rare plant produces seeds at irregular\n" +
        "      intervals, and we can't always be here to\n" +
        "    collect them.  If you see a seed in this area,\n" +
        "      please plant it in a bare patch of ground.\n" +
        "        Thank you - The Landscaping Department\n\n");

    add_item(({"palace","colors","color","patches","light"}),
        "You stand before the tallest face of the palace, " +
        "a towering spire of gleaming crystal whose facets " +
        "reflect light in a cavalcade of rays " +
        "and arcs throughout the gardens.\n");

    /* FLOWER ITEMS */

    switch (Flower)

        {

        case "roses":

            add_item(({"rose", Colorword + " rose"}),
                "This magnificent " + Colorword + " rose " +
                "stands on the northern rim of the floral ring, " +
                "as if marking a cardinal point on " +
                "some mystic compass.  Just beneath it you " +
                "notice a small brass plaque that had " +
                "been obscured by the foliage.\n");

            break;

        case "irises":

            add_item(({"iris", Colorword + " iris"}),
                "The iris' ruffled " + Colorword + " " +
                "petals contrast vividly with the radiant " +
                "yellow of its interior.  Standing tall " +
                "against rows of somewhat duller flowers, " +
                "this iris gives the impression of a commander " +
                "in a plumed cap reviewing his troops.  Just " +
                "beneath it you notice a small brass plaque " +
                "that had been obscured by the foliage.\n");

            break;

        case "dahlias":

            add_item(({"dahlia", Colorword + " dahlia"}),
                "The dahlia's " + Colorword + " petals " +
                "shimmer iridescently in the sunlight, revealing " +
                "hints of all the colors of the rainbow.  " +
                "Just beneath it you notice a small brass " +
                "plaque that had been obscured by the foliage.\n");

            break;

        case "jonquils":

            add_item(({"jonquil", Colorword + " jonquil"}),
                "This jonquil's unusual and striking " +
                Colorword + " coloring reveals a complex " +
                "pattern of subtly shaded swirls " +
                "and vortices upon closer examination.  Just " +
                "beneath it you notice a small brass plaque " +
                "that had been obscured by the foliage.\n");

            break;

        case "lilies":

            add_item(({"lily", Colorword + " lily"}),
                "Such color intensity is rare in a lily, " +
                "and even more remarkable in this instance " +
                "because of the distinct " + Colorword + " " +
                "hue that dominates the petals.  The " +
                "edges are tinged with delicate traces " +
                "of white, perhaps a reminder of this " +
                "lily's kinship with the paler, " +
                "more common varieties.  Just beneath it you " +
                "notice a small brass plaque that had " +
                "been obscured by the foliage.\n");

            break;

        case "moonblooms":

            add_item(({"moonbloom", Colorword + " moonbloom"}),
                "This moonbloom has the typical shape of " +
                "this native Calian flower - a " +
                "hemisperical array of tightly pleated and " +
                "ruffled petals.  It is unusual both for its dazzling " +
                Colorword + " color and for its stature, for " +
                "instead of growing in clusters as most do, " +
                "this one stands alone on a tall leafy stalk.  " +
                "It exudes a piquant aroma, sweet but " +
                "spicy and reminiscent of cinammon.  Just beneath " +
                "it you notice a small brass plaque that had " +
                "been obscured by the foliage.\n");

            break;

        case "fairy-slippers":

            add_item(({"fairy-slipper", Colorword + " fairy-slipper"}),
                "Like all fairy-slippers, this one has a single " +
                "bloom perched atop a long, tapered stem.  " +
                "The large central petal is curved along its " +
                "length so that the edges just touch.  " +
                "The outside is vivid " + Colorword + ", and inside " +
                "it is a fluffy white lining.  The surrounding " +
                "petals overlap each other with no obvious seams " +
                "and are slightly curved, so that the entire flower " +
                "looks like a slipper laid on a round satin pillow.  " +
                "Just beneath it you notice a small brass plaque " +
                "that had been obscured by the foliage.\n");

            break;

        }

    }
