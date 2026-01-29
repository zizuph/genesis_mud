/*
 * /waterdeep/control/patrol_obj.c
 * A controller object to make mobiles patrol along a set path
 *
 * Created by Brine, Feb 2021
 * ---------
 * CHANGELOG
 * ---------
 * 2021/08/01 Brine     Added movement, fixes to team logic
 */

 /* TODO:
 - domain-wide controller to pause/ restart, through register_patrol
 */

#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>

// prototypes
int do_move();
void make_team();

// internal properties
private object my_env;
private object team_leader;
private object *my_mobiles;
private string *my_path;
private string how_arrive_on_join = "arrives";
private int current_index = 0;
private int path_len;
private int reverse_direction = 0;
private int circular_path;
private float move_interval = 60.0; // seconds
private int my_alarm;

void
create_object()
{
    set_name(({ "object", "patrol_obj" }));
    set_adj("patrol");

    set_short("patrol_obj");
    set_long(
        "This object controls a patrol of NPCs. But tell me, how are you even "
        + "reading this?!?\n"
    );

    set_no_show();
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_S_WIZINFO, "An object for controlling NPC patrols\n");
}

/* Configuration */
void
register_patrol(string *path, object *mobiles, int circular = 0)
{
    // TODO: load rooms?
    my_env = find_object(path[0]);
    my_path = path;
    path_len = sizeof(path);
    my_mobiles = mobiles;
    circular_path = circular;
}

void
set_move_interval(float interval)
{
    move_interval = interval;
}

void
set_how_arrive_on_join(string how)
{
    how_arrive_on_join = how;
}

/* Team logic */
void
move_to_here(object mob)
{
    if (!present(mob, my_env))
    {
        tell_room(
            ENV(mob),
            "The " + mob->short() + " marches on along " + HIS_HER(mob)
                + " patrol route.\n",
            mob,
            mob
        );
        mob->move(my_env, 1);
        tell_room(
            my_env,
            CAP(LANG_ADDART(mob->query_nonmet_name()))
                + " " + how_arrive_on_join + ".\n",
            mob,
            mob
        );
    }
}

void
join_mobile(object mob)
{
    move_to_here(mob);

    if (team_leader)
        team_leader->team_join(mob);
    else
        make_team();
}

int
compare_avg_stat(object a, object b)
{
    return b->query_average_stat() - a->query_average_stat();
}

void
make_team()
{
    object *mobs_alive = FILTER_LIVE(my_mobiles);

    if (!sizeof(mobs_alive))
    return;

    sort_array(mobs_alive, compare_avg_stat);

    team_leader = mobs_alive[0];

    for (int i = 1; i < sizeof(mobs_alive); i++)
    {
        mobs_alive[0]->team_join(mobs_alive[i]);
    }
}

/* Movement logic */
void
start_patrol()
{
    if (my_mobiles && my_path)
    {
        my_alarm = set_alarm(move_interval, move_interval, &do_move());
    }
}

int
get_next_movement_index()
{
    if (circular_path)
        return (current_index == path_len - 1) ? 0 : current_index + 1;

    int should_reverse = (current_index == path_len - 1)
        || (current_index == 0 && reverse_direction);

    if (should_reverse)
        reverse_direction = !reverse_direction;

    return reverse_direction ? current_index - 1 : current_index + 1;
}

int
check_combat()
{
    foreach (object ob: FILTER_LIVE(my_mobiles))
    {
        if (ob->query_attack())
            return 1;
    }

    return 0;
}

int
do_move()
{
    // Is a member of the team in combat?
    if (check_combat())
        return 1;

    // Does the team have a leader?`
    if (!team_leader)
    {
        make_team();
        return 2;
    }

    // Move all members of team to the leader
    object* team = team_leader->query_team();
    foreach (object ob: team)
    {
        move_to_here(ob);
    }

    // Where should we move?
    int next_index = get_next_movement_index();
    string destination = my_path[next_index];

    // How should we move?
    string how_move = "heading further along their patrol route";
    object* exits = my_env->query_exit();
    int direction_index = member_array(destination, exits) + 1;

    if (direction_index && direction_index < sizeof(exits))
        how_move = "" + exits[direction_index];

    // Do the move
    team_leader->move_living(how_move, destination);
    my_env = find_object(destination);
    current_index = next_index;

    return 0;
}

void
reset_patrol()
{
    my_env = find_object(my_path[0]);
    current_index = 0;
    reverse_direction = 0;
}
