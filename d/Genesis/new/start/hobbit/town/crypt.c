/*
 * File         : /d/Genesis/start/hobbit/town/crypt.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/14/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village crypt is a selldom used facility. The inhabitants are
 *        very suspisous about religion and magics in general. They rather
 *        stick to their crop fields and trade. If they need advice or
 *        guidance for their souls they rather go to the pub. Still a
 *        crypt was dug into the ground as one of the first things when
 *        this settlement were fomed. Some inhabitants still trust in
 *        their gods but rather than gaining the wrath of powerful enemies
 *        (i.e. Dorm) they let it reside down here until they have grown
 *        stronger.
 * 
 * TODO         :
 *        Add FAQ book 
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";



/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <login.h>
#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();
int start(string str);
int pray(string str);
int rest(string str);

/* globals */


/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("the village crypt");
    set_long(
      "Darkness surrounds the small dusty altar by the wall which is " +
      "only lit by two candles. A large torch on the opposite wall " +
      "illuminates the exit and a few rows of wooden benches infront of " +
      "the altar. It sounds like there are faint voices comming from " +
      "nearby but this crypt seems to be the only room down here.\n");
    add_item("altar", 
      "The small dusty altar is made of blackened wood. \n");
    add_item(({ "bench", "benches", "wooden benches" }), 
      "The few wooden benches in the crypt seems almost unused. \n");
    add_item(({ "candle", "candles", "bee-wax candles" }), 
      "A pair of bee-wax candles spreads a sweet smell in the room. \n");
    add_item(({ "ceiling", "plank", "planks", "beam" }), 
      "The ceiling is made of wooden planks and is kept in place with " +
      "sturdy wooden beams. \n");
    add_item("floor", 
      "The floor is made of packed dirt. \n");
    add_item("smell", 
      "A cold moisty smell of dark underground mixed with the sweet " +
      "scent of bee-wax candles fills the room. \n");
    add_item("torch", 
      "The torch is lightening the back wall where the staircase " +
      "comes through the ceiling. \n");
    add_item(({ "voice", "voices" }), 
      "You think you hear an upset voice talking about reincarnation " +
      "or is it just an imagination? \n");
    add_item(({ "wall", "walls" }), 
      "Rectangular stones and packed dirt makes up the walls of the " +
      "crypt. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/14/99.\n");
    
    add_exit("villagehall.c", "up");
    
    
    
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    
}

void
init()
{
    add_action(start, "start");
    add_action(pray, "pray");
    add_action(pray, "regenerate");
    add_action(rest, "rest");
    ::init();
}

/*
 * Function name: start(string)
 * Description  :  Handle the start command
 *                 Originally from /d/Genesis/start/human/town/church.c
 * Arguments    : A string with the command arguments
 */
int
start(string str)
{
    if (str != "here")
    {
        notify_fail("Start where? Here?\n");
        return 0;
    }
    if (RACESTART[this_player()->query_race()] != MASTER)
    {
        notify_fail("This is not your racial starting location.\n");
        return 0;
    }
    if (this_player()->set_default_start_location(MASTER))
    {
        write("Next time you enter the game, you will start here.\n");
    }
    else
    {
        write("Somehow it is not possible for you to start " +
        "here. The room apparently has not been approved of by the " +
        "archwizards of Genesis. Please mail the archwizard of " +
        "player affairs ('mail aop') to get it allowed.\n");
    }
    return 1;
}

/*
 * Function name: pray(string)
 * Description  : Handle the pray command
 *                Originally from /d/Genesis/start/human/town/church.c
 * Arguments    : A string with the command arguments
 */
int
pray(string str)
{
    write("You kneel at the altar.\n"+
        "The chilly darkness makes it hard to focus your vision.\n"+
        "As your mind clears, you are overcome by a sensation of ease.\n");
    if (!TP->query_invis())
    {
        say( ({METNAME +" kneels at the stone.\n",
        ART_NONMETNAME +" kneels at the stone.\n"}) );
    }
    
    /*
    * First we see if the player has a ghost_player.c object.
    * If this is the fact, we'll make sure they've got a ghost
    * var set so the death mark will function, and then give
    * a new death mark to try to repeat the death sequence.
    */
    if (MASTER_OB(TP) == LOGIN_NEW_PLAYER)
    {
        /*
        * Player is a physical ghost. Make sure the ghost
        * var is 33 (GP_DEAD | GP_BODY) and send them to
        * the bodies room.
        */
        TP->set_ghost(GP_DEAD | GP_BODY);
        write("A brilliant light shines above you from out " +
            "of nowhere. You feel yourself drawn upwards " +
            "into the light, to another place.\n");
        say(QCTNAME(TP) + " suddenly looks upwards, as " +
            "a brilliant beam of white light descends through "+
            "the ceiling and falls upon " + TP->query_possessive() +
            " shoulders. Before you realize it, " + 
        TP->query_pronoun() + " has vanished.\n");       
        TP->move_living("M", "/d/Genesis/login/bodies", 1, 0);
        say(QCTNAME(TP) + " arrives in a flash of light.\n");
        return 1;
    }
    
    /*
    * Ok, the player isn't using a ghost_player.c object, but we
    * have to make sure it's not a normal player with a ghost
    * var set running around. That's an easy repair by just
    * removing the ghost variable.
    */
    else if (TP->query_ghost())
    {
        write("Suddenly you feel more solid.\n");
        say(QCTNAME(TP) + " suddenly shimmers into view in " +
            "a more solid form.\n");
        TP->set_ghost(0);
        return 1;
    }
    write("Nothing else happens.\n");
    return 1;
}

/*
 * Function name: rest(string)
 * Description  :  Handle the rest command
 *                 Originally from /d/Genesis/start/human/town/church.c
 * Arguments    : A string with the command arguments
 */
int
rest(string str)
{
    write("Ah, wasn't that nice.\n");
    return 1;
}


