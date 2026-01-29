/*
 *  /d/Sparkle/area/orc_temple/rooms/3_pit.c
 *
 *  One of the rooms in the dungeons beneath the orc temple. This room is
 *  on level 3. Here, the High Priest conducts his terrible rituals to
 *  feed the Arch Demon.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <stdproperties.h>
#include "../defs.h"

inherit ROOMS_DIR + "pentagram_room";


/* Prototypes */
public void         create_pentagram_room();
public int          enter_pit(string arg);
public void         init();


/*
 * Function name:        create_pentagram_room
 * Description  :        constructor for the room
 */
public void
create_pentagram_room()
{
    add_name("_demon_pit");
    set_alarm(0.0, 0.0, &set_short("at the center of a vast chamber"));
    set_alarm(0.0, 0.0, &set_long("Long chains extend from the ceiling here to dangle over"
      + " a small circular opening at the very center of this vast"
      + " chamber. Thousands of candles surround you, tracing the"
      + " form of a pentagram that fills the entire area. A gnawing"
      + " horror fills your mind the longer you stand here.\n\n"));

    add_item( ({ "manacle", "manacles", "set",
                 "set of manacles" }),
        "The manacles are made of black metal and are fastened to"
      + " the long chains that dangle from the ceiling.\n");
    add_item( ({ "black metal", "metal" }),
        "Hard. Strong. Able to keep an extremely unfortunate person"
      + " hanging in place over the pit.\n");
    add_item( ({ "unfortunate person", "extremely unfortunate person" }),
        "There isn't one now, it isn't hard to imagine.\n");
    add_item( ({ "link", "links", "chain", "chains",
                 "chain link", "chain links", "thick link",
                 "thick links", "thick chain", "thick chains",
                 "thick chain link", "thick chain links", "long chain",
                 "long chains" }),
        "Manacles are fixed to the end of each chain about four feet"
      + " above the rim of the circular pit.\n");
    add_item( ({ "opening", "circular opening", "small opening",
                 "small circular opening", "pit", }),
        "As you gaze at the pit, a strange whispering seems to flow"
      + " from all corners of the chamber, needling into your mind"
      + " with hoarse, rasping, choking syllables that you cannot"
      + " seem to understand. It is a thing of horror that is there!\n");
    add_item( ({ "whispering", "strange whispering",
                 "syllables", "choking syllables", "syllable" }),
        "Yog ... So ... Thoth ... \n");
    add_item( ({ "rim", "rim of the circular pit", "rip of the pit" }),
        "It is beneath that rim that one would NEVER wand to"
      + " descend.\n");
    add_item( ({ "gnawing horror", "horror" }),
        "The pit. It sees you. It knows you. It will have you! Arrgh!"
      + " You wrench your mind away from the thought.\n");
    add_item( ({ "thing of horror" }),
        "Your mind edges closer to the horror you sense, and you"
      + " feel your sanity melting from your mind like loose flesh"
      + " on a rancid corpse! Aiiiiigh!! You wrench your thoughts"
      + " away from the precipice.\n");

    add_delay_cmd_item(
        ({ "opening", "circular opening", "small opening",
           "small circular opening", "pit", }),
        "search",
        "wrestling with the seeming insurmountable horror",
        10,
        "You begin working up the will to approach the pit.\n",
        &enter_pit("pit"));

    add_npc(NPC_DIR + "pit_priest", 5, &->arm_me());
    add_npc(NPC_DIR + "high_priest", 1, &->arm_me());

    add_exit("3_hall4", "northwest");
    add_exit("3_hall5", "north");
    add_exit("3_hall6", "northeast");
    add_exit("3_hall7", "east");
    add_exit("3_hall8", "southeast");
    add_exit("3_hall1", "south");
    add_exit("3_hall2", "southwest");
    add_exit("3_hall3", "west");

} /* create_pentagram_room */


/*
 * Function name:        enter_pit
 * Description  :        allow players to try to enter the pit
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
enter_pit(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [in] [into] [the] [small] [circular] 'opening'"
      + " / 'pit'"))
    {
        notify_fail("Where do you wish to " + query_verb() + "?\n");
        return 0;
    }

    write("The mere presence of that ghastly opening is chipping away"
      + " at what feels like the last fragmented remains of your"
      + " sanity as it is. Even fleeting thoughts of approaching it"
      + " send your mind reeling into spasms of horror that release"
      + " what feels like very real physical pain.\n");

    return 1;
} /* enter_pit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter_pit, "enter");
    add_action(enter_pit, "descend");
    add_action(enter_pit, "jump");
} /* init */