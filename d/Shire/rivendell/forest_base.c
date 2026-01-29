/*
 * Base file for forest of Rivendell
 * Modified from ~Shire/examples by Finwe
 * November 1997
 * 
 * Added numeric checks for who can wander in forest. 
 * By default, if check_players is not set in file, its value is set
 * to 0 and will allow anyone who has done elrond's quest and noldor
 * to see the exits. Other values allow other guilds to see the exits
 * and even have secret paths thru the forest. See check_person() 
 * to see how it is set up. check_person() is used in exit routines.
 * -- Finwe, July 2004
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include "/d/Shire/guild/noldor/noldor.h"
inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
//inherit "/d/Shire/rivendell/gs_include";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */

#define QUEST_NAME      "forest"

//string moon_dir = "", star_dir = "";

string herb_here; 
static string add_white_stone = "";
int check_players = 0;
int see_exit = 2; // 0 = player can see/use exit, 2 player cannot see/use exit
 
void create_forest_room() {}
 
 
public void
create_area_room()
{
    set_area("somewhere in the Lone-lands on");
    set_areaname("the Misty Mountains");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("track");
    set_grass("sparse, dry");
    set_treetype("conifer");
 
    set_short("@@short_desc@@");
    add_item(({"thick trees", "thick tree"}),
        "They are ancient and giant in size. Their tops reach " +
        "to the sky and dwarf the trees below them.\n");
    add_item("stunted trees",
        "These trees grow on the rock outcroppings. They are " +
        "deformed and twisted by the harsh elements.\n");
    add_item(({"rocks", "pebbles", "coloured rocks", "coloured pebbles",
            "coloured rock", "coloured pebble"}),
        "Different colored rocks and pebbles are scattered " +
        "about the ground. They are the color of the mountains " +
        "and surrounding area.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a diverse number of plants grow in the " +
        "forest. Flowers and bushes grow everywhere, many " +
        "hampering your travel and blocking your view.\n");
    add_item(({"bushes", "shrubs"}),
        "Bushes of different color and sizes grow everywhere. " +
        "Some are thick and block your view while others are " +
        "thin and spindly.\n");
    add_item(({"moss", "mosses"}),
        "Moss can be seen growing on logs, rocks, on trees, and " +
        "under the trees in patches. It is healthy and a deep " +
        "green. Some patches of moss are so large that bumps " +
        "can be seen under them.\n");
    add_item(({"lichen", "lichens"}),
        "Lichen can be seen on some rocks and trees. It is grey " +
        "and white coloured. Some are simple while others are " +
        "large and fan shaped\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them " +
        "are partially buried in the ground or the forest debris.\n");
    add_item(({"flowers", "wild flowers"}),
        "Various wild flowers are growing about the forest, " +
        "scattered about among the forest's floor. They are " +
        "white, yellow, pink, and other bright colours. They " +
        "add colour to the forest and sway in the breezes.\n");
    add_item(({"tree","trees"}),
        "Evergreens, the dominant tree in this part of the " +
        "forest, grow thick here.\n");
    add_item(({"evergreen trees", "conifer trees", "evergreen", 
        "evergreens", "conifers", "conifer"}),
        "The dominate evergreen trees here are tall pines. Also " +
        "growing here are hemlocks and some cedars. The trees reach " +
        "to the sky and block out much of the light.\n");
    add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
        "cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
        "cedar trees", "cedar tree"}),
        "These evergreens dominate the forest. Some grow on the rocks " +
        "in a scraggly manner.\n");
    add_item(({"ground", "forest debris", "debris", 
        "forest's floor", "floor", "down"}),
        "The ground is littered with dead branches, pine needles, " +
        "and some fallen trees.\n");
    add_item(({"leaves", "leaf"}),
        "You see a mat of both fresh and dead leaves covering the " +
        "ground. Poking out of them are dead branches, some " +
        "plants, stones, and other signs of a living forest.\n");
    add_item(({"fallen branches", "dead branches", "dead branch", 
            "branches", "branch"}),
        "They are broken and lay scattered across the ground. " +
        "Some look like they just fell from the trees, " +
        "splintered and twisted. They lay on the ground in " +
        "various stages of decomposition.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the " +
        "forest's floor.\n");
    add_item(({"needles", "pine needles"}),
        "Some fresh and dead pine needles litter the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lay rotting under a blanket of fallen " +
        "pine needles and forest debris.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs are in various forms of decomposition. " +
        "Some are hollowed out and look to be homes for " +
        "woodland animals.\n");
    add_item(({"peaks", "mountain peaks"}),
        "They are hard to see with the trees moving about. " +
        "Nonetheless, some snow-capped tops can be seen as well " +
        "as some buried in the clouds.\n");
    add_item(({"mountains", "misty mountains", "mountain"}),
        "The Misty Mountains rise up before you. Their peaks " +
        "are buried in the clouds. Their sides are " +
        "covered with trees up until the snow line. Tales tell " +
        "of the mountains infested with all kinds of orcs and " +
        "trolls, making travel through the mountains dangerous.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "@@daylight_desc@@ filters through the tall trees " +
        "covering the ground in patches of @@light_type@@. " +
        "Tall trees are everywhere, some have fallen over and block " +
        "paths in the forest while others grow tall and block the " +
        "sky above. Fallen branches, leaves, pine needles, and other " +
        "debris cover the forest's floor.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow under the trees, making travel " +
        "through the forest difficult and obscuring your way.\n");
    add_item(({"outcroppings", "rock outcroppings", 
            "rock outcropping", "outcropping"}),
        "These bits of rock protrude from the ground. They are " +
        "weather beaten with a few trees clinging to them, " +
        "trying to grow in the dense forest.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("You feel as if something is watching you.");
    add_room_tell("A fox creeps by.");
    add_room_tell("The bushes rustle next to you.");
    add_room_tell("A branch above you suddenly moves.");
    add_room_tell("Suddenly the forest becomes silent.");
    add_room_tell("A large bird screams in the sky above you.");
    add_room_tell("A branch crashes down from trees above you.");  
    add_room_tell("A leaf falls gently to the ground."); 
    add_room_tell("A cold breeze blows down from the mountain.");
    add_room_tell("Nearby, you hear an animal forage in " +
        "the underbrush.");
    add_room_tell("A tap-tap-tap-tap-tap sound fills the air.");
    add_room_tell("A sudden movement catches your eye.");
    add_room_tell("Squirrels dart about the branches above you.");
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents teleporting there.\n");

    create_forest_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

//    add_std_herbs("forest");
/*
    add_prop(OBJ_I_SEARCH_TIME, 4);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    set_search_places(({"bush","bushes","trees"}));
*/

 
}

