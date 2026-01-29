/*
 *  This is the base room for the farmhouses of the Woodcutters
 *  Based on Tom Bombadil's house
 *  Updated by Finwe, November 2005
 *
 */

/*
 * Functions

close_curtains()
move_rug()
open_curtains()
open_drawers()
open_dresser()
set_add_doorknob()
set_add_fireplace()
set_add_staircase(string str)
set_add_staircase_closet()
set_extra_floor(string str)
set_extra_window(string str)
window_count(), window_position()
set_add_rug()






*/

inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>


#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */
#define ROOM_TELL_TIME  60+random(120)

int num_of_windows = 1;

void
create_house_room()
{
}

public void
create_shire_room()
{
    add_item(({"lamp","lamps"}),
        "They are simple, oil lamps with burning wicks inside of " +
        "cut crystal globes. The flames dance behind the globes, " +
        "filling the room with gentle light.\n");
    add_item("ceiling",
        "The ceiling is smooth and panelled. Large beams run the length " +
        "of the ceiling.\n");
    add_item(({"walls", "wall"}),
        "The walls are paneled with dark wood. They look warm and inviting, " +
        "and glow from the candle light in the room. Pictures hang on the " +
        "walls. @@window_num@@ set in the walls.\n");
    add_item(({"beams", "carved beams", "richly carved beams"}),
        "The beams are large and square shaped. They are spaced " +
        "evenly across the ceiling and support it. They are " +
        "stained a deep color and glow from the reflected light. " +
        "Lamps swing from the beams, filling the room with light.\n");
    add_item(({"candles", "candle"}),
        "The candles are all sizes. Some are tall and tapered " +
        "while others are short and round.\n");
    add_item(({"lights"}),
        "Lamps hang from the beams and candles burn scattered " +
        "about the room and fill the room with light.\n");
    add_item(({"wood"}),
        "It is used throughout the room, in furniture, in the floor, " +
        "the walls, even in the beams that support the ceiling. The " +
        "wood is polished and glows warmly.\n");
    set_room_tell_time(ROOM_TELL_TIME);


    add_prop(ROOM_I_LIGHT, 2);  // Lamps add extra light.
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy.

    create_house_room();
}



void
set_extra_window(string str)
{
    add_item(({"windows","window"}),
        "@@window_count@@ large and made from clear panes of glass. " +
        "Looking out, you notice it is @@day_desc@@. @@window_position@@ " +
        "covered by curtains.\n");
    add_item("curtains",
        "They are made from fabric and are open, " +
        "letting @@daylight_desc@@ fill the room.\n");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
}

/*
 * Function name : set_add_doorknob
 * Description   : adds descr of doorknobs
 */
void set_add_doorknob()
{
    add_item("doorknob",
        "The doorknob is small enough to fit in your hand, round, and " +
        "made of wood.\n");
}


/*
 * Function name : set_add_rug
 * Description   : adds descr of 
 */
void set_add_rug(string shape)
{
    add_item(({"rug", "carpet"}),
        "It is large and " + shape + " shaped. The rug fills the room " +
        "and looks well worn.\n");

}


string close_curtains()
{
    return "The curtains cannot be closed\n";
}

string open_curtains()
{
    return "You notice they are open already.\n";
}


string move_rug()
{
    return "You lift up the rug and look under it. There's " +
        "nothing under it, so you put it back.\n";
}


string open_dresser()
{
    return "You try to open the drawers in the dresser but " +
        "discover they are won't open. They must be locked.\n";
}


string open_drawers()
{
    return "Open what, the dresser drawers or the vanity drawers?\n";
}


void
set_extra_floor(string str)
{
    add_item(({"floor", "down", "ground"}),
        "The floor is made from dark hardwoods. They are smooth, " +
        "worn in places, and very clean. " + str + "\n");
    add_item(({"hardwoods", "dark hardwoods", "dark hardwood", "hardwood"}),
        "They are strips of wood and laid side by side to make up the floor. " +
        "They are of varying shades of dark and smooth.\n");

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
daylight_desc()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "moonlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle starlight";
    }
}


string window_num()
{
    if(num_of_windows >1)
        return "There are " + LANG_NUM2WORD(num_of_windows) + " windows";
    else
        return "There is a window";
}


string
window_count()
{
    if(num_of_windows >1)
        return "They are";
    else
        return "It is";
}

string
window_position()
{
    if(num_of_windows >1)
        return "The windows are";
    else
        return "The window is";
}


