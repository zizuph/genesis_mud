inherit "/d/Emerald/std/emerald_monster";

#include "../defs.h"
#include "/d/Genesis/login/login.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define MOVE_INTERVAL (rnd() * 2.0)

public string dest_dock;

public string traveller_act(int combat);
public int move_alarm = 0;

public void
create_traveller()
{
    string race;
    mapping attr_map = ([]);
    string *attrs, *categories;
    int attrnum = 2;
    int *raceattrs, height, weight, appearance, volume;

    race = ({ "elf", "gnome", "human", "dwarf" })[random(4)];
    set_race_name(race);

    /* Set up some random adjectives, choosing from the same set a player
     * does in the character creation sequence.
     */
    setuid();
    seteuid(getuid());
    attr_map = LOGIN_FEATURES->query_features();

    switch (race)
    {
        case "elf":
            // elves never have beards
            attr_map = m_delete(attr_map, "beard");
            break;
        case "dwarf":
            // dwarves always have beards
            attrs = attr_map["beard"];
            if (sizeof(attrs))
            {
                set_adj(attrs[random(sizeof(attrs))]);
                attrnum--;
            }

            attr_map = m_delete(attr_map, "beard");
            break;
        default:
            break;
    }

    while (attrnum-- > 0)
    {
        categories = m_indices(attr_map);
        if (!sizeof(categories))
        {
            break;
        }

        attrs = attr_map[categories[random(sizeof(categories))]];
        if (!sizeof(attrs))
        {
            continue;
        }

        add_adj(attrs[random(sizeof(attrs))]);
    }

    // Get the standard race properties
    raceattrs = RACEATTR[race] || RACEATTR["human"];

    // Height varies by +-1/3
    height = raceattrs[0];
    height += random(height / 3) - random(height / 3);
    add_prop(CONT_I_HEIGHT, height);

    // Weight varies by +-1/3
    weight = raceattrs[1] * 1000;
    weight += random(weight / 3) - random(weight / 3);
    add_prop(CONT_I_WEIGHT, weight);

    // Opinion is race standard
    set_opinion(raceattrs[2]);
    
    // Appearance varies by +-1/10
    appearance = raceattrs[3];
    appearance += random(appearance / 10) - random(appearance / 10);
    set_appearance(appearance);

    // Volume varies proportional to weight
    volume = raceattrs[4] * 1000;
    volume = (100 * weight / (raceattrs[1] * 1000) * volume / 100);
    add_prop(CONT_I_VOLUME, volume);

    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 1, 0 }));
}

nomask void
create_emerald_monster()
{
    set_act_time(8 + random(5));
    add_act(&traveller_act(0));
    set_cact_time(8 + random(5));
    add_cact(&traveller_act(1));

    create_traveller();
}

public mixed
traveller_act(int combat)
{
    object env = environment();
  
    if (!env)
    {
        return "";
    }

    if (!combat)
    {
        if (present("ticketing_agent", env) && !random(8))
        {
            return "ask agent question";
        }
    
        if (env->query_pavilion_room())
        {    
            return "emote studies the schedule";
        }
    
        return ({ "emote paces back and forth",
                  "say I hope the ship is on time", })[random(2)];
    }
    else
    {
        return "panic";
    }
}

public void
set_destination_dock(string dest)
{
    dest_dock = dest;
}

/*
 * Function name: start_wander_pavilion
 * Descrption:    Make the traveller wander
 */
public void
start_wander_pavilion()
{
    set_monster_home(DOCK_DIR + "clone_handler");
    set_random_move(15 + random(10));
    set_restrain_path(DOCK_DIR + "pav*");
}

/*
 * Function name: stop_wander_pavilion
 * Description:   Disable wandering
 */
public void
stop_wander_pavilion()
{
    set_monster_home(0);
    set_random_move(0);
}

/*
 * Function name: startup
 * Description:   Do some additional initialization that might not always
 *                be preferred.
 */
public void
startup()
{
    set_destination_dock(({ TEREL_LINE,
                            SPARKLE_LINE,
                            AVENIR_LINE,
                            FAERIE_LINE })[random(4)]);
    setuid();
    seteuid(getuid());
    SHIP_MGR->register(this_object());

    start_wander_pavilion();
}

/*
 * Function name: board_ship
 * Description:   Attempt to board a ship
 */
