/* This object controls the army, influenced from this objects are only
 * platoons though.
 * 
 * This object must load platoons if they have stored data.
 */

#define TEST_DUMMY    "/d/Krynn/common/army/test_dummy"

inherit "/std/callout";

static object *platoons = ({});
static string *march_start_rooms;
static string *march_target_rooms;
string platoon_file;
string platoon_data_dir;
static int max_platoons = 4;
static int command_interval = 2880;
string *platoon_soldier_files;
static string *searched_rooms = 0;

/*prototype*/
int init_path_search(string start, string target, int id);


void
set_army_soldiers(string *str)
{
    platoon_soldier_files = str;
}

string
query_random_soldier_file()
{
    if (!platoon_soldier_files)
      return 0;

    return platoon_soldier_files[random(sizeof(platoon_soldier_files))];
}

void
set_platoon_file(string str)
{
    if (extract(str,-2) == ".c")
      platoon_file = extract(str,0,-3);
    else
      platoon_file = str;
}

void
set_max_platoons(int i)
{
    max_platoons = i;
}

void
set_platoon_data_dir(string str)
{
    platoon_data_dir = str + "/";
}

void
set_target_rooms(string *str)
{
    march_target_rooms = str;
}

void
set_start_rooms(string *str)
{
    march_start_rooms = str;
}


void
set_command_interval(int i)
{
    command_interval = (i * 120);
    /* convert to Krynnish hours! */
}

void
create_army()
{
}

nomask void
create()
{
    setuid();
    seteuid(getuid());
    create_army();
}

void
start_army()
{
    set_alarm(0.0, itof(command_interval),
	      "next_command");
}

mixed
get_platoon(int id)
{
    int i;
    int *ids = platoons->query_platoon_id();
    
    for(i=0;i<sizeof(ids);i++)
      if (ids[i] == id)
	return platoons[i];
}

int
add_platoon(mixed platoon)
{
    /* just add the the list */
    if (!platoons)
      platoons = ({});

    platoon->set_army(this_object());
    platoons += ({ platoon });
}

int
remove_platoon(object platoon)
{
    rm(platoon_data_dir + "pl" + (platoon->query_platoon_id()) + ".o");
    platoon->remove_object();
    platoons -= ({ 0 });
    if (!platoons || !sizeof(platoons))
      destruct();
}

object
new_platoon(int id)
{
    object ob = clone_object(platoon_file);
    ob->set_platoon_id(id);
    init_path_search(march_start_rooms[random(sizeof(march_start_rooms))],
		     march_target_rooms[random(sizeof(march_target_rooms))],
		     id);
    add_platoon(ob);
    return ob;
}

object
recover_platoon(int id)
{
    object ob = clone_object(platoon_file);
    ob->set_platoon_id(id);
    ob->recover_platoon();
    add_platoon(ob);
    return ob;
}


void
make_new_platoon()
{
    int *id_list = platoons->query_platoon_id();
    int i, id;
    string *dir = get_dir(platoon_data_dir + "*");

    /* Are there any platoon left to recover from file? */
    for(i=0;i<sizeof(dir);i++)
      {
	  if (sscanf(dir[i],"pl%d.o",id) != 1)
	    continue;
	  if (member_array(id,id_list) > -1)
	    continue;
	  recover_platoon(id);
	  break;
      }
    
    /* If not, create a new platoon */
    for(i=1;i<max_platoons;i++)
      if (member_array(id,id_list) == -1)
	new_platoon(id);
}

void
next_command()
{
    if (!platoons || !sizeof(platoons))
      make_new_platoon();
    else if (sizeof(platoons) < max_platoons && !random(10))
      make_new_platoon();
}

/* This function below initiates a search program that tries to find a 
 * path from a start_room to a target_room. When a path is found, the
 * function found_path(string *the_path) is called. That function should
 * then transmit this info to the platoon.
 */
void
found_path(string *the_path, string *path_cmds, int id)
{
    object platoon = get_platoon(id);

    find_living("aridor")->catch_msg("FOUND PATH\n");

    searched_rooms = 0;
    platoon->setup_platoon(platoon_data_dir+"pl" + id, id,
			   the_path[0],the_path[1..],path_cmds);
    platoon->start_platoon();
}

int
init_path_search(string start, string target, int id)
{
    if (searched_rooms)
      return -1;
    /*set_alarm(0.1,0.0,"init_path_search", start, target, id);*/
    searched_rooms = ({});
    set_alarm(0.0,0.0,"path_search",start,target,({}),({}),0,id);
    return 0;
}

void
path_search(string start, string target, string *the_path,
	    string *path_cmds, int depth, int id)
{
    string *rooms, *cmds;
    int i;
    object test;
    
    find_living("aridor")->catch_msg(start + "\n");
    if (member_array(start, searched_rooms) > -1)
      return;

    searched_rooms += ({ start });

    if (start == target)
      {
	  found_path(the_path + ({target}), path_cmds, id);
	  while(find_call_out("path_search") != -1)
	    remove_call_out("path_search");
	  return;
      }

    if (depth > 15)
      return;

    rooms = start->query_exit_rooms();
    cmds = start->query_exit_cmds();
    if (sizeof(rooms) > 2)
      {
	  i = random(sizeof(rooms));
	  rooms = rooms[(i+1)..(sizeof(rooms))] + rooms[0..i];
	  cmds = cmds[i+1..sizeof(cmds)] + cmds[0..i];
      }
    for(i=0;i<sizeof(rooms);i++)
      {
	  if (member_array(rooms[i], searched_rooms) > -1)
	    continue;

	  if (rooms[i] != "")
	    {
		set_alarm(0.1,0.0,"path_search",rooms[i],
			  target,the_path + ({ start }),
			  path_cmds + ({ cmds[i] }), depth+1,id);
	    }
	  else
	    {
		seteuid(getuid());
		(test = clone_object(TEST_DUMMY))->move_living("xx",start);
		find_living("aridor")->catch_msg("Cmd: " + cmds[i] + "\n");
		test->command(cmds[i]);
		set_alarm(0.1,0.0,"path_search",
			  file_name(environment(test)),
			  target,the_path + ({ start }),
			  path_cmds + ({ cmds[i] }), depth+1,id);
		test->remove_object();
	    }
      }
}
