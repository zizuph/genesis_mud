/*
 * Base file for trees in the forest of Rivendell
 * Modified from ~Shire/examples by Finwe
 * March 1999
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
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
 
void create_shawrom() {}
mixed *room_alias;

public void
create_area_room()
{
    set_area("of a forest somewhere in");
    set_areaname("the trollshaws");
    set_land("Eriador");
    set_areatype(0);
    set_areadesc("dark path");
    set_grass("sparse, dry");
    set_treetype("conifer");

    add_item(({"evergreen trees", "conifer trees", "evergreen",
        "evergreens", "conifers", "conifer", "trees"}),
        "Evergreen trees are everywhere, some stunted and " +
        "others full grown.\n");
	add_item(({"pine trees", "pine tree", "hemlock", "hemlocks",
        "cedar", "cedars", "pines", "hemlock trees", "hemlock tree",
        "cedar trees", "cedar tree"}),
        "They some are tall while others are stunted. Their " +
        "long needles look sharp and dangerous.\n");
    add_item(({"ground", "path", "forest debris", "debris",
        "forest's floor", "floor"}),
        "The ground is covered with broken branches, pine " +
        "needles, moss and lichens, and other forest debris.\n");
      add_item(({"branch", "branches"}),
        "The branches are thick from age and bend slight " +
		"in the breeze.\n");
    add_item(({"leaves", "leaf"}),
        "You don't see leaves here.\n");
    add_item(({"needles", "pine needles"}),
        "They are green and musty smelling. The needles are " +
		"long and sharp.\n");
    add_item(({"mountains", "misty mountains", "mountain"}),
        "The Misty Mountains rise up before you. Their peaks " +
        "are buried in the clouds. Their sides are " +
        "covered with trees up until the snow line. Tales tell " +
        "of the mountains infested with all kinds of orcs and " +
        "trolls, making travel through the mountains dangerous.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "@@daylight_desc@@ filters through the tree " +
        "soaking the branches in patches of @@light_type@@.\n");
    add_item(({"broken branches", "fallen branches"}),
        "Some are twisted and lying on the ground. Others hang " +
        "from the trees, moving in the wind.\n");
    add_item(({"forest debris", "debris"}),
        "Broken and fallen branches litter the ground as well " +
        "as fallen pine needles, mosses, and lichens.\n");
    add_item(({"moss", "mosses"}),
        "They mosses are pale green and look sickly. Some grow " +
        "on the ground and on the barks of the trees.\n");
    add_item(({"lichen", "lichens"}),
        "The lichen hangs from tree branches, like old men's " +
        "grey beards, and some lays on the ground.\n");
    add_item(({"bark", "tree bark"}),
        "The bark of the trees is as varied as the trees " +
        "themselves. Some looks old and chisled from age or " +
        "gashed by monsters, while the newer trees have younger " +
        "looking bark. \n");
    add_item(({"marks", "gashes", "marks and gashes"}),
        "The marks and gashes in the trees look like they were " +
        "made by clubs, claws, or teeth, probably from the wild " +
        "trolls or beasts that roam the area.\n");
    add_item(({"tracks", "troll tracks", "troll track", "track"}),
        "These large, clawed tracks are fresh and appear to " +
        "have been made by wild beasts, or perhaps by trolls.\n");

    set_room_tell_time(random(60)+30);
/*
    add_room_tell("Something watches you from the bushes.");
    add_room_tell("The forest suddenly becomes silent.");
    add_room_tell("A branch crashes down from trees above you.");
    add_room_tell("A sudden movement catches your eye.");
    add_room_tell("Squirrels dart about the branches above you.");
    add_room_tell("A howl is heard in the distance. It is " +
        "answered by another howl.");
    add_room_tell("A howl is heard in the distance. It sounds nearby.");
*/
    add_room_tell("Something crashes about in the bushes to the @@crash_dir@@ of you.");

    create_shawrom();

    add_prop(ROOM_I_INSIDE, 0); /* This is an outdoor room. */
//    set_no_herbs();  /* don't want players herbing up here. */

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

/*
 * Function name:   add_cmd_list
 * Description:     Common routine to add_cmd/call/neg/tell.
 * Arguments:       list    - list of elements
 *                  elem    - the element
 */

string *
add_cmd_list(string *list, mixed *elem)
{
    int i;

    if (obj_no_change)
        return list;
            
    if (!pointerp(list))
        list = ({});
                        
    if (pointerp(elem[0]))
    {
        for (i=0; i<sizeof(elem[0]); i++)
             list = add_cmd_list(list,
                 ({ elem[0][i], elem[1], elem[2], elem[3], elem[4] }));
        return list;
    }
    list = list + ({ elem });
    return list;
}


/*
 * Function name:   add_call
 * Arguments:       action  - action to add
 *                  form    - string to parse_command
 *                  call    - the function to call
 *                  nf      - notify_fail message.
 * Examples:
 *      add_call("smell", "[reek] [of] 'cookies'", "smell_cookies");
 *      .
 *      .
 *
 * int
 * smell_cookies(string arg)
 * {
 *     write("You smell the reek of cookies in the air.\n"
 *         + "Ah!! Smells wonderful!\n");
 *     say(QCTNAME(TP) + " smells the reek of cookies in the air.\n"
 *       + QCTNAME(TP) + " smiles as " + HE_SHE(TP) + " inhales the reek.\n");
 *     return 1;
 * }
 *
 */

varargs void
add_call(mixed action, string form, string call, string nf)
{
    room_alias = add_cmd_list(room_alias, ({ action, form, 2, call, nf }));
}


// randomly selects a direction where crashing sound comes 
// from in the room_tells
string crash_dir()
{
    int crash_count = 7;
    string direction;

    switch (random(crash_count))
    {
    case 0:
        direction = "north";
        break;
    case 1:
        direction = "south";
        break;
    case 2:
        direction = "east";
        break;
    case 3:
        direction = "west";
        break;
    case 4:
        direction = "northeast";
        break;
    case 5:
        direction = "northwest";
        break;
    case 6:
        direction = "southeast";
        break;
    case 7:
        direction = "southwest";
        break;
    }
    return direction;
}