public void
board_ship()
{
    object env = environment();
    object ship;

    setuid();
    seteuid(getuid());

    if (ship = present(SHIP_MGR->query_ship(dest_dock), env))
    {
        MONEY_EXPAND(this_object());
        command("buy ticket");
        MONEY_CONDENSE(this_object());
        command("board " + OB_NAME(ship));

        trig_new("%s 'leaves' [the] %s", "trig_leave");
    }
}

/*
 * Function name: disembark
 * Description:   Cause the traveller to leave the ship
 */
public void
disembark()
{
    command("exit ship");
    remove_object();
}

public void
trig_leave(string who, string what)
{
    if (environment(this_object())->query_ship()->query_board_enabled())
    {
    	trig_delete("%s 'leaves' [the] %s");
    	set_alarm(itof(random(3) + 1), 0.0, disembark);
    }
}


/*
 * Function name: ship_arrived
 * Description:   Called by the dock room, this tells us that the ship
 *                has arrived.
 */
public void
ship_arrived()
{
    // Delay slightly and board
    set_alarm(itof(random(5) + 2), 0.0, board_ship);
}

/*
 * Function name: walk
 * Description:   Try to walk in a given direction
 * Arguments:     (string) The direction to walk
 * Returns:       1 - npc moved
 *                0 - npc did not move
 */
public int
walk(string dir)
{
    object *doors;
    object env = environment();
    int i;

    // Check to see if we need to open a door along the way
    doors = env->query_prop(ROOM_AO_DOOROB);
    for (i = 0; i < sizeof(doors); i++)
    {
        if (doors[i]->query_door_exit_direction() == dir)
        {
            command("open " + OB_NAME(doors[i]));
            break;
        }
    }

    // Use the exit
    command(dir);

    return (env != environment());
}

/*
 * Function name: move_toward_dest
 * Description:   Move this npc toward the given dock.
 * Arguments:     (string) The name of the dock
 */
public void
move_toward_dest(string dest)
{
    string next;
    mixed *exit_info;
    int i;
    
    if (!strlen(dest))
    {
        return;
    }

    // Find the name of the next room on the way to the dock
    setuid();
    seteuid(getuid());
    next = DIRECTION_MGR->query_next_room(this_object(), dest);

    if (!strlen(next))
    {
        if (environment()->query_ceral_dock())
        {
            // We must have arrived at the dock
            board_ship();
        }
        else
        {
            /* At a dead end or back in the pavilion.  Either way, start
             * wandering again.
             */
            start_wander_pavilion();
        }

        return;
    }

    // Find which exit leads to the next room
    exit_info = environment()->query_exit();
    for (i = 0; i < sizeof(exit_info); i += 3)
    {
        if (wildmatch("*" + next, exit_info[i]))
        {
            // Try to use the exit
            if (walk(exit_info[i + 1]))
            {
                // Pause, then try to move again
                move_alarm =
                    set_alarm(MOVE_INTERVAL, 0.0, &move_toward_dest(dest));
                return;
            }
            else
            {
            }
        }
    }

    // We've come to a dead end
    move_alarm = set_alarm(MOVE_INTERVAL, 0.0, &move_toward_dest("pavil"));
}

/*
 * Function name: start_boarding
 * Description:   Use this to start the sequence that causes this npc
 *                to move toward the given dock and board the ship.
 * Arguments:     (string) The name of the dock
 */
public void
start_boarding(string dock = dest_dock)
{
    string dest;

    if (!strlen(dock))
    {
        return;
    }

    stop_wander_pavilion();

    switch (dock)
    {
        case TEREL_LINE:
            dest = "terel";
            break;
        case FAERIE_LINE:
            dest = "faerie";
            break;
        case AVENIR_LINE:
            dest = "avenir";
            break;
        case SPARKLE_LINE:
            dest = "sparkle";
            break;
    }

    if (move_alarm && get_alarm(move_alarm))
    {
	remove_alarm(move_alarm);
    }

    move_alarm = set_alarm(MOVE_INTERVAL, 0.0, &move_toward_dest(dest));
}

/*
 * Function name: ship_docked
 * Description:   Called by SHIP_MGR to tell us that a ship has docked.
 * Arguments:     (string) The name of the shipline
 */
public void
ship_docked(string line)
{
    if (line == dest_dock)
    {
        start_boarding();
    }
}
