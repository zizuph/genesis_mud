/*
 * skywalk.c
 *
 * A narrow walkway above a reflecting pool in the center of the ruins
 * of Castle Chimera in Eldoral. This room is part of what's called by
 * myself the 'sword in the stone' quest. In this room, what is required
 * of the player is that they drop objects onto specific locations on
 * a pattern in the bottom of the pool. Once sufficient volume of objects
 * is placed onto these locations, they become registered as 'marked' in
 * the quest brain (~Calia/eldoral/special/sword_brain.c).
 *
 * Coded by Khail, Jan 1/97
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>

#define VOLUME_LIMIT    10000   /* 10 liters */
#define TIMEOUT         1800    /* 30 minutes */

inherit STDROOM;

/* 
 * Global vars. Formats are:
 * markers = ([location string desc: ({short desc of item(s) there...})]);
 * volumes = ([numeric location (0-23): ({volume of objects there})]);
 */
mapping markers;
mapping volumes;
object may_not_reset;
int may_not_reset_id;

/* Prototypes */
public void reset_quest();
public void create_room();
public string exa_pool();
public void init();
public int do_drop(string str);
public void update_dropped(object ob, int loc);

public void
remove_reset_lockout()
{
    may_not_reset = 0;
}

/*
 * Function name: reset_quest
 * Description  : resets the quest-related things in this room, 
 *                such as re-initializing the 'markers' and 
 *                'volumes' variables.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_quest()
{
    tell_room(TO, "You hear a rushing sound, and look down to " +
        "see the water in the pool whirling around, as if fresh " +
        "water has swept in from somewhere, taking out the old " +
        "and anything in it.\n");
    markers = ([]);
    volumes = ([]);
    SWORD_BRAIN->reset_marked();
}

/*
 * Function name: reset_room
 * Description  : Attempts to reset the room. With this particular
 *                room, however, we do not always want it to reset
 *                normally. All the variables that may require
 *                resetting are in reset_quest, so call that function
 *                if we can reset. We will reset only if one of the
 *                following is true:
 *                1: Object pointer to the last player to weight
 *                   a trigger stone (may_not_reset variable) is
 *                   no longer valid.
 *                2: may_not_reset has no environment.
 *                3: may_not_reset has been linkdead longer than a
 *                   15 minutes.
 *                4: may_not_reset has left the domain Calia.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    if (may_not_reset &&
        objectp(may_not_reset) &&
        environment(may_not_reset) &&
        (time() - may_not_reset->query_linkdead() < (TIMEOUT / 2)) &&
        domain(environment(may_not_reset)) == domain(TO))
    {
        return;
    }

  /* In addition to the checks for this room, also make sure */
  /* nobody is using the information created by this room */
  /* in the catacomb hub before resetting. */
    else if ((RUIN + "catacomb_hub")->query_reset_lockout())
    {
        return;
    }

    else
    {     
        reset_quest();
    }
}

/*
 * Function name: tower_block
 * Description  : VBFC'd exit blocking which tests to make sure the
 *                seer is alone before allowing players to enter
 *                this way.
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.
 *                1 - Player can't pass.
 */
public int
tower_block()
{
    object seer;

    if (!find_object(RUIN + "seer_tower"))
        return 0;

    if ((RUIN + "seer_tower")->query_quester(1))
    {
        write("A strange force repels you from the entrance, " +
            "it seems your presence is not wanted, at the " +
            "moment.\n");
        return 1;
    }
    else if (seer = (RUIN + "seer_tower")->query_seer())
    {
        seer->test_for_dagger(TP);
        return 0;
    }
    else
    {
        return 0;
    }
}

