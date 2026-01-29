/*
 * area_handler.c
 *
 * This object is documented separately and extensively in
 * /doc/man/objects/area_handler. 
 *
 * This is a copy of the area_handler from /lib with one
 * extension: It is possible to create 'line' objects such
 * as paths or roads which will connect in other directions
 * than n,s,w,e, too. Per default, NO obvious exits are
 * shown, except those of such 'line' objects. Be careful
 * when adding line objects, and make sure that no undesired
 * obvious exits are shown.
 */
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define ERRM	"# Error in area handler: "
#define AREA    "/d/Ansalon/common/area"
#define MAX_S	75
#define TP	this_player()
#define TO	this_object()

int	Timeout,	/* The Timeout of any room */
	Map_w,		/* The width of the map */
	Map_h,		/* The height of the map */
	Map_o,		/* The origins of the map */
        Map_init;	/* The map is read */
string	Mapfile,	/* The file containing the map */
    	Mapname,	/* The name of the map */
    	Roomdir,	/* The dir to put the rooms in */
	Trashcan,	/* The room to put trash in, if any */
        Areadir,	/* Generic room preamble, postamble dir */
        Lines_map;      /* List of the lines in this map */
mapping	Desc_map,	/* The map of descriptions. */
    	Bound_map;	/* The map of boundaries. */

/*
 * Prototypes.
 */
static int index(string str, string sstr);
static nomask string find_room(int x, int y);
static nomask int create_room(string room);
static nomask string get_map_symbol(int x, int y);
static nomask void del_rooms();
static nomask int *find_coords(int x, int y, string dir);

/*
 * create_area
 *
 * It's intended that this function should be masked by the user
 * of this object.
 */
public void
create_area()
{
}

/*
 * create_object
 *
 * This function defines some basic initalizations. Use create_area for
 * the area-specific initializtions.
 */
nomask void
create_object()
{
    if (IS_CLONE)
    {
	remove_object();
	return;
    }

    Areadir = AREA;
    Timeout = 30;
    Desc_map = ([]);
    Bound_map = ([]);
    Map_w = Map_h = Map_o = Map_init = 0;
    Trashcan = "";
    Mapfile = "";
    Mapname= "";
    Roomdir = "";
    obj_no_change = 0;
    obj_no_show = 0;

    create_area();
    seteuid(getuid());
}

/*
 * init_map
 *
 * Initialize the map from the Mapfile.
 */
static nomask int
init_map()
{
    int lno, i;
    string line, *map_arr;

    if (!strlen(Mapfile))
    {
	write(ERRM + "No map file registered.\n");
	return 0;
    }

    if (file_size(Mapfile + ".m") > 0)
    {
	if (file_time(Mapfile) < file_time(Mapfile + ".m"))
	{
	    line = read_file(Mapfile + ".m", 0, 1);
	    sscanf(line, "%d|%d|%d|%s|%s|%s\n", Map_w, Map_h, Timeout, Mapname, Roomdir, Areadir);
	    Map_o = strlen(line);
	    Map_init = 1;
	    Map_w--;
	    return 1;
	}
    }

    if (file_size(Mapfile) <= 0)
    {
	write(ERRM + "Map file is corrupt.\n");
	return 0;
    }

    lno = 0;
    map_arr = ({});
    do {
	line = read_file(Mapfile, lno, 1);
	if (strlen(line) && line[0..0] != "\n" && line[0..0] != "#")
	{
	    map_arr = ({ explode(line, "\n")[0] }) + map_arr;
	    Map_w = Map_w > strlen(line) ? Map_w : strlen(line);
	    Map_h++;
	}
	else if (strlen(line) >= 6 && line[0..5] == "#NAME ")
	    Mapname = explode(line[6..strlen(line)], "\n")[0];
	else if (strlen(line) >= 9 && line[0..8] == "#ROOMDIR ")
	    Roomdir = explode(line[9..strlen(line)], "\n")[0];
	else if (strlen(line) >= 9 && line[0..8] == "#AREADIR ")
	    Areadir = explode(line[9..strlen(line)], "\n")[0];
	else if (strlen(line) >= 9 && line[0..8] == "#TIMEOUT ")
	{
	    Timeout = atoi(explode(line[9..strlen(line)], "\n")[0]);
	    Timeout = Timeout < 10 ? 10 : Timeout > 120 ? 120 : Timeout;
	}
	else if (strlen(line) >= 10 && line[0..9] == "#TRASHCAN ")
	    Trashcan = explode(line[10..strlen(line)], "\n")[0];
	lno++;
    } while(strlen(line));
    Map_w++; /* Newline */

    if (!strlen(Mapname) ||
	!strlen(Roomdir) ||
	!strlen(Areadir))
    {
	write(ERRM + "Badly initialized map.\n");
	remove_object();
	return 0;
    }

    if (Map_w > MAX_S + 1 || lno > MAX_S)
    {
	if (Map_w > MAX_S + 1)
	    write(ERRM + "The map is too wide.\n");
	if (lno > MAX_S)
	    write(ERRM + "The map is too high.\n");
	remove_object();
	return 0;
    }
	
    rm(Mapfile + ".m");
    write_file(Mapfile + ".m", (Map_w + 1) + "|" + Map_h + "|" + Timeout + "|" + Mapname + "|" + Roomdir + "|" + Areadir + "\n");
    for (i = 0 ; i < Map_h ; i++)
	write_file(Mapfile + ".m", sprintf("%-" + (Map_w - 1) + "s\n", map_arr[i]));
    
    line = read_file(Mapfile + ".m", 0, 1);
    Map_o = strlen(line);
    Map_init = 1;
    del_rooms();
    return 1;
}

