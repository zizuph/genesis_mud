/*
 * fi.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "forest.h"

void
create_room()
{
    set_short("Forest");
    set_long("You are standing in a big forest. Around you are lots and " +
             "lots of trees, and you feel a little dizzy as you look at " +
             "their tops, high up above you. The sky is a little darker " +
             "here, and in the distance you hear a howling owl.\n");

    TREES;
    TREE1;

    add_exit("fj", "east");
    add_exit("fh", "southwest");
}