/*
 * Function name: create_room
 * Description  : Does the obvious, sets vars to turn this object into
 *                a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_room()
{
    set_short("upon an elevated walkway in " +
        CASTLE_NAME);
    set_long("You are upon an elevated walkway " +
        "running east and west between two ruins in " +
        CASTLE_NAME+". To your east, a " +
        "large structure with a number of ruined " +
        "towers and walls stands. Smaller " +
        "buildings, halls and towers lie to the " +
        "north and south, and the west of this " +
        "walkway ends at an opening in the ruins of " +
        "another old tower. Directly beneath you, " +
        "you see a spectacular sight, a wide pool " +
        "dominating a small courtyard. Aside from a " +
        "narrow path around the edge of the pool, " +
        "the only other thing in the small " +
        "courtyard seems to be small statues in each " +
        "of the four corners.\n\n");

    add_item(({"pool"}), "@@exa_pool");
    add_item(({"sky", "mist"}),
        "Above your head, a heavy white mist blankets the sky.\n");
    add_item(({"ground", "floor", "walkway"}),
        "You are in the center of a wide stone walkway which " +
        "stretches between a building to the east, and a tower " +
        "to the west.\n");
    add_item(({"courtyard"}),
        "Below you spreads a small courtyard dominated by a " +
        "wide pool of clear water.\n");
    add_item(({"building"}),
        "The building to the east is in rough condition, made " +
        "of large blocks of grey stone which now show cracks and " +
        "crumbling facades where smoothly polished stone once " +
        "stood.\n");
    add_item(({"tower"}),
        "To the west rises an ominous tower. Rising high above " +
        "the surrounding ruins, its top is shrouded in mist.\n");
    add_item(({"path"}),
        "A narrow path circles the pool in the courtyard, but " +
        "there doesn't seem to be a way onto it.\n");
    add_item(({"statues"}),
        "Statues, or what once were statues, stand in the four " +
        "corners of the courtyard. Now all that is left of them " +
        "is little more than elongated lumps of eroded stone.\n");
       
    add_exit(RUIN + "build_6_u", "east");
    add_exit(RUIN + "seer_tower", "west", VBFC_ME("tower_block"));

    reset_room();
}

/*
 * Function name: exa_pool
 * Description  : Generates a VBFC'd description for the 'pool' add_item.
 * Arguments    : n/a
 * Returns      : A string that shows where things have been dropped in
 *                the pool.
 */
public string
exa_pool()
{
    string str,
           *arr;
              
    str = "Beneath the walkway, dominating the small courtyard, " +
        "a wide pool with remarkably clear water stands in " +
        "silence. At the bottom of the pool, some sort of " +
        "strange pattern ripples in the shifting light, part " +
        "warrior, part chimera.\n";

  /* Get a list of the descriptors of all locations in the pattern */
  /* at the bottom of the pool that have had things dropped on them */
  /* in the form of an array, and implode it for a return string. */
    if (sizeof(arr = SWORD_BRAIN->translate_locs(SWORD_BRAIN->query_marked())))
    {
        if (sizeof(arr) == 1)
            str += "Beneath the water of the pool, you can see a hazy " +
                "outline of something lying on the pattern " + arr[0] +
                ".\n";
        else
            str += "Beneath the water of the pool, you can see blurry " +
                "forms lying at different points on the pattern; " +
                COMPOSITE_WORDS(arr) + ".\n";
    }

    return str;
}

/*
 * Function name: init (MASKED)
 * Description  : Used to add the 'drop', 'put', and 'place' commands
 *                to a player who enters the room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_drop, "drop");
    add_action(do_drop, "put");
    add_action(do_drop, "place");
}

/*
 * Function name: do_drop
 * Description  : Called by the locally defined add_actions to allow
 *                players to drop markers into the pool.
 * Arguments    : str - a string supplied by the player as the argument
 *                      to the command.
 * Returns      : 1 - Success, stop threading.
 *                0 - Failure, keep threading.
 */
