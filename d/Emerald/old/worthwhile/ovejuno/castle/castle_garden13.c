/* The Manor's Garden XIII
*Coded by Marisol (9/8/97) 
 *The mosquito npc and the weak sting poison are Gondor code.
 *The mosquito npc was coded by Mercade and the weak sting poison by
 *Gnadnar. The rest is mine.
 *Modified by Marisol(07/27/98) to be used in the village of Ovejuno
 *in Emerald.
*Copyright (c) Marisol Ramos 1997
*/

#include "../defs.h"

inherit CASTLE_GARDEN;

#define SCARABAE CASTLE_GARDEN_NPC + "g_scarabae"
#define MOSQUITO CASTLE_GARDEN_NPC + "g_mosquito"

object scarabae;
object mosquito;

void reset_room()
{
/*
    if (!scarabae)
    {
   	scarabae= clone_object(SCARABAE);
   	scarabae->move(this_object());
   	scarabae->command("emote crawls in.");
    }

    if (!mosquito)
    {
   	mosquito= clone_object(MOSQUITO);
   	mosquito->move(this_object());
   	mosquito->command("emote flies in.");
    }
*/
}

void
create_emerald_garden()
{
    set_em_long("An old ruined garden lies in front of your eyes. "+
       "The ground is a mix of tall grass and bog. It smells "+
       "of stagnant water. The plants here are very strange and eery. "+
       "The buzzing of insects fill the air. The Castle is a dark "+
       "shadow that blocks any light.\n");

    add_item("plants",
        "The ground is covered with three different kind of "+
        "plants. One looks like red hairy clams ready to close "+
        "its shells. The second, like green coral with many "+
        "branches with a ball full of red hairs. The third "+
        "looks like an open white jaws ready to bite.\n");

    add_item("red plant",
        "This is a Venus Fly-Trap! This carnivorous plant "+
        "eats small unaware flies and insects that have the "+
        "bad luck to fall inside its clam-like leaves. The "+
        "leaves are red and lined with small yellow teeth-like "+
        "leaves. The inside of the trap is filled with a sweet "+
        "smelling liquid to attact its victims.\n");

    add_item("green plant",
        "This is a Roundleaf Sundew! This carnivorous plant "+
        "eats small unaware flies and insects that have the bad "+
        "luck to land in its ball of sticky hair. This particular "+
        "plant have round leaves that look like small balls covered "+
        "with modified leaves that resemble sticks and topped with "+
        "little red pinkish drops that remind you as morning dew.\n");

    add_item("white plant",
        "This is a white Dragonflower, also known as Dragon's mouth. "+
        "This dainty flower is a member of the orchid family. It "+
        "vagely resembles the mouth of a dragon, with a deep-red "+
        "throat and a long, protruding lip rimmed with a fringe of "+
        "pale, white hairs. Its aroma is like rotten fruit.\n");

    add_item("ground",
        "The ground here is a mix of tall grass and spongy bog.\n");

/* Lilith gave me permission to use the description of the dragonflower
* for this garden. The flower is sold in Sybarus Bazzar.*/

    add_exit("castle_garden08", "west");
    add_exit("castle_garden09", "east");

    reset_room();
}


