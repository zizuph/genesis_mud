/* 
 * /d/Ansalon/guild/society/room/rack_room.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Kender equipment rack room 
 * Coded by Gwyneth, 1999
 * Gwyneth, January 2001: Added the dragon statue.
 * Gwyneth, June 2004: Fixed description error
 */
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;

object eq_rack, neq_rack, box;

void
reset_kendermore_room()
{
    if (!eq_rack)
    {
        eq_rack = clone_object(KGOBJ + "eq_rack");
        eq_rack->move(TO);
	eq_rack->remove_non_glowing();
    }

    if (!neq_rack)
    {
        neq_rack = clone_object(KGOBJ + "neq_rack");
        neq_rack->move(TO);
        neq_rack->check_glow_rack();
    }

    if (!box)
    {
        box = clone_object(KGOBJ + "box2");
        box->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A cluttered equipment room");
    set_long("You stand in a windowless room, lit by four colourful globes " + 
        "on each wall. A wooden rack has been built into one wall by an " + 
        "expert carpenter. Various things, from junk to magic rings, can " + 
        "often be found laying around on the ground or stashed away in the " + 
        "rack. A set of stairs leads up to a library.\n");

    add_item(({"stairs", "stair", "set", "set of stairs"}), "They look " + 
        "a bit old, but should hold your weight easily.\n");
    add_item("globes", "There are four different globes, golden, silver, " + 
        "green and blue.\n");
    add_item("globe", "Which globe? There are golden, silver, green and blue.\n");
    add_item("green globe", "You stare into the green globe, and the " + 
        "world around you twists and turns. For a brief moment, you are " + 
        "standing in the midst of a cool softly lit forest. Small animals " + 
        "chatter in the brush. Birds flutter in the high branches above " + 
        "you. Insects with gaily coloured wings flit past. Leaves rustle " + 
        "and stir, flowers sway though no breeze touches them - as if the " + 
        "plants revel in being alive. Suddenly you are yanked back to " + 
        "the brightly lit room in Kendermore.\n");
    add_item("golden globe", "You stare into the golden globe, and the " + 
        "world around you twists and turns. For a brief moment, you are " + 
        "standing on a high cliff over the fabled city of Qualinost. " + 
        "Looking down, you see four slender spires rising from the city's " + 
        "corners like glistening spindles, their brilliant white stone " + 
        "marbled with shining silver. Graceful arches, swooping from " + 
        "spire to spire, soar through the air. Crafted by ancient dwarven " + 
        "metalsmiths, they are strong enough to hold the weight of an " + 
        "army, yet they appear so delicate that a bird lighting on them " + 
        "might overthrow the balance. These glistening arches are the " + 
        "city's only boundaries; there is no wall around Qualinost. " + 
        "The elven city opens its arms lovingly to the wilderness. " + 
        "Suddenly, just as you were beginning to enjoy yourself, you " + 
        "are yanked back to the brightly lit room in Kendermore.\n");
    add_item("silver globe", "You stare into the silver globe, and the " + 
        "world around you twists and turns. For a brief moment, you are " + 
        "staring at a magnificent silver dragon gliding towards you. " + 
        "She alights gracefully onto the ground, and as her claws touch " + 
        "the grass, she transforms into a woman. She smiles at you with " + 
        "full red lips, and brushes back a lock of her glistening " + 
        "silvery hair. You stare in awe into two almond-shaped eyes the " + 
        "colour of sunlight, and a deep melodious laugh comes from her " + 
        "lips. She whispers to you, 'I can be a kender too!'. With that, " + 
        "her ears grow even pointier, and her hair is swept up into a " + 
        "topknot. Suddenly, you are yanked back into the brightly lit " + 
        "room in Kendermore, but not before you notice the woman waving " + 
        "goodbye, hoopak in hand.\n");
    add_item("blue globe", "You stare into the blue globe, and the world " + 
        "twists and turns. For a brief moment, you are standing beside " + 
        "a beautiful white fountain in Kendermore. This is a sight you've " + 
        "seen before, but now, four kender sit perched on the edge, " + 
        "speaking in hushed tones. One is very cheerful looking, with " + 
        "very pointy ears. Her shoulder length chestnut coloured hair " + 
        "compliments her pale brown skin and mischievous light brown " + 
        "eyes. A whippik rests lightly in one hand, while the other is " + 
        "idly playing with something in her pouch. The second is " + 
        "taller than usual for a kender, but very skinny. His hair " + 
        "has been dyed blue, and sticks straight up with every passing " + 
        "breeze. Despite the unkempt appearance and rosy red cheeks of " + 
        "a mischievous child, there lies a spark of wisdom in his " + 
        "rainbow coloured eyes. The third kender is tiny in comparison " + 
        "to the second one, and you notice nimble fingers that are " + 
        "currently rummaging through the tall kender's pack, even as " + 
        "they speak. The fourth kender seems to be looking straight " +
        "at you with his alert mahogany eyes! He loads his hoopak and " +
        "aims it straight at you! Suddenly, you are yanked back into " +
        "the brightly lit room in Kendermore.\n");

    add_exit(KGROOM + "train", "east", 0);
    add_exit(KGROOM + "start", "west", 0);
    add_exit(KGROOM + "courtyard", "north", 0);
    add_exit(KGLIB + "library", "up", 0);

    add_prop(ROOM_I_NO_CLEANUP, 1);

    reset_kendermore_room();
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters the room and " +
            "escorts you out of the guild.\n");
        say("A very large looking kender enters the room and escorts " +
            QTNAME(who) + " out of the guild.\n", who);
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " +
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KROOM + "joinroom", 0, 0);
        return;
    }
    return;
}

