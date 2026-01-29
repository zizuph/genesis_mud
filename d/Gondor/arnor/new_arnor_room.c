/*
 *  Arnor revisited
 *  Original coding adapted from Arren and Olorin
 *
 *  Updated sky and time descriptions to reflect
 *  "Evendim"--Twilight of the north
 *
 *  Some sky descriptions borrowed from Gondor files
 *  of Alto and Serif
 *  
 *  Tigerlily--June 2003
 *    --updated March 2005
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c"; 
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "arnor_defs.h"

/*
 *  Global variables
 */
string  sky_text;

/*
 *  Prototypes
 */
public string sky_desc();
public int    sky_add_items();
void          add_road_downs_tells();
void          add_road_downs_items();
void          add_carn_tells();
public string star_view(object tp);
string        set_road_downs_long(string road_dirs);
string        set_grass_room_long(string extra);
void          add_grass_room_items();
void          set_grass_wandering_msg();
public int    off_road();
string        downs_day_night_tells();
string        can_see_path(string dir);
public string query_arnor_moon();
public int    set_tracks(string dir, string race);
public string set_orc_camp_long(string extra);
void          add_orc_camp_items();
//--------------------------------------------------------------
string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        sky_text = " An ocean of stars blankets the deep blue night " +
            "sky overhead";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale silver of the full " +
                "moon."; 
            break;
        case "waxing crescent":
            sky_text += " as the slender crescent moon begins to rise.";
            break;
        case "waxing gibbous":
            sky_text += " as the nearly full moon rises over the " +
                "horizon."; 
            break;
        case "waning gibbous":
            sky_text += ". The moon, slightly past full, casts a pale " +
                "silver glow over the area."; 
            break;
        case "waning crescent":
            sky_text += " as the moon tilts its sharp horns over the dark " +
                "landscape."; 
        break;
        default:
            sky_text += ", but the moon cannot be seen.";
            break;
        }
        break;
  
    case "morning":
        sky_text = " The morning sun rides low over the eastern " +
		    "horizon.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead.";
        break;
	case "afternoon":
        sky_text = " The afternoon sun shines softly on the " +
            "landscape of Arnor.";
        break;
    case "evening":
        sky_text = " Dusky twilight of early evening " +
            "bathes the realms in soft colour.";
        break;
    case "early morning":
        sky_text = " The first rays of sun peek over the " +
            "horizon.";
        break;
    default:
        sky_text = " The sky is obscured by gathering clouds.";
        break;
    }
    return (sky_text);
}

int
sky_add_items()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
	object tp = this_player();

    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":

        add_item(({"star", "stars"}), &star_view(tp));
        add_item(({"sky", "night sky"}), "The night sky is illuminated by " +
            "numerous twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon " +
                "shines down from the night sky.\n"); 
            break;
        case "waxing gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has almost " +
                "reached its full phase and will likely peak within a " +
                "few days.\n"); 
            break;
        case "waning gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has passed " +
                "its full phase and grows increasingly less illuminating " +
                "with the passing of days.\n"); 
            break;
        case "waxing crescent":
        case "waning crescent":
            add_item(({"moon", "crescent moon"}), "The crescent moon hangs " +
                "low upon the horizon, its sharp ends dangling with the " +
                "tilt of its axis.\n");
            add_item(({"end", "ends"}), "The ends of the moon dangle " +
                "with the tilt of its axis.\n");
            break;
        default:
            break;
        }
        break;
    case "afternoon": 
        add_item(({"sky", "afternoon sky"}), "The afternoon sky is lit " +
            "by the warm light of the sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun shines " +
            "down upon the landscape.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit " +
            "by the growing light of the sun.\n");
        add_item(({"sun", "morning sun", "horizon", "eastern horizon"}), 
            "The morning sun rides low in the eastern horizon.\n");
        break;
    case "noon":
        add_item(({"sky", "noon sky"}), "The noon sky is illuminated by " +
            "the gentle light of the sun directly overhead.\n");
        add_item(({"sun", "noon sun"}), "The noon sun is directly " +
            "overhead.\n");
        break;
    case "evening":
        add_item(({"sky", "evening sky"}), "The evening sky is lit " +
            "by the fading light of the sinking sun.\n");
        add_item(({"sun", "evening sun", "horizon", "western horizon"}),
            "The evening sun is sinking into the western horizon.\n");
        break;
    case "early morning":
        add_item(({"sky", "early morning sky"}), "The morning sky is lit " +
            "by the first rays of the rising sun.\n");
        add_item(({"sun", "early morning sun", "morning sun", "horizon",
            "eastern horizon", "rays", "ray"}), "The early morning sun " +
            "is just peeking over the eastern horizon.\n");
        break;
    default:
        add_item(({"sky", "clouds", "gathering clouds"}), "The sky " +
            "is obscured by gathering clouds.\n");
        break;
    }

    return 1;
}

