/*
 *  /d/Sparkle/guilds/new_merc/s_hallway.c
 *
 *  The hallway along the south side of the Merc Lodge, up on the second
 *  floor. This is just outside the library and the evil bunks.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public int         ring_bell(string arg);
public void        init();


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("a corridor on the south side of the second floor");
    set_long("A corridor travels east from here toward a landing at"
      + " the top of some stairs. Various trophies and other objects"
      + " are displayed on these walls. A long black chain hangs"
      + " near to the western door at the end of the hallway.\n\n");

    add_item( ({ "chain", "black chain", "long chain",
                 "long black chain" }),
        "It extends from a tiny slot in the ceiling just above the"
      + " western door.\n");
    add_item( ({ "slot", "tiny slot", "slot in the ceiling",
                 "tiny slot in the ceiling" }),
        "Wait... Did you see eyes peering at you up there??!\n");
    add_item( ({ "eyes", "up there" }),
        "They blink at you malevolently... Ugh!\n");
    add_item( ({ "corridor", "here", "hall", "hallway", "passage" }),
        "The passage seems to end here before the two doors.\n");
    add_item( ({ "second floor", "second level", "second story",
                 "second storie" }),
        "Yep... We're up on the second floor here.\n");
    add_item( ({ "landing", "east" }),
        "A bit to the east, the corridor joins with a landing at the"
      + " top of the stairs.\n");
    add_item( ({ "stair", "stairs", "stairway", "stair" }),
        "The stairs are to the east. You'd need to head over there"
      + " to take a proper look.\n");
    add_item( ({ "trophies", "trophy", "various trophies" }),
        "The walls here are covered with various displays. You see"
      + " a tattered garb bearing the Colours of Caliana, a stained"
      + " tabard of Solamnia, a partially burned dwarf beard,"
      + " a bent star-shaped brooch, and a bloodied belt of"
      + " pouches.\n");
    add_item( ({ "display", "displays", "various displays" }),
        "There is a definite theme at work here.\n");
    add_item( ({ "theme" }),
        "Any fool could see that this part of the lodge is not friendly"
      + " toward good aligned guilds.\n");
    add_item( ({ "fool", "any fool" }),
        "Seriously?\n");
    add_item( ({ "tattered garb", "garb", "colors", "colours",
                 "colors of caliana", "colours of caliana",
                 "garb bearing the colors of caliana",
                 "garb bearing the colours of caliana",
                 "tattered garb bearing the colors of caliana",
                 "tattered garb bearing the colours of caliana" }),
        "The garb looks like something a Calian Warrior might have"
      + " once worn proudly. It has a dreadful looking tear through"
      + " its midsection, and someone has written \"Ha Ha\" on the"
      + " collar.\n");
    add_item( ({ "collar", "ha", "ha ha" }),
        "The handwriting is pretty sloppy, possibly orcish.\n");
    add_item( ({ "handwriting", "writing", "hand writing" }),
        "Can orcs even spell? I suppose \"Ha Ha\" is within their"
      + " capabilities.\n");
    add_item( ({ "tabard", "tabard of solamnia", "solamnian tabard",
                 "stained tabard", "stained tabard of solamnia",
                 "stained solamnian tabard" }),
        "Upon closer inspection, the dark stains on this Solamnian"
      + " tabard are clearly dried blood.\n");
    add_item( ({ "stain", "dark stain", "stains", "dark stains",
                 "blood stain", "blood stains", "dried blood" }),
        "The dried blood on the tabard appears to have been spilled"
      + " from a neck wound suffered by the original wearer, as it"
      + " is cascading down the front of the garment.\n");
    add_item( ({ "garment" }),
        "The tabard is a garment, yes.\n");
    add_item( ({ "original wearer", "wearer" }),
        "Probably dead. Probably missing a head, too.\n");
    add_item( ({ "beard", "burned beard", "partially burned beard",
                 "dwarf beard", "burned dwarf beard",
                 "partially burned dwarf beard", }),
        "I suppose one could call this the dwarf version of being"
      + " scalped. It looks as if someone grabbed the poor dwarf, and"
      + " hacked off the beard from the living face of the owner. A"
      + " bit of the chin is still attached at the top of the beard,"
      + " though it has withered and dried over time.\n");
    add_item( ({ "chin", "bit of the chin" }),
        "Um.... Yuck.\n");
    add_item( ({ "brooch", "star shaped brooch", "star-shaped brooch",
                 "bent brooch", "bent star shaped brooch",
                 "bent star-shaped brooch" }),
        "Awww... Someone took a Ranger's brooch and twisted it all"
      + " up! Very troubling, or utterly hilarious? You decide.\n");
    add_item( ({ "ranger brooch", "rangers brooch", 
                 "ranger's brooch" }),
        "I bet they were really mad. Or.... Dead.\n");
    add_item( ({ "pouch", "pouches", "belt", "belt of pouches",
                 "bloodied belt", "bloodied belt of pouches" }),
        "Hmmm... This looks like one of those things Kenders always"
      + " seem to be wearing. Guess this one wasn't quick enough!\n");
    add_item( ({ "object", "objects", "other object", "other objects" }),
        "There are all sorts of things on display here. Only the"
      + " trophies seem to tell any specific story, but the general"
      + " idea is the same everywhere you look. Whoever put this stuff"
      + " on the walls is not a nice person.\n");
    add_item( ({ "things", "thing" }),
        "All sorts.\n");
    add_item( ({ "sort", "sorts", "all sorts" }),
        "Yep. Things.\n");
    add_item( ({ "all sorts of things" }),
        "Golly, look at 'em all.\n");
    add_item( ({ "em all", "'em all" }),
        "You're fun.\n");
    add_item( ({ "fun" }),
        "Okay, now you're scary.\n");
    add_item( ({ "scary" }),
        "And now you're bored.\n");
    add_item( ({ "bored" }),
        "And now we're BOTH bored.\n");
    add_item( ({ "both bored", "both" }),
        "Jerk.\n");
    add_item( ({ "jerk" }),
        "Loser.\n");
    add_item( ({ "loser" }),
        "I know you are but what am I?\n");
    add_item( ({ "story", "specific story" }),
        "The story goes something like this: I am mean and evil and like"
      + " to put things on the wall to prove it.\n");
    add_item( ({ "general idea", "idea" }),
        "Yeah... The story this stuff tells is pretty clear.\n");
    add_item( ({ "nice person", "nice people" }),
        "Nice people don't hang out in this hallway.\n");
    add_item( ({ "downstairs", "first floor" }),
        "You can't see the first floor from here.\n");
    add_item( ({ "good aligned guilds", "good aligned guild",
                 "guild", "guilds" }),
        "Well, just look at these trophies!\n");
    add_item( ({ "these walls" }),
        "They are covered with trophies and other objects.\n");

    add_tell("An extremely rough looking Mercenary arrives from the"
      + " stairs, enters the room to the west, and slams the door"
      + " behind him.\n");
    add_tell("You hear some muffled laughter from somewhere nearby.\n");
    add_tell("Your eyes happen to fall on one of the trophies on"
      + " the wall - it isn't a pretty sight.\n");
    add_tell("You hear some loud footsteps from downstairs.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("s_landing", "east");

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest" }),
        "You poke around the corner of the hallway, but don't find"
      + " any way to move in that direction.\n");
    set_no_exit_msg( ({ "south" }),
        "There is a wall there.\n");

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "s_library_s");
    room_add_object(DOORS_DIR + "evil_e");
} /* create_room */


/*
 * Function name:        ring_bell
 * Description  :        let the player try to ring the bell
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
ring_bell(string arg)
{
    string  bell_msg = "CLANNNNNG!! ... \n"
                     + "Hmmm... Someone must be out in the hall ringing"
                     + " the bell.\n";
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [long] [black] 'chain' / 'bell'"))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    write("You give the long black chain a tug, and hear a faint bell"
      + " sounding from the room to the west.\n");
    say(QCTNAME(this_player()) + " tugs on the long black chain, causing"
      + " a bell to ring in the room to the west.\n", this_player());

    tell_room(ROOM_DIR + "evil_start", bell_msg);
    tell_room(ROOM_DIR + "evil_rack", bell_msg);

    return 1;
} /* ring_bell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(ring_bell, "ring");
    add_action(ring_bell, "pull");
    add_action(ring_bell, "tug");
    add_action(ring_bell, "yank");
} /* init */

