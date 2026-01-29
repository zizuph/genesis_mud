/*
 * beast_brain.c
 *
 * Master brain object to control the movement of an npc
 * in the northern ravine of Eldoral. Specifically, unless
 * the beast is trapped, it comes in, attacks the player,
 * and leaves again every 30 seconds.
 *
 * Khail, Jan 20/97
 */
#pragma strict_types

#include "defs.h"

#define TESTING

inherit "/std/object";

object beast,
       *present;
int hunt_alarm;

public void set_beast(object ob);
public object query_beast();
public void notify_arrived(object ob);
public void notify_left(object ob);
public void hunt(object ob);
public void attempt_escape(string where, object who);
public void backup_escape(object who);

/*
 * Function name: set_beast
 * Description  : Sets the object pointer to the current beast.
 * Arguments    : ob - Object ointer the the current beast.
 * Returns      : n/a
 */
public void
set_beast(object ob)
{
    beast = ob;
}

/*
 * Function name: query_beast
 * Description  : Returns the object pointer to the current beast.
 * Arguments    : n/a
 * Returns      : As above.
 */
public object
query_beast()
{
    return beast;
}

/*
 * Function name: notify_arrived
 * Description  : Called by the rooms in the ravine when someone
 *                arrives. Starts the beast stalking the player,
 *                when appropriate.
 * Arguments    : ob - Object pointer to the player that arrived.
 * Returns      : n/a
 */
public void
notify_arrived(object ob)
{
  /* Don't bother with non-interactives */
    if (!interactive(ob))
        return;

  /* Do nothing if 'ob' has just killed the beast, or has */
  /* completed this quest. */
    if (ob->query_prop(LIVE_I_KILLED_BEAST) ||
        ob->test_bit("Calia", ELDORAL_QUEST_GROUP,
        ELDORAL_BEAST_QUEST_BIT))
        return;

  /* Add 'ob' to the 'present' global array. */
    if (!present)
        present = ({ob});
    else
        present += ({ob});

  /* If there's no beast, clone one. */
    if (!beast)
    {
        setuid();
        seteuid(getuid());
        beast = clone_object(NPC + "ravine_beast");
        beast->move(RAVINE + "beast_waiting");
    }

  /* If there's more than one person in the ravine, stop */
  /* hunting. */
    if (sizeof(present) > 1)
    {
        remove_alarm(hunt_alarm);
        beast->move(RAVINE + "beast_waiting");
    }

  /* Otherwise, start hunting the new target. */
    else
    {
        remove_alarm(hunt_alarm);
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(ob));
    }
}

/*
 * Function name: notify_left
 * Description  : Called by rooms in the ravine when players leave
 *                the ravine area.
 *                Decides if anyone is left, and responds accordingly.
 * Arguments    : ob - Object pointer to the player who left.
 * Returns      : n/a
 */
public void
notify_left(object ob)
{
  /* Do nothing for non-interactive objects */
    if (!interactive(ob))
        return;

  /* Remove 'ob' from the 'present' global array, if need be. */
    if (!present)
        present = ({});
    else
        present -= ({ob});

  /* Do nothing if there is still more than one person in */
  /* the ravine. */
    if (sizeof(present) > 1)
        return;

  /* If nobody is left in the ravine, stop all hunting. */
    if (sizeof(present) == 0)
    {
        remove_alarm(hunt_alarm);
        beast->move(RAVINE + "beast_waiting");
        return;
    }

  /* If there is only one person in the ravine, continue */
  /* hunting. */
    if (sizeof(present) == 1)
    {
        remove_alarm(hunt_alarm);
        beast->move(RAVINE + "beast_waiting");
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(present[0]));
    }
}

/*
 * Function name: hunt
 * Description  : Controls the beast's hunting of players.
 *                Decides if to attack, where to attack from,
 *                and what direction to escape in.
 * Arguments    : who - Object pointer to player to attack.
 * Returns      : n/a
 */
