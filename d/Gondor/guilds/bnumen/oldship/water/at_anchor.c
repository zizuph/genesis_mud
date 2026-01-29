#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <macros.h>
#include "/d/Gondor/std/tell.c"

#define NSHIP  (BNUMEN_DIR + "ship/nship")

string boat_desc();
int sky_add_items();
string sky_desc();

static object Ship;

public void
reset_room()
{
    if (objectp(Ship))
        return;

    Ship = clone_object(NSHIP);
    Ship->start_ship();
    Ship->stop_ship("");

}


void
create_room()
{
    set_short("An isolated cove");
    reset_room();
    set_long("The cove is sheltered from the wind and weather on the " +
        "lee side of the island. From here rocky outcrops on the island " +
        "and a strange dark cliff wall are visible. To the east ominous " +
        "dark clouds shroud the horizon." + sky_desc() +  boat_desc());

    add_item((({"clouds", "dark clouds", "ominous dark clouds", "east"})),
        "The East is darkened by storm clouds and some other " +
        "deep grey haze.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
/*
    add_prop(ROOM_I_NO_CLEANUP, 1);
*/

}
string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  sky_text;

    switch (time)
    {
    case "night":
        sky_text = " An ocean of stars blankets the deep blue night " +
            "sky, sparkling on the surface of the Sundering Sea";
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
            sky_text += " as the moon tilts its sharp horns."; 
        break;
        default:
            sky_text += ", but the moon cannot be seen.";
            break;
        }
        break;
  
    case "morning":
        sky_text = " The morning sun rides low over the horizon, trying " +
		    "to pierce the dense darkness in the east.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead, sparkling " +
            "brightly on the dark-blue waves.";
        break;
	case "afternoon":
        sky_text = " The afternoon sun paints the sea golden.";
        break;
    case "evening":
        sky_text = " Dusky twilight of early evening casts a soft " +
            "glow on the sea.";
        break;
    case "early morning":
        sky_text = " The first rays of sun momentarily pierce the " +
            "darkness to the east.";
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
        add_item(({"sky", "night sky"}), "The night sky is illuminated by " +
            "numerous twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon " +
                "reflects silver on all below.\n"); 
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
            "down upon the sea, making it golden.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit " +
            "by the growing light of the sun, piercing the darkness.\n");
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

string
boat_desc()
{
    if (present(Ship))
    {
        return " A vast, long black ship lies at anchor " +
            "here, its masts towering high over the waves like " +
            "the tall trees they were hewn from.\n";
    }
    return "\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }   
}


