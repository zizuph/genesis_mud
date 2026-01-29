/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 * 
 * Added to /d/Genesis/race/shapeshift/wohs_polymorph_self_*
 */

#pragma strict_types
#include "/d/Krynn/common/defs.h"
#include "../defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#define WOHS_DRAGON_DESTINATION "_wohs_dragon_destination_prop"

string
get_soul_id() 
{ 
    return "wohs polymorph self soul"; 
}

int 
query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */
      "dragonbreath"  : "do_ability",
      "fly"           : "dragon_fly",
      "fly2"          : "dragon_fly2",
      "fly3"          : "bird_fly",
      /* Emote name   : Function name */
      "beat"          : "dragon_wing",
      
    ]);
}

public mapping
query_ability_map()
{
    return ([
             "dragonbreath" : SOHM_SPELLS + "dragon_breath"
            ]);
}

public int
dragon_fly(string str)
{
    string arg, room;
    object env = environment(TP);
    string target_room_file = SOHM_SPELLS + "objs/wohs_dragon_flight_room";
    string *room_options;

    room_options = ({ "tower", "wayreth", "wayreth forest", "home", 
                      "tower of high sorcery" });

    if (TP->query_race_name() != "dragon")
    {
        notify_fail("What?\n");
        return 0;
    }

    if(env->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot fly while inside!\n");
        return 0;
    }

    if(env->query_prop(ROOM_UNDER_WATER))
    {
        notify_fail("You cannot fly while under water!\n");
        return 0;
    }

    if(env->query_prop(ROOM_IN_AIR))
    {
        notify_fail("You are already airborn!\n");
        return 0;
    }

    if(env->query_prop(ROOM_M_NO_TELEPORT_FROM))
    {
        notify_fail("Something prevents you from flying out of this area.\n");
        return 0;
    }

    if (!str)
    {
       write("You beat your leathery wings once and launch yourself into the air, circling " +
          "the area briefly before returning to the ground.\n");
       allbb(" beats " +HIS(TP)+ " leathery wings once and launches into the air, " +
          "circling the area briefly before returning to the ground.");
       return 1;
    }

    if (TP->query_attack() || !TP->query_relaxed_from_combat())
    {
        notify_fail("You are too focused on ground combat to fly right now.\n");
        return 0;
    }

    if(parse_command(str, env, "[to] %s", arg))
    {
       room = lower_case(arg);

       if (member_array(room, room_options) == -1)
       {
          write("You can't fly to that location. You can however fly home to the " +
             "tower of High Sorcery.\n");
          return 1;
       }

       setuid();
       seteuid(getuid());
       object flying_room = clone_object(target_room_file);

       write("You beat your leathery wings once and launch yourself into the air, and " +
             "up high into the sky!\n");
       allbb(" beats " +HIS(TP)+ " leathery wings once and launches into the air, " +
          "vanishing into the clouds!");

       TP->add_prop(WOHS_DRAGON_DESTINATION, "/d/Krynn/wayreth/forest/forest31.c");
       TP->move_living("M", target_room_file, 1, 0);

       return 1;
    }

    write("You beat your leathery wings once.. twice.. and launch into the air, circling " +
          "the area briefly before returning to the ground looking lost.\n");
    allbb(" beats " +HIS(TP)+ " leathery wings once.. twice.. and launches into the air, " +
          "circling the area briefly before returning to the ground looking lost.");

    return 1;
}

/* This function is for the serpent figurine in the Tharkadan mountain range 
   /d/Krynn/tharkadan/obj/polymorph_figurine.c */

