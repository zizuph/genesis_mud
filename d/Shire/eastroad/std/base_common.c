/*
 * File of common routines for all of the East Road
 * Finwe, May 2004
 */

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
 
// Sets up time defs for area.
#define LATE_NIGHT		0..5	/*12am-5am*/
#define EARLY_MORNING	6..7	/*6am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/


static string   add_forest          = "",
                add_marsh           = "",
                add_sky             = "",
                add_weather_hills   = "", 
                add_bushes          = "",
                add_east_whills     = "",
                add_rocks           = "",
                add_rocky_plains    = "",
                add_foothills       = "",
                add_trollshaws      = "",
                add_mistys          = "";

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


/*
 * Function name : set_add_sky
 * Description   : adds descr of sky
 */
void set_add_sky()
{
    add_item("sky",
        "It is @@day_desc@@, with @@light_type@@ filling " +
        "the sky.\n");
}

/*
 * Function name : add_rocks
 * Description   : adds descr of rocks and pebbles
 */
void set_add_rocks()
{
    add_item(({"pebbles"}),
        "They are small rocks with smooth edges. They look like they " +
        "have broken off the boulders and rocks that lay scattered " +
        "around the land.\n");
    add_item(({"rocks"}),
        "They are larger than pebbles and lay scattered all over the " +
        "hills. They have jagged edges worn smooth by wind and rain.\n");
}

/*
 * Function name : set_add_forest
 * Description   : adds descr of north road
 */
void set_add_forest()
{

    add_item("branches",
        "They block your view of of anything beyond the trees due to their " +
        "thickness and abundance of leaves.\n");
    add_item(({"ground", "forest debris", "debris", 
         "forest floor", "floor", "down"}),
        "The ground is littered with dead branches, leaves, " +
        "and some fallen trees.\n");
    add_item(({"leaves", "leaf"}),
        "A thick mat of leaves cover the forest floor. Twigs and broken " +
        "branches litter the ground. Growing between the trees are plants " +
        "and wild flowers.\n");
    add_item(({"fallen branches", "dead branches", "dead branch"}),
        "They are broken from the trees and lie scattered across the " +
        "ground. Some are freshly broken off and others are half decomposed, " +
        "ready to fall apart and buried on the forest floor.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
            "dead tree"}),
        "These are old " + treetype + " trees. They have fallen over " +
        "from old age and lay on the ground. They are rotting, and some " +
        "are ready to fall apart. Moss and lichens grow on the oldest " +
        "fallen trees.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs lay on the ground, the oldest ones buried by " +
        "fallen leaves and fallen branches. Some are hollowed out and look " +
        "to be homes for woodland animals.\n");
    add_item(({"forest"}),
        "The forest is large, made up of mostly tall " + treetype + " trees, " +
        "and stretches in all directions. @@daylight_desc@@ filters through " +
        "the upper branches, creating rippling pools of @@light_type@@. " +
       "fallen branches, leaves, and other debris cover the forest floor.\n");
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow beneath the trees, making travel through the " +
        "forest difficult and obscuring your way.\n");
    add_item(({"thick trees", "thick " + treetype + " trees", 
            treetype + " trees"}),
        "The " + treetype + "trees are very old and quite large. They reach " +
        "upwards and dwarf the trees below them.\n");
    add_item(({"young trees", "young " +treetype + " trees"}),
        "These trees trees are small to medium in size. They grow scattered " +
        "around the forest, filling in the empty areas of the forest.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a many different plants grow in the forest. There " +
        "are flowers and bushes grow everywhere.\n");
    add_item(({"bushes", "shrubs"}),
        "Bushes of different color and sizes grow here. They are both thick " +
        "and young looking.\n");
    add_item(({"moss", "mosses"}),
        "Moss can be seen growing on logs, trees, and on the ground in " +
        "patches. It is healthy and a deep green. Some moss patches are " +
        "very large.\n");
    add_item(({"lichen", "lichens"}),
        "Lichen can be seen on some rocks and trees. It is grey and white " +
        "colored. Some are simple strands while others are large and fan " +
        "shaped.\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them are partially " +
        "buried in the ground or in the forest debris.\n");
    add_item(({"flowers", "wild flowers", "wildflowers", "wild-flowers"}),
        "Various wild flowers are ground within the forest. Their scattered " +
        "arrangements of white, yellow, pink, and other vibrant shades add " +
        "color to the forest floor. They sway lazily in the breezes.\n");

//    set_add_sky();

/*
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
  
*/
}

/*
 * Function name : set_add_mistys
 * Description   : adds descr of Misty Mountains
 */
