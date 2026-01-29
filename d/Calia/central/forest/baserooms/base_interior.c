// ROOM:  base_interior.c

    /*  Calia Domain

    HISTORY

    [99-06-21] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_INT.DOC].

    PURPOSE

    This file is the inherited base for rooms in the interior of the Great
    Central Forest. "Interior" is defined as being surrounded on all sides by
    other forest rooms - any forest room that does not have exits in all eight
    compass directions to other forest rooms must not use this base! It
    contains the function for generating long descriptions and adding typical
    forest features. Since many, perhaps even most forest rooms look alike, it
    adds to the player's interest to present some variation in the
    descriptions. Some of these items can be used to advantage during combat.

    Separate base rooms define terrain at the edge of the forest and forest
    rooms which connect to other areas.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define EXIT_FATIGUE_WITH_TRAIL         2
#define EXIT_FATIGUE_WITHOUT_TRAIL     12

// GLOBAL VARIABLES

string This_Location;

// FUNCTIONS

// Function:  enter_inv(object, from_object)

/*

Purpose:  tell players in the room when something falls from above.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    string from_room;

    ::enter_inv(ob, from);

    if (from) from_room = file_name(from);
    else return;  /* Prevents error for objects cloned directly into room. */

    if (living(ob)
        ||
        (from_room != LOW + This_Location
        && from_room != MIDDLE + This_Location
        && from_room != UPPER + This_Location)) return;

    if (ob->query_heap() && (ob->query_heap_size > 1))

    {

        tell_room(this_object(), capitalize(ob->plural_short()) +
            " fall from the " + query_prop(FOREST_TREE_TYPES)[0] + " tree.\n");

    }

    else

    {

        tell_room(this_object(),
            capitalize(LANG_ADDART(ob->query_short())) +
            " falls from the " + query_prop(FOREST_TREE_TYPES)[0] +
            " tree.\n");

    }

}

// Function:  start_forest_combat()

/*

Purpose:  put the forest_combat_effect object in the room when fighting begins.
The object is only needed if it isn't here already.

Arguments:  none.

Returns: 0.

*/

int
start_forest_combat()

{

    object to = this_object();
    object combat_effect;

    if (!present(GROUND_COMBAT_OBJECT, to))

    {

        combat_effect = clone_object(GROUND_COMBAT_OBJECT);
        combat_effect->move(to);

    }



    return 0;

}

// Function create_pit()

/*

Purpose:  put a pit in the room if it doesn't already exist. This function is
primarily used either at room definition time (for permanent pits) or by the
falling_object, which may create a pit as the result of a player's fall from a
tree.

Arguments:  none.

Returns: nothing.

*/

void
create_pit()

{

    string *pit_line =
        ({"The ground has sunken here, forming a" +
        " deep, steep-sided pit, but there is plenty of" +
        " room to walk around it, so there is" +
        " little chance you'll accidentally fall in.",
        "Between two of the trees you can see that a" +
        " deep pit has formed; it looks to be of natural" +
        " origin, as it is smooth and uniformly lined with" +
        " leaves and vines, and there are no shovel-marks or" +
        " other evidence of digging.",
        "A deep pit lies nearly hidden in the shadows, but" +
        " you spot it before you get close enough to fall in.",
        "A small patch of the soft ground has given way," +
        " and a narrow but deep pit has formed here."});

    /*
     *  Never create a pit under either of the following conditions: 
     *  1.  A pit already exists in the room.
     *  2.  A trail exists in the room.
     *  Checking for a pit is easy - just look for one in the local combat
     *  inventory.  To see if there's a trail, check the room exit fatigue
     *  level.    
     */

    if (member_array("pit", query_prop(CALIA_COMBAT_INVENTORY)) != -1
        || query_tired_exit(0) == EXIT_FATIGUE_WITH_TRAIL)
        return;

    set_long(explode(query_long(), "\n")[0] + " " +
        pit_line[random(sizeof(pit_line))] + "\n");

    add_prop(CALIA_COMBAT_INVENTORY,
        query_prop(CALIA_COMBAT_INVENTORY) + ({"pit"}));

    add_item(({"pit", "deep pit"}), "@@pit_description@@");
    add_exit(BELOW + This_Location, "n", 1, 1);

}

// Function:  tree_plural_check(tree)

/*

Purpose:  determine if "s" or "es" is needed to make a tree name plural.

Arguments:  string containing the name of the tree.

Returns: string containing "s" or "es".

*/

string
tree_plural_check(string tree)

{

    if (wildmatch("*h", tree) || wildmatch("*s", tree)) return "es";
    else return "s";

}

// Function:  pit_description()

/*

Purpose:  return pit description, which varies by awareness of the viewer and
contents of the pit.

Arguments:  none.

Returns: string containing pit description.

*/

string
pit_description()

{

    string desc = "The pit edge is roughly oval in shape, and you can" +
        " ascertain that the sides are steep, smooth, and evenly" +
        " covered with vegetation. It's difficult to see just" +
        " how deep it is, but from where you're standing it" +
        " looks like a long way down. Fortunately, it's in" +
        " an obvious spot, so you don't have to worry" +
        " about falling into it while you're walking around.\n";

    object pit = find_object(BELOW + This_Location);
    object *contents;
    int m;
    int n;

    if (!pit || this_player()->query_skill(SS_AWARENESS) < 25) return desc;

    contents = FILTER_LIVE(all_inventory(pit));

    m = sizeof(contents);

    for (n=0; n<m; n+=1)

    {

        if (!contents[n]->query_prop(OBJ_I_HIDE))

        {

            desc = desc + QCNAME(contents[n]) + " is in the pit.\n";

        }

    }

    this_player()->catch_msg(desc);

    return "";

}

// Function:  create_forest_interior(location, rooms, trees, trails, slope)

/*

Purpose:  Generate a short description, long description, items, and exits for
an interior forest room.

Arguments:  The filename of the room being created (required), an array of
adjacent room filenames (required), an array of tree types (required) and an
optional third argument consisting either of an array of trail directions or a
single-element array containing the string "pit". The filename must be in
simplest form: no directory names or ".c" should be attached.

The adjacent room filenames must be in the same format and arranged in the
array starting with the room to the north and proceeding clockwise to
northwest.

At least one tree type must be supplied, more are permissible; the first tree
in the array is the dominant variety in the room. Tree types must be lower case
strings such as "oak", "pine", "fir", etc. Supplying more than three types will
excessively complicate the descriptive text, but on the outside chance that
more may occasionally be needed, the functions will process up to five without
error. To indicate trails, up to 8 compass directions may be supplied as an
array of strings; these strings indicate the directions in which trails lead
from the current room. Alternately, an array with the single element "pit"
indicates that a pit (natural sinkhole) is present in the room. Rooms with
trails never have pits, and vice-versa; only one pit is permitted per room.
Every GROUND_LEVEL room with a pit must have a corresponding pit room on the
BELOW level. If neither trail directions nor a pit is specified, the room will
be supplied with a standard set of combat-related features.

Use the optional parameter "slope" to make this room a hilside or hilltop.  The
value is a string containing either the word "hill", which indicates a hilltop
(level ground), or a compass direction, which indicates the direction of the
downward slope.

Returns: nothing. This function calls standard room functions set_long,
set_short, and add_item to create its descriptions. It also adds three
properties to the room, FOREST_LOCATION, FOREST_ADJACENT_ROOMS, and
FOREST_TREE_TYPES for use by other functions. The proper use of this function
in a room file looks like:

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine"}));

          or

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine"}), ({"northwest"}));

          or

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine"}), ({"east", "north"}));

          or

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine", "spruce"}), ({"pit"}));

          or (on a hillside sloping down to the east)

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine", "spruce"}), ({"pit"}), "east");

          or (on a hilltop)

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine", "spruce"}), ({"pit"}), "hill");

          or (on a hilltop with no trail or pit)

          create_forest_interior("filename", ({array_of_filenames}),
              ({"pine", "spruce"}), 0, "hill");

*/

