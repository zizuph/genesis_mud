/* -*- Mode: C -*-
 *
 * lib/room_tells.c
 *
 * By Skippern 20(c)01
 *
 * A list of pre generated room tells.
 */
inherit "/d/Gondor/std/tell";

#include "../defs.h"

public void
pier_tells()
{
    add_tell("You smell a mix of salt water and tared lumber.\n");
    add_tell("You hear a rushing sound as a wave breads against some " +
	     "rocks.\n");
    add_tell("A ship tugs its mooring lines.\n");
}

public void
ship_tells()
{
    add_tell("A squeezing is coming from one of the mooring lines.\n");
    add_tell("You can see a sailor resting on the railing of one of the " +
	"ships.\n");
    add_tell("A cracking sound comes from one of the mooring lines.\n");
}

public void
square_tells()
{
    add_tell("Somebody announces apples for sale.\n");
    add_tell("Somebody announces carrots for sale.\n");
    add_tell("Some noise raises as a cart tumbles into the square " +
	     "and crashes in one of the sales stands.\n");
    add_tell("You catch somebody ruffling through your belongings.\n");
}

public void
bay_tells()
{
    add_tell("You hear the sound of waves.\n");
    add_tell("You see some sea gulls play out on the bay.\n");
    add_tell("A sea gull goes: SQUEEK.\n");
}

public void
street_tells()
{
    add_tell("A citizen passes by you.\n");
    add_tell("A cart passes by you.\n");
    add_tell("Some dust blows down the street.\n");
}