/*
 * get_map_symbol
 *
 * Read the map symbol from the modified map.
 */
static nomask string
get_map_symbol(int x, int y)
{
    string rval;
    rval = read_bytes(Mapfile + ".m", Map_o + Map_w * y + x, 1);
    return rval;
}

/*
 * enter_map
 *
 * Enter the map through an entry point.
 */
public nomask int
enter_map(string entryp)
{
    int i, len, pos, *new;
    string room, dir, line;

    if (entryp[0] < 'A' || entryp[0] > 'Z')
    {
	write(ERRM + "Trying to enter through map-location '" + entryp + "'\n");
	return 1;
    }

    dir = query_verb();

    if (!Map_init)
	if (!init_map())
	    return 1;

    for (i = 0 ; i < Map_h ; i++)
    {
	line = read_file(Mapfile + ".m", i + 2, 1);
	if ((pos = index(line, entryp)) >= 0)
	    break;
    }

    if (pos < 0)
    {
	write(ERRM + "Error in loading room, entry point '" + entryp + "' can't be found\n");
	return 1;
    }
    
    new = find_coords(pos, i, dir);
    room = find_room(new[0], new[1]);
    if (!strlen(room) || !create_room(room))
    {
	write(ERRM + "Error in loading room " + room + ", " + dir + " of entry point '" + entryp + "'\n");
	return 1;
    }

    TP->move_living(dir, Roomdir + "/" + room);
    return 1;
}

/*
 * move_in_map
 *
 * Move a player to a room in the map.
 */
public nomask int
move_in_map(string room)
{
    if (create_room(room))
	TP->move_living(query_verb(), Roomdir + "/" + room);
    else
	write(ERRM + "Can't load room '" + room + "'\n");
    return 1;
}

static nomask int
check_path_this_direction(string sym, string new_sym)
{
    string *str1 = 0, *str2 = 0;

    if (sym != " " && new_sym != " ")
      {
	  str1 = explode(Lines_map, sym + new_sym);
	  str2 = explode(Lines_map, new_sym + sym);
      }

    return ((str1 && sizeof(str1) > 1) || (str2 && sizeof(str2) > 1));
}

/*
 * create_room
 *
 * Create a room.
 */
