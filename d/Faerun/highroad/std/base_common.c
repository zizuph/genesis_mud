#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/sys/mudtime.h";
#include "/d/Faerun/sys/sunlight.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

//inherit "/cmd/std/command_driver";
inherit "/std/room";
inherit "/d/Faerun/std/room_tell";
inherit HERB_SEARCH;


void add_neverwinterf()
{
    add_item(({"woods", "forest", "neverwinter wood", "neverwinter woods"}),
        "Tall trees make it up the forest. It stand in the distance to " +
        "the east and spreads in that direction.\n");
}

void add_rocks_and_dirt()
{
    add_item(({"large rocks", "rocks", "stone", "stones", "pebbles"}),
        "They are large and scattered around the mountain. Many are " +
        "dark and various sizes, and rolled down from higher up on the " +
        "mountain.\n");
    add_item(({"boulders"}),
        "They are large, round rocks laying around the mountainside. " +
        "Most of them are taller than a man. Some are cracked and " +
        "splintered. Some are partially buried in the ground.\n");
    add_item(({"dirt", "ground", "soil"}),
        "The dirt is dark brown and rocky. It is made up of rocks that " +
        "have been ground down to grit and pebbles.\n");
    add_item(({"grit"}),
        "It is brown, red, and other earth colors. It is composed of " +
        "rocks that have been ground down to small bits. Rocks and " +
        "pebbles are mixed into it.\n");
}


void add_rocks_and_dirt_cold()
{
    add_item(({"large rocks", "rocks", "stone", "stones", "pebbles"}),
        "They are large and scattered around the mountain and have rolled " +
        "down the mountain. Most of the are jagged and covered with snow.\n");
    add_item(({"boulders"}),
        "They are large, round rocks laying around the mountainside. " +
        "Most of them are taller than a man. Many are cracked and " +
        "splintered from the stress of the elements. They are all covered " +
        "with snow.\n");
    add_item(({"dirt", "ground"}),
        "The ground is rocky and covered with snow. There are bumps in the " +
        "snow which are rocks and pebbles.\n");
    add_item(({"snow"}),
        "It is has blown down from the higher peaks of the mountains. It's " +
        "gathered in drifts with the " + CLOCK->query_light_type() + 
        " reflecting off it.\n");
    add_item(({"drifts", "snow drifts"}),
        "They are deposits of snow created by the wind into mounds " +
        "during snowstorms.\n");
}

void add_grasslands()
{
    add_std_herbs("meadow");

    add_item(({"grasslands"}),
        "They are a large, rolling area covered in tall grass. A few " +
        "trees dot the land. The grass is tall and waves in the breeze.\n");
    add_item(({"grass"}),
        "The grass covers the grasslands. It is " +
        "green with slender leaves and waves in the breeze.\n");
    add_item(({"birds"}),
        "They are various sizes and colors. Some fly around, chirping " +
        "and singing in the grasslands.\n");
    add_item(({"trees"}),
        "They grow in groups around the grasslands. They look strong and " +
        "healthy.\n");
    add_item(({"bushes"}),
        "They are all sizes and shapes, and grow scattered everywhere. " +
        "They are low plants with many branches that spread outward.\n");

}

void add_highroad()
{
    add_item(({"road", "highway", "high road", "highroad"}),
        "The highway is wide and old looking. It is covered with large " +
        "cobbles and looks well used. Bushes and grass have been cleared " +
        "from the side of the road.\n");
    add_item(({"cobbles", "cobblestones"}),
        "They are rectangular shaped paving stones with curved tops. They " +
        "are laid into the road and look worn.\n");

    add_room_tell("Some travellers push past you.");
    add_room_tell("A wagon rumbles past along the road.");

}