public int
dragon_fly2(string str)
{
    string arg, room;
    object env = environment(TP);
    string target_room_file = "/d/Krynn/tharkadan/room/thark_dragon_flight_room";
    string *room_options;

    room_options = ({ "vale" });

    if (TP->query_race_name() != "dragon")
    {
        notify_fail("What?\n");
        return 0;
    }

    if(env->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot fly while inside!\n");
        return 0;
    }

    if(env->query_prop(ROOM_UNDER_WATER))
    {
        notify_fail("You cannot fly while under water!\n");
        return 0;
    }

    if(env->query_prop(ROOM_IN_AIR))
    {
        notify_fail("You are already airborn!\n");
        return 0;
    }

    if(env->query_prop(ROOM_M_NO_TELEPORT_FROM))
    {
        notify_fail("Something prevents you from flying out of this area.\n");
        return 0;
    }

    if (!str)
    {
       write("You beat your leathery wings once and launch yourself into the air, circling " +
          "the area briefly before returning to the ground.\n");
       allbb(" beats " +HIS(TP)+ " leathery wings once and launches into the air, " +
          "circling the area briefly before returning to the ground.");
       return 1;
    }

    if (TP->query_attack() || !TP->query_relaxed_from_combat())
    {
        notify_fail("You are too focused on ground combat to fly right now.\n");
        return 0;
    }

    if(parse_command(str, env, "[to] %s", arg))
    {
       room = lower_case(arg);

       if (member_array(room, room_options) == -1)
       {
          write("You can't fly to that location.\n");
          return 1;
       }

       setuid();
       seteuid(getuid());
       object flying_room = clone_object(target_room_file);

       write("You beat your leathery wings once and launch yourself into the air, and " +
             "up high into the sky!\n");
       allbb(" beats " +HIS(TP)+ " leathery wings once and launches into the air, " +
          "vanishing into the clouds!");

       TP->add_prop(WOHS_DRAGON_DESTINATION, "/d/Krynn/tharkadan/room/vale2");
       TP->move_living("M", target_room_file, 1, 0);

       return 1;
    }

    write("You beat your leathery wings once.. twice.. and launch into the air, circling " +
          "the area briefly before returning to the ground looking lost.\n");
    allbb(" beats " +HIS(TP)+ " leathery wings once.. twice.. and launches into the air, " +
          "circling the area briefly before returning to the ground looking lost.");

    return 1;
}

public int
bird_fly(string str)
{
    string arg, room;
    object env = environment(TP);
    string target_room_file = SOHM_SPELLS + "objs/wohs_bird_flight_room";
    string *room_options;

    room_options = ({ "tower", "wayreth", "wayreth forest", "home", 
                      "tower of high sorcery" });

    if (TP->query_race_name() != "bird")
    {
        notify_fail("What?\n");
        return 0;
    }

    if(env->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot fly while inside!\n");
        return 0;
    }

    if(env->query_prop(ROOM_UNDER_WATER))
    {
        notify_fail("You cannot fly while under water!\n");
        return 0;
    }

    if(env->query_prop(ROOM_IN_AIR))
    {
        notify_fail("You are already airborn!\n");
        return 0;
    }

    if(env->query_prop(ROOM_M_NO_TELEPORT_FROM))
    {
        notify_fail("Something prevents you from flying out of this area.\n");
        return 0;
    }

    if (!str)
    {
       write("You beat your wings and launch yourself into the air, circling " +
          "the area briefly before returning to the ground.\n");
       allbb(" beats " +HIS(TP)+ " wings and launches into the air, " +
          "circling the area briefly before returning to the ground.");
       return 1;
    }

    if (TP->query_attack() || !TP->query_relaxed_from_combat())
    {
        notify_fail("You are too focused on ground combat to fly right now.\n");
        return 0;
    }

    if(parse_command(str, env, "[to] %s", arg))
    {
       room = lower_case(arg);

       if (member_array(room, room_options) == -1)
       {
          write("You can't fly to that location. You can however fly home to the " +
             "tower of High Sorcery.\n");
          return 1;
       }

       setuid();
       seteuid(getuid());
       object flying_room = clone_object(target_room_file);

       write("You beat your wings once and launch yourself into the air, and " +
             "up high into the sky!\n");
       allbb(" beats " +HIS(TP)+ " wings once and launches into the air, " +
          "vanishing into the clouds!");

       TP->add_prop(WOHS_DRAGON_DESTINATION, "/d/Krynn/wayreth/forest/forest31.c");
       TP->move_living("M", target_room_file, 1, 0);

       return 1;
    }

    write("You beat your wings once.. twice.. and launch into the air, circling " +
          "the area briefly before returning to the ground looking lost.\n");
    allbb(" beats " +HIS(TP)+ " wings once.. twice.. and launches into the air, " +
          "circling the area briefly before returning to the ground looking lost.");

    return 1;
}


public int
dragon_wing(string str)
{
    if (TP->query_race_name() != "dragon")
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!str)
    {
        notify_fail("Beat what? Your wings?\n");
        return 0;
    }

    if (str != "wings")
    {
        notify_fail("Beat what? Your wings?\n");
        return 0;
    }

    write("You extend your leathery wings and beat them lazily, stirring " +
       "the air around you.\n");
    allbb(" extends " +HIS(TP)+ " leathery wings and beats them lazily, stirring " +
       "the air around you.");
    return 1;
}