void set_add_fireplace()
{
    add_item("fireplace",
        "The large fireplace sits against a wall and made from large stones. " +
        "It is tall and has a fire burning in it. The fire light fills " +
        "the room with a gentle yellow glow and the warmth comforts you. " +
        "The fireplace has a large brass screen in front of it to prevent " +
        "logs from rolling out and to keep sparks inside. A large stone " +
        "hearth sits in front of the fireplace.\n");
    add_item(({"screen", "brass screen", "large brass screen"}),
        "The brass screen is made up of several panels of " +
        "brass. The panels are made of woven brass wires that " +
        "have been stretched across each panel, preventing " +
        "sparks from flying out but allowing light to fill " +
        "the room.\n");
    add_item(({"hearth", "stone hearth", "large stone hearth"}),
        "The stone hearth is made of smooth stones. Its purpose " +
        "is to catch any falling items or errant sparks from " +
        "the fire. The hearth extends out from the fireplace and " +
        "made of stone. Some fire irons sit on the hearth.\n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend " +
        "the fire and stoke it when necessary. They are made of " +
        "hardened steel and include a shovel, poker, and a set " +
        "of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to " +
        "clean the fireplace out. It is about the size of a small " +
        "snow shovel with a large mouth for scooping ashes and " +
        "fireplace debris.\n");
    add_item("ashes",
        "The ashes sitting closest to the hot flames are white " +
        "and turn from gray to black the further from the " +
        "flames they are.\n");
    add_item("fireplace debris",
        "Around the edges of the fire you see partially burned " +
        "twigs, sticks, and a few logs.\n");
    add_item(({"partially burned twigs", "partially burned sticks",
                "partially burned logs", "burned logs",
                "burned twigs", "burned sticks"}),
        "They are the remains from yesterday's fire and are " +
        "scattered around the perimeter of the fire. The ends " +
        "are burned.\n");
    add_item("poker",
        "This long pole is made of hardened steel. One end has a" +
        " point and just below the point is a curved claw, " +
        "useful for poking the fire and moving logs around.\n");
    add_item("tongs",
        "This instrument is made of two arms that are joined " +
        "together by a steel pin. The ends of the tongs are " +
        "shaped like claws and are used for grasping logs and " +
        "placing them in the fire or for moving wood around " +
        "within the fireplace. They are made of hardened steel.\n");
    add_item("bellows",
        "The bellows are made of two pieces of smooth wood. " +
        "They are joined together at the front with a strip of " +
        "leather. A tube is set into the center to direct the " +
        "airflow. The sides and back of the instrument are " +
        "joined together with a large piece of tanned hide. " +
        "When pumped, the bellows blow a stream of air into " +
        "the fire, improving the draft of the fire.\n");
    add_item(({"stone blocks", "blocks of stone"}),
        "The stone blocks are irregular in shape and are grey " +
        "colored. The stones are stacked on top of each other and " +
        "cemented together to form the fireplace.\n");

    add_room_tell("A loud pop erupts from the fireplace.");
    add_room_tell("The fire flares up briefly.");
    add_room_tell("The fire flares, filling the room with " +
        "a dim yellow glow.");
    add_room_tell("The wood burns, slumping further into the " +
        "fireplace.");
    add_room_tell("The fire slumps down slightly.");
    add_room_tell("Shadows from the flames dance across the " +
        "room.");
}

/*
 * Function name : set_add_staircase
 * Description   : describes staircase for hallway
 */
void set_add_staircase(string str)
{
    add_item(({"staircase", "stairs", "staircase"}),
        "The stairs are set against the back wall. It is made of " +
        "solid pieces of wood and looks very sturdy. " + str + "\n");
    add_item(({"stairsteps", "stair steps"}),
        "They are wooden and make up the staircase.\n");
    add_item("stairwell",
        "It is a large hole cut into the back of the ceiling " +
        "for the staircase.\n");

}

/*
 * Function name : set_add_staircase_closet
 * Description   : describes staircase closet for Tom's hallway
 */
void set_add_staircase_closet()
{
    add_item(({"small door", "door", "closet door"}),
        "The small door is set underneath the staircase. The top " +
        "is rounded with a small brass doorknob. The doorknob is on " +
        "right side of the door about halfway down.\n");
    set_add_doorknob();
}

/*
 * Function name : set_add_great_room
 * Description   : adds descr of great room furniture
 */
void set_add_great_room()
{

    add_item(({"furniture"}),
        "It is all made of wood and spread around the room. There is a " +
        "sofa, an end table, a dining room table, some dining room chairs, " +
        "and pictures on the wall.\n");

    add_item(({"sofa", "couch"}),
        "This is a long seat able to sit three or four people. It has " +
        "several cushion and looks comfortable to sit on.\n");
    add_item(({"cushions"}),
        "They are rectangular in shape, and over stuffed. The cushions are " +
        "on the sofa and chairs.\n");

    add_item(({"tables"}),
        "They are made of wood and look sturdy. There is a dining room " +
        "table and an end table\n");
    add_item(({"end table"}),
        "This is a low rectangular table. It is made of wood and sits " +
        "next to the sofa. It's stained a dark brown and looks well used.\n");
    add_item(({"dining room table"}),
        "The table is made from wood and sits in one corner of the room. " +
        "The table is oval shaped and a natural color. It looks well " +
        "used and has some chairs set around it.\n");
    add_item(({"chairs", "dining room chairs"}),
        "They are made of wood and set around the dining room table. Each " +
        "chair has a seat with cushion and a high back.\n");

    add_item(({"pictures"}),
        "They are paintings of natural scenes and hang on the walls. Some " +
        "pictures are paintings of family members.\n");
}

/*
 * Function name : set_add_master_bedroom
 * Description   : adds descr of master bedroom
 */
void set_add_bedroom()
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
 * Function name : set_add_kitchen 
 * Description   : adds descr of kitchen
 */
void set_add_kitchen()
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
 * Function name : set_add_kids_bed
 * Description   : adds descr of kids bed
 */
void set_add_kids_bed()
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
 * Function name : set_large_bed
 * Description   : adds descr of large bed
 */
void set_large_bed()
{
    add_item(({"bed", "large bed"}),
        "The bed is large and set against a wall. It is ornately carved " +
        "of wood by an expert carpenter. Large quilts are spread acrossed it. " +
        "Some fluffy pillows are set at the head of the bed.\n");
        add_item("mattress",
        "The mattress is thick and comfortable looking. It is probably " +
        "full of feathers and covered with a white cotton linen cloth.\n");
    add_item(({"quilts", "large quilts"}),
        "They are thick and warm looking. The quilts are hand sewn and " +
        "made from pieces of cloth. The quilts are spread across the bed.\n");
}
