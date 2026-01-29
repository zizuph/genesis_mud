/*******************************************************************************
 * Outside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;
void
create_outpost_outside_room()
{
    set_short("Outside the gates of the elven outpost");
    set_em_long("You are standing outside the gates of the elven outpost. " +
        "The gates are inset into the rough stone wall. In all corners of " +
        "the outpost you can see tall wooden towers looming over the walls. " +
        "You have the definate sense of being watched from those towers.\n");

    add_item( ({"gate" , "gates"}),
        "The gates are about eight feet tall and made of thick wooden logs " +
        "that are held together with iron bands.\n");

    add_item( ({"wall" , "stone wall"}),
        "The wall is about as tall as a man and made of rough stone blocks. " +
        "It surrounds the outpost providing some protection against invaders.\n");

    add_item( ({"tower" , "towers" , "wooden towers"}),
        "The towers are made entirely of wood. Rising about 30 feet off the " +
        "ground, they provide the tactical advantage of a total view of the " +
        "area and an avenue to launch a deadly rain of arrows upon would-be " +
        "attackers.\n");

    add_exit("gate02.c","north");
} 