void set_add_mistys()
{
    add_item(({"misty mountains", "misties", "mountains",   
        "towers of mist", "hithaeglir"}),
        "They rise in the distance to the east. They are rugged looking and the higher peaks are covered with snow. The lowlands rise in the distance to the feet of the mountains.\n");
    add_item(({"peaks", "mountain peaks"}),
        "The peaks of the mountains are jagged and rugged. The highest peaks are covered with snow and hidden from view.\n");
    add_item(({"snow"}),
        "It gleams in the distance on the tall peaks of the Misty Mountains.\n");

}


/*
 * Function name : set_add_marsh
 * Description   : adds descr of midgewater marsh
 */
void set_add_marsh()
{
    add_item(({"marsh", "swamp", "bog"}),
        "The marsh is an area of soft, wet land. Pools of brackish water " +
        "are surrounded by spongy hillocks. Dead plants and sparse grasses " +
        "cover on the hillocks.\n");
    add_item(({"hillocks"}),
        "These are small knolls that rise out of the marsh. They are " +
        "various sizes and very spongy looking. Dead plants cover them " +
        "with some sparse grass growing on the hillocks. They don't look " +
        "stable floating in the pools of brackish water.\n");
    add_item(({"pools", "brackish waters", "pools of brackish water", 
            "pools of water", "water"}),
        "These are slimy pools of dark water. They are brackish looking " +
        "with dead plants floating on the surface. They do not look safe " +
        "enough to drink from.\n");
    add_item(({"dead plants", "plants"}),
        "They are made up of dead grasses, dead trees, and leaves. They are " +
        "decomposing and cover the hillocks and float in the pools of " +
        "water.\n");
    add_item(({"dead grasses"}),
        "These are long blades of grass that are dead and lay flat on the " +
        "hillocks or float in the water.\n");
    add_item(({"leaves"}),
        "They are grey leaves that have fallen into the marshes. They are " +
        "decomposing and lay on the hillocks or float in the water.\n");
    add_item(({"trees"}),
        "They are dead, decomposing stumps of trees that once grew in the " +
        "marsh. They reach out of the water, are bare of leaves, and look " +
        "ghostly in distance.\n");
    add_item(({"grasses"}),
        "The grasses are sparse and grow on the hillocks. It is grey and " +
        "bent over, covering the ground.\n");
    add_item(({"insects", "bugs"}),
        "All kinds of bugs and insects fly around you. They are noisy and " +
        "hum in your ears. Some skitter across the surface of the pools, " +
        "and others wander across the hillock.\n");
    add_item(({"flowers", "wild flowers", "wildflowers", "wild-flowers"}),
        "Wild flowers grow sparsely on different hillocks. They look " +
        "paltry, barely surviving in the marsh. They are dark colored and " +
        "nod in the breeze.\n");

//    set_add_sky();

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("Close by you hear: neek-breek, breek-neek.");
    add_room_tell("Far away you hear: neek-breek, breek-neek.");
    add_room_tell("Nearby you hear: neek-breek, breek-neek.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("A sickly odor floats past.");
    add_room_tell("Clouds of insects suddenly fly up from the ground.");
    add_room_tell("Insects fly around you.");

}


/*
 * Function name : set_add_weather_hills
 * Description   : adds descr of weather hills
 */
void set_add_weather_hills()
{
    add_item(({"hills", "weather hills"}),
        "These hills are bare and run from the northwest to the southwest. They " +
        "are wind blown and brown colored. Visible grooves run down the " +
        "side of the hills.\n");
    add_item(({"grooves"}),
        "These are vertical and run down the side of the hills. They " +
        "were probably formed from the constant winds that blow through " +
        "the hills and rainfall. They are brown, like the hills, and look " +
        "desolate.\n");
    add_item(({"boulders"}),
        "They are large, angular rocks that have broken off from the " +
        "hills. They lay scattered about the hills with grasses and " +
        "bushes growing around the.\n");
    add_item(({"pebbles"}),
        "They are small rocks with smooth edges. They look like they " +
        "have broken off the boulders and rocks that lay scattered " +
        "around the hills.\n");
    add_item(({"rocks"}),
        "They are larger than pebbles and lay scattered all over the " +
        "hills. They have sharper edges and appear to have broken off " +
        "from the boulders.\n");
    add_item(({treetype, treetype+" trees", "trees"}),
        "The "+treetype+" trees grow sparsely in the hills. They are " +
        "ragged looking, and not very tall. The branches are thin and " +
        "scarcely covered by leaves. The trees hug the base of the hills.\n");
    add_item(({"branches"}),
        "The tree branches are thin and not very healthy looking. Some " +
        "leaves cover them.\n");
    add_item(({"leaves"}),
        "The leaves are tear-drop shaped and light green. They grow " +
        "sparsely on the trees.\n");
    add_item(({"weathertop", "amon sul", "hill", "tall hill"}),
        "This hill is at the southern end of the Weather hills. It is " +
        "the tallest of the hills and commands a wide view of " +
        "the area. It is wide at the base and rises above everything. " +
        "The top looks flat with nothing growing on it.\n");
    add_item(({"bushes"}),
        "They are short and scrubby looking. The bushes grow in clumps " +
        "in and around the hills.\n");
    add_item(({"grass", "grasses"}),
            "The grasses are dry and sparse. They grow in clumps scattered " +
            "around the hills. They are gray colored and very short. \n");    

}

/*
 * Function name : set_add_bushes
 * Description   : adds descr of general bushes for Great East Road
 */
void set_add_bushes()
{
    add_item(({"bushes", "shrubs"}),
        "The bushes and shrubs grow scattered across the land. They are " +
        "healthy and different sizes. Some are even large enough to hide " +
        "a traveller.\n");
}


/*
 * Function name : set_add_east_whills
 * Description   : adds descr of east side of weather hills
 */
void set_add_east_whills()
{
    set_add_rocks();
    add_item(({"hills", "weather hills"}),
        "The wind blown, brown colored, bare hills are to the west. " +
        "Visible grooves run down their sides.\n");
    add_item(({"grooves"}),
        "These are vertical and run down the side of the hills. They " +
        "were probably formed from the constant winds that blow through " +
        "the hills and rainfall. They are brown, like the hills, and look " +
        "desolate.\n");
    add_item(({"boulders"}),
        "They are large, angular rocks that have broken off from the " +
        "hills. They lay scattered about the hills with grasses and " +
        "bushes growing around the.\n");
}

/*
 * Function name : set_add_rocky_plains
 * Description   : adds descr of the area between the Weather Hills 
 * and the Trollshaws
 */
void set_add_rocky_plains()
{
    set_add_rocks();
    set_add_bushes();
    add_item(({"wild grasses", "grasses", "sparse grasses"}),
        "The grasses are about ankle deep, and sparse looking. They " +
        "hide most of the rocky terrain here. Wild flowers grow in " +
        "clumps on the land and dotting the land are groves of aspens.\n");
    add_item(({"flowers", "wild flowers", "wildflowers", "wild-flowers"}),
        "Various wild flowers are ground within the forest. Their " +
        "scattered arrangements of earthy toned flowers add color to " +
        "the area. They sway lazily in the breezes.\n");
    add_item(({"vegetation", "sparse vegetation"}),
        "The land looks dry and only sparse grasses, wild flowers, " +
        "some bushes, and aspens grow here.\n");
    add_item(({"aspen", "aspens"}),
        "These trees grow in groups and are tall with spreading branches " +
        "towards the crown of the tree. The trunks are smooth and gray. " +
        "The branches are covered with simple, heart shaped leaves.\n");
    add_item(({"branches"}),
        "The branches are concentrated at the top of the tree and spread " +
        "out. They are covered with many leaves.\n");
    add_item(({"leaves"}),
        "The leaves are light green and heart shaped. They cover the " +
        "branches of the aspen trees.\n");
    add_item(({"trunk", "trunks"}),
        "The trunks are large and gray colored. They are bare of any " +
        "branches except for those at the crown of the trees.\n");
    add_item(({"bark"}),
        "The bark is gray colored and very smooth.\n");
    add_item(({"crown", "crown of the tree", "crown of the aspens", 
            "aspen crown"}),
        "The crown of the trees is the top of the tree. Large branches " +
        "grow beneath it which are covered with leaves.\n");
    add_item(({"groves", "groves of aspen", "groves of aspens", "grove"}),
        "The groves are small clusters of aspens that grow scattered " +
        "across the land. They aren't very large and provide some " +
        "protection to the land.\n");

}

/*
 * Function name : set_add_foothills
 * Description   : adds descr of foothills west of Rivendell and around
                   Trollshaws
 */
void set_add_foothills()
{
    set_add_mistys();
    add_item(({"foothills"}),
        "They are small hills at the feet of the Misty Mountains. A " +
        "forest of trees covers the hills.\n");
    add_item(({"small hills", "hills", "low hills"}),
        "The hills are rough looking and reddish colored. They have " +
        "many ravines and ridges and sparsely covered with trees. The " +
        "hills spread to the east.\n");
    add_item(({"trees"}),
        "The trees are conifer and cover the hills half-hazardly. Many " +
        "of them are straggly looking, growing on the edges of ridges.\n");
    add_item(({"ridges", "ridge"}),
        "It is an outcropping from the hill that is long and narrow. " +
        "It is rocky with a few stunted trees growing on it. \n");
    add_item(({"ravines", "ravine","valley"}),
        "It is a deep, narrow gorge carved in the hills. It looks " +
        "deep but the bottom is hidden by trees and bushes.\n");
    add_item(({"stunted trees", "stunted tree"}),
        "The stunted trees are primarily conifers. The trees grow from " +
        "the sides of the ridges. They are twisted and not very tall. " +
        "Many have exposed roots that seem to cling onto the side of " +
        "the hills.\n");
    add_item(({"forest"}),
        "The forest is made up of conifers. It is spread over the hills " +
        "and made up of mostly stunted trees.\n");
    add_item(({"branches", "tree branches"}),
        "The tree branches are rough and gray colored. They have needles " +
        "on them. \n");
    add_item(({"needles", "green needles"}),
        "The green needles are long and grayish-green colored. They " +
        "cover the branches of the trees,\n");
    add_item(({"mosses", "moss"}),
        "It is soft green moss, a bit yellow in patches.\n");
    add_item(({"ground", "forest debris", "debris", 
         "forest floor", "floor", "down"}),
        "The forest is covered with fallen needles and fallen branches. " +
        "Some dead tree trucks lay buried by the forest debris.\n");
    add_item(({"dead tree trunks", "tree trunks"}),
        "\n");
    add_item(({"fallen branches", "dead branches", "dead branch"}),
        "They are broken from the trees and lie scattered across the " +
        "ground. Some are freshly broken off and others are half " +
        "decomposed, ready to fall apart and buried on the forest floor.\n");
    add_item(({"twig", "twigs"}),
        "They are small branches, laying scattered across the ground.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees", 
            "dead tree"}),
        "These are dead " + treetype + " trees that have fallen over " +
        "from old age and lay on the ground. Some are rotting, and some " +
        "are ready to fall apart. Moss and lichens grow on the oldest " +
        "fallen trees.\n");
    add_item(({"log", "logs", "rotting log", "rotting logs"}),
        "The rotting logs lay on the ground, the oldest ones buried by " +
        "fallen leaves and fallen branches. Some are hollowed out and look " +
        "to be homes for woodland animals.\n");    
    add_item(({"undergrowth", "underbrush"}),
        "Dense bushes grow beneath the trees, making travel through the " +
        "forest difficult and obscuring your way.\n");
    add_item(({"plants", "woodland plants"}),
        "Besides trees, a many different plants grow in the forest. There " +
        "are flowers and bushes grow everywhere.\n");
    add_item(({"lichen", "lichens"}),
        "Lichen can be seen on some rocks and trees. It is grey and white " +
        "colored. Some are simple strands while others are large and fan " +
        "shaped.\n");
    add_item(({"hollow logs", "hollow log"}),
        "The logs are rotting and hollowed out. Most of them are partially " +
        "buried in the ground or in the forest debris.\n");
    add_item(({"flowers", "wild flowers", "wildflowers", "wild-flowers"}),
        "Various wild flowers are ground within the forest. Their scattered " +
        "arrangements of white, yellow, pink, and other vibrant shades add " +
        "color to the forest floor. They sway lazily in the breezes.\n"); 
}


/*
 * Function name : set_add_trollshaws
 * Description   : adds descr of trollshaws
 */
void set_add_trollshaws()
{
    set_add_foothills();

    add_item(({"paw prints", "prints"}),
        "They are large and thick in the ground, appearing to belong to " +
        "great wolves.\n");
    add_item(({"marks", "gashes", "marks and gashes"}),
        "The marks and gashes in the trees look like they were " +
        "made by clubs, claws, or teeth, probably from the wild " +
        "trolls or beasts that roam the area.\n");
    add_item(({"tracks", "troll tracks", "troll track", "track"}),
        "These large, clawed tracks are fresh and appear to " +
        "have been made by wild beasts--or worse, by trolls.\n");
    add_item(({"broken trees"}),
        "These trees have been broken and splintered in half. They look " +
        "like they were broken by trolls or other large beasts.\n");
    add_item(({"bushes", "shrubs"}),
        "The bushes are thorny but scraggly looking. They grow scattered " +
        "across the area and some look large enough to block your passing.\n");
}
