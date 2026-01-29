/*
 * Base room for Lebennin rooms
 *
 * Based on work from Anorien by Varian
 * Rungne 2017
 */

#include "/d/Gondor/lebennin/std/defs.h"
#include <macros.h>

inherit "/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/time";

void set_items_plains();
void set_items_road();
void set_items_pelargir();
void set_items_linhir();
void set_items_corsair_camp();
void set_herbs(int group);
string get_time_desc(mapping type);
string set_day_night_tells(string day_str, string night_str);
static string npc_team_file = "";

function sun_moon = &get_time_desc(SUN_MOON);
function light_type = &get_time_desc(LIGHT_TYPE);
function daylight = &get_time_desc(DAYLIGHT);
function day = &get_time_desc(DAY);
#define DEBUG(x) find_player("rungne")->catch_msg("[DEBUG]: " + x + "\n")

public void
create_lebennin_room() 
{
}

/*
    add_tell("Several clouds pass in front of the " + sun_moon() +
        ", temporarily blocking out the " + light_type() + " that shines " +
        "down upon these plains.\n");
    add_tell("As some clouds part in the sky, bright " + light_type() + 
        " from the " + day() + " " + sun_moon() + " spreads out across " +
        "the grassy plains.\n");
    add_tell("A gentle breeze ripples through the tall grasses, causing " +
        "them to bend and sway with each gust of wind.\n");
    add_tell("A small flock of birds chase each other, swooping and diving " +
        "all across the grassy plains.\n");
    add_tell("A large flock of birds chase each other, swooping and diving " +
        "all across the plains.\n");
    add_tell("A gentle breeze ripples through the tall grasses, causing " +
        "them to bend and sway with each gust.\n");
    add_tell("Off in the distance, you see what appears to be a bear " +
        "wandering across the plains.\n");
    add_tell("A horde of tiny flies start buzzing around your face, biting " +
        "at your bare flesh.\n");
    add_tell("A brightly coloured dragonfly zips past, chasing down some of " +
        "the insects for a quick meal.\n");
    add_tell("A grey snake swiftly slithers past, quickly becoming lost " +
        "in the tall grasses.\n");
    add_tell("A flight of swallows dance in the air before taking shelter " +
        "in a nearby grove of fir trees.\n");
    add_tell("A small flight of swallows dance in the air before taking " +
        "shelter in a nearby grove of elm trees.\n");
    add_tell("A small flight of swallows dance in the air before taking " +
        "shelter in a nearby grove of oak trees.\n");
    add_tell("Dozens of tiny butterflies flutter across the grassy plains " +
        "in a parade of bright colours.\n");
    add_tell("A handful of tiny butterflies flutter across the grassy " +
        "plains in a parade of bright colours.\n");
    add_tell("A couple of tiny butterflies flutter across the grassy plains " +
        "in a parade of bright colours.\n");
    add_tell("A large deer, grazing in the plains looks up at you and " +
        "bounds away into a grove of oak trees.\n");
    add_tell("A young buck, grazing in the plains looks up at you and " +
        "bounds away into a grove of elm trees.\n");
    add_tell("The droning chirp of crickets echoes across the plains.\n");
*/
nomask void
create_room()
{
    create_lebennin_room();
    set_tell_time(random(400) + 90);
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

/*
 * Function name:        set_items_plains
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_plains(); 
 *                       Use for all plains rooms in Anorien
 */
void
set_items_plains()
{
/*    add_item(({"grasses", "grass", "ground", "plain", "plains", "green grass"}),
        "The ground here is full of a tall, green grass which bends gently " +
        "in the wind, swaying back and forth. Stretching off into the " +
        "distance, the plains are filled with endless insects which buzz " +
        "around everywhere, often around the large clusters of wildflowers " +
        "which hide in the grass.\n");
    add_item(({"flower", "flowers", "wildflower", "wildflowers"}),
        "Scattered across the plains, brilliant hues of red, purple, blue " +
        "and orange are visible where clusters of wildflowers are nestled " +
        "in the tall green grass.\n");
    add_item(({"insect", "insects"}),
        "The wide grassy plains are filled with the endless, buzzing drone " +
        "of insects. Most of the insects seem to be of the biting kind, " +
        "although you do see a number of bees hovering around the " +
        "wildflowers. Despite everything you do to shoo them away, it " +
        "does feel like there is an endless cloud of bitemes hovering " +
        "around your head.\n");
    add_item(({"biteme","bitemes", "fly", "flies"}),
        "These annoying little insects seem to be overjoyed that you, their " +
        "most recent meal, have arrived. No matter how much you swat at " +
        "them, there are still dozens more hovering around your head and " +
        "biting at your skin.\n");
    add_item(({"swallow","swallows"}),
        "Every once in a while, you can see a small group of swallows " +
        "dipping and diving across the waters of the great river.\n");
    add_item(({"bird","birds"}),
        "This land is full of life, including hundreds of birds which " +
        "keep the air alive with song, and fly from one grove of trees " +
        "to another in small flocks.\n");
    add_item(({"dragonfly","dragonflies"}),
        "Dozens of dragonflies are zipping about, chasing down their " +
        "meals of the small, bothersome insects that constantly seem " +
        "to be in your face.\n");
    add_item(({"crickets","cricket", "grasshopper", "grasshoppers"}),
        "The constant chipring of crickets and grasshoppers drones in " +
        "your ears as you pass through these plains. You occasionally " +
        "spot some as they jump and fly around in the grass.\n");
    add_item(({"butterfly","butterflies"}),
        "Fluttering through the air, pushed along by the gentle breezes, " +
        "hundreds of butterflies drift across the plains in a dazzling " +
        "display of colours on parade.\n");
    add_item(({"west", "western horizon"}),
        "The plains of Lebennin stretches far to the west, until they meet " +
        "the confluence of the rivers Gilrain and Serni and the city " +
        "Linhir.\n");
    add_item(({"southwest", "southwestern horizon"}),
        "The plains of Lebennin stretches far to the southwest before they " +
        "meet the seashore.\n");
    add_item(({"northwest", "northwestern horizon"}),
        "The river Serni flow sluggishly through the plains which dominate " +
        "the northwestern horizon.\n");
    add_item(({"north", "northern horizon"}),
        "The plains of Lebennin stretches into the horizon to the north.\n");
    add_item(({"east", "eastern horizon"}),
        "The great city of Pelargir lies to the east, with the river Sirith " +
        "flowing around the city to meet the rushing waters of the mighty " +
        "Anduin River.\n");
    add_item(({"southeast", "southeastern horizon", "estuary"}),
        "The plains stretch far to the southeast, rolling over hills until " +
        "they reach the mighty Anduin River.\n");
    add_item(({"northeast", "northeastern horizon"}),
        "The grey waters of the Entwash flow sluggishly through the marshy " +
        "lands which dominate the northeastern horizon before they empty " +
        "out into the rushing waters of the Anduin.\n");
    add_item(({"south", "southern horizon"}),
        "The plains of Lebennin stretches all the way to the wide river " +
        "delta of Ethir Anduin to the south. Beyond the delta you can see " +
        "the sea.\n");
    */
    add_item(({"Lebennin"}),
        "You are in the lands of Lebennin, in the nation of Gondor.\n");
}

/*
 * Function name:        set_items_anduin
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_anduin(); 
 *                       Use for all plains rooms in Anorien near the Anduin
 */
void
set_items_pelargir()
{
    add_item(({"rivers"}),
        "To the east you can see the river Sirith flowing down to join the " +
        "mighty Anduin river.\n");
    add_item(({ "anduin", "mighty river"}),
        "South of Pelargir the grey waters of the mighty Anduin river rush " +
        "past towards the sea.\n");
    add_item(({"walls", "wall", "city walls"}), "The city walls surrounding " +
        "Pelargir raises above Sirith to the east.\n");
    add_item(({"Pelargir", "pelargir", "city"}), "The great city Pelargir " +
        "stands to the east. The city stands well protected with Sirith " +
        "forming a natural moat before the fortified walls.\n");
    add_tell("You catch a glimpse of " + daylight() + " reflected on the " +
        "armour of a guard patrolling the walls of Pelargir.\n");
}

/*
 * Function name:        set_items_linhir
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_linhir(); 
 *                       Use for all plains rooms in Lebennin near Linhir
 */void
set_items_linhir()
{

}

/*
 * Function name:        set_items_road
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_road(); 
 *                       Use for all plains rooms on the road
 */
void
set_items_road()
{
    add_item(({"road", "stone road", "old road", "cobblestones", "stones",
        "cobblestone", "old cobblestone road"}), 
        "This old cobblestone road looks well travelled. Some stones are " +
        "missing, but still the road looks well-maintained. It runs across " +
        "the plains of south Lebennin.\n");
//    add_item(({}), )
    add_tell("A grey-cloaked human rides past you on the road, the loud " +
        "clacking sound of hooves scares some small birds into flight.\n");
    add_tell("You catch sight of a small mouse scurrying across the road.\n");
    add_tell("A red-tailed hawk swoops down and snatches a mouse from the " +
        "grass next to the road.\n");
}

/*
 * Function name:        set_items_corsair_camp
 * Description  :        Items added to the corsrair camp rooms when you include
 *                       the line set_items_corsair_camp(); 
 *                       Use for all rooms in the corsair camp
 */
void
set_items_corsair_camp()
{
//    add_item(({}), )
}

/*
 * Function name:        set_herbs
 * Arguments    :        int group - Choose herb group
 * Description  :        Makes all herbs of the group available to be found
 *                       when searching for herbs.
 *                       see /d/Gondor/lebennin/std/defs.h for reference
 */
void
set_herbs(int group)
{
    set_up_herbs(LEBENNIN_HERBS[group], ({"ground", "plain"}), 5);
}

/*
 * Function name: get_time_desc
 * Description:   Returns a string with different day/night
 *                descriptions for use in room descriptions and room tells
 * Argument:      One of many mappings defined in /w/Gondor/lebennin/std/defs.h
 */
string
get_time_desc(mapping type)
{
    switch(qhour())
    {
    case LATE_NIGHT_RANGE:
        return type[LATE_NIGHT];
    case EARLY_MORNING_RANGE:
        return type[EARLY_MORNING];
    case MORNING_RANGE:
        return type[MORNING];
    case NOON_RANGE:
        return type[NOON];
    case AFTERNOON_RANGE:
        return type[AFTERNOON];
    case EVENING_RANGE:
        return type[EVENING];
    case EARLY_NIGHT_RANGE:
        return type[EARLY_NIGHT];
    }
}

/*
 * Function name: get_all_no_exits
 * Description: Returns an array of strings with exits for use with
 *              set_no_exit_msg()
 * Argument: Array of exits to exclude, for simplicity you can use
 *           nw instead of northwest, etc.
 */
string *
get_all_no_exits(string *exits)
{
    string *r_exits = m_values(NORMAL_EXITS);

    foreach (string exit: exits) {
        foreach (string ind, string val: NORMAL_EXITS) {
            if (exit == ind || exit == val) {
                r_exits -= ({ val });            
            }
        }
    }

    return r_exits;
}

/*
 * Function name: set_day_night_tells
 * Description: Returns one of the provided strings based on which time
 *              it is
 * Arguments: day_str: String to return if it is day
 *            night_str: String to return if it is night
 */
string
set_day_night_tells(string day_str, string night_str)
{
    switch(qhour())
    {
    case 22..5:
        return night_str;
    default:
        return day_str;
    }
}

/*
 * Call this with npc id for npcs to team automatically
 * 
 */
void
set_team_npc(string file)
{
    npc_team_file = file;
}

object
do_npc_team()
{
    object *npcs = container_objects[npc_team_file][3];
    int i;
    int avg = 0;
    int this_avg;
    object leader;

    // Make the biggest npc the leader
    for (i = 0; i < sizeof(npcs); i++) {
        this_avg = npcs[i]->query_average_stat();
        if (this_avg > avg) {
            leader = npcs[i];
            avg = this_avg;
        }
    }
    return leader;
    /*
    //team up
    for (i = 0; i < sizeof(npcs); i++) {
        if (npcs[i] != leader) {
            leader->team_join(npcs[i]);
        }
    }
    */
}

public void
init()
{
    add_action(check_time, "time");
    ::init();
}
