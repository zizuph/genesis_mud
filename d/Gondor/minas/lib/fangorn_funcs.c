/*
 *  /d/Gondor/minas/lib/fangorn_funcs.c
 *
 *  Functions that contain base-room repeats for Fangorn forest.
 *
 *  Alto 15 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

public int initiate_torchless();
public int catch_torchless(string str);


/* These items are common to the rooms of Fangorn Forest */

void
add_fangorn_items()
{
    add_item(({"tree", "trees", "oak tree", "oak trees", "spruce tree",
        "spruce trees", "hickory tree", "hickory trees", "forest", "Fangorn",
        "fangorn", "fangorn forest", "Fangorn Forest"}), "Night seems "
        + "to have taken refuge between the trees, leaving your surroundings "
        + "very dim and stuffy. Most of the trees are half covered with "
        + "ragged dry leaves that have never fallen, and have long beards "
        + "of trailing lichen. You need to step "
        + "carefully to avoid tripping over the many tangled roots.\n");
    add_item(({"lichen", "beards", "whiskers"}), "Long strands of lichen "
        + "cling to the trees, resembling "
        + "weeping and trailing beards or whiskers.\n");
    add_item(({"leaves", "leaf", "dry leaves"}), "Leaves are "
        + "everywhere. Some cling "
        + "to the trees, many lie upon the ground below your feet. The "
        + "entire place is so tree-ish, it is hard to imagine animals "
        + "living here at all.\n");
    add_item(({"surroundings"}), "You look around and see many things "
        + "within it.\n");
    add_item(({"ground"}), "It is covered with dry, dead leaves.\n");
    add_item(({"animal", "animals"}), "There do not seem to be any living "
        + "here.\n");
    add_item(({"sky"}), "It is above the trees, but very hard to see "
        + "through the dim haze surrounding you.\n");
    add_item(({"haze", "dim haze"}), "The air here is so stuffy you almost "
        + "have trouble breathing. A haze seems to have settled beneath the "
        + "trees that dampens both hearing and sight.\n");
    add_item(({"limb", "limbs"}), "The limbs of the trees sometimes seem "
        + "to move of their own accord. Many of the trees "
        + "have limbs shaped like great knotted arms, which, if real, "
        + "would no doubt crush skulls with ease.\n");
    add_item(({"rain", "drops", "raindrops"}), "A storm seems to be "
        + "blowing in. The first drops are just beginning to fall among "
        + "the trees.\n");
    add_item(({"eagle"}), "Now and then you hear the piercing cry of a "
        + "great eagle. Even in the open it would be difficult to see so "
        + "far. Under the thick canopy it is impossible.\n");
    add_item(({"canopy"}), "The leaves are thick and tangled above you. "
        + "It is nearly impossible to see the sky through them.\n");
    add_item(({"root", "roots"}), "Beneath your feet is a complex web "
        + "of long gnarled roots. There are so many, and their intertwining "
        + "is so complex that you could never hope to determine which roots "
        + "belong to which tree.\n");

    add_prop("_room_m_da_dragonsteed_no_land", "The trees are too "
        + "thick for the dragon to land!\n");
    
    add_prop(ROOM_I_HIDE, 0);

    setuid();
    seteuid(getuid());
    clone_object("/d/Gondor/fangorn/npc/torchless_object.c")->move(TO);
} 


/* These tells are common to the rooms of Fangorn Forest */

void
add_fangorn_tells()
{
    add_tell("Dark clouds drift across the sky.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("You suddenly feel as if you are being watched.\n");
    add_tell("A tree shifts behind you.\n");
    add_tell("The haze grows more dense.\n");
    add_tell("Something stirs in the leaves nearby.\n");
    add_tell("Leaves float gently to the ground.\n");
    add_tell("Something crashes through the trees to the northwest.\n");
    add_tell("Something crashes through the trees to the northeast.\n");
    add_tell("Something crashes through the trees to the southwest.\n");
    add_tell("Something crashes through the trees to the southeast.\n");
    add_tell("Scattered drops of rain patter on the leaves.\n");
    add_tell("Things suddenly become quiet.\n");
    add_tell("Trees creak and groan as they settle.\n");
    add_tell("A low murmuring rises around you, just out of sight.\n");
    add_tell("Limbs clack and mutter above you, but you sense no wind.\n");
    add_tell("Hmm. You are sure that tree was not there before.\n");
    add_tell("Limbs brush your shoulder unexpectedly.\n");
    add_tell("An eagle cries somewhere high above.\n");

}


public int 
catch_torchless(string str)
{
    string  vb = query_verb();
    object torcher;
    torcher = TP;

    if (torcher->query_npc())
    {
    return 0;
    }
    
    switch (vb)
    {
    case "light":
    case "ignite":
    case "burn":
        WRITE("The brooding menace of the forest seems to prevent that.");
        return 1;
        break;
    default:
        return 0;
    }
}

public int
initiate_torchless()
{
    add_action(catch_torchless, "", 1);
}
