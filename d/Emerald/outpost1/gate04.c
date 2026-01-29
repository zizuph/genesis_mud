/*******************************************************************************
 * Outside the elven outpost.
 * By Mhyrkhaan, November 1998
 *******************************************************************************/

#include "defs.h"

inherit OUTPOST_OUTSIDE_ROOM;
void
create_outpost_outside_room()
{
    set_short("Outside the rear gates of the elven outpost");
    set_em_long("You are standing outside the back gates of the elven outpost. " +
        "The gates are inset into the rough stone wall. In all corners of " +
        "the outpost you can see tall wooden towers looming over the walls. " +
        "You have the definate sense of being watched from those towers. " +
        "before you lies a small trail that disappears into a murky forrest. In the " +
        "distance, through dark clouds you can see the foothills and looming peaks " +
        "of the Darkspyre Mountains.\n");

    add_item( ({"gate" , "gates"}),
        "The gates are about eight feet tall and made of thick wooden logs " +
        "that are held together with iron bands.\n");

    add_item( ({"trail" , "small trail"}),
        "The muddy trail doesn't appear to be used that often.\n");

    add_item( ({"forrest" , "murky forrest"}),
        "The murky forrest seems to mave a sense of depression and sadness with it " +
        "The trees are sagging and the ground is muddy, it doesn't look like it " +
        "would be a plesant walk through it.\n");

    add_item( ({"clouds" , "dark coulds"}),
        "The coulds are dark, they look like they are storm clouds.\n");

    add_item( ({"foothills" , "peaks" , "mountains" , "darkspyre mountains"}),
        "These mountains seem dark, bleak and barren. The forrest that leads up " +
        "to the base of them is murky and forboding. The whole area to the north " +
        "of here looks cold, stormy and wet.\n");

    add_item( ({"wall" , "stone wall"}),
        "The wall is about as tall as a man and made of rough stone blocks. " +
        "It surrounds the outpost providing some protection against invaders.\n");

    add_item( ({"tower" , "towers" , "wooden towers"}),
        "The towers are made entirely of wood. Rising about 30 feet off the " +
        "ground, they provide the tactical advantage of a total view of the " +
        "area and an avenue to launch a deadly rain of arrows upon would-be " +
        "attackers.\n");

    add_exit("gate03.c","south");
} 
