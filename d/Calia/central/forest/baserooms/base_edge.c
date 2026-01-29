// ROOM:  base_edge.c

    /*  Calia Domain

    HISTORY

    [98-11-25] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_EDG.DOC].

    PURPOSE

    This file is the inherited base for most rooms at the edge of the Great
    Central Forest. It contains the function for generating long descriptions
    and adding typical forest features. Since many, perhaps even most forest
    rooms look alike, it adds to the player's interest to present some
    variation in the descriptions.

    A separate base room defines terrain in the forest interior. Those rooms
    often contain special features that affect combat. Edge rooms are intended
    only to form a realistic boundary between the forest and other terrain;
    they have no spceial combat features. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "stdproperties.h"
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

    string *tree_list = ({"tree"}) + query_prop(FOREST_TREE_TYPES);

    if (member_array(tree, tree_list) != -1)

        {

        write("The " + tree + "'s trunk is far too straight and" +
            " smooth and its branches far too high above the" +
            " ground for you to consider climbing it.\n");

        }

    else write ("Climb what?\n");

    return 1;

    }

// 

/* Function:  create_forest_edge(this_location, adjacent_room_array,
tree_array, barrier_array, trails, slope) */

/*

Purpose:  Generate a short description, long description, and items for a
forest room.

Arguments:  A string containing the current location, a string array containing
adjacent room filenames, an array of tree types, an array of trail directions,
and an array describing the type of barrier a player encounters which prevents
travel in certain directions.

At least one tree type must be supplied, more are permissible; the first tree
in the array is the dominant variety in the room. Tree types must be lower case
strings such as "oak", "pine", "fir", etc. Supplying more than three types will
excessively complicate the descriptive text.

The barrier array contains at a minumum one string selected from the list of
barriers below. Each barrier may be accompanied by an element that describes
its location relative to the observer. For example, the pair ({"mountain",
"south"}) indicates that a mountain rises directly south of the observer, while
({"mountains", "south and east"}) indicates that a curving mountain range
blocks the observer's path both south and east. The exceptions are a rapids,
river, or stream, which require two elements and may be defined by three: the
barrier name and the direction of flow are required; a third element may be
added to indicate the rapids/river/stream's position relative to the observer.
A river flowing south would be represented by ({"river", "south"}). To indicate
that this river is to the observer's west, use ({"river", "south", "west"}).

You can generate more than one barrier by simply adding more elements to the
array. In many cases a single barrier needs no direction indicator, as its
location should be obvious from the available exits, but for clarity's sake
multiple barriers should always be accompanied by directions. To surround the
observer with a mountain range to his south, a river to his east flowing
northeast, and a thicket to his west, use the array ({"mountains", "south",
"river", "east", "northeast", "thicket", "west"}); just be sure to provide an
exit north! The first barrier in the array is the most prominent one and will
be mentioned in the room's short description; other barriers in the same room
will not.

Barriers processed by this routine cannot be entered. You cannot climb the
mountains or ford the rivers. Nor can you jump over the thickets, wade through
the ponds, or swim across the lakes for that matter. If you want to use such
features as exits, do not use this routine to generate them.

Barrier list:    barricade   (felled trees)
                 bog         (muddy ground too soft to walk on)
                 lake        (always too big to see the far shore)
                 mountain    (for a single mountain)
                 mountains   (for a mountain range)
                 pond        (always completely enclosed by the forest)
                 rapids      (river with a powerful churning current)
                 river       (smoother but still powerful current)
                 stream      (smaller than a river but still impassible)
                 thicket     (tangle of vegetation too thick to break through)

Trails are specified as compass directions.  The array may contain up to eight
entries; if no trails are desired, the variable may be omitted or set to 0.

Use the optional parameter "slope" to make this room a hilside or hilltop.  The
value is a string containing either the word "hill", which indicates a hilltop
(level ground), or a compass direction, which indicates the direction of the
downward slope.

Returns: nothing. This function calls standard room functions set_long,
set_short, and add_item to create its descriptions. The proper use of this
function (assuming a filename of C01_R01 and adjacent rooms C02_R01, C02_R02,
and C01_R02) in a room file looks like:

          create_forest_edge("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine"}), ({"pond"}));

          or on a slope

          create_forest_edge("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine"}), ({"river", "east"}), "north");

          or with trails leading east and south

          create_forest_edge("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine", "spruce"}), ({"mountains"}), ({"east", "south"}));

          or

          create_forest_edge("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"oak"}), ({"mountains", "west and north"}));

          or

          create_forest_edge("C01_R01",
              ({0, 0, "C02_R01", "C02_R02", "C01_R02", 0, 0, 0}),
              ({"pine", "spruce"}),
              ({"mountains", "west", "river", "east", "south"}));

*/