static nomask int
create_room(string room)
{
    int i, j, x, y, num, *new;
    mixed desc;
    string exit_string, foo, dir, rmd, sym, new_sym, *my_exits = ({ }),
	   *dirs = ({ "north", "west", "south", "east" }),
           *dirs2 = ({ "northwest", "northeast", "southwest", "southeast" });

    if (file_size(Roomdir + "/" + room) > 0)
	return 1;
    
    rmd = Roomdir + "/" + room;
    sscanf(room, "%s.%d.%d.%s", foo, x, y, foo);

    foo = read_file(Areadir + "/preamble.c");
    write_file(rmd, foo);

    write_file(rmd, "    Master_ob = \"" + MASTER_OB(TO) + "\";\n");
    write_file(rmd, "    Timeout = " + (Timeout * 30) + ";\n");

    sym = get_map_symbol(x, y);
    desc = Desc_map[sym];
    if (!sizeof(desc))
    {
	rm(rmd);
	write(ERRM + "Can't find description for position: " +  x + ", " + y + " '" + sym + "'\n");
	return 0;
    }
    
    for (i = 0 ; i < 4 ; i++)
    {
	new = find_coords(x, y, dirs[i]);
	dir = find_room(new[0], new[1]);
	new_sym = get_map_symbol(new[0], new[1]);
	if (check_path_this_direction(sym, new_sym))
	  my_exits += ({ dirs[i] });
	if (strlen(dir))
	    if (dir[0] != '#')
		write_file(rmd, "    add_exit(\"\", \"" + dirs[i] + "\", \"@@move_in_map:" + MASTER_OB(TO) + "|" + dir + "@@\", " + desc[0][3] + ");\n");
	    else
		write_file(rmd, "    add_exit(\"" + dir[1..strlen(dir)] + "\", \"" + dirs[i] + "\", 0, " + desc[0][3] + ");\n");
    }

    if (sym[0] >= '0' && sym[0] <= '9')
      {
	  for(i=0; i<4; i++)
	    {
		new = find_coords(x, y, dirs2[i]);
		dir = find_room(new[0], new[1]);
		if (strlen(dir))
		  {
		      new_sym = get_map_symbol(new[0], new[1]);
		      if (check_path_this_direction(sym, new_sym))
			{
			    if (dir[0] != '#')
			      write_file(rmd, "    add_exit(\"\",\"" + dirs2[i] +
					 "\",\"@@move_in_map:" + MASTER_OB(TO) +
					 "|" + dir + "@@\"," + desc[0][3] + ");\n");
			    else
			      write_file(rmd, "    add_exit(\"" + dir[1..strlen(dir)] +
					 "\", \"" + dirs2[i] + "\", 0," + desc[0][3] + ");\n");
			    my_exits += ({ dirs2[i] });
			}
		  }
	    }
      }

    if (sizeof(my_exits))
      {
	  if (sizeof(my_exits) > 1)
	    {
		exit_string = "\\nThere are " + LANG_WNUM(sizeof(my_exits)) +
		  " obvious exits: ";
		for (i=1;i<sizeof(my_exits);i++)
		  exit_string += my_exits[i] + ", ";
	    }
	  else
	    exit_string = "\\nThere is " + LANG_WNUM(sizeof(my_exits)) +
	      " obvious exit: ";
	  exit_string += my_exits[0];
      }

    write_file(rmd, "\n    set_short(\"" + desc[1][0] + (exit_string ? "." + exit_string : "") + "\");\n");
    num = sizeof(desc[1]);
    i = random(num - 1, x + 1 * y + 1) + 1;
    write_file(rmd, "    set_long(\"" + desc[1][i] + (exit_string ? exit_string + "." : "") + "\\n\");\n\n");

    if (sizeof(desc[2]))
    {
	write_file(rmd, "\n");
	for (i = 0 ; i < sizeof(desc[2]) ; i += 2)
	{
	    if (pointerp(desc[2][0]))
	    {
		write_file(rmd, "    add_item(({ ");
		for (j = 0 ; j < sizeof(desc[2][0]) ; j++)
		    write_file(rmd, "\"" + desc[2][0][j] + "\", ");
		write_file(rmd, "}), \"" + desc[2][1] + "\\n\");\n");
	    }
	    else
		write_file(rmd, "    add_item(\"" + desc[2][0] + "\", \"" + desc[2][1] + "\\n\");\n");
	}
    }
    
    if (sizeof(desc[3]))
    {
	write_file(rmd, "\n");
	for (i = 0 ; i < sizeof(desc[3]) ; i++)
	    write_file(rmd, "    clone_object(\"" + desc[3][i] + "\")->move(TO, 1);\n");
	write_file(rmd, "\n    set_cleanup_time((120 * 30));\n");
    }
    else
	write_file(rmd, "\n    set_cleanup_time(" + (Timeout * 30) + ");\n");
    
    write_file(rmd, "\n    add_prop(ROOM_I_TYPE, " + desc[0][0] + ");\n");
    write_file(rmd, "    add_prop(ROOM_I_INSIDE, " + desc[0][1] + ");\n");
    write_file(rmd, "    add_prop(ROOM_I_LIGHT, " + desc[0][2] + ");\n");
    
    if (strlen(desc[4]))
	write_file(rmd, "\n    create_extra();\n");

    foo = read_file(Areadir + "/postamble.c");
    write_file(rmd, foo);
    return 1;
}

