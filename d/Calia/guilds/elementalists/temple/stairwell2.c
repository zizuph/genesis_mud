/*
 * Central Stairwell on the Elemental Worshipper floor
 * 
 * Created by Petros, March 2014
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
public int do_study(string args);
public void show_murals(object player, int counter);

// Global Variables
public int study_alarm = 0;

public void
create_temple_room()
{
    set_short("Second Floor Central Stairwell");
    set_long("Compared to the complex elegance of the main floor of the Elemental "
             + "Temple, you are quite surprised to find that this floor is "
             + "actually quite simple. The walls do not seem to be made of the "
             + "same grey rock material and there are no signs of the crystalline "
             + "veins that you have seen elsewhere in the Temple. You see rooms "
             + "that serve the Elemental Worshippers to the northeast, northwest, "
             + "southeast, and southwest.\n\n");

    try_item( ({ "walls", "wall" }),
              "The walls are made of wood panels, lacquered over with a glossy paint. "
              + "Painted upon them are beautiful murals that depict the Elementals "
              + "interacting with their creation.\n");
     
    try_item( ({ "paint", "glossy paint", "mural", "murals", "beautiful murals",
                    "elementals", "creation", "painting" }),
        "There are murals on every available surface of this stairwell. The "
        + "Elementals are shown in various states of action. You get the "
        + "sense that Calia's creation story can be learned by studying "
        + "these murals.\n");

    try_item( ({ "northeast", "practice room" }),
              "To the northeast, you spot what appears to be a practice room. Other "
              + "Elemental Worshippers are learning to control the elements.\n");

    try_item( ({ "northwest", "lounge" }),
              "To the northwest, you see a room with some couches and prayer mats. "
              + "It appears to be some sort of lounge.\n");

    try_item( ({ "southeast", "board room" }),
              "To the southeast, you see a large bulletin board. Some gnomes busy "
              + "themselves with posting and adjusting the notes on the board.\n");

    try_item( ({ "southwest", "storage chamber", "equipment room" }),
              "To the southwest, you see a number of equipment lying around. You "
              + "suspect that this is the storage chamber for the Elemental Worshippers.\n");
        
    try_item( ({ "staircase", "stairwell", "steps" }),
        "The black stairwell appears to have been grown rather than been "
      + "carved out of the inside of the pillar. Block wooden steps lead down to the "
      + "main floor of the Temple.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "middle2", "down"); 
    add_exit(ELEMENTALIST_TEMPLE + "ew_rack", "southwest", "@@cannot_enter_restrict_seekers_punished", 1, "@@cannot_see_restrict_seekers_punished");
    add_exit(ELEMENTALIST_TEMPLE + "ew_boardroom", "southeast", "@@cannot_enter_restrict_seekers", 1, "@@cannot_see_restrict_seekers");
    add_exit(ELEMENTALIST_TEMPLE + "ew_lounge", "northwest");
    add_exit(ELEMENTALIST_TEMPLE + "ew_practice", "northeast", "@@cannot_enter_worshipper_floor", 1, "@@cannot_see_worshipper_floor");
    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "up", "@@cannot_enter_cleric_floor", 1, "@@cannot_see_cleric_floor");
}

public void
init()
{
    ::init();
    
    add_action(do_study, "study");
}

public int
do_study(string args)
{
    if (!strlen(args)) 
    {
        notify_fail("Study what? The murals?\n");
        return 0;
    }

    args = lower_case(args);
    if (args != "murals" && args != "mural")
    {
        notify_fail("Study what? The murals?\n");
        return 0;
    }

    if (sizeof(get_alarm(study_alarm)))
    {
        notify_fail("You get the sense that you should wait a bit before "
                    + "trying to study these murals.\n");
        return 0;
    }

    show_murals(this_player(), 0);
    return 1;
}

public void
show_murals(object player, int counter)
{
    if (environment(player) != this_object())
    {
        return;
    }

    string message = "";
    switch (counter)
    {
    case 0:
        message = "As you begin to study the murals you feel images forming "
            + "within your mind...\n\n";
        break;

    case 1:
        message = "First .. Void....\n\n";
        break;
    
    case 2:
        message = "Then Quickening....\n\n";
        break;
    
    case 3:
        message = "A myriad of colours appears in your mind's vision. The colors are "
            + "so intricate and detailed that language itself cannot describe "
            + "them.\n\n";
        break;

    case 4:
        message = "A Spark of Light and Dark. A set of motion and the colours "
            + "twirl and twirl....\n\n";
        break;

    case 5:
        message = "To your right, a massive rock from the Core of Earth...\n\n";
        break;

    case 6:
        message = "Through Purifying Flame and Endless Depths of Water the "
            + "Rock takes shape.\n\n";
        break;

    case 7:
        message = "Primordial Winds move the Rock...\n\n";
        break;

    case 8:
        message = "Another Spark of massless light, dark and shadow. The "
            + "firstborn emerges...\n\n";
        break;
    case 9:
        message = "You step back and ponder what you just witnessed.\n";
        break;
    default:
        return;
    }

    player->catch_tell(message);
    study_alarm = set_alarm(3.5, 0.0, &show_murals(player, counter + 1));
}

