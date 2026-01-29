/*
 * t.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit "/std/room";
inherit ROKEDIR + "lib/roomcode";

#include <macros.h>

void
create_room()
{
    init_sp_quest();

    set_short("top of the mountain");
    set_long("You are at the top of a large mountain. To the south you see " +
             "a volcano, and deep below you is a cave entrance. The view is " +
             "excellent from here and you realize that it is possible to " +
             "look in all directions.\n");

    add_exit("c1", "down");
}

void
glo()
{
    say(QCTNAME(TP) + " studies the surroundings.\n");
}

int
look(string s)
{
    NF("Look where?");
    switch (s)
    {
    case "n":
    case "north":
        glo();
        write("You look north and spot the island Nyreese, with its huge " +
              "mountains, far away. " +
              "To the northwest you barely see the village Cadu.\n");
        return 1;
    case "nw":
    case "northwest":
    case "north-west":
        glo();
        write("You look northwest, and study Cadu carefully. Somewhere in " +
              "the forest north of the village you think that you detect a " +
              "small spot of ancient powerful magic.\n");
        return 1;
    case "w":
    case "west":
        glo();
        write("You look west, but see nothing else than the open sea.\n");
        return 1;
    case "se":
    case "southeast":
    case "south-east":
        glo();
        write("You see a small galleon at the horizon. It is most likely the\n" +
              "ship between Re Albi and Sparkle.\n");
        return 1;
    case "s":
    case "south":
        glo();
        write("You look south, over the large volcano crater, that totally " +
              "dominates this island. Poisonous clouds of sulphur rise " +
              "towards the sky, and occasionally you see a mysterious " +
              "multi-legged creature swimming around in the hot lava.\n");
        return 1;
    case "sw":
    case "southwest":
    case "south-west":
        glo();
        write("Far away, barely visible above the horizon, is the top of " +
              "an island.\n");
        return 1;
    case "e":
    case "east":
        glo();
        write("You see nothing but plain, ordinary water.\n");
        return 1;
    case "ne":
    case "northeast":
    case "north-east":
        glo();
        write("You see the eastern end of Nyreese, where the high mountains " +
              "brutally lead down into the deep ocean, and many tales are " +
              "told about brutal death in the thick forests.\n");
        return 1;
    case "down":
    case "d":
        glo();
        write("You see your own feet. They are dirty.\n");
        return 1;
    case "up":
    case "u":
        glo();
        write("The sky is blue and the sun shines brightly above you.\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    initrc();

    add_action(look, "look");
}
