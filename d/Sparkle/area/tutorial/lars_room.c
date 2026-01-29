/*
 *  /d/Sparkle/area/tutorial/lars_room.c
 *
 *  This is the room players go immediately following character creation
 *  the first time they play the game.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "defs.h"
#include "/d/Genesis/start/newbie/newbie.h"
inherit "/std/room";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <files.h>


/* prototypes */
public void        create_room();
public int         validate_player(object who);
public void        first_message(object who);
public void        second_message(object who);
public void        third_message(object who);
public void        fourth_message(object who);
public void        fifth_message(object who);
public void        sixth_message(object who);
public void        map_message(object who);
public void        seventh_message(object who);
public void        eighth_message(object who);
public void        ninth_message(object who);
public void        transfer(object who);
public void        enter_inv(object ob, object from);


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    add_name("lars_room");
    set_short("your eyes are having trouble focusing yet. You try to"
      + " blink a few times, as odd sensations wash over you");
    set_long(capitalize(short()) + ".\n");

    add_item( ({ "lars" }),
        "Before you stands Lars the Implementor, Creator of the Lands"
      + " of Genesis. You find his presence oddly comforting, and yet"
      + " aren't sure how to interpret the odd look he is giving"
      + " you right now.\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);
} /* create_room */

public int
validate_player(object who)
{
    if (!who || !IS_PLAYER_OBJECT(who))
    {
        return 0;
    }
    
    if (environment(who) != this_object())
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function name:        first_message
 * Description  :        first message for the player
 * Arguments    :        object who - the player
 */
public void
first_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("\nLars arrives through a rift in the fabric of"
      + " space.\n\n");
    set_alarm(4.0, 0.0, &second_message(who));

    return;
} /* first_message */


/*
 * Function name:        second_message
 * Description  :        second message for the  player
 * Arguments    :        object who - the player
 */
public void
second_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("Lars smiles at you.\n\n");
    set_alarm(2.0, 0.0, &third_message(who));

    return;
} /* second_message */


/*
 * Function name:        third_message
 * Description  :        third message for the  player
 * Arguments    :        object who - the player
 */
public void
third_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("Lars says: Ah ... Welcome to Genesis, traveller. I"
      + " am very glad you have come. These lands are filled with many"
      + " like you. Even so, I am unsure as to what your destiny in"
      + " these realms shall be. Your fate is shielded from my eyes.\n\n");
    set_alarm(7.0, 0.0, &fourth_message(who));

    return;
} /* third_message */


/*
 * Function name:        fourth_message
 * Description  :        fourth message for the player
 * Arguments    :        object who - the player
 */
public void
fourth_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("Lars ponders the situation.\n\n");
    set_alarm(4.0, 0.0, &fifth_message(who));

    return;
} /* fourth_message */


/*
 * Function name:        fifth_message
 * Description  :        fifth message for the player
 * Arguments    :        object who - the player
 */
public void
fifth_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("Lars says: Hmmm ... yes ... yes ... You are"
      + " still young, and perhaps have many questions. I will send you"
      + " to Silverdell on Tutori Isle. There, you will have a chance to"
      + " begin your quest for identity and learn the ways of this"
      + " world. Here, take these, they will aid you.\n\n");
    set_alarm(7.0, 0.0, &sixth_message(who));

    return;
} /* fifth_message */


/*
 * Function name:        sixth_message
 * Description  :        sixth message for the player
 * Arguments    :        object who - the player
 */
public void
sixth_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    if(!present("_tutorial_journal", who))
    {
        clone_object(OBJ_DIR + "journal")->move(who, 1);
        who->catch_tell("Lars gives you a tutorial journal.\n\n");
    }
    else
    {
        who->catch_tell("Lars says: Oh, I see you already have a"
          + " Tutorial Journal. Excellent.\n\n");
    }

    set_alarm(1.0, 0.0, &map_message(who));

    return;
} /* sixth_message */


/*
 * Function name:        map_message
 * Description  :        map message for the player
 * Arguments    :        object who - the player
 */
public void
map_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    if(!present("_sparkle_magic_map", who))
    {
        clone_object("/d/Sparkle/std/obj/magic_map")->move(who, 1);
        who->catch_tell("Lars gives you a magic map.\n\n");
    }
    else
    {
        who->catch_tell("Lars says: Oh, I see you already have a"
          + " magic map. Excellent.\n\n");
    }

    set_alarm(1.0, 0.0, &seventh_message(who));

    return;
} /* map_message */


/*
 * Function name:        seventh_message
 * Description  :        seventh message for the player
 * Arguments    :        object who - the player
 */
public void
seventh_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    if(!present(PIN_UNIQUE_ID, who))
    {
        clone_object(NEWBIE_PIN)->move(who, 1);
        who->catch_tell("Lars gives you a newbie pin.\n\n");
    }
    else
    {
        who->catch_tell("Lars says: Oh, I see you already have a"
          + " newbie pin. Excellent!\n\n");
    }

    set_alarm(4.0, 0.0, &eighth_message(who));

    return;
} /* seventh_message */

/*
 * Function name:        eighth_message
 * Description  :        eighth message for the player
 * Arguments    :        object who - the player
 */
public void
eighth_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    MONEY_ADD(who, 220);
    who->catch_tell("Lars says: We will meet again, my friend.\n\n");
    set_alarm(4.0, 0.0, &ninth_message(who));

    return;
} /* eighth_message */


/*
 * Function name:        ninth_message
 * Description  :        ninth message for the player
 * Arguments    :        object who - the player
 */
public void
ninth_message(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->catch_tell("You feel yourself magically transferred.\n\n");
    set_alarm(0.0, 0.0, &transfer(who));

    return;
} /* ninth_message */


/*
 * Function name:        transfer
 * Description  :        move the player to the new room
 * Arguments    :        object who - the player
 */
public void
transfer(object who)
{
    if (!validate_player(who))
    {
        return;
    }
    
    who->move_living("M", TOWN_DIR + "hilltop");
    who->set_default_start_location(file_name(environment(who)));
    tell_room(environment(who), QCTNAME(who) + " arrives in a flash of"
      + " shimmering light.\n", who);
    return;
} /* transfer */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!IS_PLAYER_OBJECT(ob))
    {
        return;
    }
    
    set_alarm(2.0, 0.0, &first_message(ob));
    return;
} /* enter_inv */
