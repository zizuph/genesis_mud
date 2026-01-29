/*
 * Base file for road in the Barrow Downs
 * Finwe, December 2001
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

/* The stone number players are moved to.
 * Corresponds to the barrow number they dig into.
 */
static string stone_num = "/d/Shire/obj/stone1";
void set_stone_num(string str) {stone_num = str;}


void create_road_room() {}

static string add_wight_sounds = "",
              add_valley_descrs = "";

static string in_exit = "",
              out_exit = "";

public void
create_area_room()
{
    set_area("west");
    set_areaname("Old Forest");
    set_land("the Downs");
    set_areatype(0);
    set_areadesc("rocky path");
    add_item(({"road", "ground", "path"}),
        "The ground is rocky and broken in the Downs. The " +
        "path is overgrown with grasses and shrubs, making it " +
        "difficult to follow.\n");
    add_item(({"grasses", "grass", "field", "field of green grass"}),
        "The grass is green yet looks undisturbed. It grows in " +
        "large patches, punctuated with stones and rocks poking "+
        "out of the ground.\n");
    add_item(({"stones", "rocks", "fallen stones", "fallen rocks"}),
        "The stones and rocks are half buried beneath the grass " +
        "and ground. They look like they were once fine structures " +
        "but are now destroyed and buried, silent testaments to " +
        "something unknown. Grass and shrubs grow around them.\n");
    add_item("sky",
        "It is @@day_desc@@ in "+land+". @@daylight_desc@@ fills " +
        "the sky.\n");
    add_item(({"valleys", "valley", "vale", "vales"}),
        "The vales are bowl shaped valleys in the Downs. They are " +
        "covered with grass, and some even have fallen stones and " +
        "cairns on them, monuments to who was buried there.\n");
    add_item(({"downs", "barrow downs", "barrow-downs"}),
        "The Barrow Downs are the most ancient burial ground of " +
        "the Kings of Men. Once, they were revered by the Dunedain, " +
        "but during the wars of Angmar, they become corrupted, " +
        "inhabited by evil Barrow-wights. Now, they are a place of " +
        "dread and an unwholesome place.\n");
    add_item(({"fogs", "fog", "mists", "mist"}),
        "The fogs and mists swirls about in some unseen " +
        "breeze. They seem to be nothing more than water mists, " +
        "but in the Barrow Downs, one can never be too sure. They " +
        "are hypnotic, lulling unwary travellers into cold sleeps. " +
        "Some even seem to be alive, following your every movement " +
        "and calling to you.\n");
    add_item(({"trees", "old trees"}),
        "The old trees are sparse with very few growing in the " +
        "Downs. They are gnarled and ancient looking and stunted " +
        "from the elements.\n");

// wight sounds/beckonings are in set_add_wight_sounds()
// and called by each road room.
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A cold mist rises up from the ground.");
    add_room_tell("Dark mists swirl and dance before you.");
    add_room_tell("Mists blow across the Downs.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("Hazy figures appear in the distance, then disappear.");
    add_room_tell("An icy feeling blows past you.");
    add_room_tell("A misty figure seems to follow you.");

    create_road_room();
    add_std_herbs("plain");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

}


void
init()
{
    ::init();
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
string road_desc1()
{
    return "The path winds its way past fallen stones, old trees " +
        "and shrubs as it meanders through the Downs. ";
}

string road_desc2()
{
    return "The path dips and rises as it crossess hills and " +
        "valleys in the Downs. Mists swirl up when you move, " +
        "creating haunting images. ";
}

string road_desc3()
{
    return "Mists swirls around with every movement as you walk " +
        "this way. Eerie images seem to entice you to " +
        "follow them. The grass is wet with moisture as it covers " +
        "the hills and vales. ";
}

string road_desc4()
{
    return "The barrows rise up before, crowned with bone white " +
        "cairns. Mists swirl around them in haunting patterns. ";
}

/*
 * Function name : set_add_wight_sounds
 * Arguments     : str: none
 * Description   : adds sounds wights make on the road
 */

void set_add_wight_sounds()
{
    add_room_tell("A haunting voice whispers: I will make you powerful...");
    add_room_tell("Somewhere in the distance, you hear: Come, follow me...");
    add_room_tell("In the distance, you hear something whisper: I " +
        "can grant you anything you want...");

    add_item(({"bone white stone", "bone white stones", "white stones",
            "bone white stone"}),
        "The bone white stones make up the cairns and monoliths " +
        "of the Barrows. It looks like they were one fine stones, " +
        "but now they are marred by time and elements, cracked and " +
        "fallen, to be buried by the earth.\n");
    add_item(({"barrows", "barrow"}),
        "They are large mounds of earth which mark the burial places " +
        "of ancient men and women. The barrows are covered with " +
        "grass and crowned with cairns of stone.\n");
    add_item(({"cairn", "cairns", "monuments","marker"}),
        "They are old monoliths made of bone white stone " +
        "that mark the burial place of ancient men. Some are mounds " +
        "of worked stone that still stand, cracked and battered " +
        "by the elements. Others are nothing more than a circle of " +
        "buried rocks, thrown down by tresspasers or fallen over " +
        "by the ravages of time.\n");
    add_item(({"shrubs", "shrub"}),
        "The shrubs are fresh looking yet look scraggly. They " +
        "grow in clumps, some by fallen stones and rocks.\n");

}


/*
 * Function name : set_add_valley_descrs
 * Arguments     : str: none
 * Description   : adds basic descriptions to the valley
 */

void set_add_valley_descrs()
{
    add_item(({"hills", "hill", "rolling hills", "rolling hill"}),
        "The rolling hills are scattered throughout the valley. " +
        "They are bare of any vegetation except for green grass.\n");
    add_item(({"barrows", "barrow"}),
        "They are large mounds of earth. They are north and east " +
        "and rise from the valley. The barrows are covered with " +
        "grass.\n");
    add_item("valley",
        "The valley slopes away from the Downs. Some rolling hills " +
        "are scattered about the valley, but nothing else of " +
        "interest can be seen.\n");

}




// dig routine to enter the cairns

do_dig(str)
{
   if (this_player()->query_prop(LIVE_O_STEED))
   {
      write("You must dismount before digging here.\n");
      return 1;
   }

    write("You start to dig in the ground with your hands. Suddenly the "
	+ "ground below gives away! You slip, and fall into a dark pit.\n");
    say(QCTNAME(TP)+ " falls into a dark hole and disappears...\n");

    this_player()->move_living("M", stone_num,1);
    return 1;
}


/* The remaining routines are copied from /d/Shire/lib/area_room.c
 * Minor modifications have been made to suit the Downs.
 */

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
   desc = " The sun is on its way up in the morning sky "
   + "to the east.";
   break;
    case "noon":
   desc = " The sun is almost at its peak on its way across "
   + "the sky. It is noon in " + land + ".";
   break;
    case "evening":
   desc = " The sun is setting in the west, colouring the sky "
   + "golden red.";
   break;
    case "early morning":
   desc = " The sun is rising in the east, casting long shadows "
   + "across "+land+".";
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
   desc = " Massive dark clouds cover the sky, making it "
   + "difficult to distinguish night and day. The clouds seem "
   + "to be coming from the east, where Mordor lies. You "
   + "suspect it is night now, as it is as dark as it can get.";
   break;
    case "morning":
   desc = " A thick cover of clouds prevent the sun from "
   + "shining on the lands of "+land+", and it is almost as "
   + "dark as at night. However you gather that it is probably "
   + "morning, as it is getting a bit lighter than earlier.";
   break;
    case "noon":
   desc = " A dark mass of clouds seems to be rolling in from "
   + "the east, covering the sky above "+land+". It is not much "
   + "lighter now than it usually is at night, but still you "
   + "suspect it is the middle of the day.";
   break;
    case "afternoon":
   desc = " A thick mass of clouds covers the sky, making it "
   + "difficult to see far. You suspect that it is afternoon, "
   + "as it is getting a bit darker than earlier.";
   break;
    }

    return desc;
}

/*
 * Function name : hole_check
 * Arguments     : none
 * Description   : if BAR_SHAFT_EXITprop set, then they came thru
 *                 barrows to valley and can enter shafts to
 *                 exit valley
 */
hole_check()
{
// can players see this exit?
    if(this_player()->query_prop(BAR_SHAFT_EXIT))
        return 0;
    else
        return 1;

}

/*
 * Function name : check_room
 * Arguments     : none
 * Description   : determines which exit players go into based
 *                 on BAR_SHAFT_EXIT prop
 */
string check_room()
{
    if(this_player()->query_prop(BAR_SHAFT_EXIT) || this_player()->query_wiz_level())
    {
        write("You enter the fog and go up into the barrow.\n");
            return in_exit;
    }
    else
    {
        write("Thick fogs and mists swirl about you, blinding " +
            "and confusing your movements.\n");
        return out_exit;
    }

}