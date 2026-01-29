/*
 * Base file for paths in the Misty Mountains
 * Finwe, September 2004
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit BASE_COMMON;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
 
void create_mt_room() {}

public void
create_area_room()
{

    set_areadesc("rocky path");
    set_area("in");
    set_areaname("the Misty Mountains");
    set_land("Eriador");
    set_areatype(0);
    add_item(({"path", "ground"}),
        "The path is barely visible in the mountains. It meanders around " +
        "boulders and bushes. It is rocky and strewn with rocks.\n");
    add_item(({"boulders"}),
        "The boulders are different sizes. Some are so tall you cannot " +
        "see over them. They are jagged, having broken off and rolled " +
        "down the mountain.\n");
    add_item(({"mountains", "misty mountains", "towers of mist", "hithaeglir"}),
        "This is a vast range of mountains that runs north and south. " +
        "It divides the land and was raised ages ago. It is very high " +
        "and many of its tallest peaks are cloaked in clouds or covered " +
        "with snow. The mountains are very rocky and dangerous, and " +
        "rumoured to be inhabited by orcs and trolls, and other nameless " +
        "enemies. Only the bravest travel through the Misty Mountains.\n");
    add_item(({"peaks"}),
        "They are rugged looking and various sizes. Some rise into the " +
        "clouds and are hidden from view. Others are not as tall but " +
        "are covered with snow. Others are low enough to be covered " +
        "with low bushes.\n");
    add_item(({"snow covered peaks"}),
        "These peaks covered with snow. Some of them are the tallest in " +
        "the mountains and are buried in the clouds that hover over the " +
        "mountains.\n");
    add_item(({"cloud covered peaks"}),
        "These peaks are the tallest in the mountains. They are so high " +
        "that clouds hide them from view. Under the clouds, snow covers " +
        "the peaks.\n");
    add_item(({"snow line", "snowline"}),
        "This is the lowest boundary of the snow covered peaks. During " +
        "the warmer months, it rises on some of the lowest peaks.\n");
    add_item(({"bushes"}),
        "They are various sizes and shapes. Most of them look ragged " +
        "and thin from the harsh climate in the mountains or from " +
        "being trampled from animals that wander through the mountains.\n");
    add_item(({"flowers", "wildflowers"}),
        "They are sparse and short. They grow in clumps around the " +
        "mountains and provide small splashes of color in an otherwise " +
        "bleak land.\n");
    add_item(({"clouds"}),
        "They are white and billowy looking. They hide the highest peaks, " +
        "moving around slowly by the blowing winds.\n");
    add_item(({"rocks"}),
        "They have fallen off the mountain and lay scattered about the land. " +
        "They are jagged and gray colored.\n");
    add_item(({"tracks", "animal tracks"}),
        "They vary in size. Some are small, made from wild animals. " +
        "Others are large. They appear to have been made by wild beasts, " +
        "or perhaps by trolls or orcs that inhabit the mountains.\n");
    add_item(({"troll tracks", "orc tracks"}),
        "They are large and run along the path. The tracks look twisted " +
        "and almost human like.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A cold wind blows past you.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("An eagle flys overhead.");
    add_room_tell("A startled bird flies out of the bushes.");
    add_room_tell("In the distance you hear: Chuck chuck chuck. " +
        "Chuck chuck chuck.");
    
    
    create_mt_room();
//    set_add_sky();
    add_std_herbs("hills");
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
}

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


string path_desc1()
{
    return "The path runs through the broken land. It looks thin and " +
        "not much more than an animal path. Tall peaks rise in the " +
        "distance among the scattered bushes and wildflowers. ";
}

string path_desc2()
{
    return "Tall peaks rise in the distance and along the path. They " +
        "block the " + light_type() + ", casting long shadows across the " +
        "mountains. Wildflowers grow in groups among the bushes. ";
}

string path_desc3()
{
    return "Tracks run across the path. Some of them look dangerous and " +
        "from trolls or orcs that inhabit the mountains. The path is " +
        "thin and meanders and disappears into the bushes. Wildflowers " +
        "dot the rocky land. ";
}

string path_desc4()
{
    return "The path is rugged and nothing more than a thin line running " +
        "through the mountains. Tall peaks rise on either side of you. " +
        "Bushes grow in scattered bunches across the bare mountains. ";
}

string path_desc5()
{
    return "Bushes row in scattered groups across the mountains. They " +
        "make travel through the rocky land dangerous. The path meanders " +
        "through the mountains and is covered with rocks and boulders. ";
}
