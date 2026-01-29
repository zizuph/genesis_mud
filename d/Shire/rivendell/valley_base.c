/*
 * Base file for valley of Rivendell
 * Modified from ~Shire/examples by Finwe
 * November 1997
 */

#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */

void create_valley_room() {}
static string extra_wall   = "";
string herb_here; 

public void
create_area_room()
{
    add_prop(ROOM_S_MAP_FILE, "rivendell.txt");

    set_area("Imladris");
    set_areaname("the valley of Imladris");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("track");
    set_grass("green, fertile");
    set_treetype(({"oak", "beech"}));

    add_item(({"valley", "valley of Imladris", "valley of imladris"}),
        "The valley sits in the shadows of the Misty Mountains, " +
        "protected by the power of Elrond. Most of the valley is " +
        "covered with grasslands with stands of trees scattered " +
        "about. A house sits in the center of the valley.\n");
    add_item (({"beech", "beech trees"}),
        "The trees are tall with thick trunks. The branches " +
        "are covered with many small green leaves that rustle " +
        "in the breeze. The trunks are very large, silver " +
        "colored, and surprisingly smooth.\n");
    add_item(({"oak", "oak trees"}),
        "The oak trees are tremendously large. The trees are " +
        "ancient with many branches spreading out and up to the " +
        "sky. Large, green, serrated leaves cover the branches " +
        "and rustle in the wind.\n");
    add_item("grass",
        "The grass is lush and green, providing a gentle place " +
        "to rest and relax.\n");
    add_item("plants",
        "Many varieties of plants grow here. Some are familiar, " +
        "and others are plants you have never seen before. " +
        "They are all healthy.\n");
    add_item(({"bush", "bushes"}),
        "most of the bushes are about waist-high, covered with " +
        "green leaves. Some are covered with berries providing " +
        "good food for the animals.\n");
    add_item(({"mountains", "misty mountains"}),
        "The Misty Mountains are tall, almost seeming to touch " +
        "the sky. The jagged peaks stretch for miles and " +
        "provide shelter and protection within the valley. The " +
        "tops of the highest peaks are covered with snow.\n");
    add_item(({"tree","trees"}),
        "You see some tall deciduous trees growing here. They " +
        "are enormous and grow in clumps here in the valley.\n");
    add_item(({"deciduous trees", "deciduous",}),
        "The dominate trees here are oak and beech. Other " +
        "deciduous trees grow here including maples and birches.\n");
    add_item(({"down", "ground", "path", "forest debris", "debris"}),
        "The ground is clear of any debris.\n");
    add_item(({"leaves", "leaf"}),
        "You notice that there aren't many leaves on the ground.\n");
    add_item(({"dead branches", "dead branch", "twig", "twigs"}),
        "The ground is free of forest debris.\n");
    add_item(({"fallen trees", "fallen tree", "dead trees",
        "dead tree"}),
        "You don't see any fallen trees.\n");
     add_item(({"flowers", "wildflowers"}),
        "The wildflowers are bright and beautiful. Bees hum " +
        "about the flowers.\n");
    add_item(({"sky"}),"@@sky_light@@");

    create_valley_room();

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A group of elves pass by, laughing merrily.");
    add_room_tell("Two elves run by you as they chase each other.");
    add_room_tell("A nightingale sings in the distance.");
    add_room_tell("You feel an elf brush past you.");
    add_room_tell("An elf greets you as he passes by.");
    add_room_tell("An elf greets you as she passes by.");
    add_room_tell("You hear some laughing nearby.");
    add_room_tell("Some elves can be heard singing nearby.");
    add_room_tell("Somewhere nearby you hear a fair voice " +
        "reciting a lay.");
    add_room_tell("A bird warbles a tune in the distance.");
    add_room_tell("Some elves wander by quietly.");
    add_room_tell("An elf patrols the area.");
    add_room_tell("In the distance you hear a group of elves " +
        "laughing gaily and singing songs.");

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

    add_prop(ROOM_I_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_FROM, 
        "A great elven-power prevents that from happening.\n");

    add_prop(ROOM_M_NO_STEAL,
        "Evil acts like that are not permitted in Imladris.");
    reset_shire_room();
}

string
forest_desc()
{
    switch(random(4))
    {
        case 0:
            return "This part of the valley is a blanket of " +
            "green meadows. The grass is lush and punctuated " +
            "with a few small stands of trees. ";
            break;
        case 1:
            return "The land here is well tended and permits " +
            "easy travel. Vegetation has been cleared to " +
            "allow a view of the valley below. ";
            break;
        case 2:
            return "The valley is green and luxurious. Some " +
            "trees grow in small groups shading the grass " +
            "under your feet. ";
            break;
        case 3:
            return "Green trees spot the land here. A thick " +
            "blanket of grass covers the area. It is dotted with " +
            "bright wildflowers that sway in the breeze. ";
            break;

        default:
            return "The grass moves gently in a warm breeze. " +
            "A few trees grow in clusters here, dotting the land. ";
            break;
     }
}

string
sky_light()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "The moon shines dimly in the sky.\n";
        case LATE_NIGHT :
            return "The stars of Elbereth twinkle in the night " +
                "sky. A group of seven stars shine brightly.\n";
        case EARLY_MORNING :
            return "The sun is beginning to creep up in the " +
                "horizon.\n";
        case MORNING:
            return "The morning sun fills the sky with soft " +
                "light.\n";
        case NOON:
            return "The sun is overhead, burning brightly.\n";
        case AFTERNOON:
            return "The afternoon sun slowly moves towards the " +
                "horizon.\n";
        case EVENING:
            return "The moon is rising in the night time sky.\n";
    }
}

void set_fence(string str)
{
    add_item(({"fence", "split-rail fence", "split rail fence"}),
        "The fence is constructed of timbers that have been " +
        "split in two. " + str);
    add_item(({"fence post", "fence posts", "posts", "post"}),
        "The fence posts are sunk deep into the ground, " +
        "offering a secure foundation for the fence. The rails " +
        "are securely attached to the posts.\n");
    add_item(({"rails", "fence rails", "fence rail", "rail"}),
        "The fence rails are made from split cedar. They are " +
        "weathered and securely fastened to the fence posts.\n");
}

public int
do_climb(string str)
{
     if(!str)
     {
         NF("Climb what?\n");
         return 0;
     }
     write("You can't climb the " + str + ".\n");
     return 1;
 }

void
add_path_herbs()
{
    herb_here = ONE_OF_LIST(({GONDOR_HERB_DIR + "astaldo",
                GONDOR_HERB_DIR + "athelas",
                GONDOR_HERB_DIR + "attanar",
                GONDOR_HERB_DIR + "seregon",
                GONDOR_HERB_DIR + "suranie",
                SHIRE_HERB_DIR + "huckleberry",
                SHIRE_HERB_DIR + "lianor_berry",
                SHIRE_HERB_DIR + "grass",
                KRYNN_HERB_DIR + "tiger_lily",
                "/d/Faerun/herbs/herb_files/amaranth"}));

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"bush","bushes","trees", "flowers"}));
    add_herb_file(herb_here);
}