/*
 * /d/Gondor/mordor/ungol/stairs/std_straight.c
 *
 * This file is the default file for the Straight Stair leading to Torech
 * Ungol, Shelobs lair. It defines several functions that are very handy,
 * allowing me to keep the actual room files to the absolute minimum.
 *
 * Currently, if you fall you don't drag anyone else with you, but that
 * might be changed later. I fancy such a feature. The same goes for the
 * objects that might drop down the stairs.
 *
 * /Mercade, 21 November 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/common/room";

#include <filter_funs.h>
#include <language.h>
#include "/d/Gondor/defs.h"
#include "stairs.h"

/*
 * Function name: init
 * Description  : This function is used to add the command 'climb' to the
 *                player. Also add the commands 'up' and 'down' for I don't
 *                want to mess with the noshow_obvious stuff.
 */
void
init()
{
    ::init();

    add_action("do_climb", "climb");
    add_action("do_down",  "down");
    add_action("do_up",    "up");
}

/*
 * Function name: add_walls
 * Description  : This function add description of the walls on either side
 *                of the path on the Straight Stair.
 */
void
add_walls()
{
    string str;

    switch(random(4))
    {
    case 0:
	str = "The walls on either side of the stairs make you feel a " +
	    "little secure for they give you some hold.";
	break;
    case 1:
	str = "Ever as the stair cuts its way deeper into the sheer " +
	    "mountain the rocky walls rise higher and higher above your " +
	    "head.";
	break;
    case 2:
	str = "The walls on either side of the stairs are very steep. There " +
	    "is no way to climb them. The stair is the only way to get up " +
	    "to whichever perils may lay beyond it.";
	break;
    case 3:
    default:
	str = "The walls these stair is cut out of is rather smooth. " +
	    "However there are some ruggednesses that give you some hold " +
	    "in your struggle with the stairs.";
	add_item( ({ "ruggedness", "ruggednesses", "bulge", "bulges" }),
	    BSN("There are several bugles or ledges that an experienced " +
	    "climber might use to get some hold other than on the stairs " +
	    "themselves."));
    }

    add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	BSN(str));
}

/*
 * Function name: add_mountain
 * Description  : This function adds some add_items to this room.
 */
void
add_mountain()
{
    string str;

    add_item( ({ "rocky mountains" }),
	BSN("Aren't they somewhere else?"));

    switch(random(4))
    {
    case 0:
	str = "The mountain the stair is hewn out of is a part of the " +
	    "Mountains of Shadow, also known as Ephel Duath.";
	break;
    case 1:
	str = "The mountain rises high over your head. Inside this cleft " +
	    "all you can see is dark rock.";
	break;
    case 2:
	str = "You are deep inside the Mountains of Shadow, Ephel Duath. " +
	    "The stairs lead up into the mountains, in the direction of the " +
	    "Nameless Land.";
	break;
    case 3:
    default:
	str = "You are inside a narrow chasm in the Mountains of Shadow, " +
	    "Ephel Duath.";
    }

    add_item( ({ "mountain", "rocky mountain" }),
	BSN(str));

    switch(random(4))
    {
    case 0:
	str = "The solid rock walls are smooth and steep. There are " +
	    "some small rocks, or rather fragments or stone, on the steps.";
	break;
    case 1:
	str = "You are standing on solid rock... In fact you are surrounded " +
	    "by stone walls and the cleft is so small you cannot see " +
	    "entrance nor exit.";
	break;
    case 2:
	str = "Little rocks are on the stone steps. They make the steps " +
	    "less smooth than they actually are, but when you climb you are " +
	    "likely to kick them down maybe hurting those that are down.";
	break;
    case 3:
    default:
	str = "The rocky steps look strong, yet they are worn and some are " +
	    "broken.";
    }

    add_item( ({ "rock", "rocks", "stone", "stones" }),
	BSN(str));
}

/*
 * Function name: add_stair
 * Description  : This function adds the add_items on the stair to the room.
 */
