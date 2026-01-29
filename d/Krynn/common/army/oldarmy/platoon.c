/* This controls a platoon of npcs. Each platoon has one tent and consists
 * of max. 6 npcs. A platoon will walk around as a team.
 *
 * created by Aridor, 07/15/95
 *
 * A platoon must save its data! There must be a special dir for each army
 * where such data is stored.
 */
//#pragma no_clone

#include <ss_types.h>

//inherit "/std/object";

static object leader;
static object *soldiers = ({}); /* all soldiers including leader */
static object *sentry = ({});   /* those soldiers who are sentries */
int packed = 0;
string current_platoon_room;
string *path_to_walk = ({});
string *path_rooms_to_walk = ({});
string walk_end_room;
static string save_dir;
static int platoon_id;
static object army;
int interval = 1200;
int max_troop_size = 5;
string save_file;

/*prototype*/
void select_leader();


void
setup_platoon(string sdir, int id, string start, string *path_rooms,
	      string *path)
{
    save_dir = sdir;
    platoon_id = id;
    path_to_walk = path;
    path_rooms_to_walk = path_rooms;
    current_platoon_room = start;
}

void
create_platoon()
{
}

nomask void
create_object()
{
    army = previous_object();
    create_platoon();
}

void
start_platoon()
{
    set_alarm(5.0,0.0,"next_action");
}

void
end_action()
{
    soldiers->set_aggressive(1);
}

void
replenish_troop()
{
    int i;

    if (!soldiers)
      soldiers = ({});

    i = max_troop_size - sizeof(soldiers);
    if (random(i))
      this_object()->new_soldier();
}

void
do_pack()
{
    sentry->release_from_guard_duty();
    leader->command("out");
    leader->command("pack tent");
    leader->command("take pack");
    packed = 0;
}

void
do_unpack()
{
    leader->command("set up tent");
    leader->command("enter tent");
    sentry->command("out");
    sentry->get_ready_for_guard_duty();
    packed = 1;
}

void
recalculate_route_to_target()
{
    /* prolly needs to call the search function in the army object */
}

void
walk_to_next_room()
{
    string *rooms;
    string next_cmd, next_room;
    int index;

    if (!leader)
      return;

    if (!packed)
      do_pack();

    if (!path_to_walk || !sizeof(path_to_walk))
      {
	  recalculate_route_to_target();
	  do_unpack();
	  return;
      }

    next_room = path_rooms_to_walk[0];
    path_rooms_to_walk = path_rooms_to_walk[1..];
    next_cmd = path_to_walk[0];
    path_to_walk = path_to_walk[1..];

/*    rooms = environment(leader)->query_exit_rooms();
    index = member_array(next_room,rooms);
    if (index == -1)
      recalculate_route_to_target();
    else
      leader->command((environment(leader)->query_exit())[index * 3 + 1]);
*/
    leader->command(next_cmd);
    
    do_unpack();
}

/* returns true if someone from the troop is currently fighting */
int
troop_is_fighting()
{
    mixed *fight = soldiers->query_attack();
    fight -= ({0});
    return sizeof(fight);
}

void
next_action()
{
    if (current_platoon_room == walk_end_room)
      {
	  set_alarm(5.0,0.0,"end_action");
	  return;
      }

    if (sizeof(soldiers) < max_troop_size)
      replenish_troop();
    if (!leader)
      select_leader();
    /* here is the part where the troop will move, and do stuff */
    if (leader && !troop_is_fighting())
      walk_to_next_room();

    set_alarm(itof(interval),0.0,"next_action");
}

int
query_platoon_id()
{
    return platoon_id;
}

void
set_army(object ob)
{
    army = ob;
}

/* give the number in Krynn hours */
void
set_action_interval(int i)
{
    interval = i * 120;
}

void
set_max_troop_size(int i)
{
    max_troop_size = i;
}

int
max_from_array(int *arr)
{
    int i,j;
    if (!arr || !sizeof(arr))
      return 0;

    j = arr[0];
    for(i=1;i<sizeof(arr);i++)
      if (arr[i] > j)
	j = arr[i];

    return j;
}

void
select_leader()
{
    int *dis = soldiers->query_stat(SS_DIS);
    int i, max = max_from_array(dis);

    if (!soldiers || sizeof(soldiers) < 3)
      return;
    if (leader)
      return;
    
    for(i=0;i<sizeof(dis);i++)
      if (dis[i] == max)
	break;

    leader = soldiers[i];
    //soldiers->set_leader(leader);
    for(i=0;i<sizeof(soldiers);i++)
      {
	  soldiers[i]->set_leader(leader);
	  leader->team_join(soldiers[i]);
      }

    if (!sentry)
      sentry = ({});
    sentry = soldiers[0..1];
    sentry -= ({leader});
    if (sizeof(sentry) < 2)
      sentry += ({soldiers[2]});
}

void
add_soldier(mixed npc)
{
    if (!objectp(npc))
      return;

    soldiers += ({ npc });
    leader = 0;
    select_leader();
}

void
remove_soldier(object npc)
{
    soldiers -= ({ npc });
}

void
new_soldier()
{
    object new;
    new = clone_object(army->query_random_soldier_file());
    new->move_living("xxx",current_platoon_room);
    add_soldier(new);
}

void
save_platoon()
{
    if (!save_file)
      return;
    save_object(save_file + platoon_id);
}

void
recover_platoon()
{
    restore_object(save_file + platoon_id);
}


object
query_leader()
{
    return leader;
}

object *
query_soldiers()
{
    return soldiers;
}

object *
query_sentry()
{
    return sentry;
}

string
query_current_room()
{
    return current_platoon_room;
}

string *
query_path_to_walk()
{
    return path_to_walk;
}

