/*
 *  /d/Emerald/blackwall/del_rimmon/lakeside/cliffs/outpost2a.c
 *
 *  This is the southern outpost which Formandil and his men established
 *  in their watch over Del Rimmon. This room served as a sleeping
 *  quarters and gathering place for the men stationed here.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/lakeside/east_overlook";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public int         lie_down(string arg);
public void        init();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("in a large chamber with rock walls on all sides");
    set_long("In a large chamber with rock walls on all sides."
      + " The room spreads out in a circular shape from the doorway"
      + " in its western wall, running perhaps thirty meters from"
      + " end to end. It may have once served as a sleeping chamber"
      + " of some kind, as there are many bedrolls lining the north"
      + " and south walls. To the east, a corridor leads further"
      + " inward.\n");

    add_item( ({ "chamber", "area", "room", "here", "large chamber" }),
        "This room is large and circular. It looks to have at one time"
      + " been used as a sleeping chamber. This must have been many"
      + " ages ago, however, as thick dust lies everywhere.\n");
    add_item( ({ "wall", "walls", "rock", "rock wall", "rock walls",
                 "wall of rock", "walls of rock" }),
        "The walls of this chamber are rounded somewhat, creating"
      + " a fairly circular perimeter. They have been hewn directly"
      + " from the stone of Melan Rath.\n");
    add_item( ({ "stone", "stone of melan rath" }),
        "The stone is dark and hard. Skilled hands must have worked"
      + " it, for there are few flaws in the smooth surfaces.\n");
    add_item( ({ "flaw", "flaws", "surface", "surfaces",
                 "smooth surface", "smooth surfaces" }),
        "Here and there you see the occasional evidence of a stroke"
      + " gone awry, but otherwise, the surface of the stone is"
      + " extremely smooth and even.\n");
    add_item( ({ "melan rath", "cliff", "cliffs", "peak" }),
        "Though you know you are within the peak of Melan Rath, it"
      + " is quite impossible to view from here.\n");
    add_item( ({ "shape", "circular shape", "shape of the chamber" }),
        "The shape of the chamber is roughly circular. The walls"
      + " curve slightly to form an even perimeter in all directions.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west" }),
        "A stone doorway is set in the wall to the west.\n");
    add_item( ({ "north wall", "northern wall", "north",
                 "wall to the north" }),
        "Bedrolls line the floor at the foot of the northern wall.\n");
    add_item( ({ "south wall", "southern wall", "south",
                 "wall to the south" }),
        "Bedrolls line the floor at the foot of the southern wall.\n");
    add_item( ({ "east wall", "eastern wall", "east",
                 "wall to the east" }),
        "A narrow corridor extends beyond the eastern wall.\n");
    add_item( ({ "sleeping chamber" }),
        "With the many bedrolls which line the northern and southern"
      + " walls, it would indeed stand to reason that this chamber"
      + " once housed sleeping men. That time, however, must have"
      + " been long ago. There is nothing but thick dust upon the"
      + " beds now.\n");
    add_item( ({ "dust", "thick dust", "layer of dust", "layer",
                 "thick layer of dust" }),
        "A thick layer of dust coats the floor and bedrolls of this"
      + " chamber. It looks as if things here have not been disturbed"
      + " for hundreds of years.\n");
    add_item( ({ "bed", "beds", "bedroll", "bedrolls" }),
        "The bedrolls are completely covered with a thick layer of"
      + " dust, and do not seem to have been used for hundreds of"
      + " years. They line the walls to the north and south leaving"
      + " an east-west aisle open from the doorway to the eastern"
      + " corridor.\n");
    add_item( ({ "door", "doorway", "doors" }),
        "A large stone slab rests in a doorway in the western wall."
      + " Upon its surface, an emblem of some kind has been carved.\n");
    add_item( ({ "slab", "stone slab", "surface", "surface of the door" }),
        "The surface of the door is smooth and free of dust. An emblem"
      + " of some kind is carved upon it.\n");
    add_item( ({ "corridor", "eastern corridor", "corridor to the east",
                 "narrow corridor" }),
        "A narrow corridor leads to the east, where it appears as if"
      + " there is a smaller chamber.\n");
    add_item( ({ "small chamber", "smaller chamber" }),
        "You cannot make out any clear details from this distance,"
      + " but the room is not dark.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is thickly covered with a layer of dust. Along"
      + " the walls to the north and south, bedrolls have been"
      + " placed.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling of the chamber is rather low, and has also been"
      + " hewn from the rock of the peak.\n");


    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost2b", "east");
    add_exit(DELRIMMON_DIR + "lakeside/east_overlook", "west",
             door_exit, 0, 1);

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southwest", "south", "southeast" }),
        "You are halted by the walls of the chamber.\n");

    reset_room();
} /* create_del_rimmon */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       outpost doors
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    string  txt = LOW(arg);

    if (txt == MANAGER->query_password(this_player()) ||
        txt == MANAGER->query_password(this_player()) + "." ||
        txt == MANAGER->query_password(this_player()) + "!")
    {
        if (this_player()->query_prop(TOUCH_PROP))
        {
            corporeal_flux(this_player());
            return 1;
        }

        write("You incant: "
          + CAP(MANAGER->query_password(this_player())) + "!\n"
          + "The stone door in the western wall pulses briefly"
          + " with a bright blue light.\n");
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* say_password */


/*
 * Function name:        corporeal_flux
 * Description  :        if not already in this state, the player is
 *                       rendered non-corporeal, allowing him to pass
 *                       through the stone doorway into the room
 *                       beyond.
 * Arguments    :        object player - the player object
 * Returns      :        1 - do it, 0 - already done, so don't do it
 */
public int
corporeal_flux(object player)
{
    if (player->query_prop(FLUX_PROP))
    {
        player->catch_tell("You are already in flux!\n");
        return 0;
    }

    player->add_prop(FLUX_PROP, 1);
    player->catch_tell(
        "You say: " + CAP(MANAGER->query_password(player)) + "!\n"
      + "The door pulses briefly with a bright blue light, which travels"
      + " up your arm and over your whole body. You no longer"
      + " feel your own weight upon the ground, and your hand moves forward"
      + " into the rock, disappearing beyond the surface of the door.\n");
    player->remove_prop(TOUCH_PROP);
    player->set_no_show_composite(1);
    player->set_invis(1);

    set_alarm(5.0, 0.0, &end_flux(player));

    return 1;
} /* corporeal_flux */


/*
 * Function name:        lie_down
 * Description  :        allow the player to lie down on the beds
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
lie_down(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[down] [on] [the] 'bed' / 'beds' / 'bedroll' / 'bedrolls'"))
    {
        return 0; /* we don't understand the syntax, so we pass it on */
    }

    write("You lie down for a moment on one of the nearest bedrolls,"
        + " and allow your mind to relax. Images float through your"
        + " mind of a time long past, and of many men coming to and"
        + " fro, called to various duties. The visions pass, and you"
        + " again rise to your feet.\n");

    return 1;
} /* lie_down */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(lie_down, "lie");
    add_action(lie_down, "lay");
    add_action(lie_down, "sleep");
    add_action(lie_down, "rest");
    add_action(lie_down, "relax");
} /* init */
