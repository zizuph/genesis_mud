/*
 * Base room for village settlement
 * Finwe, November 2015
 */

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_INDOORS_BASE;
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";

void create_house()
{
}

void
create_indoor_room()
{
    setuid();
    seteuid(getuid());
//    ::create_faerun_room();
    add_prop(ROOM_S_MAP_FILE, "thornhold_map.txt");

    add_prop(ROOM_I_LIGHT, 2);  // Lamps add extra light.
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're mess

	add_item(({ "wall", "walls" }),
		"The walls are constructed of thick gray stone, chiseled into " +
		"wide bricks that are set with coarse mortar.\n");
		
	add_item(({ "bricks" }),
		"The bricks appear to be made of a type of granite and " +
		"are texutered from extensive chiselwork.\n");
		
	add_item(({ "floor", "down" }),
		"The floor is made of broad planks of weathered oak.\n");

	add_item(({ "ceiling", "up" }),
		"Broad oaken beams support the ceiling of the fortress.\n");

	add_item(({ "door", "doorway" }),
		"The doorway is a threshold constructed of oaken beams, " +
		"and a thick oak door attached with wrought-iron hinges " +
		"is propped open to accomodate the bustle of activity " +
		"that is common in the fortress.\n");
		
    set_room_tell_time(60 + random(60));
    reset_faerun_room();

    create_house();
}
	

void
reset_faerun_room()
{
}

void
init()
{
    ::init();
}

/*
 * Function name : add_doorknob
 * Description   : adds descr of doorknobs
 */
void
add_doorknob()
{
    add_item("doorknob",
        "The doorknob is small enough to fit in your hand, round, and " +
        "made of wood.\n");
}

/*
 * Function name : add_candles
 * Description   : adds descr of candles
 */
void
add_candles()
{
    add_item(({"candle", "candles"}),
        "The candles are large and scattered around the room. They are " +
        "golden yellow and made of beeswax.\n");
}

/*
 * Function name : add_rug
 * Description   : adds descr of rug
 */
void
add_rug(string shape)
{
    add_item(({"rug", "carpet"}),
        "It is large and made from braided strips of cloth. The rug is " +
        shape + " shaped. It covers the floor and looks well worn.\n");

}

string
move_rug()
{
    return "You lift up the rug and look under it. There's nothing under " +
        "it, so you put it back.\n";
}


string
open_dresser()
{
    return "You try to open the drawers in the dresser but discover they " +
        "won't open. They must be locked.\n";
}


string
open_drawers()
{
    return "Open what, the dresser drawers or the vanity drawers?\n";
}

void
add_floor(string str)
{
    add_item(({"floor", "down", "ground"}),
        "The floor is made of wood planks. They are smooth and worn in " +
        "places, and very clean. " + str + "\n");
    add_item(({"wood planks", "planks"}),
        "The planks of wood are wide and make up the floor. Visible " +
        "paths have been worn into them.\n");
}

void
add_plain_walls(string str)
{
    add_item("walls",
        "The walls are plain and have been been painted white" + str + ".\n");
}

void
add_plain_ceiling(string str)
{
    add_item(({"ceiling", "up"}),
        "The ceiling is plain. Like the walls, it has been painted white. " +
        str + "\n");
}
/*
 * Function name : add_staircase_up
 * Description   : describes staircase leading upstairs
 */
void
add_staircase_up()
{
    add_item(({"staircase", "stairs", "staircase"}),
        "The staircase is set against the back wall. It is made of " +
        "solid pieces of wood and looks very sturdy. It leads upstairs.\n");
    add_item(({"stairsteps", "stair steps"}),
        "They are made of solid wood planks and make up the staircase.\n");
    add_item("stairwell",
        "It is a large hole for the staircase. It is in the back of " +
        "the room and leads upstairs.\n");
}

/*
 * Function name : add_staircase_down
 * Description   : describes staircase leading stairs
 */
void
add_staircase_down()
{
    add_item(({"staircase", "stairs", "staircase"}),
        "The staircase is set against the back wall. It is made of " +
        "solid pieces of wood and looks very sturdy. The staircase leads " +
        "downstairs.\n");
    add_item(({"stairsteps", "stair steps"}),
        "They are flat, solid planks of wood that make up the staircase.\n");
    add_item("stairwell",
        "It is a large hole for the staircase. It is cut into the floor " +
        "in the back of the room and leads downstairs.\n");
}
/*
 * Function name : add_staircase_closet
 * Description   : describes staircase closet for Tom's hallway
 */