void
add_stair()
{
    string str;

    switch(random(4))
    {
    case 0:
	str = "The stairway is almost at steep as a ladder. It is hewn out " +
	    "of the rocky mountain, leading up, deep into the mountain.";
	break;
    case 1:
	str = "The stair consists of numerous steps. There is no way to " +
	    "tell when this stair will come to an end.";
	break;
    case 2:
	str = "On one side, the stair goes up high into the mountain and on " +
	    "the other side it is a long way down. Better make sure you do " +
	    "not fall.";
	break;
    case 3:
    default:
	str = "Steps. Lots of steps, hewn out of the rocky mountain. That " +
	    "is all there is to this stair.";
    }

    add_item( ({ "stair", "stairs", "stairway", "straight stair" }),
	BSN(str));

    switch(random(4))
    {
    case 0:
	str = "The steps are narrow and unevenly spaced. They are hewn out " +
	    "of this rocky mountain.";
	break;
    case 1:
	str = "Many of the steps are treacherous. They are worn and smooth " +
	    "at the edges; some are broken and some may crack as you set " +
	    "foot upon them.";
	break;
    case 2:
	str = "The steps look dangerous. One slip might be fatal since the " +
	    "foot of the stairs may be a long way down. Better be careful.";
	break;
    case 3:
    default:
	str = "The narrow and unevenly spaced steps are smooth at the " +
	    "edges, which make it hard to climb them.";
    }

    add_item( ({ "step", "steps"}),
	BSN(str));
}

/*
 * Function name: set_long_description
 * Description  : This function sets the long description of this room. It
 *                will add a possible extra long description. It will also
 *                create a little random in the description.
 * Arguments    : extra_long - the extra text to add to the long description.
 */
void
set_long_description(string extra_long)
{
    string str;

    switch(random(4))
    {
    case 0:
	str = "You are somewhere on the Straight Stair in the Mountains of " +
	    "Shadow, Ephel Duath. The stairs lead up and down and there " +
	    "are steep walls on either side of the stairs.";
	break;
    case 1:
	str = "These are the Straight Stair, leading up into the Mountains " +
	    "of Shadow, Ephel Duath. You are somewhere between heaven and " +
	    "earth on the steep stairs, flanked by two even steeper walls. " +
	    "The stairs lead up and down.";
	break;
    case 2:
	str = "Looking around, you see only two things: narrow stairs and " +
	    "steep walls. You are on the Straight Stair that lead deep into " +
	    "the Mountains of Shadow, Ephel Duath. You can climb up or down " +
	    "the stairs.";
	break;
    case 3:
    default:
	str = "You are on the Straight Stair deep in the Mountains of " +
	    "Shadow, Ephel Duath. Are you halfway? You cannot tell. Looking " +
	    "up and down you see only steps. On either side of the stair " +
	    "is a steep wall and there is nothing else to see.";
    }

    set_long(BSN(str + (strlen(extra_long) ? (" " + extra_long) : "")));
}

/*
 * Function name: set_short_description
 * Description  : This function sets the short description of the room to a
 *                randomized room description.
 */
void
set_short_description()
{
    string str;

    switch(random(5))
    {
    case 0:
	str = "Somewhere on the Straight Stair";
	break;
    case 1:
	str = "On the Straight Stair in the Mountains of Shadow";
	break;
    case 2:
	str = "In a cleft in the Mountains of Shadow on the Straight Stair";
	break;
    case 3:
	str = "The Straight Stair, somewhere in Ephel Duath";
	break;
    case 4:
    default:
	str = "On a narrow step on the Straight Stair";
    }

    set_short(str);
}

/*
 * Function name: make_the_room
 * Description  : This function will set up the room, setting the long
 *                description and adding several nice add_items.
 * Arguments    : extra_long - the text to add to the long desctiption.
 */
varargs void
make_the_room(string extra_long = "")
{
    set_short_description();
    set_long_description(extra_long);

    add_walls();
    add_stair();
    add_mountain();

    add_prop(ROOM_I_NO_ME_SUN, 1);
    add_prop(OBJ_S_WIZINFO,
	BSN("You are on the Straight Stair. The first stairs on the " +
	"journey to Torech Ungol, Shelobs lair. A player that tries to " +
	"climb this stair might just find himself lying hurt or even dead " +
	"at the foot and those that survive will have to climb the Winding " +
	"Stairs before they enter the lair and face Shelob... /Mercade"));
}

/*
 * Function name: do_up
 * Description  : This function is used to determine whether the player can
 *                climb up or maybe fall down.
 * Arguments    : string str - the command line argument.
 * Returns      : 1/0
 */
