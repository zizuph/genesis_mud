/*
 *  /d/Sparkle/area/orc_temple/1_armoury.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 1.
 *
 *  Created September 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "dungeon_room";


/* Global Variables */
public mixed        Stand;

/* Prototypes */
public void         create_dungeon_room();
public void         reset_room();


/*
 * Function name:        create_dungeon_room
 * Description  :        constructor for the room
 */
public void
create_dungeon_room()
{
    set_short("within a cramped armoury");
    set_long("There is very little room to move around in this chamber"
      + " due to the armour stand that dominates the floor space.\n\n");

    add_item( ({ "chamber", "here", "armoury", "cramped armoury",
                 "cramped chamber" }),
        "This room appears to be an armoury, judging by the huge armour"
      + " stand that sits amid the clutter.\n");
    add_item( ({ "floor", "floor space", "down", "ground" }),
        "You would think that such cramped conditions would encourage"
      + " people to keep the floor clear of debris. Evidently, that sort"
      + " of thinking is completely foreign to the denizens of this"
      + " dungeon. The floor is full of clutter!\n");
    add_item( ({ "conditions" }),
        "Cramped!\n");
    add_item( ({ "cramped conditions" }),
        "You'd feel more comfortable sharing an outhouse with an"
      + " elephant than you do in here!\n");
    add_item( ({ "denizens", "denizen", "denizens of this dungeon" }),
        "Goblins, and dang messy ones. Someone ought to teach them"
      + " a lesson!\n");
    add_item( ({ "clutter", "debris", "mess" }),
        "It's just the usual sort of mess that gets left when no one"
      + " picks up after themselves. Wait! What is that yellow thing"
      + " in the corner?\n");
    add_item( ({ "corner", "corners" }),
        "The room has four of them. They come standard in most rectangular"
      + " situations.\n");
    add_item( ({ "yellow", "yellow thing", "thing", 
                 "yellow thing in the corner" }),
        "Oh, it's just a banana.\n");
    add_item( ({ "banana" }),
        "Why would a banana be in here? Wait! This isn't a banana. It"
      + " is actually a banana-shaped brick on the floor, painted"
      + " yellow!\n");
    add_item( ({ "yellow brick", "banana-shaped brick",
                 "banana brick", "banana shaped brick" }),
        "Wait, actually, no, this isn't a banana-shaped brick. It is"
      + " actually just part of something yellow on the floor. Some"
      + " sort of yellow symbol has been covered by some of the clutter."
      + " Moving the clutter aside, you see that it is actually a big"
      + " yellow circle painted on the ground.\n");
    add_item( ({ "circle", "yellow circle", "big circle",
                 "big yellow circle" }),
        "The yellow circle has a smiley face inside it.\n");
    add_item( ({ "smiley face", "smiley", "smile", "face" }),
        "Awww ... isn't that fun? Who'd have thunk?\n");
    add_cmd_item( ({ "smiley face", "smiley", "smile", "face" }),
                  ({ "push", "pull", "search" }),
        "You fuss with the face. After a while you give up and just"
      + " stare at it. It is still smiling at you.\n");
    add_cmd_item( ({ "banana" }),
                  ({ "get", "take", "lift", "steal" }),
        "You can't seem to get it. What's going on here?\n");
    add_cmd_item( ({ "face", "smiley face", "smile", "smiley" }),
                  ({ "get", "take", "lift", "steal" }),
        "No need! You can just <smile> yourself and the day is won!\n");

    add_dungeon_items();

    add_npc(NPC_DIR + "tough_runt", 3 + random(2), &->arm_me());

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest" }),
        "You boldly stroll directly into a wall. OOOF!\n");

    room_add_object(DOORS_DIR + "1_armour_e");

    remove_prop(DOOR_BLOCK_ROOM); /* don't want to create deathtraps */

    reset_room();
} /* create_dungeon_room */


/*
 * Function name:        reset_room
 * Description  :        add the armour rack and fill it if it is
 *                       empty
 */
public void
reset_room()
{
    string *arm_files = ({ ARM_DIR + "crude_shield",
                           ARM_DIR + "crude_leather",
                         });
    object  armour;
    int     num = 4;

    if (!objectp(Stand))
    {
        Stand = clone_object(OBJ_DIR + "armour_rack");
        Stand->move(this_object());
    }

    if (!sizeof(all_inventory(Stand)))
    {
        foreach(string arm_file: arm_files)
        {
            num += random(4);

            while(num)
            {
                armour = clone_object(arm_file);
                armour->move(Stand);
                num--;
            }

            num = 4;
        }

        tell_room(this_object(),
            "An ugly gang of orcs crash suddenly into the room, dump"
          + " their armours into the armour stand, and leave, just as"
          + " quickly as they came. You hear a few shouts of, \"Quick!"
          + " If get to kitchen fast, maybe extra worm stew!\"\n");
    }
} /* reset_room */
