/*
 * seer_tower.c
 * 
 * This room is home to the ghost of a seer. It is one of the rooms
 * involved in the 'Seer and the Lord Quest'. This room's involvement
 * in the quest is that it contains the seer's ghost, and contains a 
 * hidden compartment which holds items needed for the 'Sword in the
 * Stone Quest', which cannot be obtained until the Seer's Quest is
 * done first.
 *
 * Coded by Khail, Jan 5/96
 */
#pragma strict_types

#include "defs.h"
#include <math.h>
#include <filter_funs.h>

inherit STDROOM;

string *walls = ({"southeast", "south", "southwest", "west",
                  "northwest", "north", "northeast"});
mapping timeout;
object compartment;
object quester;
object seer;

public int do_push(string str);
public string exa_walls();

public object
query_seer()
{
    return seer;
}

/*
 * Function name: set_quester
 * Description  : Sets the current 'quester' for the room. Since the
 *                normal code doesn't take wizards into consideration,
 *                this is used to make wizards questers for debugging.
 * Arguments    : var - Either an object pointer to the quester-to-be,
 *                      or his/her name.
 * Returns      : n/a
 */ 
public void
set_quester(mixed var)
{
    if (objectp(var))
        quester = var;
    else if (stringp(var))
        quester = find_player(var);
}

/*
 * Function name: query_quester
 * Description  : Used to return the current quest as an object
 *                pointer, or true/false if used to test if the
 *                current quester is here.
 * Arguments    : in_room = Optional flag. Set to > 0 for this
 *                          function to tell if the quester is
 *                          present or not.
 * Returns      : Object pointer to current quester.
 *                or
 *                1 - Quester present.
 *                0 - Quester not present.
 */
public varargs mixed
query_quester(int in_room = 0)
{
    if (!in_room)
        return quester;

    if (!quester)
        return 0;

    return objectp(present(quester, TO));
}

public void
create_room()
{
    set_short("an odd tower in "+CASTLE_NAME);
    set_long("You find yourself in a stark, circular chamber. " +
        "Above your head, the circular walls reach upwards for " +
        "at least three stories ending in a conical roof. The " +
        "floor is much the same construction as the walls, " +
        "cut blocks of grey stone carefully dressed and fitted " +
        "together; when new it must have been difficult to " +
        "find the seams. A number of sconces are mounted on the " +
        "walls of the rooms, and a large fireplace stands in the " +
        "center of the room. A simple archway stands in the east " +
        "wall, leading outside.\n\n");

    add_item(({"wall", "walls"}), "@@exa_walls");
    add_item(({"slit", "slits", "windows", "window"}),
        "High up on the walls near the ceiling, a single row of " +
        "narrow slits cut through the stone serves as a ring of " +
        "windows, allowing light to enter, and smoke to escape.\n");
    add_item(({"roof", "ceiling"}),
        "Concealed in shadows far above your head, you cannot " +
        "see much of the ceiling.\n");
    add_item(({"floor", "ground"}),
        "The floor in this room is made from blocks of well-cut " +
        "stone, tightly fitted together to form a smooth, " +
        "solid walking surface.\n");
    add_item(({"sconces"}),
        "Heavy iron rings, now covered in rust, are mounted " +
        "in several places around the circular wall. Once the " +
        "sconces held torches, now they hold nothing but " +
        "rust and dust.\n");
    add_item(({"fireplace"}),
        "In the center of the room, a wide, circular fireplace " +
        "stands, raised off the floor a foot or two. It must " +
        "be capable of supporting enough wood for a huge fire, " +
        "but now nothing but dust fills it.\n");

    INSIDE;

    add_exit(RUIN + "skywalk", "east");

    timeout = ([]);
}

/*
 * Function name: query_seer_stone
 * Description  : Used to determine which stone (from the bottom)
 *                of a wall is the trigger stone. Selected by 
 *                NAME_TO_RANDOM.
 * Arguments    : ob - Object pointer to the player who needs the 
 *                     info.
 * Returns      : Integer 1 through 10 representing which stone
 *                from the bottom is the trigger stone.
 */
public int
query_seer_stone(object ob)
{
  /* Generate the number, adding 1 so the value will never be 0 */
    return NAME_TO_RANDOM(ob->query_real_name(), 12345678, 10) + 1;
}

/*
 * Function name: query_seer_wall
 * Description  : Returns the appropriate trigger wall for the
 *                player, selected randomly by NAME_TO_RANDOM.
 * Arguments    : ob - Object pointer to the player.
 * Returns      : A string describing which wall the trigger lies
 *                on. I.e. 'northeast'.
 */
public string
query_seer_wall(object ob)
{
    return walls[NAME_TO_RANDOM(ob->query_real_name(), 87654321, 7)];  
}