void
add_staircase_closet()
{
    add_item(({"small door", "door", "closet door"}),
        "The small door is set underneath the staircase. The top " +
        "is rounded with a small doorknob. The doorknob is on " +
        "right side of the door about halfway down. The door is closed.\n");
    add_item(({"closet"}),
        "It is situated under the staircase. There is a small door " +
        "leading to it.\n");
    add_doorknob();
}

string
open_closet_door()
{
    return "You try to open the closet door but it won't open. The door " +
        "must be stuck or locked.\n";
}

void
add_dining_room()
{
    add_item(({"dining room table"}),
        "The table is made from wood and sits in one corner of the room. " +
        "The table is oval shaped and a natural color. It looks well " +
        "used and has some chairs set around it.\n");
    add_item(({"chairs", "dining room chairs"}),
        "They are made of wood and set around the dining room table. Each " +
        "chair has a seat with cushion and a high back.\n");
}

void
add_windows()
{
    add_item(({"large windows", "windows"}),
        "They are tall, rectangular panes of glass. The windows are set " +
        "in the front of the room, looking out onto the street and " +
        "gardens. Drapes hang in front of the windows.\n");
    add_item(({"gardens"}),
        "They grow in front of the windows. Not much can be made out " +
        "of them since you are indoors.\n");
    add_item(({"street", "road"}),
        "You can't see much of the road from inside.\n");
}

void
add_paintings()
{
    add_item(({"pictures", "paintings"}),
        "They are paintings of natural scenes and hang on the walls. Some " +
        "pictures are paintings of family members.\n");
    add_item(({"natural scenes"}),
        "They are paintings of nature, of flowers and forest scenes.\n");
    add_item(({"flowers", "flower painting", "painting of flowers"}),
        "The painting is of a vase of flowers. It hangs on a wall\n");
    add_item(({"family members", "painting of family members"}),
        "The picture of the family members is large and hangs on one wall. " +
        "It shows the parents and children dressed nicely.\n");
    add_item(({"picture frames", "frames"}),
        "The picture frames are simple and made from solid wood. They are " +
        "stained a dark color.\n");
    add_item(({"forest", "forest painting", "painting of forest"}),
        "The painting is life like an shows a forest of pine trees.\n");
}
/*
 * Function name : add_great_room
 * Description   : adds descr of great room furniture
 */
void
add_great_room()
{

    add_item(({"furniture"}),
        "It is all made of wood and spread around the room. There is a " +
        "sofa, some end tables, and pictures on the wall.\n");

    add_item(({"sofa", "couch"}),
        "This is a long seat able to sit three or four people. It has " +
        "several cushion and looks comfortable to sit on.\n");
    add_item(({"cushions"}),
        "They are rectangular in shape, and over stuffed. The cushions are " +
        "on the sofa and chairs.\n");

    add_item(({"tables"}),
        "They are made of wood and look sturdy. There is a dining room " +
        "table and an end table.\n");
    add_item(({"end table"}),
        "This is a low rectangular table. It is made of wood and sits " +
        "next to the sofa. It's stained a dark brown and looks well used.\n");
    add_paintings();
}

/*
 * Function name : add_master_bedroom
 * Description   : adds descr of master bedroom
 */
void
add_bedroom()
{

    add_item(({"pillows", "pillow", "fluffy pillows", "fluffy pillow"}),
        "There are several soft and fluffy pillows on the bed. " +
        "They are white and sit at the head of the bed.\n");
     add_item("dresser",
        "The dresser is wide and carved from wood. It has four large " +
        "drawers on both sides, which are closed. The top of the " +
        "dresser is empty. \n");
    add_item("dresser legs",
        "The legs of the dresser are plain, straight, and squared.\n");
    add_item(({"wardrobe", "closet", "clothes closet"}),
        "This is a tall cabinet. It is made of wood, wide, and designed " +
        "to hold clothes. The doors are ornately carved and closed. The " +
        "wardrobe is set in a corner of the room.\n");
}


/*
 * Function name : add_kitchen
 * Description   : adds descr of kitchen
 */
