/*
 *  /d/Sparkle/guilds/new_merc/n_hallway.c
 *
 *  The hallway along the north side of the Merc Lodge, up on the second
 *  floor. This is just outside the library and the good aligned bunks.
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
    set_short("a corridor on the north side of the second floor");
    set_long("A corridor travels east from here toward a landing at"
      + " the top of some stairs. Many beautiful paintings have been"
      + " placed on the walls here, along with a few tokens of"
      + " affiliation. A long silver chain hangs near to the door"
      + " at the western end of the hall.\n\n");

    add_item( ({ "chain", "silver chain", "long chain",
                 "long silver chain" }),
        "It extends from a tiny hole in the ceiling just above the"
      + " western door.\n");
    add_item( ({ "hole", "tiny hole", "hole in the ceiling",
                 "tiny hole in the ceiling" }),
        "Wait ... did you see eyes peering at you up there??!\n");
    add_item( ({ "eyes", "up there" }),
        "Nah ... must have been your imagination.\n");
    add_item( ({ "corridor", "here", "hall", "hallway", "passage" }),
        "The passage seems to end here before the two doors.\n");
    add_item( ({ "second floor", "second level", "second story",
                 "second storie" }),
        "Yep ... we're up on the second floor here.\n");
    add_item( ({ "landing", "east" }),
        "A bit to the east, the corridor joins with a landing at the"
      + " top of the stairs.\n");
    add_item( ({ "stair", "stairs", "stairway", "stair" }),
        "The stairs are to the east. You'd need to head over there"
      + " to take a proper look.\n");
    add_item( ({ "downstairs", "first floor" }),
        "You can't see the first floor from here.\n");
    add_item( ({ "painting", "art", "artwork", "paintings",
                 "beautiful painting", "beautiful paintings",
                 "many beautiful paintings", "many paintings" }),
        "The artwork on display here shows various scenes which"
      + " depict gallant heroes vanquishing the forces of evil.\n");
    add_item( ({ "scene", "scenes", "various scenes" }),
        "The forces of evil seem to be losing very badly in this"
      + " scene. Perhaps it serves them right.\n");
    add_item( ({ "evil", "forces", "forces of evil", "evil forces" }),
        "It's the standard stuff ... dark-clad ... twisted"
      + " expressions of hatred ... cruel-looking weapons. Is it any"
      + " wonder the heroes feel the need to vanquish such foes?\n");
    add_item( ({ "stuff", "standard stuff" }),
        "A....yup.\n");
    add_item( ({ "hatred", "hate", "expression", "expressions",
                 "expression of hatred", "expressions of hatred",
                 "twisted expression", "twisted expressions",
                 "twisted expression of hatred",
                 "twisted expressions of hatred" }),
        "Yikes! If someone looked at you that way, you'd probably feel"
      + " like drawing your own sword!\n");
    add_item( ({ "weapon", "weapons", "cruel-looking weapon",
                 "cruel-looking weapons", "cruel weapon",
                 "cruel weapons", "cruel looking weapon",
                 "cruel looking weapons" }),
        "That is just the sort of thing evil people make. Its not"
      + " enough to simply kill your enemies, you have to make it all"
      + " messy and awful, too. Jerks.\n");
    add_item( ({ "jerk", "jerks" }),
        "Total jerks.\n");
    add_item( ({ "total jerk", "total jerks" }),
        "Yeah. You tell 'em!\n");
    add_item( ({ "foe", "foes", "such foes" }),
        "They clearly need vanquishing.\n");
    add_item( ({ "vanquishing" }),
        "I suppose its why they invented heroes.\n");
    add_item( ({ "hero", "heroes", "heros", "gallant hero",
                 "gallant heros", "gallant heroes" }),
        "Ahh ... inspiring stuff, this! Forces of evil, your time is"
      + " at hand!\n");
    add_item( ({ "token", "tokens", "token of affiliation",
                 "tokens of affiliation", "affiliation" }),
        "Displayed on the walls here are items representing many of"
      + " the guilds in the game who uphold the causes of justice and"
      + " righteousness. You see a garb bearing the colours of Caliana,"
      + " a tabard of Solamnia, a Neidar axe, a star-shaped brooch,"
      + " and a hoopak.\n");
    add_item( ({ "garb", "colors of caliana", "colours of caliana",
                 "garb bearing the colors of caliana",
                 "garb bearing the colours of caliana", "crest",
                 "crest of the knighthood" }),
        "The Calian Warriors wear such things as this.\n");
    add_item( ({ "tabard", "tabard of solamnia", "solamnian tabard" }),
        "Ahh ... the crest of the Knighthood. Any right-hearted person"
      + " is always glad to see such things.\n");
    add_item( ({ "axe", "neidar axe" }),
        "It is rare to see a weapon of the Neidar Clan"
      + " on display outside of their own halls, and yet here one rests.\n");
    add_item( ({ "brooch", "star-shaped brooch", "star shaped brooch",
                 "ranger brooch" }),
        "The brooch is very beautiful, indeed. Who might have given"
      + " such an item to be displayed here?\n");
    add_item( ({ "hoopak", "kender item" }),
        "Hmmmm ... a Kender item. I suppose they can be helpful in"
      + " the face of enemies of evil intent ... but it's always risky"
      + " to have them around if you value your possessions!\n");

    add_tell("A fair-looking Mercenary steps into the hallway from"
      + " the room to the west, nods politely at you, and proceeds"
      + " east and down the stairs.\n");
    add_tell("From the door to the west you hear: Sleep well, my"
      + " friend. Our efforts today were not in vain.\n");
    add_tell("Quiet voices are barely audible coming from the"
      + " room to the south.\n");
    add_tell("You hear some loud footsteps from downstairs.\n");
    add_item( ({ "west wall", "west", "western wall",
                 "wall to the west" }),
        "A polished door is set into the wall to the west.\n");
    add_item( ({ "south wall", "southern wall", "south",
                 "wall to the south" }),
        "A pine door is set into the wall to the south.\n");
    add_item( ({ "north", "north wall", "wall to the north",
                 "northern wall" }),
        "It is covered with paintings.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("n_landing", "east");

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest" }),
        "You poke around the corner of the hallway, but don't find"
      + " any way to move in that direction.\n");
    set_no_exit_msg( ({ "north" }),
        "There is a wall there.\n");

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "n_library_n");
    room_add_object(DOORS_DIR + "good_e");
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
                     + "Hmmm ... someone must be out in the hall ringing"
                     + " the bell.\n";
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [long] [silver] 'chain' / 'bell'"))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    write("You give the long silver chain a tug, and hear a faint bell"
      + " sounding from the room to the west.\n");
    say(QCTNAME(this_player()) + " tugs on the long silver chain, causing"
      + " a bell to ring in the room to the west.\n", this_player());

    tell_room(ROOM_DIR + "good_start", bell_msg);
    tell_room(ROOM_DIR + "good_rack", bell_msg);

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
