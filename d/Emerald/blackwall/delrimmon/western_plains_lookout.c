/*
 *  /d/Emerald/telberin/western_plains_lookout.c
 *
 *  This is the view given from the torque which has been placed
 *  upon the cliffs overlooking the Western Plains of Emerald.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <language.h>

/* prototypes */
public string        describe_area();
public void          create_emerald_room();
public void          reset_room();

/* global variables */
public int           Scene = random(4);


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room, using domain presets
 */
public void
create_emerald_room()
{
    set_short("a majestic vista overlooking the Western Plains"
      + " of Emerald");
    set_long(describe_area);

    setuid();
    seteuid(getuid());

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        describe_area
 * Description  :        shows us the players who are in Telberin.
 * Returns      :        string - a description of the above stated
 */
public string
describe_area()
{
    string  desc = "The Western Plains of Emerald lie beneath you in"
      + " a wide vista stretching to the edge of sight. The Blackwall"
      + " Mountains are visible to the north, running along the edge"
      + " of the plains. To the west, there are nothing but grasslands"
      + " for miles, dotted here and there with patches of trees. ";
    int     darklings = random(4) + 1;

    switch(Scene)
    {
        case 0:
            desc += "All is quiet on the plains at present.";
            break;
        case 1:
            desc += "You see a roving band of orc scouts making their"
                  + " way along the plain.";
            break;
        case 2:
            desc += "It appears as if a large group of ogres have"
                  + " set up camp on the plains.";
            break;
        case 3:
            desc += "Far in the distance, you spot what appear to"
                  + " be " + LANG_NUM2WORD(darklings) + " or "
                  + LANG_NUM2WORD(darklings + 1) + " darklings moving"
                  + " along the plain.";
            break;
        case 4:
            desc += "The plains are filled with orcs, all of them"
                  + " armed with ugly clubs and carrying blood soaked"
                  + " bags over their shoulders. A few darklings are"
                  + " with them, marching them slowly north toward"
                  + " the mountains.";
            break;
        case 5:
        default:
            desc += "A shadow streaks suddenly across the ground,"
                  + " followed by the hideous form of a great"
                  + " silvery dragon. Though you cannot hear anything,"
                  + " the hair on the back of your neck rises as"
                  + " you see it shriek, and speed away north to"
                  + " disappear against the shapes of the distant"
                  + " mountains.";
            break;
    }
    
    return desc + "\n";
} /* describe_area */


/*
 * Function name:        reset_room
 * Description  :        clone the torque and its pillar to the room
 */
public void
reset_room()
{
    object torque;

    if (!present("_plains_torque"))
    {
        torque = clone_object(
            "/d/Emerald/torque/unique_torques/plains_torque");
        torque->set_no_show(1);
        torque->move(this_object());
    }

    Scene = random(4); /* change this from time to time */
} /* reset_room */
