/*
 * Base file for North/South Road between the Great East Road
 * and Sarn Ford
 * Finwe, December 2019
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

//inherit "/std/room";
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit HERB_SEARCH;

void create_road_room() {}
void set_add_farms();

static string add_road_sounds = "";

public void
create_area_room()
{
// A rocky path west of the Old Forest in the Downs.

//    set_area("west");
//    set_areaname("Waymeet"); 
//    set_land("Westfarthing");
//    set_areatype(0);
//    set_areadesc("well travelled road");

    add_item(({"road", "ground", "path"}),
        "The road is wide and smooth and made of hard-packed dirt. It is " +
        "well travelled and as it runs through the Shire.\n");
    add_item("sky",
        "It is @@day_desc@@ in " + land + ". @@daylight_desc@@ fills " +
        "the sky.\n");
    add_item(({"grassy fields","grass", "green grass", "grasslands", "plain", "grassland", "meadows", "meadow", "fields", "land"}),
        "The grass is a rich green. It is short and carpets the land.\n");
    add_item(({"shrubs", "bushes"}),
        "The shrubs are waist high and grow scattered across the hills.\n");
    add_item(({"wild animals", "animals"}),
        "They scurry to hide in the grass or run away.\n");
    add_item(({"flowers", "wildflowers", "wild flowers"}),
        "Dotting the fields of grass with a colorful splash are dozens " +
        "of different wildflowers. Dozens of different varieties in " +
        "a rainbow of colors attract a collection of bees and butterflies.\n");
    add_item(({"bees", "bumblebees"}),
        "The are large, winged insects. The bees are striped yellow and " +
        "black and fly from flower to flower.\n");
    add_item(({"butterfly", "butterflies"}),
        "They are beautiful flying insects with large, colorful wings. " +
        "They dart from flower to flower.\n");
    add_item(({"trees", "groves of tree"}),
        "They are tall plants growing in groups. The trees dot the land " +
        "and look mature. The branches are thick and full of leaves.\n");
    add_item(({"branch", "branches"}),
        "They are thick and are part of the trees.\n");
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A wagon rumbles past you.");
    add_room_tell("Some deer watch you from a distance.");
    add_room_tell("A hobbit greets you and passes by.");
    add_room_tell("A group of hobbits greet you as they pass by.");
    add_room_tell("Some rabbits run across the road and disappear in " +
        "the grass.");
    add_room_tell("A gentle breeze blows across the land.");

    create_road_room();
    add_std_herbs("plain");
    set_add_farms();

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
}

int check_exit() 
{
    if (!present ("ruffian"))
    {
        return 0;
    }
    else if (TP->query_skill(SS_SNEAK) > 30)
    {
        write("You manage to sneak past the ruffian.\n\n");
        say(QCTNAME(TP)+" managed to sneak past the ruffian.\n");
        return 0;
    }
    else if (TP->query_skill(SS_HIDE) > 40)
    {
        write ("You manage to hide from the ruffians and escape.\n\n");
        say (QCTNAME(TP)+" hides and escapes the ruffian's attention.\n");
        return 0;
    }

    write("The ruffians pushes you around and says: Hey, where do you think you're going?\n\n");
//
//    write ("The ruffian blocks you from going in that direction.\n\n");
//    say ("A ruffian blocks " + QCTNAME(TP) + " from going in that direction.\n");
//    return 1;
}


void
init()
{
    ::init();
}

void set_add_sarn_ford()
{
    add_item(({"ford", "sarn ford"}),
        "It is a stone bridge to the east that crosses the Brandywine river. \n");
    add_item(({"stone bridge", "bridge"}),
        "It is made of stone blocks and pillars. The stone bridge is expertly " +
        "made and stretches across the Brandywine river.\n");
    add_item(({"blocks", "stone blocks", "stone block", "block"}),
        "They are large and square shaped and rectangular shaped. They make " +
        "up the bridge that spans the Brandywine river.\n");
    add_item(({"pillars", "stone pillars"}),
        "They are made of blocks of stone, sit on either side of the river " +
        "Brandywine, and used to hold the rectangular-shaped blocks.\n");
    add_item(({"rectangular blocks", "rectangular-shaped blocks"}),
        "They are long and make up the bridge that spans across the Brandywine " +
        "river.\n");
}


void add_sarn_ford_descr()
{
    add_item(({"sarn ford"}),
        "It is a stone ford on the eastern edge of the Shire. Following " +
        "this road to the east will end there.\n");
}

void add_longbottom_descr()
{
    add_item(({"longbottom"}),
        "It is a region in Southfarthing famous for growling the best " +
        "pipeweed in the Shire. It is also known for growing very " +
        "strong red wine.\n");
}

void set_add_t_farm()
{
// tobacco farm descry
}
void set_add_farms()
{
    add_room_tell("The sounds of honking geese echoes in the distance.");
/*
    add_item(({"farm"}),
        "The farm stands in the distance. It is made up of some buildings " +
        "and surrounded by a fence.\n");
    add_item(({"buildings"}),
        "From this distance, you see a barn, a farm house, and some smaller " +
        "buildings.\n");
    add_item(({"barn"}),
        "The barn looks small from here, though it is probably quite " +
        "large. It was probably painted at one time, but now it it " +
        "looks weather worn.\n");
    add_item(({"house", "farm house"}),
        "The farm house look small in the distance. It stands in " +
        "front of the other buildings and is surrounded by smaller ones.\n");
    add_item(({"smaller building", "small buildings"}),
        "From this distance, the small buildings look " +
        "indistinguishable.\n");
    add_item(({"fence"}),
        "The fence looks small, and surrounds the farm in the distance.\n");
*/
    add_item(({"farms", "farm"}),
        "They stand in the distance, like green squares scattered " +
        "across the area. There are very few of them because they're " +
        "away from any nearby towns.\n");
}