void
add_cold_tells()
{
    set_tell_time(400);
    add_tell("Ribbons of green and purple from the Aurora " +
        "Borealis shimmer through the sky.\n");
    add_tell("With every step your feet feel " +
        "like blocks of ice.\n");
    add_tell("You shiver from the cold.\n");
    add_tell("Frigid winds blast against your face, making " +
        "your teeth chatter.\n");

}

void
add_road_downs_tells()
{
    set_tell_time(400);
    add_tell(&downs_day_night_tells());

}

string
downs_day_night_tells()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    int x = random(3);
    
    switch (time)
    {
    case "night":
        
        switch (clock->query_moon())
        {
        case "full":
            if (x == 0)
                return "The grasses shimmer under the light of the " +
                    "silver moon.\n";
            if (x == 1)
                return "The full moon rides like a galleon on " +
                    "a sea of fleeting clouds.\n";
            if (x == 2)
                return "The full moon casts its silvery light " +
                    "on the lost realm of Arnor.\n";
            break;
        case "waxing gibbous":
        case "waning gibbous":
        case "waxing crescent":
        case "waning crescent":
            if (x == 0)
                return "Far away a wolf howls at the " +
                "moon.\n";
            if (x == 1)
                return "Under the silvery moon soft breezes " +
                    "sigh through the tall grasses.\n";
            if (x == 2)
                return "The moon is partially obscured by " +
                    "clouds riding fast through the night sky.\n";
            break;
        default:
            if (x == 0)
                return "Chill night winds make a lonely " +
                    "sound, sighing through the tall grasses.\n";
            if (x == 1)
                return "You feel a cold chill " +
                "thinking of the ancient dead and fallen " +
                "buried nearby.\n";
            if (x == 2)
                return "A meteor shoots through the dark night " +
                    "sky.\n";
            break;
        }
        break;
    case "afternoon": 
        if (x == 0)
            return "The scent of sun-warmed green herbs " +
                "fills your nostrils.\n";
        if (x == 1)
            return "Sunlight filters through the afternoon haze, " +
                "making everything appear golden.\n";
        if (x == 2)
            return "Soft winds ruffle the golden green grasses, " +
                "making a sighing sound.\n";
	    break;
    case "morning":
        if (x == 0)
            return "A cloud momentarily blocks the sun, " +
                "casting shadow over the grassland.\n";
        if (x == 1)
            return "Rosy morning light glows on the snow-capped " +
                "peaks of the Misty Mountains.\n";
        if (x == 2)
            return "The grass is green and golden " +
                "under the morning sun.\n";
        break;
    case "noon":
        if (x == 0)
            return "Winds stir the grass under the " +
               "hot noon-day sun.\n"; 
        if (x == 1)
            return "A grasshopper leaps across your path " +
                "and disappears into the grass.\n";
        if (x == 2)
            return "The scent of sun-warmed herbs fills " +
                "your nostrils.\n";
	    break;
    case "early morning":
        if (x == 0)
            return "A cloud momentarily blocks the sun, " +
                "casting shadow over the grassland.\n";
        if (x == 1)
            return "Rosy morning light glows on the snow-capped " +
                "peaks of the Misty Mountains.\n";
        if (x == 2)
            return "Rays of early morning sun pierce through " +
                "a few fleeting clouds.\n";
        break;
    case "evening":
        if (x == 0)
            return "Soft evening breezes bend the tall grasses.\n";
        if (x == 1)
            return "Twilight in the west casts a soft " +
                "glow on the lost realm of Arnor.\n";
        if (x == 2)
            return "A bat darts low overhead in search of insects.\n";

        break;
    default:
        return "Sudden lightning streaks through the sky.\n";
        break;
    }
}

void
add_ruin_tells()
{
    set_tell_time(180);

    
}

void
add_carn_tells()
{

}

