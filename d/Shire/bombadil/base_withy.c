/*
 * Base file for Withywindle river flowing from
 * the Barrow Downs to the Old Forest.
 * Finwe, December 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_withy_room() {}
 
public void
create_area_room()
{
    set_areadesc("grassy");
    set_area("path along");
    set_areaname("the Withywindle");
    set_land("Eriador");
    set_areatype(0);
    
    add_item(({"plants", "water plants"}),
        "Tall grasses, flowers, reeds, and cat-tails grow in " +
        "bunches alongside the river. They provide colour and " +
        "shade the water a little. Some of the plants are bent " +
        "over, leaving trails in the water.\n");
    add_item(({"riverbank", "bank"}),
        "The riverbank is slanted on either of the river. Many " +
        "plants and flowers grow along its edges providing color and " +
        "protecting the water.\n");
    add_item(({"water flowers", "flowers"}),
        "They grow at the edge of the river. They are yellow, " +
        "blue, purple and other colours. Some are irises, " +
        "forget-me-nots, lilies, and other aquatic flowers.\n");
    add_item(({"reeds", "rushes"}),
        "They grow at the river's edge and are healthy looking " +
        "with arrow shaped ends. Some are bent over, floating " +
        "in the river.\n");
    add_item(({"cat-tails", "cattails", "cat tails"}),
        "The cat-tails are tall, grassy plants. They have flat " +
        "leaves and with long, brown, cylindrical flower spikes. " +
        "They grow in clumps at the edge of the river, providing " +
        "shelter for animals and fishes.\n");
    add_item(({"reeds"}),
        "The reeds are tall, flat grasses that grow among the " +
        "cat-tails and flowers at the river's edge. They are lush, " +
        "green, and provide some shelter for animals that live " +
        "along the river.\n");
    add_item(({"river", "withywindle", "withywindle river"}),
        "The Withywindle flows from the Downs into the Old Forest. " +
        "It is clear and cool looking, flowing past tall trees " +
        "growing over the river. Various plants and flowers grow " +
        "at the edge of the river.\n");
    add_item(({"forget-me-not", "forget-me-nots"}),
        "They are small, delicate blue flowers that grow on thin " +
        "stalks. The flowers have five sky blue petals with a sunny " +
        "center and are no bigger than a fingernail.\n");
    add_item(({"lilies", "lily"}),
        "They grow on tall stems among the river bank. Their " +
        "flowers are star shapped and brightly colored in shades " +
        "of red, white, yellow, pink, orange, and blue. The flowers " +
        "are slightly fragrant, filling the air with a sweet scent.\n");
    add_item(({"iris", "irises"}),
        "The irises grow along the bank with the other plants. The " +
        "leaves are flat, ribbed, and pointed at the ends. The " +
        "flowers grow on tall stalks. The stalks have triangular " +
        "shaped flowers that are blue, purple, white, and yellow.\n");

    add_item(({"road", "path"}),
        "The path is nothing more than a faint indentation along " +
        "the river. It winds along the bank of the Withywindle.\n");
    add_item(({"grasses", "grass"}),
        "The grass is green and lush. It grows tall along the " +
        "banks of the Withywindle in some parts.\n");
    add_item("ground",
        "The ground is covered with grass. It runs to the river's " +
        "edge where plants and trees grow.\n");
    add_item("sky",
        "It is @@day_desc@@ in "+land+". @@daylight_desc@@ fills " +
        "the sky.\n");
    add_item(({"forest", "old forest"}),
        "The Old Forest runs along the western border of the Downs. " +
        "It grows on both sides of the river, looking fearsome. " +
        "The trees look ancient, like they were part of a greater " +
        "forest at one time. Some say the river is haunted and " +
        "that it changes or moves about, though no one knows for " +
        "sure.\n");
    add_item(({"trees"}),
        "The trees of the Old Forest are ancient. Some look tall " +
        "and forbiding while others appear small and harmless. " +
        "They grow along both sides of the river, shading it with " +
        "their branches. They move about occasionally, seemingly " +
        "on their own.\n");
    add_item(({"animals", "animal"}),
        "You don't see any nearby, except for some small fish " +
        "swimming among the reeds and cat-tails.\n");
    add_item(({"fish", "small fish"}),
        "The small fish are dark and iridescent coloured. They " +
        "dart about the plants at the river's edge.\n");
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);

    set_drink_from( ({ "river", "water"}) );

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("The trees move in a silent breeze.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("The river bubbles along beside you.");
    add_room_tell("A branch seems to reach out and brush you.");
    add_room_tell("Something splashes in the river.");
    add_room_tell("Small fish dart among the water plants.");
    add_room_tell("Squirrels chatter at you from high up in a tree.");
        
    create_withy_room();
    add_std_herbs("forest");

 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
    init_drink();

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
