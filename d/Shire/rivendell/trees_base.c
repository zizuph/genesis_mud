/*
 * Base file for trees in the forest of Rivendell
 * Modified from ~Shire/examples by Finwe
 * March 1999
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
 
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
 
void create_tree_room() {}

public void
create_area_room()
{
    set_area("of a tree in");
    set_areaname("a forest");
    set_land("Eriador");
    set_areatype(0);
    set_areadesc("large branch");
    set_grass("sparse, dry");
    set_treetype("conifer");

//    set_short("@@short_desc@@");
    add_item(({"evergreen trees", "conifer trees", "evergreen",
        "evergreens", "conifers", "conifer", "trees"}),
        "Evergreen trees are everywhere, although you can't see " +
		"much from up here in this tree.\n");
	add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
        "cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
        "cedar trees", "cedar tree"}),
        "You can't make out what they are since this tree " +
		"blocks your view\n");
    add_item(({"ground", "path", "forest debris", "debris",
        "forest's floor", "floor"}),
        "You can't see that from up here\n");
    add_item("down",
        "The branch you stand on is sturdy. It bends slightly " +
		"under your weight.\n");
    add_item(({"branch", "branches"}),
        "The branches are thick from age and bend slight " +
		"in the breeze.\n");
    add_item(({"leaves", "leaf"}),
        "You don't see any from up here.\n");
    add_item(({"needles", "pine needles"}),
        "They are green and smell sweetly. The needles are " +
		"long and sharp.\n");
    add_item(({"mountains", "misty mountains", "mountain"}),
        "The Misty Mountains rise up before you. Their peaks " +
        "are buried in the clouds. Their sides are " +
        "covered with trees up until the snow line. Tales tell " +
        "of the mountains infested with all kinds of orcs and " +
        "trolls, making travel through the mountains dangerous.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "@@daylight_desc@@ filters through the tree " +
        "soaking the branches in patches of @@light_type@@.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("You feel as if something is watching you.");
    add_room_tell("A branch above you suddenly moves.");
    add_room_tell("Suddenly the forest becomes silent.");
    add_room_tell("A startled bird flaps its wings and flies " +
	    "out of the tree.");
    add_room_tell("A branch crashes down from trees above you.");
    add_room_tell("A cold breeze blows down from the mountain.");
    add_room_tell("The sound of a woodpecker fills the " +
        "air around you.");
    add_room_tell("A sudden movement catches your eye.");
    add_room_tell("Squirrels dart about the branches above you.");
    add_room_tell("An angry squirrel chatters at you.");
    add_room_tell("A strong gust of wind almost knocks " +
	    "you out of the tree.");

    create_tree_room();

    add_prop(ROOM_I_INSIDE, 0); /* This is an outdoor room. */

    add_prop(ROOM_I_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_FROM, 
        "A great elven-power prevents that from happening.\n");

    set_no_herbs();  /* don't want players herbing up here. */

}
/*
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
			return "On a hidden track in a forest";
			break;
		default:
			return "In a deep forest";
			break;
	}
}


 
string
forest_desc()
{
    switch(random(4))
    {
        case 0:
            return "All around you the forest climbs up the " +
            "Misty Mountains. The mountains are covered with " +
            "different species of trees which grow on every " +
            "available patch of earth. The ground is littered " +
            "with branches, rotting trees, and other forest " +
          "debris. ";
            break;
        case 1:
            return "The Misty Mountains rise up before you. " +
            "Evergreens cover the landscape. The " +
            "ground is covered with broken branches, pine " +
            "needles, and some rotting logs. ";
            break;
        case 2:
            return "You can't help but feel small as you look " +
            "around the forest. The mountains loom up before " +
            "you. They are covered with evergreens which thin " +
            "towards the top. Everywhere you look, the sides of " +
            "the mountains are covered with various plants and " +
            "flowers. Thick undergrowth blocks your path here. ";
            break;
        case 3:
            return "As you look around, the forest becomes " +
            "thicker here. Thick trees block your view here. " +
            "Dense undergrowth grows here. Stunted trees cover " +
            "some rock outcroppings as they struggle to live. " +
            "The ground is covered with broken branches and " +
            "pine needles. ";
            break;
 
        default:
            return "The trees move in " +
            "the wind that blows off the Misty Mountains. Dense " +
            "forest litter covers the ground here. Stunted " +
            "trees grow on exposed rocks. Standing here, it is " +
            "almost impossible to see which way to go. ";
            break;
     }
}

*/
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
 

