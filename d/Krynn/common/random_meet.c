/*
 * created by Aridor 06/22/93 
 * get_random_room() added by Macker 01/11/94 
 *
 * some fixes and better error reporting in get_random_room()
 * by Milan 2.11.2000
 *
 * Pretty total rewrite by Cotillion 2002-08-01
 * Done to improve performance.
 *
 * The workings of this object are documented in:
 *  /d/Krynn/common/doc/general/random_objects
 *  /d/Krynn/common/doc/general/random_room
 */

#pragma strict_types
#pragma no_clone

#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include <language.h>

mapping table_cache;
string  *room_array,
        *recurse_queue;

int     addition_counter, random_room_counter;

#define TABLEPATH  ("/d/Krynn/common/rndtables/")
#define LOG(x)  (write_file("/d/Krynn/log/random_meet", ctime(time()) + \
                ": " + (x) + "\n"))

/*
 * The maximum depth get_random_room will recurse too in one go. 
 */
#define MAX_RECURSE_DEPTH        (3)     /* Depth to recurse in one go ? */
#define MAX_ADDS                 (300)   /* Max amount of files to add */

/*
 * Table Cache
 *
 * The table cache mapping contains entries like this:
 *
 * table_name : ({ file_time, percentage_sum, ({ "orc" , 10, "bar", ..}) })
 *
 * This allows us to quickly check if the table is up-to-date and then do
 * the random and scan on for the correct entry. 
 */
public void
create()
{
    setuid();
    seteuid(getuid());
    table_cache = ([ ]);
    room_array = ({ });
    recurse_queue = ({ });
    addition_counter = 0;
}

static void
load_table(string file)
{
    string *rows, data, index;
    int k, sum, val;
    mixed array;
    
    setuid();
    seteuid(getuid());

    if (!stringp(file))
	return;

    if (file_size(file) <= 0)
    {
	/* Corrupt Table File */
	LOG("Missing table file: " + file);
	return;
    }
    
    data = read_file(file);
    if (!strlen(data))
    {
	LOG("Empty table file: " + file);
	return;
    }
    
    rows = explode(data, "\n");
    rows = regexp(rows, "^[^#]");
    k = sizeof(rows);

    if (!k)
    {
	/* Empty Data File */
	LOG("Empty table file: " + file);
	return;
    }
    
    array = ({ });
    while (k--)
    {
	if (sscanf(rows[k], "%s %d", index, val) != 2)
	    continue;
	
	sum += val;
	array += ({ index, val });
    }
    
    table_cache[file] = ({ file_time(file), sum, array });
}

string
get_random_name(string table)
{
    mixed arr;
    int i, size, sum, target;

    table = (table[0..0] == "/" ? table : TABLEPATH + table);
    
    /* Is it in the table cache, and up to date? */
    if (!pointerp(arr = table_cache[table]) ||
	file_time(table) != arr[0])
    {
	load_table(table);

	if (!pointerp(arr = table_cache[table]))
	    return 0;
    }

    target = random(arr[1]);
    
    size = sizeof(arr[2]);
    
    while (i < size)
    {
	sum += arr[2][i + 1];

	if (sum > target)
	    return arr[2][i];

	i += 2;
    }
    return 0;
}


public object
get_random_clone(string table)
{
    object ob;
    string file;

    setuid();
    seteuid(getuid());
    
    file = get_random_name(table);

    if (!file)
    {
	/* No such table */
	return 0;
    }

    if (LOAD_ERR(file) || !objectp(ob = clone_object(file)))
    {
	LOG(file + " does not load (" + table + ")");
	return 0;
    }

    return ob;
}

static void
process_directory(string path, int depth)
{
    string *entries, *ignore, data;
    int k;
    
    /* Don't process dirs without .marker */
    if (file_size(path + ".marker") < 0)
	return;

    
    data = read_file(path + ".marker");
    if (!data)
	ignore = ({ });
    else
	ignore = explode(data, "\n");
    
    entries = get_dir(path);
    entries -= ignore + ({ "..", ".", ".marker" });

    if (!(k = sizeof(entries)))
	return;

    while (k--)
    {
	if (file_size(path + entries[k]) == -2 &&
	    file_size(path + entries[k] + "/.marker") >= 0)
	{
	    if (member_array(path + entries[k] + "/", room_array) >= 0)
		continue;
	    
	    if (depth >= MAX_RECURSE_DEPTH ||
		addition_counter >= MAX_ADDS)
	    {
		recurse_queue += ({ path + entries[k] + "/" });
		continue;
	    }

	    room_array += ({ path + entries[k] + "/" });
	    process_directory(path + entries[k] + "/", depth + 1);
	    continue;
	}
	
	if (entries[k][-2..-1] == ".c")
	{
	    room_array += ({ path + entries[k] });
	    addition_counter++;
	}
    }
}

public string
get_random_room(string path)
{
    int i;
    string *tmp, room;

    addition_counter = 0;
    
    if (!stringp(path))
	return 0;
    
    if (file_size(path) != -2)
    {
	LOG("get_random_room called for file: " + path);
	return 0;
    }

    if (path[-1..-1] != "/")
	path += "/";
    
    if (member_array(path, room_array) < 0)
    {
	/*
	 * New path, let's recurse. 
	 */
	room_array += ({ path });
	process_directory(path, 0);
    } else {
	if (sizeof(tmp = regexp(recurse_queue, "^" + path + ".*")))
	{
	    filter(tmp, &process_directory(, 1));
	    recurse_queue -= tmp;
	}
    }

    random_room_counter++;
    
    tmp = regexp(room_array, "^" + path + ".*..c");
    if (!sizeof(tmp))
	return 0;

    i = 3;
    while (i--)
    {
	room = tmp[random(sizeof(tmp))];
	if (!LOAD_ERR(room) && room->query_prop(ROOM_I_IS))
	    return room;
	
	tmp -= ({ room });
	room_array -= ({ room });
    }

    LOG("get_random_room Returned NO results for: " + path);
    return 0;
}

/*
 * Let's provide some wiz information just for fun
 */ 
public string
stat_object()
{
    string *idx;
    int i, k, x;
    mixed a;
    
    string str = "";

    /* Random Table Part */
    
    str += "There are " + LANG_WNUM(m_sizeof(table_cache)) +
	" random tables loaded.\n";

    idx = m_indexes(table_cache);
    sort_array(idx);

    i = -1;
    k = sizeof(idx);

    while (++i < k)
    {
	a = table_cache[idx[i]];
	str += idx[i] + " (" + ctime(a[0]) + ")\n";
	
	x = sizeof(a[2]);

	while (x)
	{
	    x -= 2;
	    
	    str += sprintf("   %60-s %2d%%\n",
		a[2][x],
		a[2][x + 1] * 100 / a[1]);
	}

	str += "\n";
    }

    str += "There are " + sizeof(room_array) + " rooms in the " +
	"database.\n";
    str += "There are " + LANG_WNUM(sizeof(recurse_queue)) + " directories " +
	"in the queue.\n";
    str += "There has been " + random_room_counter + " random room queries.\n";
    
    return str;
}

/*
 * Old API, still here for now.
 */
public object
get_a_monster(string file)
{
    return get_random_clone(file);
}

public string
get_a_monster_name(string table)
{
    return get_random_name(table);
}