/*
 * Function name: check_stone
 * Description  : A function that checks a string description
 *                of which stone on which wall a player is trying
 *                to push.
 * Arguments    : stone - String describing which stone the player
 *                        is trying to use.
 *                wall - String describing which wall the player is
 *                       trying to use.
 * Returns      : 0 - Fail, specified stone & wall is the incorrect
 *                    combination.
 *                1 - Success, specified combination is correct.
 */
public int
check_stone(string stone, string wall)
{
    int true_stone;
    string true_wall;

  /* If there's no quester for some reason, this_player() is */
  /* now it. */
    if (!quester || !present(quester, TO))
        quester = TP;

  /* Query the true stone and true wall (as integers) */
    true_stone = query_seer_stone(quester);
    true_wall = query_seer_wall(quester);

    if ((LANG_ORDW(stone)) != true_stone)
        return 0;
    else if (wall != true_wall)
        return 0;
    else
        return 1;
}

/*
 * Function name: exa_walls
 * Description  : VBFC'd description for walls add_item. Done 
 *                this way to allow a place to add an extra message
 *                for players who have done this quest to remind
 *                them where the block 'trigger' to open the
 *                compartment is.
 * Arguments    : n/a
 * Returns      : String describing the walls.
 */
public string
exa_walls()
{
    string ret;

    ret = "The walls of the chamber are almost perfectly cylindrical " +
        "in shape, and extend upwards at least three stories before " +
        "ending in a conical roof at the top of the tower. They are " +
        "made from well-dressed blocks of grey stone, and at one " +
        "time it was probably impossible to locate the seams, but time " +
        "has taken care of that, and now gaps you could put your fist " +
        "through are scattered across them. Up near the ceiling, " +
        "the walls are ringed by a single row of narrow slits.\n";

  /* If the player's done this quest, remind them where the */
  /* trigger stone is. It's determined by NAME_TO_RANDOM, */
  /* so will always be the same for the same player. */
    if (TP->test_bit("Calia", 
        ELDORAL_QUEST_GROUP, ELDORAL_SEER_QUEST_BIT))
    {
        ret += "As your eyes brush across the walls, you remember " +
            "the secret compartment, triggered by the " +
            LANG_WORD(query_seer_stone(TP)) + " stone " +
            "from the floor on the " +
            query_seer_wall(TP) + " wall.\n";
    }

    return ret;
}

/*
 * Function name: boot_quester
 * Description  : Players only have 10 minutes at a time in this room.
 *                That's just to ensure nobody takes any great advantage
 *                of the fact that only one person can be in here at a
 *                time, i.e. it's not a safe idle-hideout. Called by
 *                alarm from enter_inv.
 * Arguments    : who - Object pointer to the player to boot.
 * Returns      : n/a
 */
public void
boot_quester(object who)
{
    if (!who || !present(who, TO) || who->query_wiz_level())
        return;
    tell_object(who, "You suddenly feel you have overstayed your " +
        "welcome...the room begins to grow hot and everything " +
        "becomes quite hazy. You blink, and when you open your " +
        "eyes you are somewhere else.\n");
    who->move_living("X", RUIN + "skywalk");
}

public void
remove_timeout(object who)
{
    if (timeout && timeout[who] && get_alarm(timeout[who]))
        remove_alarm(timeout[who]);
}

/*
 * Function name: summon_seer
 * Description  : Decides whether or not the seer ghost should
 *                be present, and clones him in if appropriate.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
summon_seer()
{
    object *arr;

  /* First get a list of all interactive mortals in the room */
  /* that have solved the Seer and the Lord Quest. */
    arr = FILTER_PLAYERS(all_inventory(TO));
    arr = filter(arr, &not() @ &->query_wiz_level());
    arr = filter(arr, &->test_bit("Calia", 
        ELDORAL_QUEST_GROUP, ELDORAL_SEER_QUEST_BIT));

  /* If there are any players in the above array, remove the */
  /* seer if he's present (he shouldn't be, but it doesn't */
  /* hurt to double-check), as the seer ghost never appears */
  /* to players who have seen him 'die' at the end of the */
  /* quest. */
    if (sizeof(arr))
    {
        if (seer)
            seer->remove_object();
        return;
    }

  /* Ok, there's no players in the room who have done the */
  /* quest. If the seer is here, leave him. If not, clone */
  /* him. */
    if (seer)
        return;
    seteuid(getuid());
    seer = clone_object(NPC + "seer_ghost");
    seer->move_living("M",TO);
}
    
