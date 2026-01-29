/*
 * Modifications
 *   - Corrected typo, Petros, March 2009
 */
 
#pragma strict_types

#include "defs.h"
#include "../guru_quest.h"
#include <filter_funs.h>
#include <wa_types.h>

#define FLAME_DAM 5000

string corpse_name,
       tomb_dir;
int tomb_status;
object holding_door,
       gauntlet;

/*
 * Function name: reset_crypts
 * Description  : Resets the crypt variables.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_crypts()
{
    if (tomb_status)
    {
        tell_room(TO, "Suddenly, the tomb slab slams shut all " +
            "by itself.\n");
        tomb_status = 0;
    }
    holding_door = 0;
    gauntlet = 0;
}

/*
 * Function name: tomb_long
 * Description  : Extra long desc for the room based off this tomb.
 * Arguments    : n/a
 * Returns      : A string describing the tomb.
 */
public string
tomb_long()
{
    if (!tomb_status)
        return "A long stone slab crossing the " + tomb_dir + " " +
            "wall marks the final resting place of some poor " +
            "soul.\n";
    else
        return "A long stone slab crossing the " + tomb_dir + " " +
            "wall hangs open, exposing the final resting " +
            "place of some poor soul.\n";
}

/*
 * Function name: tomb_desc
 * Description  : VBFC'd add_item for the tomb.
 * Arguments    : n/a
 * Returns      : A string describing the tomb.
 */
public string
tomb_desc()
{
    if (!tomb_status)
        return "The stone slab sealing the tomb on the " + tomb_dir +
            " wall is relatively plain and unadorned, except " +
            "for the name " + corpse_name + " engraved upon it.\n";
    else
        return "The stone slab hanging ajar from the exposed tomb " +
            "on the " + tomb_dir + " wall is relatively plain " +
            "and unadorned, except for the name " + corpse_name +
            " engraved upon it. Within the tomb, nothing of the " +
            "corpse but dust remains.\n";
}

/*
 * Function name: add_tomb
 * Description  : Adds a burial tomb to this room.
 * Arguments    : name - Name of the person buried here.
 *                dir - Direction the tomb lies in.
 * Returns      : n/a
 */
public void
create_tomb(string name, string dir)
{
    TO->add_my_desc(VBFC_ME("tomb_long"), TO);
    TO->add_item(({"tomb", "slab"}),
        VBFC_ME("tomb_desc"));
    corpse_name = name;
    tomb_dir = dir;
    TO->add_prop(ROOM_M_NO_TELEPORT, 1);

    setuid();
    seteuid(getuid());
    if (!find_object(GURU_BRAIN))
        GURU_BRAIN->reset_quest();    
}

public int
do_open(string str)
{
    object *who;
    int i;

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'tomb' / 'slab'"))
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        write("It's too dark, you can't see it.\n");
        return 1;
    }

    if (tomb_status)
    {
        write("The tomb has already been breached.\n");
        return 1;
    }

    if (holding_door && present(holding_door, TO))
    {
        TP->catch_msg("You can't open the slab with " +
            QTNAME(holding_door) + " holding it shut.\n");
        return 1;
    }

  /* Only players who have talked to krom about the guru quest */
  /* may open tomb doors. */
    if (!(TP->query_prop(LIVE_I_GURU_QUESTING) & C_GURU_KROM))
    {
        write("There is no reason for you to violate the " +
            "sanctity of the dead.\n");
        return 1;
    }

  /* Did the player open the tomb with the gauntlet? If not, */
  /* something nasty to prevent players from trying it */
  /* randomly. */
    seteuid(getuid());
    if (GURU_BRAIN->query_king() != corpse_name)
    {
        write("You carefully edge open the slab to the tomb.\n");
        say(QCTNAME(TP) + " carefully edges open the slab "+
            "to the tomb.\n");
        tell_room(TO, "A shadowy, black apparition suddenly " +
            "appears, and screams: Hell stab at thee for " +
            "disturbing my peace!\nSuddenly the very air " +
            "around you erupts into a seething mass of " +
            "flame, burning you badly!\n");
        who = FILTER_LIVE(all_inventory(TO));
        who->hit_me(FLAME_DAM, MAGIC_DT, TO, -1);
        filter(who, &not() @ &->query_hp())->do_die(TO);
        tell_room(TO, "The apparition and flames vanish again " +
            "as quickly as they appeared.\n");
        tomb_status = 1;
        return 1;
    }
    else
    {
        write("You carefully edge open the slab to the tomb.\n");
        say(QCTNAME(TP) + " carefully edges open the slab of " +
            "the tomb.\n");
        if (!gauntlet)
        {
            tell_room(TO, "Something heavy falls out of the tomb " +
                "and drops to the ground with a clank.\n");
            seteuid(getuid());
            gauntlet = clone_object(ARM + "gauntlet");
            gauntlet->move(TO);
        }
        tomb_status = 1;
    }
    return 1;
}
   
