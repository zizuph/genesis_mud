/*
 *  January 2003, Serif.
 *  Functions including in most rooms in Lorien and its environs.
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>

#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/defs.h"

/* Prototypes */

public string    sky_desc();

public int       field_add_items();
public int       forest_add_items();
public int       path_add_items();
public int       river_add_items();
public int       sky_add_items();

string           sky_text;
object           actor;

int
blocked_path()
{
    write("You wander off the path but you find nothing of "
        + "interest.\n");
    return 1;
}

public int       
field_add_items()
{
    add_item(({"grass", "tall grass",}), "Tall grass grows lushly all "
        + "about.\n");
    add_item(({"field", "vast field",}), "You are on the edge of a vast "
        + "stretching north from a dense wood.\n");
    add_item(({"mountains", "misty mountains", "Misty mountains"}), "The "
        + "Misty mountains rise out of the field several leagues to " 
        + "the west.\n");
    add_item(({"ground", "signs", "faint signs"}), "The ground shows faint "
        + "signs that a few people have passed this way with the last few "
        + "days.\n");
    add_item(({"air", "stench", "humid air", "humidity"}), "The air is "
        + "moist and soothing, smelling freshly of green growing things.\n");
    add_item(({"forest", "dense forest"}), "A dense forest rises out of "
        + "the grass a few dozen yards to the south.\n");
    return 1;
} 

void
add_field_tells()
{
    add_tell("A gentle breeze rustles the grass.\n");
}

public int       
forest_add_items()
{
    add_item(({"forest"}), "A dense forest.\n");
    return 1;
} 

void
add_forest_tells()
{
    add_tell("A gentle breeze moves through the trees.\n");
}

public int       
path_add_items()
{
    add_item(({"grass", "tall grass",}), "Tall grass grows lushly all "
        + "about.\n");
    add_item(({"field", "vast field",}), "You are on the edge of a vast "
        + "stretching north from a dense wood.\n");
    add_item(({"mountains", "misty mountains", "Misty mountains"}), "The "
        + "Misty mountains rise out of the field several leagues to " 
        + "the west.\n");
    add_item(({"ground", "signs", "faint signs"}), "The ground shows faint "
        + "signs that a few people have passed this way with the last few "
        + "days.\n");
    add_item(({"air", "stench", "humid air", "humidity"}), "The air is "
        + "moist and soothing, smelling freshly of green growing things.\n");
    add_item(({"forest", "dense forest"}), "A dense forest rises out of "
        + "the grass a few dozen yards to the south.\n");
    return 1;
} 

void
add_path_tells()
{
    add_tell("A gentle breeze rustles along the path.\n");
}

public int
river_add_items()
{
	add_item(({"river"}), "The mighty Anduin flows here.\n");
}

void
add_river_tells()
{
    add_tell("The river gurgles as it flows by.\n");
}

public mixed
find_season(string str)
{
    object  clock = find_object(CLOCK);
    string  month = clock->query_month_s();

    switch (month)
    {
    case "December":
    case "January":
    case "February":
        return "winter";
    break;

    case "March":
    case "April":
    case "May":
        return "spring";
    break;

    case "June":
    case "July":
    case "August":
    case "September":
        return "summer";
    break;

    case "October":
    case "November":
        return "autumn";
    break;
    }
    return 1;
}

public string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  month = find_season(month);

    switch (time)
    {
    case "night":
        sky_text = " The " + month + " stars twinkle clearly "
          + "as they shine brightly over the land";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale brightness of the full "
                + "moon."; 
            break;
        case "waxing crescent":
            sky_text += " as the crescent moon begins to rise.";
            break;
        case "waxing gibbous":
		    sky_text += " as the nearly full moon rises over the "
                + "mountains."; 
		    break;
        case "waning gibbous":
		    sky_text += ". The moon, slightly past full, casts a shimmering "
                + "glow over the area."; 
		    break;
        case "waning crescent":
            sky_text += ", as the moon tilts its sharp horns over the "
                + "landscape."; 
            break;
        default:
		          sky_text += ", but the moon cannot be seen.";
            break;
        }
        break;
    case "afternoon":
        sky_text = " The afternoon sun shines down upon the landscape.";
        break;
    case "morning":
        sky_text = " The morning sun is riding low in the eastern horizon.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead.";
        break;
    case "evening":
        sky_text = " The sun is sinking into the Misty Mountains to the west, "
          + "bathing the area in deep orange light.";
        break;
    case "early morning":
        sky_text = " The first rays of the sun are peeking over the eastern "
          + "horizon.";
        break;
    default:
		sky_text = " The sky is obscured by gathering clouds.";
        break;
    }
    return (sky_text);
}

public int
sky_add_items()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  month = find_season(month);

    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":
 
        add_item(({"star", "stars"}), "The stars twinkle faintly in the deep "
            + "night sky of " + month + ".\n");
        add_item(({"sky", "night sky"}), "The night sky is illuminated "
            + "faintly by the twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon shines "
                + "down from the night sky, its face slightly pale.\n"); 
            break;
        case "waxing gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has almost "
                + "reached its full phase and will likely peak within a "
                + "few days.\n"); 
		          break;
        case "waning gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has passed "
                + "its full phase and grows increasingly less illuminating "
                + "with the passing of days.\n"); 
		          break;
        case "waxing crescent":
        case "waning crescent":
            add_item(({"moon", "crescent moon"}), "The crescent moon hangs "
                + "low upon the horizon, its sharp ends dangling with the "
                + "tilt of its axis.\n");
            add_item(({"end", "ends"}), "The ends of the moon dangle "
                + "with the tilt of its axis.\n");
            break;
        default:
            break;
        }
        break;
    case "afternoon":
        add_item(({"sky", "afternoon sky"}), "The afternoon sky is lit "
            + "by the bright light of the " + month + " sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun shines "
            + "down brightly upon the landscape.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit "
            + "by the growing light of the " + month + " sun.\n");
        add_item(({"sun", "morning sun", "horizon", "eastern horizon"}), 
            "The morning sun rides low in the eastern horizon.\n");
        break;
    case "noon":
        add_item(({"sky", "noon sky"}), "The noon sky is illuminated by "
            + "the golden light of the " + month + " sun directly overhead.\n");
        add_item(({"sun", "noon sun"}), "The noon sun is directly overhead.\n");
        break;
    case "evening":
        add_item(({"sky", "evening sky"}), "The evening sky is lit "
            + "by the fading light of the sinking " + month + " sun.\n");
        add_item(({"sun", "evening sun", "horizon", "western horizon"}), 
            "The evening sun is sinking behind "
            + "the mountains in the west.\n");
        break;
    case "early morning":
        add_item(({"sky", "early morning sky"}), "The morning sky is lit "
            + "by the first rays of the rising " + month + " sun.\n");
        add_item(({"sun", "early morning sun", "morning sun", "horizon",
            "eastern horizon", "rays", "ray"}), "The early morning sun "
            + "is just peeking over the eastern horizon.\n");
        break;
    default:
        add_item(({"sky", "clouds", "gathering clouds"}), "The sky is "
            + "obscured by gathering clouds.\n");
        break;
    }
    return 1;
}

