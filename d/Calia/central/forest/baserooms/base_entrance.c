// ROOM:  base_entrance.c

    /*  Calia Domain

    HISTORY

    [99-05-17] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_ENT.DOC].

    PURPOSE

    This file is the inherited base for rooms connecting the Great Central
    Forest to adjacent territory. It contains the function for generating long
    descriptions, short descriptions, trails, and typical forest features.
    Since many, perhaps even most forest rooms look alike, it adds to the
    player's interest to present some variation in the descriptions. In
    general, the Great Central Forest is accessed along trails, although an
    entrance can be generated which has no trails. Hidden entrances or other
    special ways to enter the forest will be sufficiently rare that a baseroom
    for them is not provided.

    Separate base rooms are provided to define terrain at the edge of the
    forest which does not connect to any other area and to define the terrain
    of the forest interior.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"

// FUNCTIONS

// Function:  climb_tree(tree)

/*

Purpose:  contrary to its name, this function prevents a player from climbing a
tree.  Climbing is possible only in interior forest rooms, not at the edge.

Arguments:  string conaining the tree if you like, but it doesn't really
matter.

Returns: 1.

*/

int
climb_tree(string tree)

    {

    if (member_array(tree, query_prop(FOREST_TREE_TYPES) + ({"tree"})) != -1)

        {

        write("The " + tree + "'s trunk is far too straight and" +
            " smooth and its branches far too high above the" +
            " ground for you to consider climbing it.\n");

        }

    else write ("Climb what?\n");

    return 1;

    }

// 

/* Function:  create_forest_entrance(this_location, *adjacent_rooms,
tree_array, trail_array, barrier, gap, hill)

Purpose:  Generate a short description, long description, and trails for a room
connecting a forest room .

Arguments:  See base_interior.c for a description of this_location and
adjacent_room_array. Three other arguments are required: an array of tree
types, an array of trail directions, and a string describing the barrier that
separates the forest at this point from other terrain. At least one tree type
must be supplied, more are permissible; the first tree in the array is the
dominant variety in the room. Supplying more than three types will excessively
complicate the descriptive text. To indicate trails, up to 8 compass directions
may be supplied as an array of strings; these strings indicate the directions
in which trails lead from the current room.

The parameter "gap" is used to specify the compass direction of a gap in the
barrier.  This parameter generates text along the lines of "the barricade is
impassible except for a gap that allows passage east."

Use the optional parameter "slope" to make this room a hilside or hilltop.  The
value is a string containing either the word "hill", which indicates a hilltop
(level ground), or a compass direction, which indicates the direction of the
downward slope.

The following barriers are available to limit player movement:

    barricade   (gap in the felled trees)
    bog         (strip of firm ground)
    mountain    (up into a mountain pass, always assumed to be a trail)
    mountains   (gap in a mountain range)
    stream      (shallow area where fording is possible)
    thicket     (gap in thick vegetation)

    Barricade, bog, stream, and thicket are always assumed to be completely
    enclosed by the forest; mountain and mountains are always assumed to be at
    the edge of the forest.

Returns: nothing. This function calls standard room functions set_long,
set_short, and add_item to create its descriptions. The proper use of this
function in a room file (assuming a filename of C01_R01 and adjacent rooms
C02_R01, C02_R02, and C01_R02) looks like:

          create_forest_entrance("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine"}), ({"northwest", "south"}),
              "mountains", "south");

          or

          create_forest_entrance("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine", "birch"}),
              ({"east", "west", "southeast"}), "thicket", "east");

          or (if no trails are desired)

          create_forest_entrance("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine", "birch"}), 0, "thicket", "east");

          or (if the room is on a hillside that slopes down toward the
          southeast)

          create_forest_entrance("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine", "birch"}), 0, "thicket", "east", "southeast");

*/

