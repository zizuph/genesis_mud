/*
 * shadowgate.c
 *
 * This room is a 'room between shadows', used by the Death
 * Warriors in the Great Northern Waste of Khalakhor to travel
 * quickly to and from a handful of locations. The locations
 * themselves are determined by the last few places warriors 
 * have entered shadowgate from. Warriors can enter shadowgate
 * currently from any room that has a 'shadow' add item.
 *
 * Khail - May 5/97
 */
#pragma strict_types

#include <language.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Khalakhor/sys/defs.h"
#include "shadowgate.h"

inherit "/d/Khalakhor/std/room";

mapping shadows;
string *shadow_dirs;

public void create_khalakhor_room();
public string shadow_exits();
public void remove_shadow(string dir);
public void add_shadow(string path);
public void enter_inv(object ob, object from);
public mapping query_shadows();
public void init();
public int go_shadow(string str);
/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("shadow filled chamber");
    set_long("You are in Shadowgate, a mysterious place that " +
        "lies between shadows in the real world. From here it " +
        "it is said all shadows emerge, and those who know the " +
        "talent can follow the roots of shadows to and from this " +
        "place. But as are shadows, the nature of this place is " +
        "ever changing, and to leave this one stable nexus in it " +
        "would be to be lost forever in the darkness. " +
        VBFC_ME("shadow_exits") + "\n");

    shadows = ([]);
    shadow_dirs = ({});

#ifdef ENABLE_MEMORY
    reset_euid();
    restore_object(MASTER);
#endif
}

/*
 * Function name: shadow_exits
 * Description  : Delivers a vbfc string for the long descs for 
 *                shadow exits out of here.
 * Arguments    : n/a
 * Returns      : String as described.
 */
public string
shadow_exits()
{
    int count;

    count = m_sizeof(shadows);
    if (!count)
        return "Swirling shadows with no real form circle the " +
            "area, there seems to be no way out.";

    else if (count == 1)
        return "A long shadow seems to form a passage north.";

    else return capitalize(LANG_WNUM(count)) + " shadows seem to " +
        "form passages to the " + 
        COMPOSITE_WORDS(m_indexes(shadows)) + ".";
}

/*
 * Function name: remove_shadow
 * Description  : Removes a shadow exit from shadowgate.
 * Arguments    : dir - Direction of the shadow to remove.
 * Returns      : n/a
 */
public void
remove_shadow(string dir)
{
    if (!shadows[dir])
        return;

    shadows = m_delete(shadows, dir);
    shadow_dirs -= ({dir});
#ifdef ENABLE_MEMORY
    reset_euid();
    save_object(MASTER);
#endif
}

/*
 * Function name: add_shadow
 * Description  : Adds a shadow exit to shadowgate.
 * Arguments    : path - Destination of the shadow.
 * Returns      : n/a
 */
public void
add_shadow(string path)
{
    int i;
    string *alldirs,
           maindir;

    alldirs = DIRS + ({});

  /* Do nothing if 'path' already exists as an exit. */
    if (member_array(path, m_values(shadows)) >= 0)
        return;

  /* Make sure there's less than the max number of exits. */
    while (m_sizeof(shadows) >= sizeof(DIRS))
        remove_shadow(shadow_dirs[0]);

  /* Loop through available exit directions, and use the */
  /* first one. */
    for (i = 0; i < sizeof(DIRS); i++)
    {
        if (!shadows[maindir = alldirs[i]])
        {
            shadows[maindir] = path;
            shadow_dirs += ({maindir});
            break;
        }
    }
#ifdef ENABLE_MEMORY
    reset_euid();
    save_object(MASTER);
#endif
}
 
/*
 * Function name: enter_inv (MASK)
 * Description  : Called when another object enters this object. Used
 *                here to create the shadow exits.
 * Arguments    : ob - The object entering the inventory.
 *                from - Object pointer to 'ob's last environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

  /* Do nothing for non-living objects. */
    if (!living(ob))
        return;

  /* Do nothing for livings entering shadowgate by some means */
  /* other than the Talent. */
    if (!ob->query_prop(LIVE_I_USED_SHADOWGATE))
        return;

  /* A living has entered shadowgate using the Talent, update */
  /* the exits. */
    add_shadow(MASTER_OB(ob->query_prop(LIVE_O_LAST_ROOM)));
    ob->remove_prop(LIVE_I_USED_SHADOWGATE);
}