public void
hunt(object who)
{
    object start,
           attack,
           *rooms;
    string dir,
           escape,
           *cmds;
    mapping temp;

  /* Make sure the target is an interactive player in the */
  /* ravine. */
    if (!who || !interactive(who) ||
        function_exists("create_ravine", environment(who)) != 
        (RAVINE + "base"))
        return;

  /* Make sure there's a beast. */
    if (!beast)
        return;

  /* First, make sure the beast isn't trapped in a dead end. */
  /* If that is the case, he'll use this round to escape */
  /* rather than attack. */
    if (file_name(environment(beast)) != RAVINE + "beast_waiting")
    {
        tell_room(environment(beast), QCTNAME(beast) + " " +
        "slips away into the trees.\n");
        beast->move(RAVINE + "beast_waiting", 1);
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
        return;
    }        

  /* Now find the room 'who' is in, and the last */
  /* room 'who' was in. */
    start = who->query_prop(LIVE_O_LAST_ROOM);
    attack = environment(who);

  /* If for some reason 'who's LIVE_O_LAST_ROOM prop */
  /* didn't point to a room in the ravine, pick one */
  /* at random from the exits of the room that 'who' */
  /* is currently in. */
    if (!start ||
        function_exists("create_ravine", start) != RAVINE + "base")
    {
        rooms = attack->query_exit_rooms();

      /* Make sure the beast can't attack from the caverns. */
        rooms -= ({CAVERNS + "cav37"});

      /* If there's no rooms the beast can attack from, */
      /* do nothing this time. */
        if (!sizeof(rooms))
        {
            hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
            return;
        }

      /* Pick a room to attack from at random from the */
      /* ones that are still available. */
        start = rooms[random(sizeof(rooms))];
    }

  /* Make a temporary mapping of the rooms around the start */
  /* room and the directions to go to them. */
    temp = mkmapping(start->query_exit_rooms(),
        start->query_exit_cmds());

  /* If there is no exit command to get to the attack room */
  /* from the start room (very odd) do nothing. Else, use */
  /* this as the direction to attack in. */
    if (!temp[file_name(attack)])
    {
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
        return;
    }
    else
        dir = temp[file_name(attack)];

    temp = mkmapping(attack->query_exit_rooms(),
        attack->query_exit_cmds());
    temp = m_delete(temp, CAVERNS + "cav37");

  /* Get a list of all the possible directions to escape from */
  /* the attack room into. */
    cmds = m_values(temp);
    
  /* If there's only one exit command, don't attack. The */
  /* beast won't knowingly be trapped, and the only way out */
  /* of the attack room appears to be the only way in. */
    if (sizeof(cmds) == 1)
    {
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
        return;
    }

  /* Make a temporary mapping of all the possible rooms to */
  /* leave the attack room into indexed off of the commands */
  /* to enter those rooms. */
    temp = mkmapping(cmds, attack->query_exit_rooms());

  /* The beast will always try to continue straight ahead. */
  /* I.e. if entering the attack room from the south will */
  /* try to leave by the north. If such a possibility does */
  /* not exist, select an attack direction at random, */
  /* excluding the direction the beast entered from. It */
  /* can't attack from the south then escape to the south, */
  /* for example. */
    if (!temp[dir])
    {
        do escape = cmds[random(sizeof(cmds))];
        while (temp[escape] == file_name(start));
    }
    else
        escape = dir;

  /* Now we've got the room to start attacking from, 'start', */
  /* the room to attack in, 'attack', the exit command to use */
  /* to get from the starting room to the attack room, 'dir', */
  /* and the exit command to escape from the player, 'escape'. */
  /* So, we'll move the beast to 'start', tell it to go 'dir' */
  /* and attack the player. */
    beast->move(start);
    beast->command(dir);
    beast->hunt_attack(who);

  /* Now, try to escape. */
    attempt_escape(escape, who);
}

public void
attempt_escape(string where, object who)
{
    mapping temp;
    object here,
           *rooms;

    here = environment(who);

  /* Try to escape in the predetermined direction. */
    beast->command(where);

  /* Beast is still in the same room as the player. The */
  /* selected exit must have been blocked, so give the */
  /* player 10 seconds to do some damage. */
    if (environment(beast) == here)
    {
        tell_room(environment(who), QCTNAME(beast) +
            " seems to have realized it cannot escape in " +
            "its preselected path!\n");
        beast->command("snarl " + OB_NAME(who));
        hunt_alarm = set_alarm(10.0, 0.0, &backup_escape(who));
        return;
    }

  /* Beast escaped, but if he escaped into a dead end, */
  /* he stays there rather than going to the waiting */
  /* room as usual. */
    here = environment(beast);
    rooms = here->query_exit_rooms();
    rooms -= ({CAVERNS + "cav37"});
    if (sizeof(rooms) < 2)
    {
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
        return;
    }
    
  /* Beast successfully escaped the player. Move it to */
  /* the waiting room and attack again in 30 seconds. */
    else
    {
        beast->move(RAVINE + "beast_waiting");
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
    }
}    

public void
backup_escape(object who)
{
  /* First off make sure the beast hasn't been killed. */
    if (!beast)
        return;

    tell_room(environment(who), QCTNAME(beast) + " suddenly " +
        "leaps into the air and vanishes into the trees.\n");

  /* Try moving the beast out of the room. If it fails for */
  /* any reason, try again in 10 seconds. */
    if (beast->move(RAVINE + "beast_waiting"))
    {
        tell_room(environment(who), QCTNAME(beast) + 
            " couldn't quite complete his escape and drops " +
            "back into view.\n");
        beast->command("growl");
        hunt_alarm = set_alarm(10.0, 0.0, &backup_escape(who));
        return;
    }

  /* Beast escaped, hunt again in 30 seconds. */
    else
    {
        hunt_alarm = set_alarm(30.0, 0.0, &hunt(who));
    }
}

public int
query_hunting()
{
    if (hunt_alarm && get_alarm(hunt_alarm))
        return 1;
    else
        return 0;
}
                    