string
set_road_downs_long(string road_dirs = "")
{
    string desc;

    desc = "The road follows a rocky ridge through green " +
        "hills covered with tall thick grass. The land is wild " +
        "and lonely, and the wind makes a mournful sighing sound. " +
        "Far to the northeast the jagged snow-capped " +
        "peaks of the Misty Mountains tower above the horizon.";
    desc += sky_desc();
    desc += road_dirs;
    return desc;
}

void
add_road_downs_items()
{
    add_item(({"grass", "tall grass", "thick grass", "tall thick grass"}),
        "Tall thick grass blankets the hills with green, and smaller " +
        "sprouts poke up through the cobblestone rubble of the road. " +
        "Along side of the road the grass stands high and would make " +
        "a good hiding place for creatures. Strangely there are few " +
        "trees here. The land appears uninhabited and has been " +
        "allowed to grow wild.\n");
    add_item(({"hills", "downs", "hill"}),
        "The downs are small hills punctuated " +
        "here and there with valleys. Occasional green mounds stand " +
		"upon the hilltops.\n");
    add_item(({"valleys", "valley"}),
        "Valleys lie between the gentle rolling hills.\n");
    add_item(({"mounds", "mound"}), 
        "Green mounds sit on some of the hilltops as though " +
        "planted intentionally at the highest places. You would " +
        "need to be closer to inspect them more carefully.\n");
    add_item(({"ridge", "rocky ridge"}),
        "The road follows a rocky ridge that winds through " +
        "the hills like a backbone.\n");
    add_item(({"road", "ancient road", "remnant"}),
        "Although it has been allowed to deteriorate and " +
        "has been broken into rubble, the road " +
        "shows that ancient craftsmanship was at work here. It " +
        "is the only sign of civilization in this lonely land.\n");
    add_item(({"stone", "cobblestone", "rubble", "craftsmanship",
        "ancient craftsmanship"}),
        "Mostly the cobblestone has been shattered into rubble, " +
        "but in spots where the stones are unbroken, they fit " +
        "closely together and have a beautiful " +
        "pattern formed into the tiles.\n");
    add_item(({"tiles", "tile", "pattern"}),
        "Here and there you see a pattern of a white " +
        "tree formed into the mosaic of the road tiles " +
        "that remain yet unbroken.\n");
    add_item(({"mountains", "mountain", "Misty Mountains",
        "northern range", "range", "peaks", "snow-capped peaks"}),
        "The farthernmost northern range " +
        "of the Misty Mountains extends far away to the " +
        "northeast and southeast " +
        "all along the horizon. The jagged snow-capped " +
        "peaks look almost like fangs.\n");
    add_item(({"civilization", "signs of civilization",
		"sign of nearby civilization"}),
        "While green and beautiful, the only sign of " +
        "civilization is the road, although clearly " +
        "it was abandoned long ago. The lonely " +
        "landscape seems to betoken the twilight of a " +
        "lost civilization.\n");
    add_item(({"weeds", "weed", "bracken"}),
        "Weeds have taken over the road, as if trying " +
        "to eliminate the last vestiges of civilization.\n");
    add_item("ground", "The ground is cleared somewhat where " +
        "the road leads through the wild.\n");

}

/*
 *  function: string set_grass_room_long(string dirs)
 *  purpose:  basic long for grass rooms with added
 *            note on exit directions
 *
 */

string  
set_grass_room_long(string extra = "")
{
    string desc;

    desc = "All around is an ocean of tall grass that " +
        "bends in the wind like waves breaking on the hills. " +
        "Here and there a bush or scrub oak tree breaks the " +
        "monotony. ";
    desc += sky_desc();
    if (strlen(extra))
        desc += extra;
    desc += "\n";
    return desc;
    
}

void
set_grass_wandering_msg()
{
    string *avail_exits = query_exit_cmds();
    string *all_exits = ({"north", "northeast",
        "east", "southeast", "south", "southwest",
        "west", "northwest", "up", "down" });
    string *non_exits = ({});

    non_exits = all_exits - avail_exits;
    set_no_exit_msg(non_exits, "You wander around " +
        "in the tall grass but can't find your way " +
        "so return to where you started.\n");
    return;
}