public int
do_drop(string str)
{
    string verb,
           where;
    object what;

    verb = query_verb();

    if (!strlen(str))
        return 0;

  /* Extract necessary information from the argument provided by */
  /* the player for evaluation. I.e. what they're trying to drop, */
  /* and exactly where they're trying to drop it. Current format */
  /* allows, for example, 'drop sword on the chimera's head', or */
  /* 'drop sword onto the chimera's head', or just plain 'drop */
  /* sword the chimera's head'. Note also that only the player's */
  /* inventory is searched for object matches, not the environment. */
    if (!parse_command(str, TP,
        "%o [onto] / [on] %s",
        what, where))
    {
        notify_fail(capitalize(query_verb()) + " what " +
            "where?\n");
        return 0;
    }

  /* Make sure what they're trying to drop can be dropped. */
    if (!what || what->query_prop(OBJ_M_NO_DROP))
    {
        notify_fail("You can't " + verb + " " +
            "that anywhere.\n");
        return 0;
    }

  /* Make sure the player can see what he/she is trying to drop, */
  /* as well as see in the room in general. */
    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, what))
    {
        write("You see no such thing to " + verb + ".\n");
        return 1;
    }

  /* Fail if we can't understand where the player's trying to drop */
  /* the object. */
    if (!SWORD_BRAIN->valid_loc(where))
    {
        notify_fail(capitalize(query_verb()) + " " +
            LANG_ADDART(what->short()) + " onto what?\n");
        return 0;
    }

  /* Make sure the object can be moved out of the player's inventory. */
  /* Since the object will be destructed in a fraction of a second */
  /* anyway if the move works, we'll just move it into their */
  /* environment. */
    if (what->move(TO, 1))
    {
        notify_fail("You cannot drop " + LANG_ADDART(what->short()) +
            " for some reason.\n");
        return 0;
    }

  /* Add the dropped object's short desc to a mapping that remembers */
  /* the appearance of everything that's been dropped, indexed off */
  /* of where it was dropped. */
    if (!markers[where])
        markers[where] = ({what->short()});
    else
        markers[where] += ({what->short()});
    
    write("You lean over the edge of the walkway, " +
        "and drop " + LANG_ADDART(what->short()) +
        " over the edge into the pool, where it lands with " +
        "a splash " + where + ".\n");
    say(QCTNAME(TP) + " leans over the edge of the " +
        "walkway, and drops " + 
        LANG_ADDART(what->short()) + " over the edge, " +
        "into the pool below, where it lands with a splash then " +
        "sinks to the bottom.\n");

  /* Set the 'may not reset' variable, and start the alarm to */
  /* remove it again. This gives the player some extra time */
  /* beyond a normal room reset, so they'll have at least a */
  /* half hour after the last time they weighted a stone to */
  /* weight the rest without the room resetting. */
    may_not_reset = TP;
    if (get_alarm(may_not_reset_id))
        remove_alarm(may_not_reset_id);
    may_not_reset_id = set_alarm(itof(TIMEOUT), 0.0, remove_reset_lockout);

  /* Call update_dropped for 'volumes' book keeping, and testing */
  /* to see if it can be added as having been marked in the */
  /* sword brain object. */
    update_dropped(what, SWORD_BRAIN->loc_number(where));
    what->remove_object();
    if (!(TP->query_prop(LIVE_I_SWORD_QUEST) & SWQ_MARKED_X))
        TP->add_prop(LIVE_I_SWORD_QUEST,
            TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_MARKED_X);
    return 1;
}   

/*
 * Function name: update_dropped
 * Description  : Does some bookkeeping on dropped objects, to make
 *                the decision on whether or not there's enough 
 *                volume on the location to create a mark.
 * Arguments    : ob - Object pointer to the object being dropped.
 *                loc - Integer number of the location that 'ob' is
 *                      being dropped on.
 * Returns      : n/a
 */
public void
update_dropped(object ob, int loc)
{
    int vol,
        i,
        temploc;
    mixed temparr;

  /* Get the object's volume. */
    vol = ob->query_prop(OBJ_I_VOLUME);

  /* Set or modify the total volume of objects on the specified */
  /* location. */
    if (!volumes[loc])
        volumes[loc] = vol;
    else
        volumes[loc] += vol;

  /* If the volume on the specified location is high enough now, */
  /* register it with the sword brain as having been marked. */
    if (volumes[loc] >= VOLUME_LIMIT)
    {
        temploc = (loc > 11 ? loc - 12 : loc);
        temparr = SWORD_BRAIN->query_marked();
        for (i = 0; i < sizeof(temparr); i++)
        {
            if (temparr[i][0] == temploc)
            {
                ob->remove_object();
                return;
            }
        }
        SWORD_BRAIN->add_marked(temploc);
        ob->remove_object();
    }
} 