add_forest_herbs()
{
    herb_here = ONE_OF_LIST(({GONDOR_HERB_DIR + "astaldo",
                GONDOR_HERB_DIR + "athelas",
                GONDOR_HERB_DIR + "attanar",
                GONDOR_HERB_DIR + "seregon",
                GONDOR_HERB_DIR + "suranie",
                SHIRE_HERB_DIR + "huckleberry",
                SHIRE_HERB_DIR + "lianor_berry",
                SHIRE_HERB_DIR + "grass",
                KRYNN_HERB_DIR + "tiger_lily",
                SHIRE_HERB_DIR + "bilberry",
                SHIRE_HERB_DIR + "maroea",
                "/d/Faerun/herbs/herb_files/amaranth"}));

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    set_search_places(({"bush","bushes","trees"}));
    add_herb_file(herb_here);
} 

string short_desc()
{
    switch(random(5))
	{
		case 0:
			return "In the Misty Mountains";
			break;
		case 1:
			return "Deep in a forest on the foothills of the " +
			"Misty Mountains";
			break;
		case 2:
			return "In the foothills of the Misty Mountains";
			break;
		case 3:
			return "Somewhere in a dark forest";
			break;
		case 4:
			return "Lost in a dark forest";
			break;
		default:
			return "In a deep forest";
			break;
	}
}

string forest_desc1()
{
    return "All around you the forest climbs up the " +
    "Misty Mountains. The mountains are covered with " +
    "different species of trees which grow on every " +
    "available patch of earth. The ground is littered " +
    "with branches, rotting trees, and other forest " +
    "debris. ";
}

string forest_desc2()
{
    return "The Misty Mountains rise up before you. " +
    "Evergreens cover the landscape. The " +
    "ground is covered with broken branches, pine " +
    "needles, and some rotting logs. ";
}


string forest_desc3()
{
    return "The mountains loom in the distance. " +
    "They are covered with evergreens which thin " +
    "towards the top. The sides of " +
    "the mountains are covered with various plants and " +
    "flowers. Thick undergrowth blocks your path here. ";
}

string forest_desc4()
{
    return "The forest is " +
    "thicker here. Tall trees block the view here. " +
    "Dense undergrowth grows here. Stunted trees cover " +
    "some rock outcroppings as they struggle to live. " +
    "The ground is covered with broken branches and " +
    "pine needles. ";
}

string forest_desc5()
{
    return "The trees move in " +
    "the wind that blows off the Misty Mountains. Dense " +
    "forest litter covers the ground here. Stunted " +
    "trees grow on exposed rocks. Standing here, it is " +
    "almost impossible to see which way to go. ";
}

string forest_desc6()
{
    return "A wide chasm opens up before you. Pebbles and rocks " +
        "roll off into its depths. Stunted trees grow along its " +
        "edges and along the exposed rocks. On this side of the " +
        "chasm, the trees grow thick up to its edge. ";
}


string
daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Gentle sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Blazing afternoon sunlight";
        case EVENING:
            return "Evening light";
    }
}

 
string
day_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}
 
string
light_type()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle nightlight";
    }
}
 