/* find_coords
 *
 * Find the coordinates of the room in the indicated direction
 * from the given coordinates.
 */
static nomask int *
find_coords(int x, int y, string dir)
{
    switch(dir)
      {
	case "s":
	case "south":
	case "se":
	case "southeast":
	case "sw":
	case "southwest":
	  y -= 1;
	  break;
	  
	case "n":
	case "north":
	case "ne":
	case "northeast":
	case "nw":
	case "northwest":
	  y += 1;
	  break;
      }
    switch(dir)
      {
	case "w":
	case "west":
	case "sw":
	case "southwest":
	case "nw":
	case "northwest":
	  x -= 1;
	  break;
	  
	case "e":
	case "east":
	case "se":
	case "southeast":
	case "ne":
	case "northeast":
	  x += 1;
	  break;
      }
    return ({x,y});
}

/*
 * find_room
 *
 * Find a room with the given coordinates. If the room isn't
 * created but does exist, create it.
 */
static nomask string
find_room(int x, int y)
{
    string rtype;

    /*
     * Trying to walk out of the map.
     */
    if (x < 0 || y < 0 || y >= Map_h ||	x >= Map_w)
	return "";

    rtype = get_map_symbol(x, y);

    /*
     * Empty space.
     */
    if (rtype == " ")
	return "";

    if (rtype[0] >= 'A' && rtype[0] <= 'Z')
	return "#" + Bound_map[rtype];
    else
	return Mapname + "." + x + "." + y + ".c";
}

/*
 * dispose_of
 *
 * Function called by the rooms to dispose of unwanted objects before
 * autodestruct.
 */
public nomask void
dispose_of(object ob)
{
    if (!strlen(Trashcan) || catch(ob->move(Trashcan, 1)))
	ob->remove_object();
}

/*
 * del_rooms
 *
 * Delete all old rooms.
 */
static nomask void
del_rooms()
{
    string *rooms;
    int i;

    rooms = get_dir(Roomdir + "/*");
    for (i = 0 ; i < sizeof(rooms) ; i++)
	if (rooms[i][0..(strlen(Mapname) - 1)] == Mapname)
	    call_other(Roomdir + "/" + rooms[i], "clean_up");
}

/*
 * index
 *
 * Find the lcoation of a string in another string.
 */
static nomask int
index(string str, string sstr)
{
    string *brk;

    brk = explode(str, sstr);

    if (sizeof(brk) > 1)
	return strlen(brk[0]);
    else if (str[0..(strlen(sstr) - 1)] == sstr)
	return 0;
    else if (str[(strlen(str) - strlen(sstr))..(strlen(str) - 1)] == sstr)
	return strlen(str) - 1;
    else
	return -1;
}

/*
 * set this and that.
 */
static nomask void
add_desc(string tag, mixed dlist)
{
    if (tag[0] >= 'A' && tag[0] <= 'Z')
    {
	write(ERRM + "Illegal map location symbol: '" + tag + "'.\n");
	return;
    }
    
    if (sizeof(dlist) < 4 || sizeof(dlist[0]) < 3)
    {
	write(ERRM + "Wrong number of arguments to add_desc for tag '" + tag + "'\n");
	return;
    }

    if (sizeof(dlist[0]) == 3)
	dlist[0] += ({ 1 });
    else if (dlist[0][3] <= 0)
	dlist[0][3] = 1;
    Desc_map[tag] = (dlist + ({ "" }));
}

static nomask void
add_bound(string tag, string room)
{
    if (tag[0] < 'A' || tag[0] > 'Z')
    {
	write(ERRM + "Illegal map boundary symbol: '" + tag + "'.\n");
	return;
    }
    
    Bound_map[tag] = room;
}

public nomask void
add_line(string *tags)
{
    string str;
    if (!tags || !sizeof(tags))
      {
	  write(ERRM + "Illegal map line array: '" + tags + "'.\n");
	  return;
      }
    
    if (!Lines_map)
      Lines_map = " ";
    
    str = implode(tags, "");
    Lines_map += (str + " ");
}

public nomask void
add_linev(string tags)
{
    string str;
    if (!tags || !stringp(tags))
      {
	  write(ERRM + "Illegal map line string: '" + tags + "'.\n");
	  return;
      }
    
    if (!Lines_map)
      Lines_map = " ";
    
    Lines_map += (tags + " ");
}

static nomask void
set_map(string map)
{
    Mapfile = map;
}

 
