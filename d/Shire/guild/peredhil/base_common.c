/*
 * /d/Shire/guild/peredhil/base_common.c
 *
 * File of common routines for the Peredhil guild
 * Finwe, February 2009
 */

#include "/d/Shire/sys/defs.h"
#include "pered.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;

// Sets up time defs for area.
#define LATE_NIGHT      0..3    /*12am-3am*/
#define EARLY_MORNING   4..7    /*4am-7am*/
#define MORNING         8..10   /*8am-10am*/
#define NOON            11..13  /*11am-1pm*/
#define AFTERNOON       14..17  /*2pm-5pm*/
#define EVENING         18..21  /*6pm-9pm*/
#define EARLY_NIGHT     22..24  /*10pm-12am*/

string daylight_desc()
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
            return "soft, gentle night light";
    }
}


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