varargs void
create_forest_interior(string location, string *adjacent_rooms,
    string *trees, string *trails, string slope)

{

    int exit_fatigue = EXIT_FATIGUE_WITHOUT_TRAIL;

    /*
     *  The following items which may affect combat are available in every 
     *  interior forest room. Depending upon the results of the routines that
     *  add descriptive text to the room, this array may receive more entries
     *  later in this function. The final value is stored in property
     *  CALIA_COMBAT_INVENTORY.    
     */

    string *combat_inventory = ({"log", "branch", "vine", "animal"});

    string text;  /*  Becomes the room long description.  */
    string s;  /*  General-purpose string. */
    int m;  /*  General-purpose counter. */
    int n;  /*  General-purpose counter. */

    /*
     *  The following arrays contain descriptive strings which will be chosen 
     *  at random and assembled into the variable "text" which eventually
     *  becomes the long description of the room.   
     */

    /*
     *  Text from tree_line and add_tree_line will be combined as dictated by 
     *  the number of trees varieties supplied. The code supports up to 5
     *  varieties in any room, which should be plenty since the different trees
     *  are purely for decoration.   
     */

    string *tree_line =
        ({"Dense stands of " + trees[0] + " trees dominate this area",
        "Towering " + trees[0] + " trees form a shadowy canopy overhead",
        "Massive " + trees[0] + " trees stand like the columns of" +
        " a grand cathedral",
        "Countless ancient " + trees[0] + " trees rise to lofty heights",
        "Here monumental " + trees[0] + " trees dominate the landscape",
        "Here massive " + trees[0] + " trees have risen" +
        " to astonishing heights",
        "Tremendous " + trees[0] + " trees reach for the heavens",
        capitalize(trees[0]) + " trees grow to astonishing heights here",
        capitalize(trees[0]) + " trees of ancient age have" +
        " grown to astounding heights here",
        "Tallest of the titans here are the " + trees[0] +
        " trees, growing so prodigiously as to defy the" +
        " ground's ability to support them",
        "Stupendous " + trees[0] + " trees thrust skyward",
        "Towering " + trees[0] + " trees cluster tightly around" +
        " you like sentries confronting an intruder",
        "Innumerable legions of majestic " + trees[0] + " trees" +
        " have claimed this ground as their dominion",
        "Mighty " + trees[0] + " trees grow in dense stands here",
        "Colossal " + trees[0] + " trees rise straight and parallel" +
        " to each other as if they were the pillars of the sky"});

    string *add_tree_line =
        ({".",
        ", dwarfing other trees nearby.",
        " while other varieties try to grow in their shade.",
        " while a number of other varieties grow in their shade.",
        ", eclipsing a surprising number of other varieties growing here."});

    string *dark_line =
        ({"The darkness is uniform and stretches on as far as you can" +
        " see, but enough green-tinged light filters through the" +
        " treetops so that you can discern nearby objects.",
        "The light in this area is subdued and slightly tinted green," +
        " but you can still see well enough to avoid walking into" +
        " the trees.",
        "Shadows obscure some detail as you look around, but you can" +
        " find your way reasonably well in the little light" +
        " that is available.",
        "Most sunlight is blocked by the dense canopy overhead," +
        " but enough filters through for you to find your way" +
        " through the trees.",
        "Wherever you look the forest looks equally dark, dense," +
        " and dormant, as the massive trees and thick vegetation" +
        " absorb light and conceal motion."});

    string *air_line =
        ({"The air is cool and moist, and little sunlight reaches" +
        " the ground through the dense foliage.",
        "The air is heavy and dank with the smell of damp bark" +
        " and vegetation, and there is little movement in the" +
        " pervasive shade of the dense trees.",
        "Under the shade of the towering trees the air is humid and" +
        " filled with pungent odors, particularly the smell of the" +
        " damp " + trees[0] + " bark.",
        "Dampness and darkness pervade the atmosphere, as the" +
        " tightly packed trees keep sunlight out and retain moisture" +
        " at ground level.",
        "Between the closely-spaced " + trees[0] + " trees, where" +
        " breezes seldom venture, the air is heavy with moisture" +
        " and the odor of the vegetation."});

    string *action_line =
        ({"Somewhere in the depths of the forest a songbird's voice" +
        " pierces the gloom.",
        "A tenuous ray of sunlight occasionally breaks through the" +
        " dark canopy and makes the beads of moisture on the" +
        " vegetation sparkle like jewels.",
        "You can hear some flying insects buzzing lazily in your" +
        " vicinity, but in the shadowy tracts beneath the trees you" +
        " can't quite see them.",
        "In addition to the moisture hanging in the air, a few drops" +
        " of water fall from the treetops, perhaps some recent" +
        " rain finally working its way through the canopy.",
        "An occasional rustle from the forest depths suggests that" +
        " a small animal may be foraging nearby.",
        "A soft rustling from above suggests that a gentle breeze" +
        " may be caressing the treetops, but here at ground level the" +
        " air is quite still.",
        "The cheery voices of songbirds echo throughout the" +
        " forest depths, though the singers remain well hidden from" +
        " view somewhere in the shadows.",
        "Somewhere nearby a tiny frog peeps its mating call, hidden" +
        " from view by the lush vegetation.",
        "A monentary breeze wafts through the trees, but it does" +
        " nothing to diminish the intense humidity.",
        "The stillness and ponderous dimensions of the trees lend this" +
        " area an air of timelessness, as if it has remained" +
        " unchanged for thousands of years."});

    string *puddle_line =
        ({"A small puddle reflects the dim light and ripples in" +
        " response to your footsteps.",
        "As you walk, you send ripples across the surface of a" +
        " small puddle just barely noticeable in the shadows.",
        "Some of the ground has sunken a bit, and water has collected" +
        " in a shallow puddle that sparkles when a bit of sunlight" +
        " grazes its surface.",
        "The vegetation disappears underwater in one small patch" +
        " where a shallow puddle has formed; its surface ripples" +
        " slightly in response to your footsteps."});

    string *flower_line =
        ({"A clump of wildflowers adds a vivid spray of color even" +
        " though light is scant here.",
        "Some wildflowers have managed to bloom here despite the" +
        " choking effect of the vines and the shortage of sunlight.",
        "Between the trees you can see a bunch of wildflowers," +
        " their beauty squandered in the dark recesses of the forest.",
        "Despite the pervasive shadows, a cluster of wildflowers makes" +
        " a vivid display in front of one of the" +
        " majestic " + trees[0] + " trees."});

    string *trail_line =
        ({"A well-beaten trail offers better support than" +
        " the surrounding vine-covered terrain.",
        "While the most of the vegetation-covered ground is" +
        " only barely passable on foot, a trail has been blazed" +
        " that provides easy travel.",
        "Although the ground is soft and offers uneasy footing," +
        " multitudes of prior travellers have beaten a" +
        " firm path between the trees to ease passage through" +
        " the forest.",
        "A trail has been carved through the forest that offers" +
        " better footing than the soft carpet of plants.",
        "Travellers have trampled a firm trail across the soft ground" +
        " and made walking a bit easier for those who would follow."});

    string *first_line;
    string *ground_line;

    This_Location = location;

    if (slope)

    {

        if (slope == "hill")

        {

            combat_inventory += ({"hill", "root"});

            first_line =
                ({"You are on a hilltop deep within a vast forest.",
                "The forest surrounds you on this hilltop," +
                " at once both magnificent and menacing.",
                "You stand on a hilltop under the dense foliage" +
                " of a great forest.",
                "The great forest surrounds you on all sides" +
                " on this hilltop.",
                "The immense forest seems to close in ever" +
                " tighter around you on this hilltop."});

            ground_line =
                ({"The ground here is higher than in other nearby" +
                " areas of the forest, and the carpet of leaves" +
                " and vines is interrupted in many places by" +
                " thick and twisted tree roots.",
                "The dampness penetrates the soft ground," +
                " which is somewhat elevated here and covered not" +
                " only with a thick carpet of vegetation but" +
                " also with numerous roots that protrude" +
                " above ground level.",
                "Tightly packed creeping vines cover the moist" +
                " ground and wrap around the many tree" +
                " roots that protrude underfoot.",
                "A dense coat of leaves and vines provides a" +
                " fair surface for walking over the soft" +
                " ground, although the many protruding tree" +
                " roots make walking somewhat laborious.",
                "The characteristic leaves and vines of Calia," +
                " hardy even in the dense shade, thrive among" +
                " the many twisted tree roots that protrude" +
                " from the ground here."});

            add_item(({"ground", "hilltop", "hill"}),
                "The ground here is higher and a bit drier than" +
                " in other nearby parts of the forest," +
                " although still rather moist and yielding," +
                " and twisted tree roots protrude in many" +
                " places through the carpet of leaves and vines.\n");

            add_item(({"twisted root", "root", "twisted roots", "roots",
                "twisted tree root", "tree root", "twisted tree roots",
                "tree roots", "carpet"}),
                "The thick carpet of vegetation ripples over" +
                " the twisted tree roots that protrude from" +
                " the ground here. While the footing is firm" +
                " in most places, the unevenness caused by" +
                " the roots impedes walking.\n");

        }

        else

        {

            combat_inventory += ({"slope", "root"});
            add_prop(FOREST_SLOPE, slope);

            first_line =
                ({"You are on a hillside deep within a vast forest.",
                "The forest surrounds you on this hillside," +
                " at once both magnificent and menacing.",
                "You stand on a hillside under the dense foliage" +
                " of a great forest.",
                "The great forest surrounds you on all sides" +
                " on this hillside.",
                "The immense forest seems to close in ever" +
                " tighter around you on this hillside."});

            ground_line =
                ({"The ground here slopes down to the " + slope +
                ", and the carpet of leaves and vines is" +
                " interrupted in many places by thick and" +
                " twisted tree roots.",
                "The dampness penetrates the soft ground, which" +
                " slopes down to the " + slope + " and is covered" +
                " not only with a thick carpet of vegetation" +
                " but also with numerous roots that" +
                " protrude above ground level.",
                "Tightly packed creeping vines cover the moist" +
                " ground and wrap around the many tree" +
                " roots that protrude underfoot.  The ground is lower" +
                " to the " + slope + " than in other directions.",
                "A dense coat of leaves and vines provides a" +
                " fair surface for walking over the soft" +
                " ground, although the many protruding tree" +
                " roots and the downward slope to the " + slope +
                " make walking somewhat laborious.",
                "The characteristic leaves and vines of Calia," +
                " hardy even in the dense shade, thrive among" +
                " the many twisted tree roots that protrude" +
                " from the ground, which slopes down toward" +
                " the " + slope + "."});

            add_item(({"ground", "hillside", "hill", "slope"}),
                "The ground slopes down toward the " + slope +
                ", and the trees have tangles of roots" +
                " exposed on their downhill sides.\n");

            add_item(({"tangle", "root", "tangles", "roots", "sides",
                "downhill sides", "side", "downhill side"}),
                "While the ground is inclined, the roots have grown" +
                " at an even level all around each tree so that" +
                " about half of them protrude through" +
                " the carpet of vegetation.\n");

        }

    }

    else

    {

        first_line =
            ({"You are deep within a vast forest.",
            "The forest surrounds you, at once both" +
            " magnificent and menacing.",
            "You stand under the dense foliage of a great forest.",
            "In every direction the forest seems to" +
            " continue without end.",
            "The great forest surrounds you on all sides.",
            "The immense forest seems to close in ever" +
            " tighter around you.",
            "The great forest closes in on all sides, and you can't" +
            " help but wonder whether it means to embrace" +
            " or besiege you.",
            "The forest stretches on in all directions as far as" +
            " you can see.",
            "The forest continues on endlessly with little" +
            " variation to distinguish one direction from another.",
            "The vast forest surrounds you not only on all sides but" +
            " with dense foliage above and thick vegetation below.",
            "The inner reaches of the forest cloak you" +
            " in concealing shadows.",
            "You stand within a forest of incalculable" +
            " depth and breadth.",
            "The forest extends in every direction," +
            " boundless and unchanging.",
            "All around you the immense forest" +
            " stretches without variation.",
            "The immense forest continues for unimaginable" +
            " distances on every side."});

        ground_line =
            ({"Soft, soggy ground covered by dense leaves and vines" +
            " spreads out beneath the trees like a luxuriant carpet.",
            "The characteristic leaves and vines of Calia, hardy even in" +
            " such shady conditions, form a plush covering over the" +
            " mucky ground.",
            "The dampness penetrates the ground, making it soft and" +
            " yielding to even a modest weight, but the dense coat of" +
            " leaves and vines provides support for walking.",
            "Tightly-packed creeping plants, the famous leaves and vines" +
            " of Calia, provide reasonable support over what would" +
            " otherwise be ground too soft for walking.",
            "Underfoot the ground is moist and somewhat spongy, far better" +
            " for growing plants than for walking."});

        add_item(({"ground", "terrain", "vegetation", "plants"}),
            "A dense mat of vegetation, composed of creeping vines" +
            " and leafy plants, covers the soft and spongy ground. In" +
            " addition to the vigorously growing plants, the area is" +
            " strewn with decaying sticks, leaves, and needles.\n");

    }

    /*
     *  Since a trail adds a couple of lines to the room description, we start 
     *  with a shorter text when a trail is present.    
     */

    if (trails) text =
        first_line[random(sizeof(first_line))] + " " +
        tree_line[random(sizeof(tree_line))] +
        add_tree_line[random(sizeof(trees))] + " " +
        dark_line[random(sizeof(dark_line))] + " " +
        ground_line[random(sizeof(ground_line))];

    else text =
        first_line[random(sizeof(first_line))] + " " +
        tree_line[random(sizeof(tree_line))] +
        add_tree_line[random(sizeof(trees))] + " " +
        air_line[random(sizeof(air_line))] + " " +
        dark_line[random(sizeof(dark_line))] + " " +
        action_line[random(sizeof(action_line))] + " " +
        ground_line[random(sizeof(ground_line))];

    /*
     *  Check for missing exits. If any are missing, write an error to the log 
     *  but let the room compile anyway.   
     */

    if (member_array(0, adjacent_rooms) > -1)

    {

        log_file("errors", "Design error: " + This_Location +
            " does not have 8 exits.\n");

    }

    /*
     *  The following items are randomly strewn throughout the forest. Some 
     *  rooms get them, some don't, and the distribution changes upon every
     *  reboot - just like a real forest!    
     */

    if (!random(10))

    {

        text = text + " " + puddle_line[random(sizeof(puddle_line))];
        combat_inventory = combat_inventory + ({"puddle"});

        add_item(({"puddle", "shallow puddle", "small puddle", "water"}),
            "There doesn't seem to be anything unusual about this" +
            " puddle. It looks as if recent rain has collected" +
            " here because the already soggy ground" +
            " simply could not absorb it quickly.\n");

    }

    if (!random(10))

    {

        /*
         *  Note: wildflowers currently have no combat effect. But if you have 
         *  a good idea for one, be sure to send it to me!   
         */

        text = text + " " + flower_line[random(sizeof(flower_line))];

        add_item(({"wildflower", "wildflowers"}),
            "This is a generic wildflower description. I'll add" +
            " a variety of pickable flowers later.\n");

    }

    /*
     *  Before any exits are added, make sure none will be obvious.   
     */

    set_noshow_obvious(1);

    /*
     *  If the room has a trail, add the appropriate sentence to the 
     *  descriptive text. If not, then add special forest-floor combat
     *  features. My reasoning is that if you're fighting on the trail, you
     *  have a clear and level surface so your footing is sure and you're not
     *  xlose enough to the trees for them to have any effect on the outcome.
     *  Off the trail, however, there are random terrain elements which may
     *  present an advantage to the clever player.   
     */

    if (pointerp(trails) && strlen(trails[0]) > 3)

    {

        /*
         *  This routine is invoked if compass directions are provided in the 
         *  array "trails". Naturally, no abbreviations are allowed so that we
         *  can rely on the (length>3) formula working to detect anything other
         *  than the word "pit". String variable "s" will be loaded with text
         *  appropriate to the trails provided.   
         */

        text = text + " " + trail_line[random(sizeof(trail_line))];
        exit_fatigue = EXIT_FATIGUE_WITH_TRAIL;
        n = sizeof(trails);

        switch (n)

        {

            /*
             *  A trail that simply ends in the middle of the forest is a 
             *  pretty strange trail, but just in case someone ever needs one,
             *  a routine to generate its description is provided.   
             */

            case 1:
                s = " The trail begins here and leads " + trails[0];
                break;

            case 2:

                s = " The trail leads " + trails[0] +
                    " and " + trails[1];

                break;

            /*
             *  An intersection of forest trails in every compass direction is 
             *  also fairly absurd, but I put in a routine to process it just
             *  in case someone ever finds a logical need for such a room.   
             */

            case 8:
                s = " Trails lead in all directions from here";
                break;

            default:

                s = " Trails lead " +
                    implode(trails[1..(n-1)], ", ") + ", and " +
                    trails[0];

                break;

        }

        add_item(({"trail", "trails"}),
            "The trail is the result of countless footsteps beating" +
            " down the vegetation and preventing its regrowth" +
            " along a meandering route between the trees. Over" +
            " time, the ground along this route has become so" +
            " hard-packed that it resists moisture, so it is much" +
            " more pleasant to walk on than the surrounding terrain.\n");

        add_item(({"vine", "vines"}),
            "Vines grow on either side of the path. They are covered" +
            " with a variety of intensely colored leaves, ranging" +
            " mostly from brilliant green to a deep green-edged indigo.\n");

        set_short("In a forest of " + trees[0] + " trees." + s);
        text = text + s + ".";

    }

    else

    {

        /*
         *  If there are no trails, then all we need for the room short 
         *  description is the generic text. Horses cannot traverse the soft
         *  and vine-covered ground of the forest interior if a trail has not
         *  been blazed.   
         */

        set_short("In a forest of " + trees[0] + " trees");
        add_prop(ROOM_I_NO_ALLOW_STEED, 1);

        /*
         *  While the following statements add descriptive text for the forest 
         *  features affecting combat, the functions controlling those effects
         *  are contained in the forest_combat object.   
         */

        add_item(({"log", "logs"}),
            "There are some old logs here, mostly obscured by" +
            " the live vegetation. Their sizes vary, but all are too" +
            " large to be carried away, and their rotten condition" +
            " makes them useless anyway.\n");

        add_item(({"vine", "vines"}),
            "Vines criss-cross the ground, forming a tight mesh" +
            " that supports your weight above the soft and soggy" +
            " soil. They are covered with a variety of intensely" +
            " colored leaves, ranging mostly from brilliant green to" +
            " a deep green-edged indigo.\n");

    }

    /*
     *  The long description (and by now it's pretty long) for the room is 
     *  finally complete!  Append the carriage return and load it into the
     *  proper place.   
     */

    text = text + "\n";
    set_long(text);

    /*
     *  Add the descriptive items for individual tree varieties. The first 
     *  variety is required and is the dominant type in this room.   
     */

    s = tree_plural_check(trees[0]);

    add_item(({trees[0] + " trees", trees[0] + s}),
        "The lofty " + trees[0] + s + " tower over everything else" +
        " in sight. Smooth and straight, they have no branches" +
        " near the ground; instead, their limbs are clustered" +
        " high overhead, where they mesh to form a nearly" +
        " opaque canopy.\n");

    /*
     *  The dominant tree variety in each forest interior room has one 
     *  climbable specimen which leads to the LOW level. LOW level is about
     *  halfway up the trunk of a large tree and leads upward to MIDDLE level.
     *    
     */

    add_item(({"tree", "nearest tree",
        trees[0],
        trees[0] + " tree",
        "first " + trees[0],
        "first " + trees[0] + " tree",
        "nearest " + trees[0],
        "nearest " + trees[0] + " tree"}),
        "@@tree_description@@");

    add_item(({"bark", "gnarled bark", "thick vines", "thick vine"}),
        "The bark of is rugged and gnarled, and strong, thick" +
        " vines have wrapped around it providing a good" +
        " surface for climbing.\n");

    add_item(({"second " + trees[0] + " tree", "second " + trees[0]}),
        "All the other " + trees[0] + s + " are tall and straight" +
        " with no unusual features.\n");

    add_item(({"third " + trees[1] + " tree",
        "third " + trees[0]}),
        "You're beginning to sense that if you've seen one " + trees[0] +
        " tree, you've seen them all, although the first one seems to" +
        " be the exception.\n");

    /*
     *  Other trees, if any, get a less lofty description.   
     */

    m = sizeof(trees);
    for (n = 1; n < m; n += 1)

    {

        s = tree_plural_check(trees[n]);

        add_item(({trees[n] + " trees", trees[n] + s}),
            "The " + trees[n] + s + " rise in the shadow of the" +
            " great " + trees[0] + " trees, and their growth is limited" +
            " for lack of sunlight. The ground here must be quite" +
            " fertile, for even with this disadvantage they manage" +
            " to look strong and healthy, albeit rather short for" +
            " full-grown " + trees[n] + s + ".\n");

        /*
         * If there are other tree varieties in the room, there will be one 
         *  climbable specimen of each which leads to a FOREST_COVERT_CONTAINER
         *  within the tree's branches. This container is a dead end - all you
         *  can do is come back down to GROUND_LEVEL. FOREST_COVERT_CONTAINER,
         *  however, provides excellent cover for listening to activity in the
         *  GROUND_LEVEL room below.   
         */

        add_item(({trees[n],
            trees[n] + " tree",
            "first " + trees[n],
            "first " + trees[n] + " tree",
            "nearest " + trees[n],
            "nearest " + trees[n] + " tree"}),
            "The " + trees[n] + s + " vary in height, although all" +
            " are fairly tall, and in general they appear too flimsy" +
            " to bear your weight, but this one looks like it could" +
            " be climbed. It's quite dense and bushy, as if it had" +
            " grown wider in hopes of catching any stray beam of" +
            " sunlight that happened to get through the canopy.\n");

        add_item(({"second " + trees[n] + " tree", "second " + trees[n],
            "third " + trees[n] + " tree", "third " + trees[n]}),
            "You see nothing particularly interesting about the other" +
            " " + trees[n] + s + ".\n");

        add_item(({"third " + trees[n] + " tree",
            "third " + trees[n]}),
            "You find this " + trees[n] + " tree utterly boring.\n");

    }

    /*
     *  Add exits. There MUST always be 8 rooms surrounding a forest interior 
     *  room in all compass directions, and these MUST be the first 8 exits
     *  defined so that they occupy the first 8 positions in the room_exits
     *  array.   
     */

    add_exit(adjacent_rooms[0], "north", 0, exit_fatigue);
    add_exit(adjacent_rooms[1], "northeast", 0, exit_fatigue);
    add_exit(adjacent_rooms[2], "east", 0, exit_fatigue);
    add_exit(adjacent_rooms[3], "southeast", 0, exit_fatigue);
    add_exit(adjacent_rooms[4], "south", 0, exit_fatigue);
    add_exit(adjacent_rooms[5], "southwest", 0, exit_fatigue);
    add_exit(adjacent_rooms[6], "west", 0, exit_fatigue);
    add_exit(adjacent_rooms[7], "northwest", 0, exit_fatigue);

    /*
     *  At ground level, motion up or down is controlled by special functions, 
    never by standard exits. The following exits are dummies provided for the
    benefit of shouts (which can be heard all the way to the treetops) and
    other functions that query the room_exits array. */

    add_exit(UPPER + This_Location, "w", 1, exit_fatigue);
    add_exit(MIDDLE + This_Location, "e", 1, exit_fatigue);
    add_exit(LOW + This_Location, "s", 1, exit_fatigue);

    /*
     *  All interior forest rooms, regardless of their other components, get 
     *  the following standard descriptive items, things you could hardly
     *  expect to be lacking in any forest. Well, maybe a forest written by
     *  Sarr.   
     */

    n = sizeof(trees);

    switch (n)

    {

        case 1:

            add_item(({"trees"}),
                "The trees are all of ancient age and formidable" +
                " size. Remarkably uniform in height, they are about as" +
                " tall as any " + trees[0] + " tree you have ever seen.\n");

            break;

        case 2:

            s = tree_plural_check(trees[1]);

            add_item(({"trees"}),
                "The trees are a mixture of " + trees[0] +
                " and " + trees[1] + ". Reaching to staggering heights," +
                " the " + trees[0] + " trees block out almost all sunlight." +
                " The " + trees[1] + s + " aren't nearly as majestic," +
                " but in the perpetual shade they nonetheless manage" +
                " to grow tall and straight.\n");

            break;

        case 3:

            s = tree_plural_check(trees[0]);

            add_item(({"trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + trees[1] + " and " + trees[2] + " trees and" +
                " a carpet of thick vegetation. Even in the dim light" +
                " that filters through the canopy, you can see that all" +
                " the plants here are green and hardy.\n");

            break;

        default:

            s = tree_plural_check(trees[0]);

            add_item(({"trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + implode(trees[1..(n-2)], ", ") +
                " and " + trees[n-1] + " trees and" +
                " a carpet of thick vegetation. Even in the dim light" +
                " that filters through the canopy, you can see that all" +
                " the plants here are green and hardy.\n");

            break;

    }

    add_item(({"branch", "branches", "limbs"}),
        "Most of the branches are high over your head, where they" +
        " have some chance of catching some sunlight. A few" +
        " trees still have some old bare branches near ground" +
        " level, but they are shriveled and too limp to" +
        " hold any weight.\n");

    add_item(({"leaf", "leaves"}),
        "The canopy is far overhead and dark, so you can't" +
        " determine what kind of leaves may be up there, but" +
        " along the ground the vines are covered with leaves" +
        " of every imaginable shape and size. Old leaves and" +
        " needles also litter the ground, and the constant" +
        " dampness hastens their process of decay.\n");

    add_item(({"needle", "needles"}),
        "Tiny needles litter the ground here, obviously fallen" +
        " from some evergreen trees or smaller plants.\n");

    add_item(({"stick", "sticks"}),
        "There is no shortage of small sticks in the area, the remains" +
        " of tiny twigs and sturdy branches that have fallen from" +
        " the trees. They are all in some stage of decay due to" +
        " the constant dampness.\n");

    add_item(({"canopy", "treetops"}),
        "The trees grow so close together that their tops form" +
        " a continuous canopy and block almost all sunlight from" +
        " reaching the ground.\n");

    add_item(({"foliage", "plants", "creeping plants", "moisture", "carpet",
        "mat"}),
        "Plants grow densely on the fertile ground and are covered" +
        " with tiny beads of moisture which sparkle whenever a ray" +
        " of sunlight strikes them, which is a rather rare occurrence" +
        " under the nearly opaque canopy formed by" +
        " the tightly packed treetops.\n");

    add_item(({"sunlight", "ray"}),
        "Every once in a while a tenuous ray of sunlight peeks" +
        " through the canopy and illuminates the foliage for just" +
        " a few seconds. If it were not for this occasional" +
        " interruption, the uniform darkness might tempt you to" +
        " believe that you were walking under a solid roof" +
        " rather than treetops.\n");

    /*
     *  Standard properties for an interior forest room.   
     */

    add_prop(ROOM_I_HIDE, 1);  /*  A great place to hide. */
    add_prop(ROOM_I_LIGHT, 1);  /*  Not much light. */
    add_prop(ROOM_I_NO_ATTACK, "@@start_forest_combat@@");

    /*
     *  Special properties used by central forest room and object functions. 
     *  Another property, FOREST_SLOPE, was added earlier in this function if a
     *  slope was defined.    
     */

    add_prop(FOREST_TREE_TYPES, trees);
    add_prop(CALIA_COMBAT_INVENTORY, combat_inventory);

    /*
     *  If there is a pit, call the create_pit function after all other room 
     *  definition is complete. The description and other features related to
     *  the pit are added by a completely self-contained function because pits
     *  can be created either at room definition time or later by a player
     *  falling from a tree.    
     */

    if (pointerp(trails) && trails[0] == "pit") create_pit();

}

// Function:  fall_in_pit()

/*

Purpose:  Put player in the pit. This usually happens inadvertently, but a
player is free to fall any time he wants to; no check for fatigue is necessary,
and team members are not compelled to follow. If someone falls in it could be a
good place for two enemies to fall in after him for the kill - climbing out is
rather difficult when you're being attacked! The pit can hold three players of
any size with ease; more can fit if they're not too busy fighting to carefully
find a way in, lest they fall onto a lance-point or axe-blade.

Arguments:  none.

Returns: 1.

*/

int
fall_in_pit(string where)

{

    object tp = this_player();
    object pit = find_object(BELOW + This_Location);
    object *contents;
    object *fighters;
    int cannot_disengage = 0;
    int m;
    int n;

    /*
     *  This function only works if there's actually a pit to jump into and the 
     *  player has typed the word "pit" at the end of the command.    
     */

    if (member_array("pit", query_prop(CALIA_COMBAT_INVENTORY)) != -1 &&
        wildmatch("*pit", where))

    {

        /*
         *  If "pit" appears in the CALIA_COMBAT_INVENTORY but the pit room 
         *  does not exist, that means that the room has not been loaded and
         *  therefore must be empty, requiring no further checking.  Players
         *  can always fall into an empty pit.

         *  The filename check is for use by the ground combat control object.
         *  It will insert the filename of this room into the "fall in pit"
         *  command.  If the filename is detected, then the fall is involuntary
         *  and uncontrolled; no further checking will be done.    
         */

        if (pit && !wildmatch(file_name(this_object()) + "*", where))

        {

            contents = FILTER_LIVE(all_inventory(pit));

            if (sizeof(contents) > 2)

            {

                /*
                 * The pit already contains at least three players. Any player 
                 *  trying to enter must do so carefully, making sure he
                 *  doesn't land on something dangerous. We query the room to
                 *  see who (if anyone) is fighting this player. Disengaging
                 *  from a fight to check out landing places in the pit is
                 *  rather difficult: you'll need better int and dex than any
                 *  of your opponents to do it. On top of that, if you're
                 *  fighting four enemies of any caliber you'll never be able
                 *  to pull it off.   
                 */

                fighters = FILTER_LIVE(all_inventory(this_object()));
                m = sizeof(fighters);

                for (n=0; n<m; n+=1)

                {

                    if (fighters[n]->query_attack() == tp)

                {

                        if ((tp->query_stat(SS_DEX) + tp->query_stat(SS_INT))
                            <
                            (fighters[n]->query_stat(SS_DEX) +
                            fighters[n]->query_stat(SS_INT)))

                        {

                            tp->catch_msg("The pit is already" +
                                " crowded! You try to find a way in, but " +
                                QCTNAME(fighters[n]) + " is keeping" +
                                " you far too busy.\n");

                            fighters[n]->catch_msg(QCTNAME(tp) + " looks" +
                                " at the crowded pit as if trying to" +
                                " find a way in, but your attack" +
                                " distracts " +
                                tp->query_objective() + ".\n");

                            return 1;

                        }

                        else cannot_disengage += 25;

                    }

                }

                if (cannot_disengage > random(100))

                {

                    tp->catch_msg("The pit is already crowded!" +
                        " Your enemies are keeping you far too busy" +
                        " to find a way in.\n");

                    say(QCTNAME(tp) + " tries to " + query_verb() +
                        " into the pit but cannot" +
                        " disengage from his enemies.\n");

                    contents[0]->catch_msg(QCNAME(tp) + " steps" +
                        " on your head as" + tp->query_pronoun() +
                        " crosses over the pit.\n");

                    tell_room(pit,
                        QCNAME(tp) + " steps on " + QCTNAME(contents[0]) +
                        "'s head as " + tp->query_pronoun() + " crosses" +
                        " over the pit.\n", ({contents[0]}));

                    return 1;

                }

                else

                {

                    tp->catch_msg("The pit is already crowded, but you" +
                        " manage to spot a place where" +
                        " you can land safely.\n");

                }

            }

        }

        tell_room(this_object(), QCTNAME(tp) +
            " " + query_verb() + "s into the pit!\n", ({tp}));

        tp->move_living("M", BELOW + This_Location, 1);

        return 1;

    }

    else

    {

        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;

    }

}

// Function:  unq_move()

/*

Purpose:  This function is a modification of the unq_move function in
/std/room/move.c; additional code moves players off their intended course when
exiting through one of the eight compass direction exits. If the player is a
team leader, movement of all tema members is handled within this function.
Forest interior rooms always have 8 exits in all compass directions, all of
them have the same fatigue value, and these are the only exits created with the
standard add_exit function, so this code can use some efficiencies that
wouldn't work in a room where the exits are not so predictable.

Whether a player is misdirected or not depends on a stat+skill test. The player
may be misdirected as much as 90 degrees right or left from his intended
course, but there's a 20% chance that in using a randomly selected exit he will
actually go in the direction he wanted anyway. Other players in the exited
room, incuding team members exiting with him, may see a message indicating the
wrong turn if they have a superior stat+skill value.

Arguments:  a string representing the intended direction.

Returns: 0/1.

*/

int
unq_move(string str)

{

    /*
     *  The following variables are from /std/room/move.c. The argument "str" 
     *  in the function is also copied from the standard function but is not
     *  used here. The array room_exits contains three elements for each
     *  defined exit; for purposes of this function only the first eight exits
     *  are considered, so the variable "size" is permanently set to 24.    
     */

    int index;
    int size = 24;
    int tired;
    int tmp;
    object room;

    /*
     *  The following variables are specific to this version of the function. 
     *    
     */

    object tp = this_player();
    object *observers = FILTER_LIVE(all_inventory(this_object())) - ({tp});
    object *movelist = ({tp});
    int movesize;
    int num_in_room = sizeof(observers);
    int new_index;
    int n;

    int skill_and_stat = tp->query_skill(SS_LOC_SENSE) +
        tp->query_stat(SS_INT);

    index = member_array(query_verb(), room_exits) - 1;

    /*
     *  The test below makes dual use of a standard property. Rooms with trails 
    are easy to navigate in and also allow horses. Deep forest rooms without
    trails do not allow horses and are confusing. A zero value of the property
    ROOM_I_NO_ALLOW_STEED therefore serves as a flag to cancel the confusion;
    otherwise, the stat and skill test is applied to see if the actual
    direction of travel (new_index) is different from the intended direction
    (index). Blocking an individual exit in the middle of the forest is an
    impractical concept and is not supported by this code. */

    if (query_prop(ROOM_I_NO_ALLOW_STEED) && skill_and_stat < random(200))

    {

        new_index = ((index + size - 6) + (random(5) * 3)) % size;

    }

    else

    {

        new_index = index;

    }

    /*
     * Abort if the destination room won't load.   
     */

    if (!objectp(room = load_room(new_index))) return 1;

    /*
     *  The object of the confusion is to get the whole team lost, not to 
     *  separate the individual team members. Instead of the standard team
     *  movement function, in which each member executes the same direction
     *  command as the leader, this routine makes sure they all get to the same
     *  room regardless of how off-course the leader takes them.   
     */

    if (tp->query_leader() == tp)

    {

        movelist += tp->query_team_others();

    }

    movesize = sizeof(movelist);

    for (n=0; n<movesize; n+=1)

    {

        /*
         * Players younger than 2 hours or people carrying less than 20 % of 
         *  their capability don't get tired from walking around in the
         *  world...   
         */

        if ((movelist[n]->query_age() > 7200) &&
            (tmp = movelist[n]->query_encumberance_weight()) > 20)

        {

            /*
             * Compute the fatigue bonus. Sneaking gives double fatigue and so 
             *  does talking with 80% encumberance.   
             */

            tired = query_tired_exit(new_index / 3);

            tired = (movelist[n]->query_prop(LIVE_I_SNEAK) ? (tired * 2) :
                tired);

            tired = ((tmp > 80) ? (tired * 2) : tired);

            if (movelist[n]->query_fatigue() < tired)

            {

                /*
                 * Player is too tired to move.   
                 */

                movelist[n]->catch_msg("You are too tired to walk" +
                    " in that direction.\n");

                continue;

            }

            movelist[n]->add_fatigue(-tired);

        }

        movelist[n]->move_living(room_exits[new_index + 1], room);

    }

    if (new_index != index)

    {

        write("TEST: intended direction was " + room_exits[index + 1] +
            " but travel was " + room_exits[new_index + 1] + ".\n");

        for (n=0; n<num_in_room; n+=1)

        {

            /*
             *  The logic of the test: your awareness must be high enough to 
             *  notice the player's error, and your combination of location
             *  sense and intelligence has to be higher than his or you'd be
             *  making the same mistake under the same circumstances. Also, you
             *  can only get notification of the leader's mistake when an
             *  entire team leaves together. The messages are different for
             *  those who moved with the leader and for those left behind.  
             */

            if ((observers[n]->query_skill(SS_AWARENESS) > random(100))
                && ((observers[n]->query_skill(SS_LOC_SENSE) +
                observers[n]->query_stat(SS_INT)) > skill_and_stat))

            {

                if (environment(observers[n]) == environment(tp))

                {

                    observers[n]->catch_msg("[You sense that " + QCTNAME(tp) +
                        " is actually leading you to the " +
                        room_exits[new_index + 1] + ".]\n");

                }

                else

                {

                    if (movesize=1)

                    {

                        observers[n]->catch_msg("[" + QCTNAME(tp) +
                            " suddenly changes direction to the " +
                            room_exits[new_index + 1] + ".]\n");

                    }

                    else

                    {

                        observers[n]->catch_msg("[" + QCTNAME(tp) +
                            " suddenly changes direction" + " and leads " +
                            tp->query_possessive() + " team to the " +
                            room_exits[new_index + 1] + ".]\n");

                    }

                }

            }

        }

    }

    return 1;

}

// Function:  climb_tree(string tree)

/*

Purpose:  climb a tree.

Arguments:  none.

Returns: 1.

*/

int
climb_tree(string tree)

{

    object to = this_object();
    object tp = this_player();
    object *tree_contents;
    object ob;
    string *trees = query_prop(FOREST_TREE_TYPES);
    mixed destination;
    int success = 100;  /*  Base value for comparing skill and stat. */
    int fatigue;  /*  Climbing effort. */
    int this_tree = -1;  /*  Tree selector. */
    int m;  /*  General-purpose counter.  */
    int n;  /*  General-purpose counter.  */

    if (!tree)  /*  Player did not specify what to climb. */

    {

        write("Climb what?\n");
        return 1;

    }

    /*
     *  The Central Forest Climbing Rule:  no player can climb a tree if his 
     *  encumbrance is more than his climb skill.   
     */

    if (tp->query_encumberance_weight() > tp->query_skill(SS_CLIMB))

    {

        write ("You are too heavily burdened to climb here.\n");
        return 1;

    }

    if (tree == "tree"
        || tree == trees[0]
        || tree == trees[0] + " tree"
        || tree == "first " + trees[0]
        || tree == "nearest " + trees[0]
        || tree == "first " + trees[0] + " tree"
        || tree == "nearest " + trees[0] + " tree")

    {

        /*
         *  Player selects dominant tree in room. If the climb is successful, 
         *  he will move to a room on the LOW level.    
         */

        destination = find_object(LOW + This_Location);
        this_tree = 0;

        /*
         *  There are only enough handholds for two players to cling to the 
         *  trunk at LOW level. Non-living objects that enter the LOW room
         *  immediately fall to the ground, so only livings are represented in
         *  the inventory.   
         */

        if (destination)

        {

            tree_contents = FILTER_LIVE(all_inventory(destination));

            if (sizeof(tree_contents) > 1)

            {

                tp->catch_msg("You see " + QNAME(tree_contents[0]) +
                    " and " + QNAME(tree_contents[1]) +
                    " already clinging to the trunk! Unless" +
                    " you're prepared to dislodge one of them," +
                    " there's no way you can climb the " + trees[0] +
                    " tree.\n");

                return 1;

            }

        }

        else  /* If there's no object then use the string value. */

        {

            destination = LOW + This_Location;

        }

        fatigue = 30;

    }

    else

    {

        m = sizeof(trees);

        for (n=1; n<m; n+=1)

        {

            if (tree == trees[n]
                || tree == trees[n] + " tree"
                || tree == "first " + trees[n]
                || tree == "nearest " + trees[n]
                || tree == "first " + trees[n] + " tree"
                || tree == "nearest " + trees[n] + " tree")

            {

                /*
                 *  Player selects secondary tree.  If the climb is successful, 
                 *  he will more to a container in this room which is an
                 *  observation site within the tree's branches.    
                 */

                destination = FOREST_COVERT_CONTAINER;
                this_tree = n;
                fatigue = 15;

            }

        }

    }

    if (this_tree == -1)  /* No such tree in this room. */

    {

        write("There doesn't seem to be a good " + tree +
            " to climb around here.\n");

        return 1;

    }

    /*
     *  Check to see if the player is too tired to climb this tree.   
     */

    if (tp->query_fatigue() < fatigue)

    {

        write("You are too tired to climb the " + trees[this_tree] + ".\n");

        say(QCTNAME(tp) + " tries to climb the " + trees[this_tree] +
            " but fails.\n");

        return 1;

    }

    /*
     *  In its simplest form, climbing success is based on comparing the sum of 
     *  a skill (SS_CLIMB) and a stat (SS_DEX) against a random number between
     *  0 and 100; not bad odds considering that this sum can exceed 200 for an
     *  advanced player. However, we do add a few modifications to increase the
     *  range of that random number: the amount that you're panicking, the
     *  burden you're carrying (as a percent of the max you can hold), and an
     *  additional 100 for fighting and for each hand that's wielding a weapon.
     *    
     */

    success +=
        tp->query_panic() +
        tp->query_encumbrance_weight() +
        objectp(tp->query_attack()) * 100 +
        objectp(tp->query_weapon(W_LEFT)) * 100 +
        objectp(tp->query_weapon(W_RIGHT)) * 100;

    write("You begin to climb the " + trees[this_tree] + " tree.\n");

    say(QCNAME(tp) + " begins to climb the " + trees[this_tree] +
        " tree.\n");

    if ((tp->query_stat(SS_DEX) + tp->query_skill(SS_CLIMB)) > random(success))

    {

        /*
         *  A non-zero value of this_tree means the player is moving to 
         *  FOREST_COVERT_CONTAINER. We have to create the container if it
         *  isn't already here and use the move function. A zero means that he
         *  is moving to the room on LOW level which requires the move_living
         *  function.   
         */

        if (this_tree)

        {

            destination = present("covert_container_" + trees[this_tree], to);

            if (!destination)

            {

                destination = clone_object(FOREST_COVERT_CONTAINER);
                destination->set_short(trees[this_tree] + " tree");
                destination->add_name("covert_container_" + trees[this_tree]);
                destination->move(to);

                ob = clone_object(FOREST_NOSEEUM);
                ob->open_channel(to);
                ob->move(destination);

                if (!present(FOREST_NOSEEUM, to))

                {

                    ob = clone_object(FOREST_NOSEEUM);
                    ob->open_channel(destination);
                    ob->move(to);

                }

            }

            success = tp->move(destination);

        }

        else

        {

            success = tp->move_living("M", destination, 1);

        }

        /*
         *  A non-zero success value means the move was unsuccessful. This 
         *  should only occur if the move was to the covert_position object, in
         *  which case the tree cannot hold the player's weight and/or volume
         *  (perhaps in combination with objects already in the tree). The tree
         *  is destroyed and its contents dumped into the room. Another tree of
         *  the same variety will replace it when someone else wants to climb.
         *    
         */

        if (success)

        {

            write("There is a creak, a snap, and then suddenly" +
                " a tree limb breaks under your weight! You fall back" +
                " to the ground unharmed.\n");

            say("There is a creak, a snap, and then suddenly" +
                " a tree limb breaks! " + QCTNAME(tp) + " falls back" +
                " to the ground unharmed.\n");

            tell_room(destination,
                QCTNAME(tp) + " tries to climb into the tree with" +
                " you but falls back to the ground when a limb" +
                " breaks under " + tp->query_possessive() + " weight." +
                " That limb was supporting your weight too!\n");

            tree_contents = all_inventory(destination);

            /*
             *  Breaking the tree deposits both a sizeable branch and a bunch 
             *  of twigs.   
             */

            ob = clone_object(FOREST_OBJECTS + "branch");
            ob->create_branch(trees[this_tree]);
            ob->move(to);

            ob = clone_object(FOREST_OBJECTS + "twigs");
            ob->create_twigs(trees[this_tree]);
            ob->move(to);

            m = sizeof(tree_contents);

            /*
             *  Tell the room about objects falling from the tree. Non-living 
             *  is shown only if it is the first thing to fall from the tree.
             *    
             */

            for (n=0; n<m; n+=1)

            {

                if (objectp(tree_contents[n]))

                {

                    if (living(tree_contents[n]))

                    {

                        if (tree_contents[n]->query_name() != "No-see-um")

                        {

                            tell_room(to, QCTNAME(tree_contents[n]) +
                                " falls from the " + trees[this_tree] +
                                " tree!\n");

                            tree_contents[n]->move_living("M", to, 1);

                        }

                        else tree_contents[n]->close_channel();

                    }

                    else

                    {

                         if (!n)
                            tell_room(to,
                            capitalize(LANG_ADDART(tree_contents[n])) +
                            " falls from the " + trees[this_tree] +
                            " tree.\n");

                        tree_contents[n]->move(to);

                    }

                }

            }

            ob = present("no-see-um", to);

            if (ob) ob->close_channel(destination);

            destination->remove_object();

        }

        else

        {

            tp->add_fatigue(-fatigue);
            say(QCNAME(tp) + " climbs up from ground level.\n");

            tell_room(to,
                QCTNAME(tp) + " leaves climbing the " + trees[this_tree] +
                " tree.\n");

            /*
             *  A player with low dex may leave some evidence of his climb.   
             */

            if (tp->query_stat(SS_DEX) < random(20))

            {

                ob = clone_object(FOREST_OBJECTS + "twigs");
                ob->create_twigs(trees[this_tree]);
                ob->move(to);

            }

        }

    }

    else

    {

        say(QCTNAME(tp) + " tries to climb the " + trees[this_tree] +
            " tree but loses " + tp->query_possessive() + " grip and" +
            " falls to the ground with a resounding thud.\n");

        write("You try to climb the " + trees[this_tree] + " tree" +
            " but lose your grip and fall to the ground with" +
            " a resounding thud.\n");

        if (tp->query_fatigue() > 1) tp->add_fatigue(-1);

    }

    return 1;

}

// Function:  tree_description()

/*

Purpose:  generate description of the largest climbable tree in the room. It
leads up to another room on LOW level which may contain up to two livings.
Anyone clinging to the bare trunk at that level should be pretty obvious.

Arguments:  none.

Returns: string containing tree description.

*/

string
tree_description()

{

    object *climbers = ({find_object(LOW + This_Location)});
    int n;

    if (climbers[0])

    {

        climbers = all_inventory(climbers[0]);
        n = sizeof(climbers);

    }

    switch (n)

    {

        case 0:

            write("The " + query_prop(FOREST_TREE_TYPES)[0] +
                " trees are mostly tall and straight with no branches" +
                " near the ground. This one, however, has rough," +
                " gnarled bark with some thick vines wrapped around it," +
                " making it possible to climb.\n");

            break;

        case 1:

            this_player()->catch_msg("The " +
                query_prop(FOREST_TREE_TYPES)[0] +
                " trees are mostly tall and straight with no branches" +
                " near the ground. This one, however, has rough," +
                " gnarled bark with some thick vines wrapped around it." +
                " " + QCNAME(climbers[0]) + " is already climbing this" +
                " tree and clinging to the trunk above you.\n");

            break;

        default:

            this_player()->catch_msg("The " +
                query_prop(FOREST_TREE_TYPES)[0] +
                " trees are mostly tall and straight with no branches" +
                " near the ground. This one, however, has rough," +
                " gnarled bark with some thick vines wrapped around it." +
                " " + QNAME(climbers[0]) + " and " + QNAME(climbers[1]) +
                " are already climbing this tree and clinging to" +
                " the trunk above you.\n");

            break;

    }

    return "";

}

// Function:  dislodge_player(player)

/*

Purpose:  drag a player who's clinging to the trunk at low-tree level; back
down to ground level.

Arguments:  string representing the player to be dislodged.

Returns: 0/1.

*/

int
dislodge_player(string enemy)

{

    object tp = this_player();
    object ep = present(enemy, find_object(LOW + This_Location));
    object to = this_object();
    string *forest_dislodge = query_prop(FOREST_DISLODGE);

    if (!enemy)

    {

        notify_fail("Dislodge whom from the " +
            query_prop(FOREST_TREE_TYPES)[0] + " tree?\n");

        return 0;

    }

    if (!ep)

    {

        write("There doesn't seem to be any " + enemy + " on the tree" +
            " to be dislodged.\n");

    }

    else

    {

        /*
         *  The Central Forest Climbing Rule:  no player can climb a tree if 
         *  his encumbrance is more than his climb skill.   
         */

        if (tp->query_encumberance_weight() > tp->query_skill(SS_CLIMB))

        {

            write ("You are too heavily burdened to climb high" +
                " enough to do that.\n");

            return 1;

        }

        /*
         *  Each time someone tries to dislodge a player and fails, both their 
         *  names are concatenated and added as a single element to the
         *  FOREST_DISLODGE property in this room. Having failed, you can't try
         *  again in this room until the game reboots. If you're successful,
         *  however, you can continue dislodging the same player as often as
         *  you like.   
         */

        if (member_array(tp->query_name() + ep->query_name(), forest_dislodge)
            != -1)

        {

            write("No, you've already tried that and failed.\n");
            return 1;

        }

        tp->catch_msg("You climb a short distance up the tree" +
            " trunk to where " + QTNAME(ep) + " is blocking your" +
            " way and pull and twist " + ep->query_possessive() +
            " legs in an attempt to dislodge " + ep->query_objective() +
            ".\n");

        ep->catch_msg(QCTNAME(tp) + " climbs a short distance up" +
            " the tree trunk to a position just below you and" +
            " pulls and twists your legs in an attempt" +
            " to dislodge you.\n");

        tell_room(to,
            QCTNAME(tp) + " climbs a short distance up the " +
            query_prop(FOREST_TREE_TYPES)[0] + " to a position just" +
            " below " + QTNAME(ep) + " and pulls and twists" +
            " " + ep->query_possessive() + " legs in an attempt" +
            " to dislodge " + ep->query_objective() + ".\n",
            ({tp}));

        tell_room(environment(ep),
            QCTNAME(tp) + " climbs a short distance up the " +
            query_prop(FOREST_TREE_TYPES)[0] + " to a position just" +
            " below " + QTNAME(ep) + " and pulls and twists" +
            " " + ep->query_possessive() + " legs in an attempt" +
            " to dislodge " + ep->query_objective() + ".\n",
            ({ep}));

        /*
         *  You need a superior combination of str, int, and climb to dislodge 
         *  someone, but not by a wide margin.   
         */

        if (((tp->query_skill(SS_CLIMB) + tp->query_stat(SS_STR) +
            tp->query_stat(SS_INT)) -
            (ep->query_skill(SS_CLIMB)+ ep->query_stat(SS_STR) +
            ep->query_stat(SS_INT))) > random(10))

        {

            tp->catch_msg("You dislodge " + QTNAME(ep) + ", who tumbles" +
                " to the ground!\n");

            ep->catch_msg(QTNAME(tp) + " dislodges you and you tumble" +
                " to the ground!\n");

            tell_room(to,
                QCTNAME(tp) + " dislodges " + QTNAME(ep) + ", who" +
                " tumbles to the ground!\n",
                ({tp}));

            tell_room(environment(ep),
                QCTNAME(tp) + " dislodges " + QTNAME(ep) + ", who" +
                " tumbles to the ground!\n",
                ({ep}));

            tell_room(to, QCTNAME(ep) + " arrives, reluctantly.\n");

            ep->move_living("M", environment(tp));

        }

        else

        {

            tp->catch_msg("You strain with all your might but cannot" +
                " dislodge " + QTNAME(ep) + ", who kicks your hands" +
                " away and makes you fall from the tree instead.\n");

            ep->catch_msg(QCTNAME(tp) +
                " strains with all " + tp->query_possessive() +
                " might but cannot dislodge you as you kick" +
                " " + tp->query_possessive() + " hands away, then falls" +
                " back to the ground in frustration.\n");

            tell_room(to,
                QCTNAME(ep) + " kicks at " + QTNAME(tp) +
                ", who loses " + tp->query_possessive() + " grip on" +
                " the tree and falls back to ground level.\n",
                ({tp}));

            tell_room(environment(ep),
                QCTNAME(ep) + " kicks at " + QTNAME(tp) +
                ", who loses " + tp->query_possessive() + " grip on" +
                " the tree and falls back to ground level.\n",
                ({ep}));

            tp->add_fatigue(-ep->query_stat(SS_STR));

            if (forest_dislodge)
                add_prop(FOREST_DISLODGE,
                forest_dislodge + ({tp->query_name() + ep->query_name()}));

            else
                add_prop(FOREST_DISLODGE,
                ({tp->query_name() + ep->query_name()}));

        }

    }

    return 1;

}

// Function:  init()

/*

Purpose:  add local commands.

Arguments:  none.

Returns: nothing.

*/

void
init()

{

    ::init();
    add_action(climb_tree, "climb");
    add_action(dislodge_player, "dislodge");
    add_action(fall_in_pit, "fall");
    add_action(fall_in_pit, "jump");

}