public int
do_close(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'tomb' / 'slab'"))
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        write("It's too dark in here to see it.\n");
        return 1;
    }

    if (!tomb_status)
    {
        write("The tomb is already closed.\n");
        return 1;
    }

    write("You carefully close the slab to the tomb up tight " +
        "again.\n");
    say(QCTNAME(TP) + " carefully closes the slab to the tomb " +
        "up tight again.\n");
    tomb_status = 0;
    return 1;
}

public int
do_hold(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP,
        "[the] 'slab' / 'tomb' 'shut' / 'closed'"))
        return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
        write("It's too dark to see it.\n");
        return 1;
    }

    if (tomb_status)
    {
        write("You'll have to close the tomb first.\n");
        return 1;
    }

    write("You brace yourself against the tomb slab, holding it " +
        "tightly shut. Until you leave or stop holding the slab " +
        "shut, it's not moving.\n");
    say(QCTNAME(TP) + " braces " + TP->query_objective() + "self " +
        "against the tomb slab, holding it tightly shut.\n");
    holding_door = TP;
    return 1;
}

public int
do_stop(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "'holding' [the] [tomb] 'slab' " +
        "[closed] / [shut]"));
        return 0;

    if (!holding_door || TP != holding_door)
    {
        write("But you aren't holding the slab closed.\n");
        return 1;
    }

    write("You cease holding the slab to the tomb shut.\n");
    say(QCTNAME(TP) + " stops holding the tomb slab shut.\n");
    holding_door = 0;
    return 1;
}

public void
init_tomb()
{
    add_action(do_open, "open");
    add_action(do_close, "close");
    add_action(do_hold, "hold");
    add_action(do_stop, "stop");
}

/*
 * Function name: leave_tomb
 * Description  : VBFC'd exit blocking function to prevent players
 *                from leaving the tomb if they've picked up the
 *                gauntlet, unless someone is holding the tomb 
 *                door shut.
 * Arguments    : n/a
 * Returns      : 0 - Player may leave.
 *                1 - Player can't leave.
 */
public int
leave_tomb()
{
    if (holding_door && TP == holding_door)
    {
        write("You stop holding the tomb slab closed to leave.\n");
        say(QCTNAME(TP) + " stops holding the tomb slab closed " +
            "to leave.\n");
        holding_door = 0;
    }

  /* Do nothing if the gauntlet hasn't been cloned. */
    if (!gauntlet)
        return 0;

  /* Do nothing if the gauntlet isn't in TP's deep_inv. */
    if (member_array(gauntlet, deep_inventory(TP)) < 0)
        return 0;

  /* If the tomb door's open, spirit takes gauntlet back. */
    if (tomb_status)
    {
        write("As you leave, a dark mist seeps " +
            "out of the tomb, surrounding you, and you find " +
            "yourself unable to leave! Perhaps you should " +
            "close the tomb again.\n");
        say("As " + QTNAME(TP) + " tries to leave, " +
            "a dark mist seeps out of the tomb, momentarily " +
            "surrounding " + TP->query_objective() + ", " +
            "and " + TP->query_pronoun() + " appears unable " +
            "to leave!\n");
        return 1;
    }

  /* Tomb door is closed, but nobody is holding it shut. */
    if (!tomb_status && 
        (!holding_door || !present(holding_door, TO)))
    {
        write("As you try to leave, the tomb slab suddenly " +
            "flies open, and a dark mist momentarily surrounds " +
            "you, preventing you from leaving! It seems just " +
            "closing it isn't enough, you'll have to find a " +
            "way to keep it shut.\n");
        say("As " + QTNAME(TP) + " tries to leave, the tomb "+
            "slab suddenly flies open, and a dark mist " +
            "momentarily surrounds " + TP->query_objective() +
            ", preventing " + TP->query_objective() + " from " +
            "leaving!\n");
        tomb_status = 1;
        return 1;
    }

  /* If someone's holding the tomb door closed, let the player */
  /* leave with the gauntlet. */
    if (!tomb_status && present(holding_door, TO))
    {
        TP->catch_msg("As you leave, the slab to the tomb " +
            "starts shuddering, as if trying to open, but " +
            QTNAME(holding_door) + " manages to keep it " +
            "held firmly shut!\n");
        holding_door->catch_msg("As " + QTNAME(TP) + " leaves, " +
            "the slab to the tomb starts shuddering, as if " +
            "trying to open, but you manage to hold it firmly " +
            "shut!\n");
        tell_room(TO, "As " + QTNAME(TP) + " leaves, the slab to " +
            "the tomb starts shuddering, as if trying to open, " +
            "but " + QTNAME(holding_door) + " manages to keep " +
            "it firmly shut!\n", ({TP, holding_door}));
        return 0;
    }
    return 0;
}

