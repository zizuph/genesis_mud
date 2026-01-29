/*
 * Base file for shore of the River Bruinen
 * Modified from ~Shire/examples by Finwe
 * January 1999
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */
#define QUEST_NAME      "forest"

int check_players = 0;
 
void create_shore_room() {}
 
 
public void
create_area_room()
{
    set_area("next to");
    set_areaname("the River Bruinen");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("riverbank");
    set_grass("sparse, dry");
    set_treetype("conifer");

    set_short("On a riverbank next to the River Bruinen");
    add_item(({"tree","trees"}),
        "Evergreens are the dominate tree in this part of the " +
        "area. They grow sparsely here and have some gashes " +
        "and marks in them.\n");
    add_item(({"evergreen trees", "conifer trees", "evergreen", 
        "evergreens", "conifers", "conifer"}),
        "The dominate evergreen trees here are tall pines. They " +
        "are sparse here and some have gashes and markes in them.\n");
    add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
        "cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
        "cedar trees", "cedar tree"}),
        "These evergreens dominate the area. Some grow on the rocks " +
        "in a scraggly manner.\n");
    add_item(({"fallen branches", "dead branches", "dead branch"}),
        "They are broken and lay scattered across the ground. " +
        "Some look like they just fell from the trees, " +
        "splintered and twisted. They lay on the ground in " +
        "various stages of decomposition.");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the " +
        "forest's floor.");
    add_item(({"needles", "pine needles"}),
        "Some fresh and dead pine needles litter the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
        "dead tree"}),
        "Some fallen trees lay rotting under a blanket of fallen " +
        "pine needles and forest debris.\n");
    add_item(({"mountains", "misty mountains", "mountain"}),
        "The Misty Mountains rise up before you. Their peaks " +
        "are buried in the clouds. Their sides are " +
        "covered with trees up until the snow line. Tales tell " +
        "of the mountains infested with all kinds of orcs and " +
        "trolls, making travel through the mountains dangerous.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions " +
        "across the river. It looks like it's made up of " +
        "evergreens and blocks your view beyond the river.\n");
    add_item(({"riverbank", "ground", "shore", "down", "bank"}),
        "The shore is spongy and covered with trampled grass. " +
        "It slopes slightly to the river's edge. Around the " +
        "edge are tall grasses, reeds, and rushes.\n");
    add_item(({"reeds", "reed", "grasses", "rushes"}),
        "The plants grow at the river's edge. Most of the " +
        "leaves are flat and partially block the view of the " +
        "river. The plants move in the breeze.\n");
    add_item(({"flowers", "flower"}),
        "Poking out of the grasses are small flowers. Some " +
        "are yellow and others purple. The flowers have " +
        "three points in the shape of a triangle, with the " +
        "ends flaring out. The throats of the flowers are " +
        "delve deep into the plant.\n");
    add_item("mud",
        "The mud is brownish-red and full of tracks.\n");
    add_item(({"marks", "gashes", "marks and gashes"}),
        "The marks and gashes in the trees look like they were " +
        "made by clubs, claws, or teeth. Probably from the wild " +
        "trolls or beasts that roam the area here.\n");
    add_item(({"tracks", "troll tracks", "troll track", "track"}),
        "These large, clawed tracks are fresh and appear to " +
        "have been made by wild beasts, or perhaps by trolls.\n");
    add_item(({"river", "river bruinen", "bruinen river", "bruinen"}),
        "The river is swift and rushes onward. It looks deep.\n");
     add_item(({"boulder", "boulders"}),
         "The large rocks jut out of the water. Some are jagged " +
         "and others smooth from the rushing water. White water " +
         "surrounds the base of the boulders where the river " +
         "rushes past them.\n");



    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("The grasses rustle at the edge of the river.");
    add_room_tell("A howl is heard in the distance. It is " +
        "answered by another howl.");
    add_room_tell("A howl is heard in the distance. It sounds nearby.");
    add_room_tell("A cool breeze drifts off the river and blows past you.");
    add_room_tell("Everything suddenly becomes deadly silent.");
    add_room_tell("A fish leaps in the river."); 
    add_room_tell("A large bird screams overhead. It swoops down to the " +
        "river, catches a fish and flies off.");
    
    create_shore_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
    add_action("drink_it",      "drink");
}
 
string
shore_desc()
{
    switch(random(3))
    {
        case 0:
            return "You stand on the edge of the riverbank of " +
                "the Bruinen. The shore is covered with grass " +
                "which is trampled in spots. The river " +
                "flows past swift and strong and animal tracks " +
                "can be seen at the edge of the bank. ";
            break;
        case 1:
            return "This is the edge of the River Bruinen. The " +
                "Misty Mountains rise above you on the other " +
                "side of the river. The shore is muddy here; " +
                "animal tracks can be seen everywhere. The " +
                "strong river rushes past you. ";
            break;
        case 2:
            return "You stand on a shore of the River Bruinen. " +
                "The ground looks trampled by many " +
                "feet, either of animals or worse... The river " +
                "is swift here and appears to bar anything from " +
                "crossing it. A forest can be seen on the " +
                "opposite side with a tall mountain range rising " +
                "up from the forest. ";
            break;
 
        default:
            return "This is a shore on the River Bruinen. The " +
                "river flows swiftly past you on its travels. " +
                "The riverbank is spongey and covered with " +
                "trampled grass. A forest grows on the other " +
                "side of the river. It looks dark and " +
                "foreboding. A tall mountain range can be seen " +
                "in the distance. ";
            break;
     }
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
            return "soft, gentle nightlight";
    }
}
 
int drink_it(string s)
{
 
int amount;
 
   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           
           }
           else
           {
           write("You cannot drink more water.\n");
           }
 
            return 1;
        }
    else
            NF("Drink what?\n");
}
 
string
exa_tracks()
{
    if (TP->query_skill(SS_TRACKING) > 40)
        return "The tracks look like troll tracks.\n";
    else
        return "They look big!\n";
}

 
check_person()
{

// allow only rangers and noldor to use these exits, and noldor have to be
// trustworthy.
    if ((IS_RANGER(TP)) ||(IS_NOLDOR(TP)) ) 
        return 0;
    else
        return 1;
}