check_person()
{
// if player has done elrond's quest or is a Noldor, 
// they may see the forest exits.
    
// if they searched the leaves, remove prop so they have to search
// the next room
    if (TP->query_prop(LEAF_PROP))
    {
        TP->remove_prop(LEAF_PROP);
    }
/*
    if (CHECK_QUEST(TP, QUEST_NAME) || IS_MEMBER(TP)) 
        return 0;
    else
        return 1;
*/


    switch(check_players)
    {
        case 0:
            // anyone who has done elrond's quest, noldor, rangers, and dunadan
            if (CHECK_QUEST(TP, QUEST_NAME) || IS_NOLDOR(TP) || IS_RANGER(TP)
                    || IS_DUNADAN(TP))
            {
                see_exit = 0;                    
                return 0;
            }
            else
            {
                see_exit = 2; // cannot see exit
                return 1;
            }
            break;
        case 1:
        {
            // allow all rangers, noldor, and dunadan to use these exits
            if (IS_RANGER(TP) || IS_NOLDOR(TP) || IS_DUNADAN(TP)) 
            {
                see_exit = 0;
                return 0;
            }
            else
            {
                see_exit = 2;
                return 1;
            }
            break;
        }
        case 2:
        {
           // allow only rangers and noldor to use these exits
            if (IS_RANGER(TP) || IS_NOLDOR(TP)) 
            {
                see_exit = 0;
                return 0;
            }
            else
            {
                see_exit = 2;
                return 1;
            }
            break;
        }
        default:
        {
            // anyone who has done elrond's quest, noldor, rangers, and dunadan
            if (CHECK_QUEST(TP, QUEST_NAME) || IS_NOLDOR(TP) || IS_RANGER(TP)
                    || IS_DUNADAN(TP)) 
            {
                see_exit = 0;
                return 0;
            }
            else
            {
                see_exit = 2;
                return 1;
            }
            break;
        }
    }
}


/*
// Obsolete routine. consolidated into check_person();
// Finwe, July 2004

elrond_friend()
{
// if player is a ranger, a dunadan, or a Noldor, they may see 
// these secret forest exits.

    if (IS_RANGER(TP) || IS_MEMBER(TP) || IS_DUNADAN(TP)) 

        return 0;
    else
        return 1;



}
*/

/*
 * Function name : set_add_white_stone
 * Description   : adds descr for white stone markers
 */
void set_add_white_stone(string star_dir, string moon_dir)
{
    add_item("white stone",
        "You see a white stone. It is buried by fallen leaves and " +
        "twigs. A star is engraved on the " + star_dir + " of " +
        "the stone and a moon engraved on the " + moon_dir + 
        " of the stone.\n");
    add_item("moss",
        "It is a verdant green color, looking velvet in the " +
        "dappled light. The moss grows over and across the " +
        "stones, covering them in a blanket of green.\n");
    add_item("heather",
        "The heather is a rich green color with tiny yellow " +
        "bell-shaped flowers. The plant is covered with tiny " +
        "leaves and crawls all over the floor of the forest.\n");
    add_item(({"leaf","leaves"}),
        "You see a mat of both fresh and dead leaves covering the " +
         "ground. Poking out of them are dead branches, some plants, " +
         "stones, and other signs of a living forest. @@exa_leaves@@\n");
}

string
exa_leaves()
{
    if(CHECK_STATS)
    {   
        TP->add_prop(LEAF_PROP,1);
        return "Hidden between the leaves you find a white stone.";
    }
    else
       return "";
}


check_player(int i)
{
// if player has done elrond's quest or is a Noldor, 
// they may see the forest exits.
    
// if they searched the leaves, remove prop so they have to search
// the next room
    if (TP->query_prop(LEAF_PROP))
    {
        TP->remove_prop(LEAF_PROP);
    }
/*
    if (CHECK_QUEST(TP, QUEST_NAME) || IS_MEMBER(TP)) 
        return 0;
    else
        return 1;
*/


    switch(i)
    {
        case 0:
            // anyone who has done elrond's quest, noldor, rangers, and dunadan
            if (CHECK_QUEST(TP, QUEST_NAME) || IS_NOLDOR(TP) || IS_RANGER(TP)
                    || IS_DUNADAN(TP)) 
                return 0;
            else
                return 1;
            break;
        case 1:
        {
            // allow all rangers, noldor, and dunadan to use these exits
            if (IS_RANGER(TP) || IS_NOLDOR(TP) || IS_DUNADAN(TP)) 
                return 0;
            else
                return 1;
            break;
        }
        case 2:
        {
           // allow only rangers and noldor to use these exits
           if (IS_RANGER(TP) || IS_NOLDOR(TP)) 
                return 0;
            else
                return 1;
            break;
        }
        case 3:
        {
           // wizards only
           if (IS_SHIRE_WIZARD(TP) || IS_GONDOR_WIZARD(TP)) 
                return 0;
            else
                return 1;
            break;
        }

        default:
        {
            // anyone who has done elrond's quest, noldor, rangers, and dunadan
            if (CHECK_QUEST(TP, QUEST_NAME) || IS_NOLDOR(TP) || IS_RANGER(TP)
                    || IS_DUNADAN(TP)) 
                return 0;
            else
                return 1;
            break;
        }
    }
}