int
do_up(string str)
{
    object tp = TP;
    int    fatigue;

    if (strlen(str))
    {
	NFN0("Up what?");
    }

    if (!STRAIGHT_PLAYER_FAIL_UP(tp))
    {
	fatigue = STRAIGHT_STAIR_FATIGUE_UP(tp);
	if (tp->query_fatigue() < fatigue)
	{
	    write("You are too tired to climb up.\n");
	    return 1;
	}

	tp->add_fatigue(-fatigue);
	tp->move_living("climbing up the stair", TO->query_room_up());

	return 1;
    }

LOG(LOG_NAME(tp) + " up  climb " + tp->query_skill(SS_CLIMB) + ".");

    LSAY("When " + PRONOUN(tp) + " tries to climb higher on the Straight " + 
	"Stair the step cracks as ", " sets foot on it and " + PRONOUN(tp) +
	" falls down the stair. You fear for " + POSSESSIVE(tp) + " life.");
    write(BSN("Trying to climb higher on the Straight Stair the step cracks " +
	"as you set foot on it and you fall down the stair. You fear for " +
	"your life."));

    /* As Olorin pointed out correctly, it is not possible to fall down
     * when you are already down, so we make this check.
     */
    if (!(TO->no_fall_down()))
    {
	tp->add_prop(STAIRS_I_I_AM_FALLING_DOWN, 1);
	/* Intended not to use move_living.. */
	tp->move(TO->query_room_down());
    }

    return 1;
}

/*
 * Function name: do_down
 * Description  : This function is used to determine whether the player
 *                can climb down or maybe fall down.
 * Arguments    : string str - the command line argument.
 * Returns      : 1/0
 */
int
do_down(string str)
{
    object tp = TP;
    int    fatigue;

    if (strlen(str))
    {
	NFN0("Down what?");
    }

    if (!STRAIGHT_PLAYER_FAIL_DOWN(tp))
    {
	fatigue = STRAIGHT_STAIR_FATIGUE_DOWN(tp);
	if (tp->query_fatigue() < fatigue)
	{
	    write("You are too tired to climb down.\n");
	    return 1;
	}

	tp->add_fatigue(-fatigue);
	tp->move_living("climbing down the stair", TO->query_room_down());

	return 1;
    }

LOG(LOG_NAME(tp) + " down climb " + tp->query_skill(SS_CLIMB) + ".");

    LSAY("When " + POSSESSIVE(tp) + " tries to climb down on the Straight " +
	"Stairs the step cracks as ", " sets foot on it and " + PRONOUN(tp) +
	" falls down the stair. You fear for " + POSSESSIVE(tp) + " life.");
    write("Trying to climb down on the Straight Stair the step cracks as " +
	"you set foot on it and you fall down the stair. You fear for your " +
	"life.");

    tp->add_prop(STAIRS_I_I_AM_FALLING_DOWN, 1);
    /* move_living not used intentionally */
    tp->move(TO->query_room_down());

    return 1;
}

/*
 * Function name: do_climb
 * Description  : This function is called when the player desides to 'climb'
 *                something rather than useing the directions 'up' and 'down'.
 * Arguments    : str - whatever (s)he wants to climb.
 * Returns      : 1/0 (succes/fail)
 */
int
do_climb(string str)
{
    object tp = TP;

    if (!strlen(str))
    {
	NFN0(CAP(QVB) + " what?");
    }

    if (parse_command(str, ({ }), " [the] [rocky] 'mountain' / " +
	"'mountains' / 'wall' / 'walls' "))
    {
	NFN0("It would be foolish to try to climb the walls on either side " +
	    "of the stair.");
    }

    if ((parse_command(str, ({ }), " 'down' [the] [straight] 'stair' / " +
	" 'stairs' / 'step' / 'steps' ")) ||
	(str == "down"))
    {
	/* Call_other to allow redefinition in an inheriting file. */
	return (TO->do_down(""));
    }

    if ((parse_command(str, ({ }), " [up] [the] [straight] 'stair' / " +
	"'stairs' / 'step' / 'steps' ")) ||
	(str == "up"))
    {
	/* Call_other to allow redefinition in an inheriting file. */
	return (TO->do_up(""));
    }

    NFN0("What exactly do you want to climb?");
}

/*
 * Function name: tell_player_that_he_continues_to_fall
 * Description  : This function tells the player that he continues to fall
 *                down and set his falling property higher.
 * Arguments    : obj  - the player that falls.
 *                prop - the number of times (s)he fell
 */