void
add_grass_room_items()
{
    add_item(({"grass", "tall grass", "thick grass", 
        "tall thick grass"}), "The hills are covered " +
        "with a deep green tall grass. It makes a good " +
        "hiding place for animals and other creatures. " +
        "It also makes a great place for an ambush.\n");
    add_item(({"oak", "scrub oak", "tree", "bushes", "bush"}),
        "While mostly devoid of forest and trees, " +
        "here and there a small scrub oak tree or " +
        "sumac bush relieves the monotony of the grassland.\n");
    add_item("ground", "The ground is covered in thick grass " +
        "making it difficult to see any path.\n");
}

/*
 *  function: string star_view(object tp)
 *  purpose:  Displays different views of the constellations
 *            depending on race and alignment.
 */

string
star_view(object tp)
{
	int ran_return;

    switch(tp->query_race_name())
    {
        case "elf":
            if (tp->query_alignment() > 0)
            {
                ran_return = random(3);
                switch(ran_return)
                {
                case 0:
                    return "You gaze upon the constellation of " +
                        "Menelgavor, Swordsman of the Sky, " +
                        "with his shining belt " +
                        "and star-jewelled sword and are " +
                        "reminded that evil cannot triumph.\n";
                    break;

                case 1:
                    return "Hope pierces your heart as you gaze upon " +
                        "the Sickle of the Valar, the " +
                        "Valacirca, as it turns through the dark " +
                        "night sky. You are reminded that this " +
                        "sign was placed in the heavens by Varda for " +
                        "the downfall of Morgoth.\n";
                    break;
                case 3:
                    return "Earendil sails among the stars " +
                        "in his silvery boat the Vingilot.\n";
                    break;
                default:
                    return "You are filled with joy to hail the " +
                           "bright stars of Elbereth in the dark " +
                           "northern sky.\n";
                }
         }
        else
            if (tp->query_alignment() < 0)
            {
                return "The bright light of Elbereth's stars " +
                    "pierces through your dark soul, making " +
                    "you shiver.\n";
            }
            break;
        case "human":
        case "hobbit":
        case "gnome":
        case "kender":
            return "The constellation of the Wain wheels through " +
                "the dark night sky.\n";
            break;
        default:
            return "The stars blanket the deep night " +
            "sky.\n";
    }
}

string
can_see_path(string dir = "")
{
    object tp = this_player();
    if (tp->resolve_task(TASK_DIFFICULT, ({TS_INT, SS_TRACKING, 
        SS_LOC_SENSE, SS_AWARENESS})) > 0)
    {
        return "You notice recent tracks heading " +
            "toward the " + dir + ".\n";
    }   
    /* else */
    return "You see no tracks.\n";
}

/*
 *
 *  Purpose:  Measures player's ability to find path off road
 *
 */
int
off_road()
{
    object tp = this_player();

    if (tp->resolve_task(TASK_DIFFICULT, ({TS_INT, SS_TRACKING, 
       SS_LOC_SENSE, SS_AWARENESS})) > 0)
    {
       write("You push your way through the tall grasses.\n");
       return 0; 
    }
    write("You wander around in the grass " +
        "but are unable to find your way. You " +
        "return to where you started.\n");
    return 1;
}
/*
 *  function: string set_orc_camp_long(string dirs)
 *  purpose:  basic long for grass rooms with added
 *            note on exit directions
 *
 */

string  
set_orc_camp_long(string extra = "")
{
    string desc;

    desc = "The ground is charred and nasty debris lies " +
        "all over. The stench is unmistakeably that of an " +
        "orc camp.";
    desc += sky_desc();
    if (strlen(extra))
        desc += extra;
    desc += "\n";
    return desc;
}

void
add_orc_camp_items()
{
    add_item(({"debris", "nasty debris"}), "Bones, broken items " +
        "and other decaying litter lie strewn around the ground. " +
        "The smell says 'Yrchh!'\n");
    add_item(({"stench", "nasty stench"}), "The smell nearly makes " +
        "you gag.\n");
    add_item("ground", "The ground is charred and littered with " +
        "debris. There is no growing thing on the ground here, " +
        "since it has been burned and charred by orc fires.\n");
    add_item(({"camp", "orc camp"}), &long());
}

void
create_arnor()
{
}

void
create_gondor()
{
    create_arnor();
}

string
query_arnor_moon()
{
    object clock = find_object(CLOCK);

    if(clock->query_time_of_day() == "night")
        return clock->query_moon();
    else
        return "none";
}

public int
set_tracks(string dir, string race)
{
    add_prop(ROOM_S_DIR,({ dir, race }));
    return 1;
}

