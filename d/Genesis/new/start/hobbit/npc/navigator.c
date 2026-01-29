/*
 * File         : /d/Genesis/start/hobbit/npc/navigator.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/29/1998
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This is an experimental NPC. It is intended to test new code used
 *        for tracking it's path and knowing its surroundings.
 * 
 * TODO         :
 *      - Test more code :)

 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

/* directives */
#pragma strict_types

/* inherits */
inherit "/std/monster";

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <ss_types.h> 

#include "../hobbit.h"

/* defines */

/* prototypes */
void create_monster();
string do_where();
string do_how();
void move_it();

/* global variables */
object   *Rooms = ({});
string   *Directions = ({});
int       Index;
int       PosX;
int       PosY;
int       MaxX;
int       MaxY;

/*
 * Function name: create_monster
 * Description  : set up the humanoid
 */
void
create_monster()
{
   if (!IS_CLONE)
      return;
    set_name("Tracker");
    set_race_name("gizmo");
    
    set_gender(G_NEUTER);
    set_long(
      "The gizmo looks confused but it might know more about this world " +
      "than you do. If you don't see a responsibel wizard around, " +
      "please kill it and mail seaweed.\n");
    add_prop(CONT_I_HEIGHT, 45);
    add_prop(CONT_I_WEIGHT, 5000);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    set_stats(({5, 5, 5, 5, 5, 5}));
    set_hp(query_max_hp());
    add_ask("where", do_where);
    add_ask("how", do_how);
    add_ask("move", move_it);
    add_act("@@move_it@@");
    set_act_time(1);
    PosX = 2;
    PosY = 2;
    MaxX = 3;
    MaxY = 4;
    
    
}

/*
 * Function name: add_introduced
 * Description  : Whenever someone is introduced to me (CC), this function
 *                is called in me to tell me that 'name' (BB) is being
 *                introduced to me. The living that does the introduction
 *                (AA) is available though this_player().
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
add_introduced(string name)
{
    command("emote turns his attention with a squeaking sound.");
    command("introduce me to " + name);
}

/*
 * Function name: do_where
 * Description  : makes the navigator tell where it is
 * Arguments    : none
 */
string
do_where()
{
    command("say I think we are here: " + file_name(environment(TO)));
    return "";
}

/*
 * Function name: do_how
 * Description  : makes the navigator tell how it got here
 * Arguments    : none
 */
string
do_how()
{
    int i;
    string *s;
    command("say I have walked " + Index + " rooms\n");
    if (Index)
    {
        command("say First I walked " + Directions[0]);
        command("say  and came to " + Rooms[0]);
        for (i = 1; i < Index; i++)
        {
            command("say Then I walked " + Directions[i]);
            command("say  and came to " + Rooms[i]);
        }
    }
    command("smile proudly");
    return "";
}

/*
 * Function name: check_exit
 * Description  : checks weather a certain is ok to use
 * Arguments    : the name of the exit
 */
int
check_exit(string str)
{
    int err;
    
    switch(str) // check east - west movement
    {
        case "east":
        case "northeast":
        case "southeast":
        {
            if (PosX >= MaxX)
            {
                err++;
            }
            else
            {
                PosX++;
            }
            break;
        }
        case "west":
        case "northwest":
        case "southwest":
        {
            if (PosX <= 1)
            {
                err++;
            }
            else
            {
                PosX--;
            }
            break;
        }
    }
    switch(str) // check north - south movement
    {
        case "north":
        case "northeast":
        case "northwest":
        {
            if (PosY >= MaxY)
            {
                err++;
            }
            else
            {
                PosY++;
            }
            break;
        }
        case "south":
        case "southeast":
        case "southwest":
        {
            if (PosY <= 1)
            {
                err++;
            }
            else
            {
                PosY--;
            }
            break;
        }
    }
    return (err == 0);
}

/*
 * Function name: move_it
 * Description  : makes the navigator move in a random direction
 * Arguments    : none
 */
void
move_it()
{
    int     number_of_exits;
    string *exits;
    string  exit;
    exits = environment()->query_obvious_exits();
    number_of_exits = sizeof(exits);
    if (number_of_exits)
    {
        command("say I can see " + number_of_exits + " exits.");
        exit = exits[random(number_of_exits)];
        if (check_exit(exit))
        {
            command("say I will go " + exit);
            command(exit);
            Directions += ({ }) + ({ exit });
            Rooms += ({ }) + ({ file_name(environment(TO)) });
            Index++;
            command("peer");
            command("shout I am here now!");
        }
        else
        {
            command("say Nahhh, " + exit + " is not a good exit for me.");
        }
    }
    else
    {
        command("say I can't see any exits.");
    }
}

