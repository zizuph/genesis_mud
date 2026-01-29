/* Moss's Garden II
 * Coded by Marisol (3/17/98)
 * Modified by Marisol (07/31/98) to be used in the village of
 * Ovejuno in Emerald.
 * The grasshopper file is from Gondor domain, 
 * coded by Mercade. The rest is coded by me.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types

#include "defs.h"
inherit HERB_GARDEN;

void
create_emerald_garden()
{

    set_long("This is the end of the sage femme's garden. It is small "+
       "and cheerful with many exotic flora from all over Emerald. "+
       "A small wooden palisade surrounds the garden to protect it "+
       "again the visitation of cats and chickens but you are not "+
       "sure if it is working. There are old chickens "+
       "poop dotting the ground here and there. In the sky, playful "+
       "clouds sails chasing each other in a endless race. Rows of "+
       "herbs crisscross the garden, so you have to step "+
       "carefully not to crush any plant. The air is wholesome "+
       "in this garden and the smells of herbs mingle with the "+
       "spring-like aroma of the forest outside "+
       "the village. Sometimes the pungent smell of chicken poop will "+
       "waifs in, carried by the playfull breeze.\n");

    add_item("palisade",
       "A sturdy and small wooden fence surounds the garden. The "+
       "wood is alive, and you can see branches with green leaves "+
       "sprouting from the wooden stakes.\n");

    add_item("clouds",
       "Small clouds, that look like playful rabits, move fast with the "+
       "breeze, making them seem like racing in the azure sky.\n");

    reset_room();

    add_exit("herb_garden01.c", "south");

}

void
reset_room()
{
    if(!present("g_bee"))
    {
     setuid();
     seteuid(getuid());
     clone_object(OV_VILLAGE_NPC + "g_bee")->move(this_object());
     
    }
}