varargs void
create_forest_edge(string this_location, string *adjacent_rooms,
    string *trees, string *barriers, string *trails, string slope)

    {

    string *barrier_list = ({"barricade", "bog", "lake", "mountain",
        "mountains", "pond", "rapids", "river", "stream", "thicket",
        "null"});

    /*  Because the barrier generating routine always checks the next entry
        after a barrier to see if it is a direction indicator, a work array
        with an added dummy entry is used to prevent a subscript error. The
        barrier_list includes the element "null" to prevent the routine from
        interpreting it as a compass direction. */

    string *work = barriers + ({"null"});

    string s;  /*  General-purpose string. */
    int m;  /*  General-purpose counter. */
    int n;  /*  General-purpose counter. */

    /*  The following arrays contain descriptive strings which will be chosen
        at random and assembled into the variable "text" which eventually
        becomes the long description of the room. */

    /*  Text from tree_line and add_tree_line will be combined as dictated by
        the number of trees varieties supplied. The code supports up to 5
        varieties in any room, which should be plenty since the different trees
        are purely for decoration. */

    string *tree_line =
        ({"Dense stands of " + trees[0] + " trees dominate this area",
        "Towering " + trees[0] + " trees rise to the sky" +
        " in countless numbers",
        "Massive " + trees[0] + " trees stand like the columns of" +
        " a grand cathedral",
        "Countless ancient " + trees[0] + " trees rise to lofty heights"});

    string *add_tree_line =
        ({".",
        ", dwarfing other trees nearby.",
        " while other varieties encroach upon their ranks.",
        " while a number of other varieties also compete for space.",
        ", dwarfing the numerous other varieties growing here."});

    string *dark_line =
        ({"Within the forest depths there is little light, as" +
        " the tightly packed treetops form a nearly opaque canopy.",
        "Under the trees the light is subdued, as the dense network" +
        " of branches prevents most sunlight from reaching the ground.",
        "The treetops are uniform in height and densely packed, and few" +
        " of the sun's rays filter through to light the ground beneath.",
        "Little space separates one tree from the next, and their" +
        " tops mesh together, blocking most light from reaching" +
        " the ground below."});

    string *action_line =
        ({"Somewhere between the trees a songbird breaks the silence" +
        " with a gentle, lilting tune.",
        "A bit of a breeze sways the treetops ever so gently, but" +
        " farther down in the forest all is still.",
        "Vague, diverse odors emanate from the forest, some woody," +
        " some bearing the fragrance of flowers, some bearing a" +
        " tinge of decay.",
        "An occasional sign of movement flickers between the" +
        " trees, suggesting that some small animals are going about" +
        " their daily routines despite your presence.",
        "Somwehere high in the treetops two songbirds call to" +
        " each other, oblivious and invisible to land-bound" +
        " creatures below."});

    string *first_line;
    string *barrier_line_1;
    string *barrier_line_2;
    string *barrier_line_3;
    string text;

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
            " " + barriers[0] + ", but you notice that under the" +
            " trees it is moist and soft, uncomfortable" +
            " footing at best.\n");

        }

    /*  If the room is bordered by a lake, mountain, or mountains, it is
        assumed to be at the edge of the forest.  Otherwise, it is assumed to
        be completely enclosed by the forest.  */

    if (member_array("lake", barriers) != -1
        || member_array("mountain", barriers) != -1
        || member_array("mountains", barriers) != -1)

        {

        first_line =
            ({"You stand" + s + " at the edge of a great forest.",
            "A vast forest extends" + s + " before you.",
            "You stand" + s + " before an immense forest."});

        }

    else

        {

        first_line =
            ({"You stand" + s + " in the midst of a great forest.",
            "You stand" + s + " are surrounded by a" +
            " forest of incalculable depth and breadth.",
            "You stand" + s + " within an immense forest."});

        }

    text = first_line[random(sizeof(first_line))] +
        " " + tree_line[random(sizeof(tree_line))] +
        add_tree_line[random(sizeof(trees))] +
        " " + dark_line[random(sizeof(dark_line))] +
        " " + action_line[random(sizeof(action_line))];

    m = sizeof(barriers);

    for (n=0; n<m; n+=1)

        {

        if (member_array(work[n], barrier_list) != -1)

            {

            switch (work[n])

                {

                case "barricade":

                barrier_line_1 =
                    ({"A barricade of felled trees has" +
                    " been built here.",
                    "A mound of felled trees form" +
                    " a sturdy barricade here.",
                    "Felled trees have been piled here to form" +
                    " an impenetrable barricade.",
                    "Here a barricade has been" +
                    " constructed from felled trees."});

                barrier_line_2 =
                    ({"The barricade prevents travel to the",
                    "The barricade bars any movement to the",
                    "The barricade stands high and steep enough to" +
                    " prevent you from travelling",
                    "The barricade blocks the way"});

                barrier_line_3 = ({});

                add_item(({"barricade", "pile"}),
                    "This is a stupendous pile of logs that" +
                    " has been jammed between some trees.  They" +
                    " are wedged in tight and stacked so" +
                    " high that climbing over them is out" +
                    " of the question.\n");

                add_item(({"logs", "felled logs", "pile of logs"}),
                    "These logs seem to be cut from the same kind" +
                    " of " + trees[0] + " trees that dominate this" +
                    " part of the forest, although there is" +
                    " no evidence of stumps to indicate" +
                    " where they once stood.\n");

                set_short("By a barricade in the forest");

                break;

                case "bog":

                barrier_line_1 =
                    ({"Here where the ground is just a" +
                    " bit lower than elsewhere" +
                    " in the forest a soft bog has formed.",
                    "Between the trees a bog of mud and" +
                    " decomposing matter has formed here."});

                barrier_line_2 =
                    ({"The bog prevents travel to the",
                    "The bog lies directly before you," +
                    " blocking your way",
                    "The bog spreads out before you to the",
                    "The bog is an impassible barrier" +
                    " to any traveller headed"});

                barrier_line_3 = ({});

                add_item(({"bog"}),
                    "The ground here is a bit lower than in the rest" +
                    " of the forest, and runoff from rain seems" +
                    " to have collected over the years and turned the" +
                    " soil into a soupy muck, impossible for even" +
                    " the lightest traveller to traverse.\n");

                add_item(({"muck"}),
                    "You bend down to observe the muck. Yes, this" +
                    " is genuine muck. The mighty " + trees[0] + "trees" +
                    " must have tremendous deep roots to stay upright" +
                    " in such terrain. You, on the other hand, have" +
                    " no such roots, so you'd better just stay" +
                    " away from it.\n");

                set_short("By a bog in the forest");

                break;

                case "lake":

                barrier_line_1 =
                    ({"A large lake borders the forest, its" +
                    " waters lapping up against the trees.",
                    "The forest ends abruptly at a vast lake" +
                    " whose waters stretch beyond the horizon.",
                    "Your progress is obstructed by an expansive" +
                    " lake, its waters reaching from the edge of" +
                    " the trees to somewhere beyond your view.",
                    "At the forest edge is a lake whose" +
                    " far shore lies somewhere beyond the horizon."});

                barrier_line_2 =
                    ({"The lake prevents travel to the",
                    "The lake's still waters bar any further" +
                    " travel to the",
                    "The lake borders the forest to the",
                    "From this point you can not travel any farther"});

                barrier_line_3 = ({});

                add_item(({"lake", "large lake"}),
                    "The lake is placid and wide, its" +
                    " dimensions inestimable from where you're" +
                    " standing. You surmise that the water is deep" +
                    " and cold. There doesn't seem to be any danger" +
                    " there, but nothing of any particular interest" +
                    " to you either.\n");

                add_item(({"water"}),
                    "The water is still and dark, which makes" +
                    " you contemplate that it must also be quite deep." +
                    " That and your inability to see the far shore" +
                    " convince you that swimming across it" +
                    " is an impossibility.\n");

                set_short("A lake at the edge of the forest");
                add_prop(OBJ_I_CONTAIN_WATER, 1);

                break;

                case "mountain":

                barrier_line_1 =
                    ({"A mountain thrusts up from the edge" +
                    " of the forest, abruptly cutting off any" +
                    " room for its expansion",
                    "The forest borders on a sheer" +
                    " mountain, the ground abruptly giving way" +
                    " to barren rock where nothing can grow",
                    "A steep and barren mountain presees" +
                    " against the forest edge as if the" +
                    " enormous rock were trying to pack the" +
                    " trees ever more tightly",
                    "The trees grow at the foot of a" +
                    " mountain, looking much like an army" +
                    " of giants preparing to seige" +
                    " a titanic fortress"});

                barrier_line_2 =
                    ({"The mountain prevents travel to the",
                    "The mountain rises sharply from ground" +
                    " level and blocks your way",
                    "No further travel is possible",
                    "This mountain provides no room for movement"});

                barrier_line_3 = ({});

                add_item(({"mountain", "rock"}),
                    "The mountain does not appear especially" +
                    " high, certainly not as high as others you've seen" +
                    " in this land, but its sides are sheer enough" +
                    " to make climbing impossible. It looks like" +
                    " nothing more than a great heap of barren rock" +
                    " that was placed here on purpose just to keep" +
                    " you from leaving the forest.\n");

                set_short("A mountain at the edge of the" +
                    " forest");

                break;

                case "mountains":

                barrier_line_1 =
                    ({"A range of sheer and jagged mountains rises" +
                    " up at the edge of the forest, as if a" +
                    " giant saw had suddenly been halted in" +
                    " its task of cutting away the outermost" +
                    " layer of trees.",
                    "A continuous mountain range hems in the" +
                    " forest the way that a stone wall" +
                    " confines sheep, although the massive " + trees[0] +
                    " trees hardly seem inclined to attempt escape.",
                    "The trees end abruptly at the base of sheer and" +
                    " jagged mountains standing in barren contrast" +
                    " to the lush fertility of the forest.",
                    "The trees grow at the foot of a sheer and" +
                    " jagged range of mountains, and they face" +
                    " each other at close quarters like rival" +
                    " armies of wood and stone."});

                barrier_line_2 =
                    ({"The mountains prevent travel to the",
                    "The mountains rise sharply before you and" +
                    " block your way",
                    "No further travel is possible",
                    "These mountains provide no" +
                    " opportunity for movement"});

                barrier_line_3 = ({});

                add_item(({"mountains", "range"}),
                    "The mountains rise straight up from the ground," +
                    " far too sheer to be climbed even by an expert." +
                    " Other than the effective barrier they make," +
                    " there's not much that you find of" +
                    " interest about them.\n");

                set_short("Mountains at the edge of the forest");

                break;

                case "pond":

                barrier_line_1 =
                    ({"The trees encircle a small pond.",
                    "The forest rings a small a pond, surrounded" +
                    " on all sides by trees so tall that they make" +
                    " it look like the bottom of a well.",
                    "A small pond interrupts the otherwise continuous" +
                    " carpet of vegetation.",
                    "Here a small pond has formed between the trees."});

                barrier_line_2 =
                    ({"The pond prevents travel to the",
                    "The pond looks just deep enough to" +
                    " prevent you from travelling",
                    "The pond seems placid and innocuous, but" +
                    " it blocks your way",
                    "The is a modest barrier, but a" +
                    " barrier nonetheless which blocks your way"});

                barrier_line_3 = ({});

                add_item(({"pond", "small pond"}),
                    "The pond is still and seems to" +
                    " harbor nothing more than a few" +
                    " insects and fish.\n");

                add_item(({"fish"}),
                    "There seem to be a few fish swimming in" +
                    " the pond, but they are too deep below" +
                    " the surface for you to examine any closer.\n");

                add_item(({"insect", "insects"}),
                    "An occasional flying insect touches the" +
                    " surface of the water for a brief second," +
                    " but the fish don't seem the least" +
                    " bit interested in them." +
                    " Neither are you.\n");

                set_short("By a pond in the forest");
                add_prop(OBJ_I_CONTAIN_WATER, 1);

                break;

                case "rapids":

                barrier_line_1 =
                    ({"The forest is bordered by a rushing" +
                    " river; its torrents surge",
                    "At the forest edge a rushing river churns"});

                barrier_line_2 =
                    ({" far too violently for anyone" +
                    " to consider swimming across.",
                    ", threatening to carry away the" +
                    " closest trees despite" +
                    " their formidable bulk."});

                barrier_line_3 =
                    ({"The river prevents travel to the",
                    "The river blocks your way",
                    "No further travel is possible",
                    "The river is unfordable and" +
                    " completely obstructs any movement"});

                add_item(({"river", "rushing river"}),
                    "The river surges swiftly" +
                    " to the " + work[n+1] + " with" +
                    " such force that the entire surface is churned" +
                    " white. It is obviously impossible for you" +
                    " to cross it.\n");

                add_item(({"surface", "foam"}),
                    "The surface of the river is completely opaque" +
                    " with foam from the churning of the" +
                    " vigorous current.\n");

                set_short("By a river in the forest");
                add_prop(OBJ_I_CONTAIN_WATER, 1);

                break;

                case "river":

                barrier_line_1 =
                    ({"The forest is bordered by a wide river;",
                    "The forest ends abruptly at the edge of" +
                    " a wide river;"});

                barrier_line_2 =
                    ({" its deceptively placid surface" +
                    " is betrayed by floating debris" +
                    " whose brisk travel reveals a" +
                    " swift and powerful current. the" +
                    " swift departure of bits of debris warns" +
                    " of a forceful current beneath" +
                    " the smooth surface."});

                barrier_line_3 =
                    ({"The river prevents travel to the",
                    "The river blocks your way",
                    "No further travel is possible",
                    "The river is unfordable and" +
                    " completely obstructs any movement"});

                add_item(({"river", "wide river"}),
                    "The river flows relentlessly to the " + work[n+1] +
                    " and would likely carry in the" +
                    " same direction anything that might fall in.\n");

                add_item(({"surface", "debris", "litter"}),
                    "The river's surface carries a steady" +
                    " stream of small debris composed of" +
                    " leaves and other common forest litter.\n");

                set_short("By a river in the forest");
                add_prop(OBJ_I_CONTAIN_WATER, 1);

                break;

                case "stream":

                barrier_line_1 =
                    ({"A deep stream cuts through the forest" +
                    " on its way",
                    "The forest is divided here by a" +
                    " deep stream that rushes toward the"});

                barrier_line_2 = ({"."});

                barrier_line_3 =
                    ({"The stream prevents travel to the",
                    "The stream blocks your way",
                    "No further travel is possible",
                    "The stream's depth and rapid current" +
                    " completely obstruct any movement"});

                add_item(({"stream", "deep stream"}),
                    "The stream cuts deep into the ground as" +
                    " it rushes to the " + work[n+1] + ".\n");

                set_short("By a stream in the forest");
                add_prop(OBJ_I_CONTAIN_WATER, 1);

                break;

                case "thicket":

                barrier_line_1 =
                    ({"The tall trees give way to a thicket" +
                    " which, although composed of smaller plants," +
                    " is so dense with thorns and tough branches" +
                    " that it is impassible.",
                    "A thicket has grown up here at the edge" +
                    " of the forest, filling in every bit of" +
                    " space between the trees. While the" +
                    " plants are not particularly tall, they are" +
                    " exceedingly dense, thorny, and impenetrable.",
                    "A dense and tangled thicket poses" +
                    " an impenetrable barrier here, but there" +
                    " are still several directions in which" +
                    " you can travel.",
                    "Among the trees a dense thicket has grown" +
                    " which blocks your progress" +
                    " in several directions."});

                barrier_line_2 =
                    ({"The thicket prevents travel to the",
                    "The thicket blocks your way",
                    "The tangled and twisted thicket bars any" +
                    " travel to the",
                    "The thicket is an impassible barrier" +
                    " to any traveller headed"});

                barrier_line_3 = ({});

                add_item(({"thicket", "plants"}),
                    "The thicket is composed of a battery of" +
                    " formidable plants: twisted vines thicker than" +
                    " your arm, thorns like daggers, tough" +
                    " branches so intertwined that you can't begin" +
                    " to tell where one ends and another begins. It's" +
                    " no wonder that even the mighty " + trees[0] +
                    " trees don't encroach on this space!\n");

                set_short("A thicket in the forest");

                break;

                }

            /*  Rapids, river, and stream use a third parameter to account for
                flow direction; other barriers need only two parameter.  */

            if (sizeof(barrier_line_3))

                {

                text = text +
                    " " + barrier_line_1[random(sizeof(barrier_line_1))] +
                    " " + work[n+1] +
                    barrier_line_2[random(sizeof(barrier_line_2))];

                /*  If the next element in the array is not a barrier, it must
                    be a direction indicator. */

                if (member_array(work[n+2], barrier_list) == -1)
                    text = text +
                    " " + barrier_line_3[random(sizeof(barrier_line_3))] +
                    " " + work[n+2] + ".";

                }

            else

                {

                text = text +
                    " " + barrier_line_1[random(sizeof(barrier_line_1))];

                /*  If the next element in the array is not a barrier, it must
                    be a direction indicator. */

                if (member_array(work[n+1], barrier_list) == -1)
                    text = text +
                    " " + barrier_line_2[random(sizeof(barrier_line_2))] +
                    " " + work[n+1] + ".";

                }

            }

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
                " A trail begins here and leads " + trails[0] + ".";

            break;

            case 2:

            text = text + " A trail leads " + trails[0] +
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

        add_item(({"trail", "trails"}),
            "The trail is the result of countless footsteps" +
            " beating down the vegetation and preventing its" +
            " regrowth along a meandering route between the trees.\n");

        }

    /*  The long description for the room is finally complete!  Append the
        carriage return and load it into the proper place. */

    text = text + "\n";
    set_long(text);

    /*  Add the descriptive items for individual tree varieties. The first
        variety is required and is the dominant type in this room. */

    if (wildmatch("*h", trees[0])) s = "es";
    else s = "s";

    add_item(({trees[0] + " tree", trees[0] + "trees",
        trees[0], trees[0] + s}),
        "The lofty " + trees[0] + s + " tower over everything else" +
        " in sight. Smooth and straight, they have no branches" +
        " near the ground; instead, their limbs are clustered" +
        " high overhead, where they mesh to form a nearly" +
        " opaque canopy.\n");

    /*  Other trees, if any, get a less lofty description. */

    m = sizeof(trees);
    for (n = 1; n < m; n += 1)

        {

        if (wildmatch("*h", trees[n])) s = "es";
        else s = "s";

        add_item(({trees[n] + "tree", trees[n] + "trees",
            trees[n], trees[n] + s}),
            "The " + trees[n] + s + " rise in the midst of the" +
            " great " + trees[0] + " trees as if to challenge" +
            " them for sunlight. They look strong and healthy, but" +
            " they hardly match the magnificence of" +
            " their titanic neighbors.\n");

        }

    /*  All forest edge rooms get the following standard descriptive items.
        Since forest edge rooms are merely intended to put a nice border on the
        more interesting forest interior, the descriptions here are not as
        elaborate as those further inside. */

    n = sizeof(trees);

    switch (n)

        {

        case 1:

            add_item(({"tree", "trees"}),
                "The trees are all of ancient age and formidable" +
                " size. Remarkably uniform in height, they are about as" +
                " tall as any " + trees[0] + " tree you have ever seen.\n");

            break;

        case 2:

            if (wildmatch("*h", trees[1])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "The trees are a mixture of " + trees[0] +
                " and " + trees[1] + ". Reaching to staggering heights," +
                " the " + trees[0] + " trees steal most of the sunlight" +
                " from the " + trees[1] + s + ", which nonetheless seem" +
                " to be flourishing.\n");

            break;

        case 3:

            if (wildmatch("*h", trees[0])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + trees[1] + " and " + trees[2] + " trees" +
                " of lesser but still impressive dimensions. The" +
                " ground here must be quite fertile to support" +
                " such extraordinary growth.\n");

            break;

        default:

            if (wildmatch("*h", trees[0])) s = "es";
            else s = "s";

            add_item(({"tree", "trees"}),
                "Under the shadow of the towering " + trees[0] + s +
                " grow " + implode(trees[1..(n-2)], ", ") +
                " and " + trees[n-1] + " trees, also of impressive" +
                " size. Surely interesting things must lurk within" +
                " stands of trees of such size and variety.\n");

            break;

        }

    add_item(({"canopy", "treetops"}),
        "The trees grow so close together that their tops form" +
        " a continuous canopy and block almost all sunlight from" +
        " reaching the ground within the forest depths.\n");

    add_item(({"vegetation", "plants", "plant"}),
        "The ground is covered with a dense carpet of leaves" +
        " and vines which grow vigorously under the trees" +
        " despite the shady conditions.\n");

    /*  Special properties used by forest room functions.  */

    add_prop(FOREST_TREE_TYPES, trees);
    add_prop(FOREST_LOCATION, this_location);
    add_prop(FOREST_ADJACENT_ROOMS, adjacent_rooms);

    /*  Forest edge rooms typically have fewer than 8 exits in all compass
        directions, all of them obvious. I could use a loop for this, but I
        decided to trade a little space in the baseroom code for faster
        execution. */

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
