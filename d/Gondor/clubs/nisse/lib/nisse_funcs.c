/*
 *  /d/Gondor/clubs/nisse/lib/nisse_funcs.c
 *
 *  Various functions common to the Nisse Ohtar camp.
 *  Sky descriptions and sky items have been taken from Alto's code of the
 *  newbie area Riverstead.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
string	sky_text;

/*
 *  Prototypes
 */
string	sky_desc();
int	sky_add_items();
void	add_camp_tells();

string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        sky_text = " An ocean of stars blankets the deep night sky above";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale brightness of the full " +
                "moon."; 
            break;
        case "waxing crescent":
            sky_text += " as the crescent moon begins to rise.";
            break;
        case "waxing gibbous":
            sky_text += " as the nearly full moon rises over the horizon."; 
            break;
        case "waning gibbous":
            sky_text += ". The moon, slightly past full, casts a pale " +
                "glow over the area."; 
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
    case "afternoon":
        sky_text = " The afternoon sun glows warmly in the sky.";
        break;
    case "morning":
        sky_text = " The morning sun is riding low in the eastern horizon.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead.";
        break;
    case "evening":
        sky_text = " The sun is sinking into the western horizon, bathing " +
            "the area in deep orange light.";
        break;
    case "early morning":
        sky_text = " The first rays of sun are peeking over the eastern " +
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

    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":

        add_item(({"star", "stars"}), "The stars blanket the deep night " +
            "sky.\n");
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
        add_item(({"sky", "clouds", "gathering clouds"}), "The sky is " +
            "obscured by gathering clouds.\n");
        break;
    }

    return 1;
}

void
add_camp_tells()
{
    set_tell_time(180);

    add_tell("High overhead a hawk soars in a wide circle.\n");
    add_tell("There is a noise in the underbrush as a startled rabbit "+
        "dives for cover.\n");
    add_tell("Soft breezes ruffle the leaves on grass and bushes.\n");
    add_tell("Wings beat overhead and a hawk suddenly swoops into the " +
        "bushes.\n");
    add_tell("Tiny black ants crawl along the ground in single file.\n");
    add_tell("A gopher peers out from a hole in the ground, chatters " +
        "loudly, then is suddenly gone.\n");
    add_tell("Crickets chirp happily in the bushes.\n");
}

void
add_tent_tells()
{
    set_tell_time(180);

    add_tell("A dark bird enters a hole in the top of a nearby tent.\n");
    add_tell("The tent walls rustle slightly in the breeze.\n");
    add_tell("From somewhere nearby a woman's voice shouts, issuing " +
        "orders.\n");
    add_tell("Clanging sounds of metal on metal tell you a duel is going " +
        "on somewhere close by.\n");
}

string
dfly_colour()
{
    string df_colour = one_of_list(({"dark-green", "sky-blue", "tawny", 
        "yellow-black"}));
    return df_colour;
}

void
add_pool_tells()
{
    set_tell_time(180);

    add_tell("Breezes stir gentle silvery ripples on the tranquil pool.\n");
    add_tell("A @@dfly_colour@@ dragonfly hovers over the pool.\n");
    add_tell("The pool attracts you and you feel mesmerized.\n");
    add_tell("Willow branches sway softly in the breeze.\n");
    add_tell("A willow leaf drifts down and lands on the still surface of " +
        "the pool.\n");
}