void add_mere()
{
    add_std_herbs("seacoast");

    add_item(({"marsh", "swamp"}),
        "It is a large swamp full of low lying water and floating hillocks. " +
        "It smells awful and dangerous. It's known as the Mere of Dead Men.\n");
    add_item(({"mere", "mere of dead men"}),
        "It is an ancient battle field where wars were waged and countless " +
        "warriors died. Since that time, it has flooded and become haunted. " +
        "Rumors say it is full of undiscovered treasure where only " +
        "the strongest and bravest go, but few return, and unspeakable " +
        "horrors live.\n");
    add_item(({"water", "low lying water", "brackish water"}),
        "The water is brackish but reeks of death and sickness. It " +
        "looks diseased and has hillocks floating in it.\n");
    add_item(({"hillocks", "hillock"}),
        "They are islands of matted grass amd debris floating in the " +
        "brackish water. The hillocks look large enough to barely support " +
        "a traveller but still dangerous.\n");

    add_room_tell("A cold mist drifts across the highway.");
    add_room_tell("The smell of stench drifts past you from the west.");
    add_room_tell("Gruff noises echo from the mere.");
}


void add_hills()
{
    add_item(({"hills"}),
        "They are brown and rocky looking. The hills are rolling and " +
        "covered with grass and are wind-blown.\n");
    add_rocks_and_dirt();
}

// Up on the hills
void add_hills1()
{
    add_item(({"hills"}),
        "They are brown and rocky looking. The hills are rolling and " +
        "covered with grass and are wind-blown.\n");
}


void add_sword_mts()
{
    add_item(({"mountains", "sword mountains"}),
        "The mountains are tall and rough looking. They run roughly " +
        "northeast and southwest. The range isn't very large, but " +
        "towers in the distance. The mountains are known by the locals " +
        "as the Sword Mountains.\n");
}

// Up on the mountain
void add_sword_mts1()
{
    add_item(({"mountains", "sword mountains"}),
        "The mountains are tall and rugged looking. They run roughly " +
        "northeast and southwest. The sides are steep and higher than " +
        "the surrounding land. A rocky trail winds through it, past " +
        "large rocks and boulders.\n");
    add_rocks_and_dirt();
}

void add_sword_mts_cold()
{
    add_item(({"mountains", "sword mountains"}),
        "The mountains are tall and rugged looking. They run roughly " +
        "northeast and southwest. The sides are steep and higher than " +
        "the surrounding land. A rocky trail winds through it, past " +
        "large rocks and boulders.\n");

    add_room_tell("A cold wind blows down from the mountains.");
    add_room_tell("Snow blows across the path, making travel more difficult.");
    add_room_tell("The wind howls in your ears.");
    add_room_tell("A gust of wind blows snow into your face, blinding you.");

    add_rocks_and_dirt_cold();
}


void add_bandit_path(string str)
{
    add_hills();
    add_item(({"trail", "path"}),
        "The trail is little more than a line in the hills. It is hidden " +
        "from everyone but the most observant eyes. It " + str + "\n");
    add_item(({"grass"}),
        "It is thin and gray looking. It grows in clumps scattered across " +
        "the hills.\n");
    add_item(({"bushes"}),
        "They grow in clumps on the hills. The bushes look windblown and " +
        "stunted.\n");
    add_item(({"rocks", "gravel"}),
        "They are broken and jagged, and of various sizes. The rocks and " +
        "gravel are different colors and lay scattered across the hills.\n");
}

void add_kryptg()
{
    add_item(({"forest", "woods"}),
        "It is a large, ancient forest that stretches to the northest. The " +
        "forest is known as Kryptgarden Forest by the locals, and is dark and " +
        "forboding.\n");
    add_item(({"kryptgarden forest", "kryptgarden"}),
        "This dark and evil place has a fell reputation throughout the " +
        "Sword Coast. Even hardened adventurers fall silent at the mention " +
        "of it. The Kryptgarden Forest is home to many dangers. Dragons " +
        "are known to lair in the many caverns that penetrate the Sword " +
        "Mountains, and other terrible foes. Many travelers have learned " +
        "this lesson the hard way, and few have returned to tell their " +
        "tales.\n");
}