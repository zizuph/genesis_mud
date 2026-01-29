/*
 * File         : /d/Genesis/start/hobbit/npc/guardian.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 11/29/1998
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village is patrolled by grim guardians which are aware of the
 *        grim dangers that Dorm the evil wizard might have in mind for
 *        the village. They will stroll around in the city and help
 *        attacked newbie hobbits when encountered
 * 
 * TODO         :
 *      - add assist of newbies under attack.
 *      - add navigation features

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
void move_it();

/* global variables */
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
    
    set_race_name("hobbit");
    
    set_gender(G_MALE);
    set_long(
      "This grim village guardian strolls around in the village to keep " +
      "it the peacefull place it is. Somehow the guardian seems be " +
      "experienced with the opposit.\n");
    add_prop(CONT_I_HEIGHT, 110);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    set_stats(({70, 110, 90, 45, 45, 110}));
    set_hp(query_max_hp());
    add_act("@@move_it@@");
    set_act_time(1);
    PosX = 4;
    PosY = 3;
    MaxX = 6;
    MaxY = 5;
    
    
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
    command("nod ackn " + name);
}

/*
 * Function name: check_exit
 * Description  : checks weather a certain exit is ok to use
 * Arguments    : the name of the exit
 */
int
check_exit(string str)
{
    int err;
    int valid_direction;
    
    switch(str) // check east - west movement
    {
        case "east":
        case "northeast":
        case "southeast":
        {
            valid_direction = 1;
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
            valid_direction = 1;
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
            valid_direction = 1;
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
            valid_direction = 1;
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
    return (err == 0) && (valid_direction == 1);
}

/*
 * Function name: move_it
 * Description  : makes the NPC move in a random direction
 * Arguments    : none
 */
void
move_it()
{
    int     number_of_exits;
    string *exits;
    string  exit;
    string  room;
    exits = environment()->query_obvious_exits();
    number_of_exits = sizeof(exits);
    if (number_of_exits)
    {
        exit = exits[random(number_of_exits)];
        if (check_exit(exit))
        {
            command(exit);
        }
    }
    else
    {
        command("say I can't see any exits.");
    }
}

