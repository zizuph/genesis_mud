/*
 * Base file for the clearing of Tom Bombadill's house
 * Finwe, December 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_path_room() {}

static string add_flowers = "";

public void
create_area_room()
{
    set_areadesc("light");
    set_area("path in");
    set_areaname("a clearing");
    set_land("the Old Forest");
    set_areatype(7);

    add_item(({"downs", "barrow downs"}),
        "The barrow downs rise remotely to the east. They are " +
        "green hills that seem to loom in the distance.\n");
    add_item(({"green hills", "hills"}),
        "The green hills rise to the east. Most likely they are " +
        "barrows. Thick fogs and mists obscure many of them.\n");
    add_item(({"fogs", "fog", "mists", "mist", "swirling fog", 
            "swirling fogs", "swirling mists", "swirling mist"}),
        "Fogs and mists rise up from the hills of the Barrow Downs. " +
        "They seem to be dark, masking most of what can be seen " +
        "there.\n");
    add_item(({"forest", "old forest","dark forest"}),
        "The forest is foreboding but grows at the edge of " +
        "clearing. It has been trimmed and clipped so as not to " +
        "interfere with the clearing here. Light filters through " +
        "the leaves, into little pools on the ground. Some say the " +
        "forest is haunted and that it moves about on its own, " +
        "though this is speculation and no one knows for sure.\n");
    add_item(({"ground"}),
        "The ground is smooth and covered with short, clipped " +
        "grass, as if it was mowed.\n");
    add_item(({"path", "trail"}),
        "The path is smooth and grass covered but otherwise plain " +
        "looking. It runs throughout the clearing and is lined with " +
        "grey stones.\n");
    add_item(({"stones", "grey stones", "gray stones"}),
        "They grey stones are rounded and smooth. They are river " +
        "stones collected from the nearby river.\n");
    add_item(({"grass", "green grass"}),
        "The green grass is smooth and short. It is clean without " +
        "any loose stones or leaves on it.\n");
    add_item(({"trees", "tree"}),
        "The trees are tall and dark looking. Many are ancient " +
        "looking and very tall. They are trimmed and none grow in " +
        "the clearing, except for a mighty oak. They seem to be " +
        "trying to encroach into the " +
        "clearing but are unable to. Their tall branches shade " +
        "the clearing and seem to move about on their own.\n");
    add_item(({"house", "cottage"}),
        "The house is small yet comfortable looking. It has two " +
        "stories and a peaked roof. It is made of stone and sits " +
        "in the center of the clearing. A small tendril of smoke " +
        "curls up from a chimney.\n");
    add_item(({"smoke"}),
        "It is grey looking and trails lazily up from the chimney.\n");
    add_item(({"peaked roof", "roof"}),
        "The roof peaked and covered with wood shingles.\n");
    add_item("eaves",
        "The eaves extend from the roof by about an arm's length, " +
        "providing protection to anyone standing beneath them.\n");
    add_item(({"wood shingles", "wood shingle"}),
        "The shingles are made from rough cut lumber and are " +
        "attached to the roofs. They cover the roof in an " +
        "overlapping pattern and are a weathered grey color.\n");
    add_item(({"chimney"}),
        "The chimney is made from stone and concrete. It " +
        "runs up the side of the house. The chimney is very wide " +
        "at the base and then becomes narrow about two thirds of " +
        "the way up the house.\n");
    add_item(({"windows"}),
        "The windows are large, allowing light into the cottage. " +
        "They are made up of square panes of glass and vary in " +
        "size from four to eight, depending on the window.\n");
    add_item("sky",
        "It is @@day_desc@@ in the the Old Forest. @@daylight_desc@@ fills " +
        "the sky.\n");
    add_item(({"oak tree", "oak", "mighty oak", "mighty oak tree"}),
        "The mighty oak tree grows beside the house, sheltering " +
        "it from the elements and providing some shade. Except " +
        "for the fruit trees, it is the only tree growing in the " +
        "clearing, and looks very ancient.\n");
    add_item(({"fruit trees"}),
        "Growing behind the house are various fruit trees. They " +
        "are tall and full of fruit.\n");
    add_item(({"soil", "dirt"}),
        "The soil in the clearing is a healthy, deep brown color. " +
        "It is rich looking and smells very earthy. It's probably " +
        "very good for growing all kinds of plants in it.\n");

    add_item(({"river", "withywindle", "withywindle river"}),
        "The Withywindle is a river that flows from the eastern " +
        "border of the Barrow Downs into the Old Forest. It is " +
        "clear and cool looking, flowing past tall trees that " +
        "grow over the river. It flows along the southern edge " +
        "of the clearing.\n");
    add_item(({"clearing"}),
        "The clearing is a wide area in the Old Forest. It is " +
        "absent of any trees and criss-crossed with stone-lined " +
        "paths. A comfortable two-story house sits in the center " +
        "of the clearing with trees growing at the border. Large " +
        "branches spread over the border that seems to keep them " +
        "out. Beyond the clearing in the east, rolling green " +
        "hills can be seen. A clear river bubbles over some " +
        "stones of a waterfall on the eastern border, which " +
        "eventually grows in size and flows along the southern " +
        "edge of the clearing into the forest.\n");


    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("The trees move in a silent breeze.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("The river bubbles in the distance.");

    add_std_herbs("forest");
        
    create_path_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
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



/* The remaining routines are copied from /d/Shire/lib/area_room.c
 * Minor modifications have been made to suit the Withywindle.
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
   desc = " Darkness covers "+areaname+" now at night.";
   switch (CLOCK->query_moon())
   {
   case "full":
       desc += " A full moon gives some light though.";
       break;
   case "waxing crescent":
   case "waxing gibbous":
   case "waning gibbous":
   case "waning crescent":
       desc += " The moon gives a little light though.";
       break;
   default:
       desc += " The sky is covered with dark clouds, and "+
       "not even the moon shines through.";
       break;
   }
   break;
    case "afternoon":
   desc = " The light of day shines across " + land + "."+
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
   desc = " The sun is setting in the west, coloring the sky "
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
 * Function name : set_add_flowers
 * Description   : adds standard flower descriptions about flower 
 *                 gardens
 */

void set_add_flowers()
{
    add_item(({"garden", "flower garden"}),
        "The flower garden is full of bright colored flowers. " +
        "They are all sizes and varieties, and some even look " +
        "unknown to you. The gardens dominate the northwest corner " +
        "of the cottage, and look well tended and cared for.\n");
    add_item(({"blooms", "flowers"}),
        "Flowers of all sizes, shapes, colors and varieties grow in " +
        "the garden. Some are tall with multiple or single blooms " +
        "on them while others are medium size and still, others " +
        "small enough to almost be hidden by the other plants. " +
        "Some blooms are star shaped, or round, or very frilly and " +
        "full, and others are single petaled. There are whites, " +
        "blues, greens, pinks, reds, and every color of the rainbow " +
        "plus some colors that defy description. They all form a " +
        "tapestry of color and beauty. Oddly enough, none of the " +
        "flowers out do any of the others.\n");
    add_room_tell("A bumblebee dances among the flowers.");
    add_room_tell("A hummingbird darts from flower to flower.");
    add_room_tell("Butterflies rest on top of some flowers.");
    add_room_tell("The flowers wave in a gentle breeze.");
    add_room_tell("Something sweet smelling wafts past you.");
}
