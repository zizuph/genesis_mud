/*
 *  This is the base room inherited by all inside rooms in Tom's area.
 *  Updated by Finwe, December 1997
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
 
int num_of_windows = 0; /* number of windows in house */
 
int     win_n_u, win_n_d,   /* window existence  0/no, 1/yes */
        win_s_u, win_s_d,
        win_e_u, win_e_d,
        win_w_u, win_w_d = 0;
 
/*
 * Extra descr for walls and floor
 */
static string extra_window = "",
              add_staircase = "",
              add_staircase_closet = "",
              extra_floor = "",
              add_fireplace = "";
 
 
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
        "The ceiling is plastered white and lightly texture. Large, " +
        "richly carved beams run the length of the ceiling.\n");
    add_item(({"walls", "wall"}),
        "The walls are an off-white color and lightly textured.\n");
    add_item(({"floor"}),
        "The floor is made from light hardwoods and is very " +
        "clean. The woods are patterned in a symmetrical pattern " +
        "with a two strips of dark hardwood forming a border " +
        "around the perimeter of the floor.\n");
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
        "about the room, filling the room with lights.\n");
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A cool breeze blows into the room.");
 
    add_prop(ROOM_I_LIGHT, 2);  // Lamps add extra light.
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_M_NO_TELEPORT_TO, "That is not permitted here.\n");
    add_prop(ROOM_M_NO_STEAL, "Evil acts like that are not permitted here."); 
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 

    create_house_room();
}
 
 

void
set_extra_window(string str)
{
    add_item(({"windows","window"}),
        str + " @@window_count@@ large and equally " +
        "divided vertically into two sections with each " +
        "vertical section divided horizontally into four " +
        "squares. Large curtains cover them. Looking " +
        "out, you notice it is @@day_desc@@.\n");
    add_item("curtains",
        "They are made from fabric and are open, " +
        "letting @@daylight_desc@@ fill the room.\n");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
	    "@@open_curtains@@");
}

string close_curtains()
{
    return "Just before closing the curtains, you decide against " +
        "it since it would block out the light.\n";
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
            "The floor is made from dark hardwoods and is very " +
            "clean. " + str + "\n");
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

 
string
window_check()
{
    if(win_n_u == 1 || win_n_d == 1) return "north";
    if(win_s_u == 1 || win_s_d == 1) return "south";
    if(win_e_u == 1 || win_e_d == 1) return "east";
    if(win_w_u == 1 || win_w_d == 1) return "west";
}

string north_up()
{
    return "The clearing spreads out until it meets the border " +
        "of the trees. The trees ling the edge of the clearing and " +
        "are bathed in "+daylight_desc()+". They spread out in " +
        "all directions. ";
}

string north_down()
{
    return "A path wanders around the side of the house. Many " +
        "colorful flowers grow outside the window, breaking the " +
        "monotony of the green grass and trees. ";
}

string south_up()
{
    return "The clearing is covered with green grass and slopes " +
        "down slightly. In the distance, you see a river winding " +
        "west into the forest. Beyond the river you see trees. ";
}

string south_down()
{
    return "The grass covered clearing slopes down to a river. ";
}


string east_up()
{
    return "The clearing spreads out and eventually reaches the " +
        "edge of a valley. A path winds its way up into the " +
        "valley. In the distance you see rolling hills. "+
        CAP(daylight_desc())+" dances across the roof of the stable. ";
}

string east_down()
{
    return "The clearing runs east until it reaches the edge of " +
        "the valley. Gardens grow alongside the house and the path. " +
        "A stable is just south of the clearing. "; 
}

string west_up()
{
    return "Looking through the window, you realize that you are " +
        "gazing westwards towards the Old Forest. The path " +
        "continues in that direction, and far to the west trees " +
        "spread out in all directions. A river flows there and " +
        "gets lost in the trees. ";
}

string west_down()
{
    return "The clearing runs to the west then stops. Trees line " +
        "the edge of the clearing and the path continues on, lost " +
        "in the trees. Flowers grow outside the window in nice gardens. ";
}
void set_add_fireplace()
{
    add_item("fireplace",
        "The large fireplace sits against the south wall and is " +
        "made from large blocks of stone. It is as tall as an " +
        "elf and burns continuously. The fire light fills the " +
        "room a gentle yellow glow and the warmth comforts " +
        "you. The fireplace has a large brass screen in front of " +
        "it to prevent logs from rolling out and to keep sparks " +
        "inside. A large stone hearth sits in front of the " +
        "fireplace.\n");
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
        "right side of the door about halfway down. @@closet_status@@\n");
    add_item("doorknob",
        "The doorknob is made of brass and small.\n");
}