void
add_kitchen()
{
    add_item(({"stove"}),
        "The stove is large and black, dominating a wall. " +
        "It is made of steel with rounded corners. The surface is " +
        "flat. There are two large doors on the front of the stove.\n");
    add_item(({"steel doors", "large doors"}),
        "The large doors are closed on the front of the stove. " +
        "They open, allowing foods to be baked inside the stove. \n");
    add_item(({"cupboards"}),
        "The cupboards are tall and made of wood. They are closed " +
        "and line the walls. The cupboards are used to store " +
        "food and kitchen utensils.\n");
    add_item(({"kitchen utensils", "food", "utensils"}),
        "You don't find any. They are presumably stored in the " +
        "cupboards.\n");
    add_item(({"counter", "counters"}),
        "The counters attached to the walls and waist-high. The are " +
        "wide and look well used in preparing meals for the family.\n");
}

/*
 * Function name : add_kids_bed
 * Description   : adds descr of kids bed
 */
void
add_kids_bed()
{
    add_item(({"small bed", "kid's bed", "kids bed"}),
        "It's made from wood and smaller than an adult's bed. Colorful " +
        "blankets cover the bed. Some fluffy pillows sit at the head " +
        "of the bed.\n");
    add_item(({"blankets", "blanket", "colorful blankets", "color blanket"}),
        "They are rectangular pieces of thick cloth. They are colorful and " +
        "spread acrossed the small bed. The blankets are tucked in with " +
        "fluffy pillows set at the head.\n");

}

/*
 * Function name : large_bed
 * Description   : adds descr of large bed
 */
void
add_large_bed()
{
    add_item(({"bed", "large bed"}),
        "The bed is large and set against a wall. It is ornately carved " +
        "of wood by an expert carpenter. Large quilts are spread across it. " +
        "Some fluffy pillows are set at the head of the bed.\n");
        add_item("mattress",
        "The mattress is thick and comfortable looking. It is probably " +
        "full of feathers and covered with a white cotton linen cloth.\n");
    add_item(({"quilts", "large quilts"}),
        "They are thick and warm looking. The quilts are hand sewn and " +
        "made from pieces of cloth. The quilts are spread across the bed.\n");
}

void
add_fireplace()
{
// fireplace
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the room with " +
        "a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is made from large " +
        "blocks of stone. It is as tall as an elf and burns continuously. " +
        "The fire light fills the room a gentle yellow glow and the " +
        "warmth comforts you. The fireplace has a large brass screen " +
        "in front of it to prevent logs from rolling out and to keep " +
        "sparks inside. A large stone hearth sits in front of the " +
        "fireplace.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of brass. The " +
        "panels are made of woven brass wires that have been stretched " +
        "across each panel, preventing " +
        "sparks from flying out but allowing light to fill the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of smooth stones. Its purpose is " +
        "to catch any falling items or errant sparks from the fire. The " +
        "hearth extends a little bit the width of the fireplace. It " +
        "extends out from the fireplace about the length of a human. \n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend the " +
        "fire and stoke it when necessary. They are made of hardened " +
        "steel and include a shovel, poker, and a set of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to clean " +
        "the fireplace out. It is about the size of a snow shovel with " +
        "a large mouth for scooping ashes and fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white and turn " +
        "from gray to black the further from the flames they are.\n");
    add_item("fireplace debris",
        "Around the edges of the fire you see partially burned twigs, " +
        "sticks, and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
                "partially burned logs", "burned logs",
                "burned twigs", "burned sticks"}),
        "They are the remains from yesterday's fire and are scattered " +
        "around the perimeter of the fire. The ends are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a point " +
        "and just below the point is a curved claw, useful for poking " +
        "the fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined together " +
        "by a steel pin. The ends of the tongs are shaped like claws " +
        "and are used for grasping logs and placing them in the fire " +
        "or for moving wood around within the fireplace. They are made " +
        "of hardened steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. They are " +
        "joined together at the front with a strip of leather. A tube " +
        "is set into the center to direct the airflow. The sides and " +
        "back of the instrument are joined together with a large piece " +
        "of tanned hide. When pumped, the bellows blow a stream of air " +
        "into the fire, improving the draft of the fire.\n");

    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("A log breaks, sending a shower of sparks flying " +
        "up the chimney.");
    add_room_tell("The fire flares, filling the room with a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the room.");

}