/*
 * Function name: enter_inv (MASKED)
 * Description  : Called when an object enters the room,
 *                used here to ensure there is only one mortal
 *                at a time in this room. For additional details,
 *                use 'sman /std/object enter_inv'
 * Arguments    : See sman page.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (seer && ob == seer)
        return;

  /* Always summon the seer for non-interactives and wizards */
    if ((living(ob) && !interactive(ob))
         || ob->query_wiz_level())
    {
        set_alarm(0.0, 0.0, summon_seer);
        return;
    }

  /* Refuse entry to players when someone else is questing, */
  /* even if the current quester is LD */
    if (quester && 
       (present(quester, TO) || quester->query_linkdead()) &&
        quester != ob)
    {
        tell_object(ob, "The room wavers in front of you, and " +
            "you sense you should not be here. Suddenly the " +
            "room fades and you are somewhere else.\n");
        ob->move_living("X", from);
        return;
    }

  /* Ok, we've got a mortal player, start the 10 minute time */
  /* limit (to prevent idlers), set the player as the current */
  /* quester, and summon the seer. */
    else if (!ob->query_wiz_level() && interactive(ob))
    {
        set_alarm(0.0, 0.0, summon_seer);
        quester = ob;
        if (timeout && timeout[ob] && get_alarm(timeout[ob]))
            remove_alarm(timeout[ob]);
        timeout[ob] = set_alarm(600.0, 0.0, &boot_quester(ob));
    }
}

/*
 * Function name: leave_inv (MASK)
 * Description  : Called whenever something leaves the inventory
 *                of this object. Used here to remove the seer
 *                when the last living in the room leaves.
 * Arguments    : ob - Object pointer to the object leaving.
 *                to - Object pointer to the ob's new environment.
 * Returns      : n/a
 */
public void
leave_inv(object ob, object to)
{
    object *arr;

    ::leave_inv(ob, to);

    if (seer && ob == seer)
        return;

  /* Get an array of all other livings in the room */
    arr = FILTER_LIVE(all_inventory(TO) - ({seer}));
    if (member_array(ob, arr) >= 0)
        arr -= ({ob});

  /* If no other livings present, remove the seer. */
    if (!sizeof(arr))
    {
        if (seer)
            seer->remove_object();
        return;
    }
}

/*
 * Function name: reset_room (MASK)
 * Description  : Resets global variables, etc.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (compartment)
        compartment->remove_object();
}

/*
 * Function name: init (MASK)
 * Description  : Called when one object meets another, here used
 *                to add commands to players entering this room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_push, "push");
    add_action(do_push, "press");
}

/*
 * Function name: do_push
 * Description  : Allows the players to attempt to push a stone
 *                on a wall to reveal the compartment.
 * Arguments    : str - String player passed as an argument to the
 *                      command verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_push(string str)
{
    string verb,
           stone,
           wall;

  /* Fail if player didn't supply an argument. */
    if (!str || !strlen(str))
        return 0;

    verb = query_verb();

  /* Can't push what you can't see. */
    if (!CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("It is too dark to see.\n");
        return 0;
    }

    notify_fail(capitalize(verb) + " which stone on which wall?\n");

  /* Fail if we can't get a syntax match. */
    if (!parse_command(str, TP, 
        "[the] %w 'block' / 'stone' [from] [the] [bottom] / [floor] " +
        "[on] / [of] [the] %w 'wall'", stone, wall))
        return 0;

  /* If the stone argument supplied can't be turned into a */
  /* number, fail. */
    if (!intp(LANG_ORDW(stone)))
        return 0;

  /* Fail if we can't make sense of which wall the player */
  /* specified. */
    if (member_array(wall, walls) < 0)
    {
        notify_fail(capitalize(verb) + " the " + stone + " stone from " +
            "the bottom of which wall?\n");
        return 0;
    }

  /* Player has a valid stone and wall, but unless they are the */
  /* correct combination as determined by check_wall(), or if */
  /* the compartment is already in the room, nothing happens. */
    if (!check_stone(stone, wall) ||
        (compartment && present(compartment, TO)))
    {
        write("You " + verb + " the " + stone + " stone from the " +
            "bottom of the " + wall + " wall, but nothing happens.\n");
        say(QCTNAME(TP) + " presses on the a stone on one of the " +
            "walls.\n");
        return 1;
    }

  /* Looks like the player has the right stone combination, */
  /* and there's no compartment in the room, so clone it */
  /* in successfully. */
    write("You " + verb + " the " + stone + " stone from the " +
        "bottom of the " + wall + " wall. Nothing happens at first, " +
        "but slowly a portion of the floor gives way, revealing a " +
        "hidden compartment!\n");
    say(QCTNAME(TP) + " pushes on a stone on the wall. After a " +
        "moment, you hear a grinding sound, and a portion of the " +
        "floor drops away to reveal a hidden compartment!\n");
    seteuid(getuid());
    compartment = clone_object(OBJ + "compartment");
  /* Pass TP off to the compartment, so it can judge what */
  /* to place in the compartment. The ring it contains should */
  /* _only_ be present to players who have just finished the */
  /* Seer and the Lord Quest. */
    compartment->set_contents(TP);
    TP->add_prop(LIVE_I_SWORD_QUEST,
        TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_FOUND_PARCH |
        SWQ_FOUND_CHAR);
    compartment->move(TO);
    return 1;
}
