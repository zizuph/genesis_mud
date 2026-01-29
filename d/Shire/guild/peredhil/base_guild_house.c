/*
 * /d/Shire/guild/peredhil/base_guild_house.c
 *
 * This is the base indoor room for the Peredhil
 * Based on the Noldor guild house code.
 * By Finwe, February 2009
 *  
 */
 
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */
 
#define SOFA1       "large overstuffed sofa"
#define SOFA2       "large overstuffed couch"

public string	look_at(string arg);    /* VBFC for chairs */
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);    /* VBFC for chairs */
 
void
create_guild_room()
{
}
 
public void
create_shire_room()
{
    add_item(({"lamp","lamps"}),
        "The lamps are slender free-standing pedestal fixtures " +
        "of varying heights. The tops are made of pear shaped " +
        "crystals that fill the room with soft, relaxing light. " +
        "The pedestals are silver and gold, resembling elegant " +
        "tree trunks. The bases fan out and resemble the roots " +
        "of great trees growing into the lawn.\n");
    add_item(({"chairs", "chair"}),
        "There are settees, divans scattered about the room.\n");
    add_item("ceiling",
        "The ceiling rises above you to a peak. It is made " +
		"of polished white stone.\n");
    add_item(({"floor", "ground"}),
        "The ground is a carpet of trimmed lush green grass. " +
		"The grass extends from the garden outside to " +
        "throughout the guild. Small wild flowers grow in small " +
        "clusters about the room.\n");
	add_item(({"flowers", "wildflowers"}), 
		"Various wildflowers grow scattered about the grass " +
		"floor. They are low growing and are various colors, " +
		"but primarily pink, white, or yellow and have either " +
		"three, four or five petals.\n");
    add_item(({"grass", "lawn"}),
        "The lawn is a rich verdant emerald green. The grass " +
        "is thick and neatly clipped. Some small wildflowers " +
        "grow in scattered about the room.\n");
    add_cmd_item("pick", ({"flowers", "wildflowers", "wildflower"}),
        "@@pick_flowers@@");
    add_item(({"arch", "arches", "doorways", "gateway"}),
        "The arches are large, intricately carved gateways set " +
        "into the walls. Two large trees are expertly carved " +
        "on both sides of each arch. Their branches twine up and " +
        "over the top of the arch.\n");
    add_item(({"trees", "carved trees"}),
        "The trees are expertly carved by skilled elven hands. " +
        "They look lifelike as the frame the arches. Their bark " +
        "and branches are a silver color with the leaves being " +
        "a contrasting silver colour. Some of the branches " +
        "twine over the top of the arch.\n");
    add_chair(SOFA1,
        "[down] [on] / [in] [the] [large] [overstuffed] 'sofa'", 4);
    add_item( ({ "sofa"}), &look_at(SOFA1) );

    add_chair(SOFA2,
        "[down] [on] / [in] [the] [large] [overstuffed] 'couch'", 1);
    add_item( ({ "couch", }), &look_at(SOFA2) );


    set_room_tell_time(random(180)+60);
    add_room_tell("A Peredhel walks by, acknowledging you.");
    add_room_tell("The smell of clean grass fills the air.");
    add_room_tell("The fragrance of the flowers wafts past you.");
    add_room_tell("The melodic sound of the River Bruinen drifts by.");
    add_room_tell("A refreshing breeze blows past.");
    add_room_tell("Some Noldor greet you and walk by.");
    add_room_tell("A Noldo pauses with a smile on her face, " +
        "and rests here.");
    add_room_tell("Some Noldor pause, noticing you, and continue " +
        "talking quietly.");
    add_room_tell("Joyful laughter echoes lightly through the room.");
    add_room_tell("A Noldo sits down on a nearby divan and relaxes.");
    add_room_tell("A Noldo stands up from a nearby divan, " +
        "smiles, and leaves the room.");
    add_room_tell("Some Noldor walk in, talking among " +
        "themselves and sit down on a settee.");
    add_room_tell("Some Noldor stand up from the settee, wave, " +
        "and walk away.");
    

     
    add_prop(ROOM_I_LIGHT, 3);  // These bright lamps add extra light.
    add_prop(ROOM_I_INSIDE, 0); // outdoor room even though it has a roof.
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents teleporting there.\n");
    add_prop(ROOM_M_NO_STEAL,
        "Evil acts like that are not permitted in Imladris."); 
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 
    create_guild_room();
}
 

void
init()
{
    ::init();
    init_room_chairs(); /* add chair verbs */

}

 public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

void add_fireplace()
{
    add_prop(OBJ_I_HAS_FIRE,1);
    add_item("fire",
        "Red and yellow flames dance across logs, filling the " +
        "room with a yellow light and a gentle warmth.\n");
    add_item(({"log", "logs"}),
        "Large logs of maple, oak, and cedar burn brightly " +
        "in the fire.\n");
    add_item("fireplace",
        "The large fireplace sits against a wall and is " +
        "made from large blocks of stone. It is as tall as an " +
        "elf and burns continuously. The fire light fills the " +
        "room a gentle yelllow glow and the warmth comforts " +
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
        "the fire. The hearth extends a little bit the width of " +
        "the fireplace. It extends out from the fireplace about " +
        "the length of a human. \n");
     add_item("fire irons",
        "These tools are set on the hearth and are used to tend " +
        "the fire and stoke it when necessary. They are made of " +
        "hardened steel and include a shovel, poker, and a set " +
        "of tongs.\n");
    add_item("shovel",
        "Made from hardened steel, the large shovel is used to " +
        "clean the fireplace out. It is about the size of a " +
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
        "This long pole is made of hardened steel. One end has a " +
        "point and just below the point is a curved claw, " +
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
}

void
set_extra_wall(string str)
{
    add_item(({"wall", "walls"}),
        "The walls are made of white stone that has been polished " +
		"to a bright luster. Elven workmanship is evident here " +
		"as the seams cannot be made out between the blocks, " +
		"yet the walls appear to be made up of many stones. " + 
        str + "\n");
}

void
set_extra_window(string str)
{
    add_item(({"windows","window"}),
        str + " They are large and equally divided " +
        "vertically into two sections. Each vertical section is " +
        "further divided horizontally into four squares. It is " +
        "@@day_desc@@.\n");
    add_item(({"mountains", "misty mountains"}),
        "The mountains rise up in the distance from the valley. " +
        "They are imposing even though their tops can't be " +
        "seen from here.\n");
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
 
/*
string
window_position()
{
    if(num_of_windows >1)
        return "The windows are";
    else
        return "The window is";
}
*/

string
pick_flowers()
{
    return "The flowers can't be picked. Doing so could mar the " +
    "beauty of the guild house.\n";
}


/*
 * Function name:   look_at
 * Description  :   VBFC to describe chair/sofa + occupants
 * Arguments    :   string arg -- what's being looked at
 *                  null str -> it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {
    case SOFA1:
    return "The sofa is large and overstuffed. It looks luxurious and inviting and covered with forest green fabric. It has four elegantly carved legs that curl outwards.\n"+
    sitting_on_chair(SOFA1, this_player(), 0);
    break;

    case SOFA2:
       return "The couch is large and overstuffed. Covered with brown fabric, it looks luxurious and inviting. It has four elegantly carved legs.\n"+
    sitting_on_chair(SOFA2, this_player(), 0);
    break;


    }
} /* look_at */
