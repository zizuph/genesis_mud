/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/ruins_wosg3.c
 *
 *  A secret tunnel in Ithilien hideout
 *
 *  Coded by Tigerlily, April 2, 2004
 *
 */
inherit "/d/Gondor/std/room.c";


#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"

string sky_desc();
string long_desc();
public string do_search(object actor, string str);
int    torch_found;
string exa_corner();
string exa_corner_tile();
string exa_tiles();
int    lift_trapdoor(string str);

void
create_gondor()
{
    set_short("a ruined house in Osgiliath");
    set_long(&long_desc());
    
    add_item(({"ruins", "building", "house"}), "The city of Osgiliath " +
        "lies in ruins from numerous attacks from Mordor. This used to " +
        "be a beautiful house, and now it is only ruins and a " +
        "shadow of what once was.\n");
    add_item(({"frame", "door","south wall", "frame of a door"}), "Part " +
        "of the south wall is still standing and outlines an empty door " +
        "frame where you can exit back to the alley.\n");
    add_item(({"wall", "walls", "stone walls", "east wall"}), "The two " +
        "partial walls that remain are built from blocks of stone set " +
        "without mortar. They have been scorched black from fire.\n");
    add_item(({"ceiling",}), "The southeast corner of the ceiling " +
        "still exists, connecting the two remaining walls, south and east. " +
        "The remaining portions of the ceiling are lying in rubble on the " +
        "ground around you.\n");
    add_item(({"ruins", "rubble"}), "Most of the house is in ruins, and " +
        "the walls and ceiling lie in rubble around you on the ground.\n");
    add_item(({"floor", "ground"}), "Rubble from the broken walls and " +
        "ceiling bear testament to the destruction wreaked by Mordor. " +
        "Beneath the rubble you can make out beautiful " +
        "mosaic patterns in the tiles.\n");
    add_item(({"corner", "southeast corner"}), &exa_corner());
    add_item(({"tiles", "mosaic tiles"}), &exa_tiles());
    add_item(({"tile", "corner tile"}), &exa_corner_tile());
    add_item(({"patterns", "mosaic"}), "The mosaic patterns show " +
        "exquisite craftsmanship and depict intricate figures " +
        "of colourful birds, trees, and flowers.\n");
    add_item("street", "You can glimpse the street through the " +
        "open door frame.\n");
    add_exit(RANGERS_ITH_TUNNEL + "ruins_street", "out", &check_ranger());
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    reset_room();
}
string
long_desc()
{
    string long_txt;

    long_txt = "This had once been a house in Osgiliath, " +
        "filled with light and music. However, now it lies in ruins, " +
        "with the stone walls caved in on two sides and the ceiling " +
        "extending over only a corner of the room. A door frame still " +
        "stands in the wall to your south and leads out to the street.";
    long_txt += sky_desc();
    return long_txt + "\n";
}
   

    
string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string sky_text = "";

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
            "landscape of Osgiliath.";
        break;
    case "evening":
        sky_text = " Dusky twilight of early evening " +
            "bathes the ruins in soft colour.";
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
    object  clock = find_object(CLOCK), tp = this_player();
    string  time  = clock->query_time_of_day();

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
reset_room()
{
    torch_found = 0;
}

public string
do_search(object actor, string str)
{
    object torch;

    if(!str)
    {
        write("Search what?\n");
        return "";
    }

    if (str == "rubble" && !torch_found)
    {
        torch_found = 1;
        torch = clone_object(OBJ_DIR + "torch");
        torch->move(actor, 1);
        return "You find an old torch in the rubble.\n";
    }
    return "You find nothing of interest in the rubble.\n";
}

string
exa_corner()
{
    if (RANGERS_MEMBER(TP))
    {
        return "The southeast corner has two semi-intact walls " +
            "and part of a vaulted ceiling covering it. " +
            "Your keen eyes notice something unusual about the " +
            "corner tile in the floor under the rubble.\n";
    }
//else
    return "The southeast corner has two semi-intact walls " +
        "and part of a vaulted ceiling covering it.\n";
}

string
exa_corner_tile()
{
    if (RANGERS_MEMBER(TP))
    {
        return "The tile is of beautiful workmanship and " +
            "is one meter square. You brush away the dust " +
            "and find that you can lift it by a handle " +
            "inset into one side. It is a trapdoor!\n";
    }
//else
    return "The tile is of beautiful workmanship from " +
        "an earlier era.\n";
}

string
exa_tiles()
{
    if (RANGERS_MEMBER(TP))
    {
        return "The tiles are of ancient workmanship and " +
             "are inlaid with intricate mosaic patterns. You " +
             "spot something unusual about a tile in the " +
             "corner that is partially covered with dust " +
             "and rubble.\n";
    }
//else
    return"The tiles are of ancient workmanship and " +
        "are inlaid with intricate mosaic patterns.\n";
}

void
init()
{
    ::init();
    add_action(&lift_trapdoor(), "lift");
}

int
lift_trapdoor(string str)
{
    object tp = this_player();

    if (str != "trapdoor" && str != "tile" &&
        str != "handle")
    {
        notify_fail("Lift trapdoor?\n");
        return 0;
    }
/*
for some reason this piece of code doesn't work
    if (TO->check_ranger(1) != 0)
    {
        notify_fail("You strain to lift the tile, " +
            "but it falls to the ground with a thud.\n");
        return 0;
    }
*/
    if (!ITHILIEN_MEMBER(tp))
    {
        notify_fail("You strain to lift the tile, " +
            "but it falls to the ground with a thud.\n");
        return 0;
    }
    write("You lift the tile that is actually a trapdoor, " +
        "and suddenly it opens.\nYou fall into a hidden " +
        "passageway.\n");
    tell_room(environment(tp), QCTNAME(tp) + " lifts " +
        "a tile in the floor, and it suddenly swings open.\n", tp);
    say(QCTNAME(tp) + " leaves down.\n");
    tp->move_living("M", RANGERS_ITH_TUNNEL + "osg_cellar", 1, 0);
    tell_room(this_object(), "The trapdoor falls shut, " +
         "stirring up the dust and rubble.\n", tp);

    return 1;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(ob))
    {
        sky_add_items();
    }
}