void
tell_player_that_he_continues_to_fall(object obj, int prop)
{
    string str;

    if (prop == 1)
    {
	str = "You continue to fall down the Stair....";
    }
    else
    { 
        switch(random(3))
        {
        case 0:
	    str = ".... and fall .... and fall ....";
	    break;
        case 1:
	    str = ".... wondering when you hit the ground ....";
	    break;
        case 2:
        default:
	    str = ".... hurting yourself on the stairs ....";
        }
    }
    obj->catch_msg(BSN(str));
}

/*
 * Function name: move_object_down
 * Description  : We do not want the object to go down all the way in
 *                one beat and therefore we use a little alarm.
 * Arguments    : obj - the object falling.
 */
void
move_object_down(object obj)
{
    if ((!objectp(obj)) || (!present(obj)))
    {
	return;
    }

    obj->move(TO->query_room_down());
}

/*
 * Function name: continue_to_fall_down
 * Description  : Something that came into this room falling will continue
 *                to fall down.
 * Arguments    : obj - the object falling.
 */
void
continue_to_fall_down(object obj)
{
    object *players;
    int    prop = obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN);

    if (living(obj))
    {
	tell_player_that_he_continues_to_fall(obj, prop);
    }

    players = all_inventory(TO);
    players = filter(players, "not_falling", TO);
    players = FILTER_PLAYERS(players);
    players -= ({ obj });

    if (living(obj))
    {
	players->catch_msg(BSN("You hear a scream and someone falls down " +
	    "the stairs. This all happens so fast that you cannot see who " +
	    "the poor soul is."));

	players->add_panic(STAIRS_SEE_FALL_ADD_PANIC_LIVING);
    }
    else
    {
	players->catch_msg(BSN("You hear some rumbling and something falls " +
	    "down the stairs. You cannot see exactly what it is though."));

	players->add_panic(STAIRS_SEE_FALL_ADD_PANIC_SOMETHING);
    }

    obj->add_prop(STAIRS_I_I_AM_FALLING_DOWN, (prop + 1));
    set_alarm(0.5, 0.0, "move_object_down", obj);
}

/*
 * Function name: object_falls_down
 * Description  : If an object is dropped in this room and it will fall down,
 *                this is the function that takes care of it.
 * Arguments    : obj  - the object to fall down
 *                from - the the source of the object
 */
void
object_falls_down(object obj, object from)
{
    if (living(from))
    {
	TELL_ROOM(TO, from, " is not careful enough and " +
	    LANG_THESHORT(obj) + " falls down the stairs for it does not " +
	    "remain in balance on the small steps.", from);
    }
    else
    {
	tell_room(TO, BSN(CAP(LANG_THESHORT(obj)) + " falls down the stairs " +
	    "as it does not remain in balance on the small steps."));
    }

    /* As Olorin pointed out correctly, it is not possible to fall down
     * when you are already down, so we make this check.
     */
    if (!(TO->no_fall_down()))
    {
	obj->add_prop(STAIRS_I_I_AM_FALLING_DOWN, 1);
	obj->move(TO->query_room_down());
    }
}

/*
 * Function name: enter_inv
 * Description  : If an object enters the room, several things can happen. If
 *                it is something that came falling from above, it will
 *                continue to fall down. If it is a living, (s)he may kick
 *                something down. If you drop something, it may either fall
 *                down or stay at the stairs or fall down.
 * Arguments    : obj  - the entering object
 *                from - the object 'obj' came from
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    /* If objects don't fall down from this room, there is no reason
     * to continue.
     */
    if (TO->no_fall_down())
    {
	return;
    }

    /* If it entered falling, let it continue falling. */
    if (obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN))
    {
	continue_to_fall_down(obj);
	return;
    }

    /* If it is a living, (s)he climbed up or down to this room. */
    if (living(obj))
    {
        START_QUEST(TP, "MORGUL ENTRY");
	return;
    }

    /* If someone drops something, it may fall down too. */
    if (STRAIGHT_STAIR_OBJECT_FALLS_DOWN(obj, from))
    {
	object_falls_down(obj, from);
	return;
    }
}

/*
 * Function name: not_falling
 * Description  : This filter checks all players that are not falling.
 * Arguments    : object obj - the object to check
 * Returns      : int - 1 if not falling, else 0.
 */
int
not_falling(object obj)
{
    return !(obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN));
}