/*
 * Function name: query_shadows
 * Description  : Simply returns the 'shadows' mapping. Mainly
 *                for debugging purposes.
 * Arguments    : n/a
 * Returns      : 'shadow' mapping.
 */
public mapping
query_shadows()
{
    return shadows + ([]);
}

/*
 * Function name: query_shadow_dirs
 * Description  : Returns an array containing all of the 'used'
 *                exit directions.
 * Arguments    : n/a
 * Returns      : The shadow_dirs string array.
 */
public string *
query_shadow_dirs()
{
    return shadow_dirs + ({});
}

/*
 * Function name: init (MASK)
 * Description  : Called when another object meets this one, used to
 *                add exit actions to the living.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    int i;

    ::init();

  /* Here we loop through all the possible exit directions, and */
  /* create an add_action to go_shadow() for each possible */
  /* command verb. This negates the difficulties of adding */
  /* and removing command verbs as shadow exits change. */
    for (i = 0; i < sizeof(DIRS); i++)
        add_action(go_shadow, DIRS[i]);
}

/*
 * Function name: go_shadow
 * Description  : Allows players to attempt to use a shadow exit.
 * Arguments    : str - Any extra arguments to the command direction.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
go_shadow(string str)
{
    string verb;
    object room,
           *watchers;

    verb = query_verb();

  /* Do nothing if the verb isn't a direction (just in case) */
    if (member_array(verb, DIRS) < 0)
        return 0;

  /* If the verb isn't an 'open' shadow exit, fail. */
    if (member_array(verb, m_indexes(shadows)) < 0)
    {
        NF("You see no shadow leading " + verb + ".\n");
        return 0;
    }
 
  /* Ok, the player is trying to use an existing shadow exit. */
  /* first thing, we make sure the destination room is loaded. */
    if (!objectp(room = find_object(shadows[verb])))
        shadows[verb]->load_me();

  /* If we _still_ don't have a destination room, remove the */
  /* exit. Also fail if there's no longer a 'shadow' add_item' */
  /* in the destination. */
    if (!objectp(room = find_object(shadows[verb])) ||
        (!room->item_id("shadow") && !room->item_id("shadows")))
    {
        write("Something seems to have disturbed the shadow, " +
            "it loses shape, and vanishes. No exit is possible " +
            "through it now.\n");
        remove_shadow(verb);
        return 1;
    }

    if (TP->query_fatigue() < FATIGUE_GATE_OUT)
    {
        write("You attempt to concentrate on passing back out " +
            "through the dark shadows to the " + verb + ", but " +
            "are too exhausted physically.\n");
        say(QCTNAME(TP) + " seems to attempt to concentrate, " +
            "but sags visibly as though exhausted.\n");
        return 1;
    }

    TP->add_fatigue(-FATIGUE_GATE_OUT);
    write("You step through the dark shadows to the " + verb +
        ", emerging somewhere else.\n");
    say(QCTNAME(TP) + " steps into the shadow to the " + verb + 
        " and vanishes within.\n");
    TP->move_living("M", room, 0, 0);

  /* This rather 'clunky' piece of code is just to ensure that */
  /* only people who can see this_player() get the message about */
  /* them emerging from a shadow. */
    watchers = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
    watchers = FILTER_CAN_SEE_IN_ROOM(watchers);
    watchers = FILTER_IS_SEEN(TP, watchers);
    watchers->catch_msg(QCTNAME(TP) + " emerges from the " +
        "shadows.\n");
    return 1;
}

/*
 * Function name: path_to_direction
 * Description  : Returns the direction of a specified path.
 * Arguments    : path - The path to look for.
 * Returns      : The direction 'path' leads in as a string.
 */
public string
path_to_direction(string path)
{
    int i;
    string dir;

    for (i = 0; i < m_sizeof(shadows); i++)
    {
        dir = m_indexes(shadows)[i];
        if (shadows[dir] == path)
            return dir;
    }

    return "";
}
        