varargs void
create_forest_entrance(string this_location, string *adjacent_rooms,
    string *trees, string *trails, string barrier, string gap, string slope)

    {

    string text;  /*  Becomes the long description of the room.  */
    string trail_text = "";  /*  Inserts description if there is a trail.  */
    string s;  /*  General-purpose string.  */
    int m;  /*  General-purpose counter.  */
    int n;  /*  General-purpose counter.  */

    /*  The following arrays contain descriptive strings which will be chosen
        at random and assembled into the variable "text" which eventually
        becomes the long description of the room.  */

    string *tree_line =
        ({"Dense stands of enormous " + trees[0] + " offer" +
        " shade and perhaps just a bit of foreboding.",
        "Towering " + trees[0] + " trees form a shadowy canopy over" +
        " the forest interior.",
        "Massive " + trees[0] + " trees stand like sentinels" +
        " guarding the entrance of a colossal citadel.",
        "Countless ancient " + trees[0] + " trees rise to lofty" +
        " heights, still, silent, and shadowy keepers of the secrets" +
        " lurking in the forest depths.",
        "Innumerable " + trees[0] + " trees, inconceivably" +
        " tall and straight, stretch as far as you can" +
        " see, blanketing the forest in deep shadows."});

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

    if (slope)

        {

        if (slope == "hill")

            {

            s = " on a hilltop";

            add_item(({"ground", "hilltop", "hill"}),
                "The ground here is higher than in other nearby" +
                " parts of the forest, although still" +
                " rather moist and yielding.\n");

            }

        else

            {

            s = " on ground that slopes downward to the " + slope;

            add_item(({"ground", "hilltop", "hill"}),
                "The ground slopes down toward the " + slope +
                ", and the trees have tangles of roots" +
                " exposed on their downhill sides.\n");

            add_item(({"tangle", "root", "tangles", "roots", "sides",
                "downhill sides", "side", "downhill side"}),
                "While the ground is irregular, the roots have grown" +
                " at an even level all around each tree so that" +
                " about half of them protrude through" +
                " the carpet of vegetation.\n");

            }

        }

    else

        {

        s = "";

        add_item(({"ground"}),
            "The ground is firm where you stand beside the" +
            " " + barrier + ", but you notice that under the" +
            " trees it is mostly moist and soft, uncomfortable" +
            " footing at best.\n");

        }

    if (trails)

        {

        add_item(({"trail", "trails"}),
            "The trail is the result of countless footsteps" +
            " beating down the vegetation and preventing its" +
            " regrowth along a meandering route between the trees.\n");

        trail_text = " on a trail";

        }

    switch (barrier)

        {

        case "barricade":

        add_item(({"barricade", "logs"}),
            "The barricade is made from many rough-hewn logs" +
            " jammed between the trees standing here.\n");

        add_item(({"gap"}),
            "It's not apparent whether this gap is part" +
            " of the original structure of the barricade or the" +
            " result of a forced breach, but the sound condition" +
            " of the logs suggests that it is not the result" +
            " of decay or termites.\n");

        text = "You stand" + trail_text + s +
            " deep within the forest." +
            " " + tree_line[random(sizeof(tree_line))] +
            " " + dark_line[random(sizeof(dark_line))] +
            " " + air_line[random(sizeof(air_line))] +
            " A barricade divides the forest here and blocks your" +
            " view, but a gap allows you to pass " + gap +
            " through the barrier to discover what lies on" +
            " the other side.";

        set_short("Near a barricade in the forest");
        break;

        case "bog":

        add_item(({"bog", "muck"}),
            "The bog is awash with muck far too soft and" +
            " yielding to support your weight; however, a narrow" +
            " strip of firm ground leading " + gap + "ward looks" +
            " like it will allow you to explore further.\n");

        add_item(({"strip", "narrow strip", "firm ground"}),
            "A narrow strip of firm ground, raised just a" +
            " bit higher and looking just a bit drier than the" +
            " rest of this area, leads into the bog.\n");

        text = "You stand" + trail_text + s + " deep within the forest" +
            " at the edge of a bog. " +
            tree_line[random(sizeof(tree_line))] +
            " " + dark_line[random(sizeof(dark_line))] +
            " " + air_line[random(sizeof(air_line))] +
            " Trees grow in the bog just as densely as they" +
            " do here, their thick canopy providing" +
            " concealing shadows for whatever may lurk within.";

        set_short("Near a bog in the forest");
        break;

        case "mountain":

        add_item(({"steep mountain", "steep mountains", "mountain",
            "mountains"}),
            "The mountain rises on either side of the trail, far too" +
            " smooth and steep for anyone to try to climb.\n");

        text = "You stand" + trail_text + s + " at the edge of a" +
            " forest where it borders on a steep mountain. " +
            tree_line[random(sizeof(tree_line))] +
            " While most of the mountain looks forbidding," +
            " a trail leading upward to the " + gap + " looks passable.";

        set_short("Where the forest borders on a mountain");
        break;

        case "mountains":

        add_item(({"steep mountain", "steep mountains", "mountain",
            "mountains"}),
            "The mountains rise sharply on either side of the gap," +
            " far too smooth and steep for anyone to try to climb.\n");

        add_item(({"gap", "narrow gap"}),
            "The gap allows travel " + gap +
            " through mountains which otherwise look impassible.\n");

        text = "You stand" + trail_text + s + " at the edge of a" +
            " forest where it borders on steep mountains. " +
            tree_line[random(sizeof(tree_line))] +
            " While most of the mountains look forbidding," +
            " a gap leading to the " + gap + " looks like it" +
            " will allow easy passage.";

        set_short("Where the forest borders on steep mountains");
        break;

        case "stream":

        add_item(({"stream", "deep stream"}),
            "The stream runs deep for most of its length, but in" +
            " one spot the water runs briskly through a shallow" +
            " area that looks easy to cross.\n");

        add_item(({"water", "shallow area", "area"}),
            "Even in the dim light that penetrates the canopy you" +
            " can see that the water is only ankle-deep in an" +
            " area that will let you cross to the " + gap + "\n");

        text = "You stand" + trail_text + s + " by a deep stream in" +
            " the middle of the forest. " +
            tree_line[random(sizeof(tree_line))] +
            " " + dark_line[random(sizeof(dark_line))] +
            " " + air_line[random(sizeof(air_line))] +
            " The stream poses a formidable barrier along most" +
            " of its length, but the water gurgles through a" +
            " shallow area to the " + gap + ".";

        set_short("By a stream in the forest");
        break;

        case "thicket":

        add_item(({"thicket", "thickets"}),
            "The thicket poses a formidable obstacle, consisting" +
            " of twisted vines as thick and hard as any" +
            " chain, dagger-like thorns, and branches so intertwined that" +
            " it is impossible to determine where one begins and" +
            " the next ends.\n");

        add_item(({"thorns", "thorn", "branches", "branch", "vines", "vine"}),
            "Your fascination with the structure of the thicket wanes." +
            " The forest beckons, and you find it far more interesting" +
            " than these thorns, branches, and vines.\n");

        add_item(({"opening", "narrow opening"}),
            "The opening is wide enough to allow you to pass " + gap +
            " through it.\n");

        text = "You stand" + trail_text + s + " by a thicket in the" +
            " middle of the forest. " +
            tree_line[random(sizeof(tree_line))] +
            " " + dark_line[random(sizeof(dark_line))] +
            " " + air_line[random(sizeof(air_line))] +
            " The thicket is dense and dark enough that" +
            " you can't detect anything inside it, let alone on" +
            " the other side, but a narrow opening offers a chance to" +
            " go " + gap + " and see what lies beyond.";

        set_short("By a thicket in the forest");
        break;

        default:

            text = text + " The trail runs directly over a" +
                " bug! Seriously, there is a problem here. Please make" +
                " a bug report and leave this area. Thank you.";

        }

    if (trails)

        {

        /*  Add trail directions to the descriptive text.  */

        n = sizeof(trails);

        switch (n)

            {

            /*  A trail that simply ends in the middle of the forest is a
                pretty strange trail, but just in case someone ever needs one,
                a routine to generate its description is provided.  */

            case 1:

            text = text +
                " The trail begins here and leads " + trails[0] + ".";

            break;

            case 2:

            text = text + " The trail leads " + trails[0] +
                " and " + trails[1] + ".";

            break;

            /*  An intersection of forest trails in every compass direction is
                also fairly absurd, especially at a barrier, but I put in a
                routine to process it just in case someone ever finds a logical
                need for such a room.  */

            case 8:

            text = text + " Trails lead in all directions from here.";
                break;

            default:

            text = text + " The trail separates here, leading " +
                implode(trails[1..(n-1)], ", ") + ", and " +
                trails[0] + ".";

            break;

            }

        }

    /*  The long description for the room is complete. Append the carriage
        return and load it into the proper place.  */

    text = text + "\n";
    set_long(text);

    /*  Add the descriptive items for individual tree varieties. The first
        variety is required and is the dominant type in this room. The
        wildmatch test forms the proper plural syntax for beech, birch, ash,
        etc. */

    if (wildmatch("*h", trees[0])) s = "es";
    else s = "s";

    add_item(({trees[0] + " tree", trees[0] + "trees",
        trees[0], trees[0] + s}),
        "The lofty " + trees[0] + s + " tower over everything else" +
        " in sight. Smooth and straight, they have no branches" +
        " near the ground; instead, their limbs are clustered" +
        " high overhead, where they mesh to form a nearly" +
        " opaque canopy.\n");

    /*  Other trees, if any, get a less lofty description.  */

    m = sizeof(trees);
    for (n = 1; n < m; n += 1)

        {

        if (wildmatch("*h", trees[n])) s = "es";
        else s = "s";

        add_item(({trees[n] + " tree", trees[n] + " trees",
            trees[n], trees[n] + s}),
            "The " + trees[n] + s + " rise in the shadow of the" +
            " great " + trees[0] + " trees, and their growth is stunted" +
            " for lack of sunlight. The ground here must be quite" +
            " fertile, for even with this disadvantage they manage" +
            " to look strong and healthy, albeit rather short for" +
            " full-grown " + trees[n] + s + ".\n");

        }

    /*  Add general tree and plant descriptions.  */

    n = sizeof(trees);

    switch (n)

        {

        case 1:

            add_item(({"tree", "trees"}),
                "The trees are all of ancient age and formidable" +
                " size. Remarkably uniform in height, they are about as" +
                " tall as any " + trees[0] + " trees you have ever seen.\n");

            break;

        case 2:

            if (wildmatch("*h", trees[1])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "The trees are a mixture of " + trees[0] +
                " and " + trees[1] + ". Reaching to staggering heights," +
                " the " + trees[0] + " trees block out almost all sunlight," +
                " leaving the " + trees[1] + s + " somewhat" +
                " stunted, although they do not look sickly.\n");

            break;

        case 3:

            if (wildmatch("*h", trees[0])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + trees[1] + " and " + trees[2] + " trees and" +
                " a carpet of thick vegetation. Even in the dim light" +
                " that filters through the canopy, you can see that all" +
                " the plants here are quite healthy.\n");

            break;

        default:

            if (wildmatch("*h", trees[0])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + implode(trees[1..(n-2)], ", ") +
                " and " + trees[n-1] + " trees and" +
                " a carpet of thick vegetation. While not as impressive" +
                " as the " + trees[0] + " trees, the other" +
                " varieties exhibit vigorous growth and health.\n");

        }

    add_item(({"canopy", "dense canopy", "treetops", "shade", "shadow",
        "shadows"}),
        "The trees grow so close together that their tops form" +
        " a continuous canopy and block almost all sunlight from" +
        " reaching the ground below.\n");

    add_item(({"vegetation", "plants"}),
        "The thick vegetation covers the ground as evenly as any" +
        " fine carpet except where the trail cuts through it. Even" +
        " in the constant shade cast by the towering " + trees[0] +
        " trees, its growth is amazingly luxuriant.\n");

    /*  Forest entrance rooms often have a trail that indicates obvious
        directions of travel and may have additional exits to parts of the
        forest on either side of the trail.  I could use a loop to add the
        exits, but I decided to trade a little space in the baseroom code for
        faster execution. */

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 2);
    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 2);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 2);
    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 2);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 2);
    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 2);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 2);
    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 2);

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

    }
