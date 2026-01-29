/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/tunnel01.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, March 25, 2004
 *
 */
inherit "/d/Gondor/std/room.c";


#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"
#define RANGER_I_SCANNED_ROAD "_ranger_i_scanned_road"

string sky_desc();
string long_desc();
int    street_exit(string str);
int    scan_road(string str);
int    block_west();


void
create_gondor()
{
    set_short("An unused street among the ruined houses of Osgiliath");
    set_long(&long_desc());
    add_item(({"ruins", "building", "house", "houses"}), "The city of " +
        "Osgiliath lies in ruins from numerous attacks from Mordor. These " +
        "were once beautiful houses, and now they are only ruins and a " +
        "shadow of what once was. You notice that there is an empty " +
        "doorway in a wall to the north that is still standing.\n");
    add_item(({"wall", "walls", "stone walls"}), "There are some walls " +
        "that remain from the devastation of Osgiliath. They have been " +
        "scorched black from fire. There is a wall to the north that " +
        "is still standing, containing an empty door frame.\n");
    add_item(({"ruins", "rubble"}), "Most of the houses are in ruins, and " +
        "the walls and ceiling lie in rubble around you on the ground.\n");
    add_item(({"floor", "ground", "street"}), "The street bears all the " +
        "signs of a war zone. There are potholes and rubble lying " +
        "everywhere. Another street is west of here.\n");
    add_item(({"west street", "street to the west", "west"}), "The " +
        "street to the west looks more heavily travelled. It would be wise " +
        "to scan it from here to make sure it is clear before you leave " +
        "the safety of the pillar. When it's safe, you can crawl west.\n");
    add_item(({"door", "door frame", "empty door frame", "doorway"}),
        "The door was blasted out long ago, leaving only an empty frame. " +
        "You can enter it to the north.\n");
    add_item(({"pillar", "large broken pillar", "broken pillar", 
        "large pillar"}), "Doubtless fallen from one of the " +
        "nearby ruined houses, the broken pillar lies in the middle " +
        "of the street. It is large enough to provide cover from the " +
        "street west of here.\n");
    add_exit(RANGERS_ITH_TUNNEL + "ruins_wosg3.c", "enter", &check_ranger());
    add_exit(ANO_DIR + "road/rroad8.c", "west", &block_west());
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    reset_room();
}
string
long_desc()
{
    string long_txt;

    long_txt = "The disused street is lined with the once-beautiful " +
        "houses of Osgiliath, a place where long ago there had been light, beauty and " +
        "music. Now, however, the houses are ruined and abandoned as a result " +
        "of the devastation of war. A partially intact wall from one of the " +
        "houses stands to the north with an empty door frame. A large broken " +
        "pillar lies in the middle of the street, partially blocking your view " +
        "of the road outside.";
    long_txt += sky_desc();
    return (long_txt + "\n");
}
   

    
string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day(), sky_text = "";

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
            sky_text += " as the nearly full moon rises over the horizon."; 
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
            "landscape of Osgiliath.";
        break;
    case "evening":
        sky_text = " Dusky twilight of early evening " +
            "bathes the ruins in soft colour.";
        break;
    case "early morning":
        sky_text = " The first rays of sun peek over the horizon.";
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
    object clock = find_object(CLOCK), tp = this_player();
    string time  = clock->query_time_of_day();

    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":

        add_item(({"sky", "night sky", "stars"}), "The night sky is " +
            "illuminated by numerous twinkling stars.\n");
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
init()
{
    ::init();

    add_action(&street_exit(), "crawl");
    add_action(&scan_road(), "scan");
}

int
street_exit(string str)
{
// check for anyone in rroad8 before leaving
// to see if the coast is clear

    object tp = this_player();
    
    if (!str || str != "west")
    {
        notify_fail("Crawl west?\n");
        return 0;
    }

    if (!tp->query_prop(RANGER_I_SCANNED_ROAD))
    {
        notify_fail("You should scan the street to the " +
            "west to make sure no enemies are nearby.\n");
        return 0;
    }

    write("You crawl west.\n");
    say(QCTNAME(tp) + " silently crawls west.\n");
    tp->move_living("M", ANO_DIR + "road/rroad8.c", 1, 0);
    tp->remove_prop(RANGER_I_SCANNED_ROAD);
    return 1;

}

int
scan_road(string str)
{
    object actor = this_player(), *items;
    string outside, surroundings;

    if (!strlen(str))
    {
        notify_fail("Scan what?\n");
        return 0;
    }


    switch (str)
    {
    case "street":
    case "the street":
    case "the street to the west":
    case "street to the west":
        outside = ANO_DIR + "road/rroad8.c";
        outside->teleledningsanka();
        if (!objectp(find_object(outside)))
        {
            surroundings = "Shadows obscure the view " +
                "and prevent you from scanning the area.\n";
            return 1;
        }
        surroundings = (find_object(outside))->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(outside)), actor);


        if (sizeof(items))
            surroundings += CAP(COMPOSITE_LIVE(items)) + ".\n";

        actor->add_prop(RANGER_I_SCANNED_ROAD, 1);
        actor->catch_tell("You look out from behind a broken pillar " 
            + "and scan the street to the west.\nThis is what you see:\n\n" 
            + surroundings
            + "\nYou quickly lean back again so that you do not "
            + "reveal yourself.\n");
        tell_room(environment(actor), QCTNAME(actor) + " leans forward to "
            + "look out from behind the broken pillar.\n", ({actor}));
        return 1;

    default:
        notify_fail("What do you want to scan? The street?\n");
        return 0;
    }
    return 1;
}

int
block_west()
{
    if (this_player()->query_prop(RANGER_I_SCANNED_ROAD))
    {
	street_exit("west");
	return 0;
    }
    
    write("You cannot go west directly, else you " +
       "might reveal your position.\n" +
       "You better scan the street first to see if the coast is clear...\n" );
    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(ob))
    {
        sky_add_items();
        ob->catch_tell("You duck behind a broken column to avoid being seen " +
        "from the street to the west of here.\n");
    }
}