void set_add_green_hills()
{
    add_item(({"green hills", "hills", "hill", "rolling hills", "rolling hill"}),
        "The hills run west to east through the Shire. They are carpeted " +
        "with grass and are fairly open and treeless. Some small " +
        "shrubs dot the hills.\n");
}

void set_add_westfarthing()
{
    add_item(({"west farthing", "farthing", "westfarthing"}),
        "This is one of the divisions in the Shire. It encompasses the " +
        "western part of the Shire and includes rolling hills and " +
        "grasslands.\n");
}

void set_add_southfarthing()
{
    add_item(({"south farthing", "farthing", "southfarthing"}),
        "This is one of the divisions in the Shire. It encompasses the " +
        "southern part of the Shire and is mostly covered with grasslands. " +
        "The Southfarthing is rural, fertile, and slightly warmer. The " +
        "Southfarthing is famous for growing the best pipe-weed and " +
        "its strong red wine. \n");
}

void set_add_longbottom()
{

}

/***************************************************************
 * Road Descriptions
 * To use them, call them in the create_room() 
 * Example:
 
    void
    create_road_room()
    {
        set_vbfc_extra(road_desc1);
    }

 * If you want to add additional details o the description, 
 * call set_extraline() after set_vbfc_extra()
 * Example:
        set_vbfc_extra(road_desc1);
        set_extraline("More descriptions go here.");
 */

string road_desc1()
{
    return "Tall grassy fields spread out in all directions. Bumblebees " +
        "and butterflies dart from flower to flower growing in the fields. " +
        "Farms dot the land, and small groves of trees grow in " +
        "scattered groups. ";
}

string road_desc2()
{
    return "Occasional fields of tall grass or clumps of bushes and " +
        "brush gather around small groves of trees. Green squares " +
        "dot the land where hobbit farms are at. Wildflowers create " +
        "patches of color in the field. ";
}

string road_desc3()
{
    return "Hobbit farms dot the fields of " + land + ". They look large " +
        "but comfortable. Many bushes and groves of trees grow in " +
        "fields. An occasional animal can be seen stalking in the grass. ";
}

string road_desc4()
{
    return "Small groves of trees dot the land. They are surrounded by " +
        "wildflowers. Almost everywhere you look, there seems to " +
        "be hobbit farms. The farms create a patchwork of fields in the " + 
        land + ". ";
}



public string
long_desc()
{
    string  time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";

    if (!(CLOCK->query_war()))
    {
        desc += describe_time(time)+" ";
    }
    else
    {
        desc += describe_war(time)+" ";
    }
    if (functionp(vbfc_extra))
        desc += vbfc_extra();
    if (strlen(extraline))
        desc += extraline;

    return (BSN(desc));
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
            return "soft, gentle night light";
    }
}

string
describe_time(string time)
{
    string desc;

    switch (time)
    {
        case "night":
            desc = "Darkness covers "+areaname+" now at night. ";
            switch (CLOCK->query_moon())
           {
               case "full":
                   desc += "A full moon gives some light though. ";
                   break;
               case "waxing crescent":
               case "waxing gibbous":
               case "waning gibbous":
               case "waning crescent":
                   desc += "The moon gives a little light though. ";
                   break;
               default:
                   desc += "The sky is covered with dark clouds, and "+
                   "not even the moon shines through. ";
                   break;
           }
            break;
        case "afternoon":
           desc = "The light of day shines across " + land + "."+
           " It is afternoon.";
           break;
        case "morning":
           desc = " The sun is on its way up in the morning sky to the east.";
           break;
        case "noon":
            desc = " The sun is almost at its peak on its way across " +
            "the sky. It is noon in " + land + ".";
            break;
        case "evening":
            desc = " The sun is setting in the west, colouring the " +
            "sky golden red.";
            break;
        case "early morning":
            desc = " The sun is rising in the east, casting long shadows " +
            "across " + land + ".";
            break;
    }
    return desc;
}

string
describe_war(string time)
{
    string desc;

    switch (time)
    {
        case "evening":
        case "night":
        case "early morning":
            desc = " Massive dark clouds cover the sky, making it " +
            "difficult to distinguish night and day. The clouds seem " +
            "to be coming from the east, where Mordor lies. You suspect " +
            "it is night now, as it is as dark as it can get.";
            break;
        case "morning":
            desc = " A thick cover of clouds prevent the sun from " +
            "shining on the lands of " + land + ", and it is almost " +
            "as dark as at night. However you gather that it is probably " +
            "morning, as it is getting a bit lighter than earlier.";
            break;
        case "noon":
           desc = " A dark mass of clouds seems to be rolling in from " +
            "the east, covering the sky above " + land + ". It is not " +
            "much lighter now than it usually is at night, but still you " +
            "suspect it is the middle of the day.";
           break;
        case "afternoon":
            desc = " A thick mass of clouds covers the sky, making it " +
            "difficult to see far. You suspect that it is afternoon, " +
            "as it is getting a bit darker than earlier.";
       break;
    }
    return desc;
}

