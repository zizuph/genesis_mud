inherit "/d/Rhovanion/lib/room";

#include <macros.h>
#include <stdproperties.h>

#define RELATIVE_DIR    ({"forward","rightforward", \
                          "right","rightbackwards", \
                          "backwards","leftbackwards", \
                          "left","leftforward"})
#define SHORT_RELATIVE_DIR  ({"ff","rf","rr","rb","bb","lb","ll","lf"})
#define STD_DIR     ({"north","northeast","east","southeast", \
                      "south","southwest","west","northwest"})

#define	MAPSERVER_OFFSET	"_mapserver_offset"

#define VBFC_ME_P(x,y) "@@"+x+":"+file_name(this_object())+"|"+y+"@@"

/*
 * Global variables
 */
string name, *map, *paths, *show;
int xx, yy, check;

/*
 * Prototypes
 */
nomask void
add_exits();

/*
 * Function name: on_map
 * Description:	  Test if this room is on map
 * Argument:	  x,y - coordinates of room
 * Returns:	  1 if it is on map    else 0
 */
int
on_map(int x, int y)
{
  if(map[y][x..x] != " ") return 1;
  return 0;
}

/*
 * Function name: reset_map_room
 * Description:	  Called from reset_room
 * Argument:	  where - letter from the map corresponding to this room
 * Usage:         redefine this instead of reset_room. Place sensitivity
 *                allows different results on different places.
 */
void
reset_map_room(string where){}

/*
 * Function name: create_map_room
 * Description:	  Called when room is created
 * Usage:         when you want to add some special things like exits
 *                Is meant to be used when you write specific map-x-y
 *                file.
 */
void
create_map_room(){}

/*
 * Function name: set_up_room
 * Description:	  Called when room from map is created
 * Argument:	  where - letter from the map corresponding to this room
 * Usage:         Here you should set things like descriprions, items,
 *                properties etc for your room.
 */
void
set_up_room(string where){}

/*
 * Function name: path_desc_start
 * Description:	  Gives additional text for path. Whole text showing paths:
 *                path_desc_start() + directions + path_desc_end() + "."
 * Argument:	  where - letter from the map corresponding to this room
 * Note:          If you dont call function add_exits() then you have
 *                relative exits, else standard exits (n,ne,e,se,s,sw,w,nw)
 *                If you want relative exits then you must NOT have any
 *                of those standard exits. You can have other like 
 *                (up,down,tree,whatever...)
 */
string
path_desc_start(string where)
{
  return "Path goes ";
}

/*
 * Function name: path_desc_end
 * Description:	  Gives additional text for path. Whole text showing paths:
 *                path_desc_start() + directions + path_desc_end() + "."
 * Argument:	  where - letter from the map corresponding to this room
 */
string
path_desc_end(string where)
{
  return "";
}

string
neighbour_desc_start(string where)
{
  return "You see something to the ";
}

string
neighbour_desc_end(string where)
{
  return "";
}

/*
 * Function name: player_is_lost
 * Description:	  Test if player lost directions
 * Argument:	  who - object living
 * Returns:	  1 if lost,  0 if knows directions
 */
int
player_is_lost(object who, string where)
{
  return 0;
}

/*
 * Function name: query_file_with_map
 * Description:	  This function is necessary to redefine
 * Returns:	  Should return string or object that defines function
 *                string *map()  (actual map of the area)
 */
mixed
query_file_with_map()
{
  return 0;
}

/*
 * Function name: query_paths
 * Returns:	  Should return array of letters representing paths on map
 */
string *
query_paths()
{
  return ({ });
}

/*
 * Function name: query_show
 * Returns:	  Should return array of letters we want to see when around
 */
string *
query_show()
{
  return ({ "p" });
}

nomask string *
get_local_map(int x, int y)
{
  string str, *mmm;
  int i, j, size, len;
  mixed file;

  if(!(file = query_file_with_map()))
    return ({ "   ","   ","   " });

  mmm = ({ });
  size = sizeof(file->map());
  for(i=y-1; i<y+2; i++)
    if((i < 0) || (i > size-1))
      mmm += ({"   "});
    else
    {
      str = "";
      len = strlen(file->map()[i]);
      for(j=x-1; j<x+2; j++)
        if((j < 0) || (j > len-1))
          str += " ";
        else
          str += file->map()[i][j..j];
      mmm += ({ str });
    }
  return mmm;
}

nomask void
create_room()
{
  string str, *list;

  if(!paths) paths = query_paths();
  if(!show) show = query_show();

  list = explode(MASTER, "/");
  str = list[sizeof(list)-1];
  name = explode(str, "-")[0];

  set_short("Forgotten room");
  set_long("Someone forgot to set_up_room. Please make 'bug' report.\n");

  if(sscanf(MASTER, "%s/"+name+"-%d-%d", str, xx, yy) == 3)
  {
    if(!map) map = get_local_map(xx, yy);
    if(on_map(1,1))
    {
      check = 1;
      set_up_room(map[1][1..1]);
    }
    else
    {
      set_short("BUG");
      set_long("BUG! This room is not at map! Please call wizard for help.\n");
      return;
    }
  }
  else
  {
    set_short("BUG");
    set_long("BUG! This room is not at map! Please call wizard for help.\n");
    return;
  }
  create_map_room();
}

void
reset_room()
{
  reset_map_room(map[1][1..1]);
}

/*
 * Function name: load_map_room
 * Description:	  Loads room if necessary
 * Argument:	  x,y - coordinates of room
 * Returns:	  pointer to room
 */
nomask object
load_map_room(int x, int y)
{
    object room;
    string file, path, *list;

    sscanf(MASTER, "%s/"+name+"-%s", path, file);
    file = sprintf("%s/"+name+"-%d-%d", path, x, y);
    room = find_object(file);
    if (room)
	return room;
    setuid();
    seteuid(getuid());
    if (file_size(file + ".c") >= 0)
	file->teleledningsanka();
    else {
        list = inherit_list(this_object());
	write_file(file + ".c", "inherit \""+list[sizeof(list)-2]+"\";\n");
	file->teleledningsanka();
	rm(file + ".c");
    }
    return find_object(file);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (find_call_out("clean_up") < 0)
	call_out("clean_up", 10);
}

void
enter_inv(object ob, object from)
{
    int offset;
    int oldx, oldy;
    string dummy;

    ::enter_inv(ob, from);
    remove_call_out("clean_up");

    if (!living(ob) || !from)
	return;

    /*
     * Paranoia, this isn't a mapserver room!
     */
    if (!check)
	return;

    if (sscanf(MASTER_OB(from), "%s/"+name+"-%d-%d", dummy, oldx, oldy) != 3) {
	offset = random(8);
	ob->add_prop(MAPSERVER_OFFSET, offset);
	return;
    }

    if     ((xx == oldx)   && (yy == oldy-1))   /* f */
	offset = 0;
    else if((xx == oldx+1) && (yy == oldy-1))   /* fr */
	offset = 1;
    else if((xx == oldx+1) && (yy == oldy))     /* r */
	offset = 2;
    else if((xx == oldx+1) && (yy == oldy+1))   /* br */
	offset = 3;
    else if((xx == oldx)   && (yy == oldy+1))   /* b */
	offset = 4;
    else if((xx == oldx-1) && (yy == oldy+1))   /* bl */
	offset = 5;
    else if((xx == oldx-1) && (yy == oldy))     /* l */
	offset = 6;
    else if((xx == oldx-1) && (yy == oldy-1))   /* fl */
	offset = 7;

    if(player_is_lost(this_player(), map[1][1..1]))
      offset += random(8);

    offset %= 8;

    ob->add_prop(MAPSERVER_OFFSET, offset);
}

nomask int
standard_offset(string direction)
{
  int i;

  for(i=0; i < 8; i++)
    if(direction == RELATIVE_DIR[i])
      return i;
  for(i=0; i < 8; i++)
    if(direction == SHORT_RELATIVE_DIR[i])
      return i;
  for(i=0; i < 8; i++)
    if(direction == STD_DIR[i])
      return i;
  return -1;
}

nomask int *
delta(int offset)
{
  int deltax, deltay;

  switch (offset)
  {
	case 0:
            deltax = 0;
	    deltay = -1;
	    break;
	case 1:
	    deltax = 1;
	    deltay = -1;
	    break;
	case 2:
	    deltax = 1;
            deltay = 0;
	    break;
	case 3:
	    deltax = 1;
	    deltay = 1;
	    break;
	case 4:
            deltax = 0;
	    deltay = 1;
	    break;
	case 5:
	    deltax = -1;
	    deltay = 1;
	    break;
	case 6:
	    deltax = -1;
            deltay = 0;
	    break;
	case 7:
	    deltax = -1;
	    deltay = -1;
	    break;
  }
  return ({ deltax, deltay });
}

nomask object
exit_room(string off)
{
  int offset;
  string dummy;

  offset = atoi(off);
  return load_map_room(xx + delta(offset)[0], yy + delta(offset)[1]);
}

nomask void
add_exits()
{
  int i;

  for(i=0; i < 8; i += 2)
    if(on_map(1+delta(i)[0],1+delta(i)[1]))
      add_exit(VBFC_ME_P("exit_room",i), STD_DIR[i]);

  for(i=1; i < 8; i += 2)
    if( on_map(1+delta(i)[0],1+delta(i)[1]) &&
       !on_map(1,1+delta(i)[1]) && !on_map(1+delta(i)[0],1) )
      add_exit(VBFC_ME_P("exit_room",i), STD_DIR[i]);
}

nomask object
find_room(string direction)
{
    int offset, deltax, deltay;

    if (!check)
	return 0;

    offset = standard_offset(direction);
    if(offset == -1) return 0;
    offset += this_player()->query_prop(MAPSERVER_OFFSET);
    offset %= 8;

    deltax = delta(offset)[0];
    deltay = delta(offset)[1];

    if (!on_map(1+deltax,1+deltay))
	return 0;

    return load_map_room(xx + deltax, yy + deltay);
}

nomask string
exist_room(int offset)
{
    int deltax, deltay;

    if (!check)
	return " ";

    offset += this_player()->query_prop(MAPSERVER_OFFSET);
    offset %= 8;

    deltax = delta(offset)[0];
    deltay = delta(offset)[1];

    return map[1+deltay][1+deltax..1+deltax];
}

public string
exits_description()
{
  string fix_show, ex = "";
  mixed *exits, *neigh_exits, *neighbours = ({ });
  int i, j, poff;

    if(check)
    {
      poff = this_player()->query_prop(MAPSERVER_OFFSET);
      if(member_array(map[1][1..1], paths) != -1)
      {
	exits = query_exit_cmds();
        if (!pointerp(exits))
          exits = ({ });

        if(sizeof(exits & STD_DIR))
	{
          exits = ({ });
	  for(i=0; i < 8; i++)
	  {
	    if(member_array(exist_room(i+8-poff), paths) != -1)
	      if((i % 2) == 0)
	        exits += ({ STD_DIR[i] });
	      else if((exist_room((i+9-poff) % 8) == " ") &&
	              (exist_room((i+7-poff) % 8) == " "))
	        exits += ({ STD_DIR[i] });
	  }
	  for(i=0; i < 8; i++)
            neighbours += ({ exist_room(i+8-poff) });
          for(i=0; i<sizeof(show); i++)
            if(member_array(show[i], neighbours) != -1)
            {
              neigh_exits = ({ });
              for(j=0; j<8; j++)
                if(neighbours[j] == show[i])
                  neigh_exits += ({ STD_DIR[j] });
	      if (sizeof(neigh_exits)) 
	      {
                fix_show = show[i];
	        ex += neighbour_desc_start(fix_show) + neigh_exits[0];
	        if (sizeof(exits) > 1)
	        {
	          for (i = 0; i < sizeof(neigh_exits) - 1; i++ )
	            ex += ", " + neigh_exits[i];
	          ex += " and " + neigh_exits[i];
	        }
	        ex += neighbour_desc_end(fix_show) + ".\n";    
	      }
            }
	  if (sizeof(exits)) 
	  {
	    ex += path_desc_start(map[1][1..1]) + exits[0];
	    if (sizeof(exits) > 1)
	    {
	      for (i = 0; i < sizeof(exits) - 1; i++ )
	        ex += ", " + exits[i];
	      ex += " and " + exits[i];
	    }
	    ex += path_desc_end(map[1][1..1]) + ".\n";    
	  }
          return ex + ::exits_description();
	}
	exits = ({ });

	for(i=0; i < 8; i++)
	{
	  if(member_array(exist_room(i), paths) != -1)
	    if(((poff + i) % 2) == 0)
	      exits += ({ RELATIVE_DIR[i] });
	    else if((exist_room((i+1) % 8) == " ") &&
	            (exist_room((i+7) % 8) == " "))
	      exits += ({ RELATIVE_DIR[i] });
	}
	for(i=0; i < 8; i++)
          neighbours += ({ exist_room(i) });
        for(i=0; i<sizeof(show); i++)
          if(member_array(show[i], neighbours) != -1)
          {
            neigh_exits = ({ });
            for(j=0; j<sizeof(neighbours); j++)
              if(neighbours[j] == show[i])
                neigh_exits += ({ RELATIVE_DIR[j] });
	    if (sizeof(neigh_exits)) 
	    {
              fix_show = show[i];
	      ex += neighbour_desc_start(fix_show) + neigh_exits[0];
	      if (sizeof(exits) > 1)
	      {
	        for (i = 0; i < sizeof(neigh_exits) - 1; i++ )
	          ex += ", " + neigh_exits[i];
	        ex += " and " + neigh_exits[i];
	      }
	      ex += neighbour_desc_end(fix_show) + ".\n";    
	    }
          }
	if (sizeof(exits)) 
	{
	  ex += path_desc_start(map[1][1..1]) + exits[0];
	  if (sizeof(exits) > 1)
	  {
	    for (i = 0; i < sizeof(exits) - 1; i++ )
	      ex += ", " + exits[i];
	    ex += " and " + exits[i];
	  }
	  ex += path_desc_end(map[1][1..1]) + ".";
	}
	ex += "\n";
      }

      exits = query_exit_cmds();
      if (!pointerp(exits))
        exits = ({ });

      if(!sizeof(exits & STD_DIR))
      {
        if(!sizeof(neighbours))
	{
          for(i=0; i < 8; i++)
            neighbours += ({ exist_room(i) });
          for(i=0; i<sizeof(show); i++)
            if(member_array(show[i], neighbours) != -1)
            {
              neigh_exits = ({ });
              for(j=0; j<8; j++)
                if(neighbours[j] == show[i])
                  neigh_exits += ({ RELATIVE_DIR[j] });
	      if (sizeof(neigh_exits)) 
	      {
                fix_show = show[i];
	        ex += neighbour_desc_start(fix_show) + neigh_exits[0];
	        if (sizeof(exits) > 1)
	        {
	          for (i = 0; i < sizeof(neigh_exits) - 1; i++ )
	            ex += ", " + neigh_exits[i];
	          ex += " and " + neigh_exits[i];
	        }
	        ex += neighbour_desc_end(fix_show) + ".\n";    
	      }
            }
        }
        exits = ({ });
        for(i=0; i < 8; i++)
        {
          if(exist_room(i) != " ")
            if(((poff + i) % 2) == 0)
              exits += ({ RELATIVE_DIR[i] });
            else if((exist_room(((i+1) % 8)) == " ") &&
                    (exist_room(((i+7) % 8)) == " "))
              exits += ({ RELATIVE_DIR[i] });
        }
        if (!sizeof(exits))
	  return ex;

        if (sizeof(exits) == 1)
	  return ex + "There is one obvious exit: " + exits[0] + ".\n";

        ex += "There are " + LANG_WNUM(sizeof(exits)) +
	      " obvious exits: " + exits[0];
        for (i = 0; i < sizeof(exits); i++ )
	  ex += ", " + exits[i];

        return ex + ".\n";
      }
      for(i=0; i < 8; i++)
        neighbours += ({ exist_room(i+8-poff) });
      for(i=0; i<sizeof(show); i++)
        if(member_array(show[i], neighbours) != -1)
        {
          neigh_exits = ({ });
          for(j=0; j<8; j++)
            if(neighbours[j] == show[i])
              neigh_exits += ({ STD_DIR[j] });
	  if (sizeof(neigh_exits)) 
	  {
            fix_show = show[i];
	    ex += neighbour_desc_start(fix_show) + neigh_exits[0];
	    if (sizeof(exits) > 1)
	    {
	      for (i = 0; i < sizeof(neigh_exits) - 1; i++ )
	        ex += ", " + neigh_exits[i];
	      ex += " and " + neigh_exits[i];
	    }
	    ex += neighbour_desc_end(fix_show) + ".\n";    
	  }
        }
      return ex + ::exits_description();
    }
    return "";
}

void
init()
{
  ::init();
  call_out("init_more",0);
}

nomask void
init_more()
{
  string str;
  mixed *exits;
  int i, x, y, poff;

  exits = query_exit_cmds();
  if (!pointerp(exits))
    exits = ({ });

  poff = this_player()->query_prop(MAPSERVER_OFFSET);

  if (check)
    if (!sizeof(exits & STD_DIR))
      for(i=0; i < 8; i++)
      {
        if(exist_room(i) != " ")
          if(((poff + i) % 2) == 0)
          {
            add_action("normal_exit", RELATIVE_DIR[i] );
            add_action("normal_exit", SHORT_RELATIVE_DIR[i] );
          }
          else if((exist_room((i+1) % 8) == " ") &&
                  (exist_room((i+7) % 8) == " "))
          {
            add_action("normal_exit", RELATIVE_DIR[i] );
            add_action("normal_exit", SHORT_RELATIVE_DIR[i] );
          }
      }
}

nomask int
normal_exit(string arg)
{
    object ob, *team;
    string vb;
    int dir;

    vb = query_verb();
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (arg)  return 0;
    ob = find_room(vb);
    notify_fail("You cannot move in that direction after all.\n");
    if (!ob)  return 0;

    dir = standard_offset(vb);

    dir += this_player()->query_prop(MAPSERVER_OFFSET);
    dir %= 8;
    team = this_player()->query_team();
    if (sizeof(team))
	team = filter(team, "check_team", this_player());
    if (sizeof(team))
	this_player()->add_prop(TEMP_DRAGGED_ENEMIES, team);
    tell_room(ob, QCTNAME(this_player()) + " arrives.\n");
    this_player()->move_living("M", ob, 1);
    tell_room(this_object(), QCTNAME(this_player()) + " leaves @@from_dir:" +
	      file_name(this_object()) + "|" + dir + "@@.\n");
    return 1;
}

nomask string
from_dir(string arg)
{
    string dir, who;
    object ob;
    int n;

    n = atoi(arg);
    n -= previous_object(-2)->query_prop(MAPSERVER_OFFSET);
    if (n < 0)
	n += 8;
    if((-1 < n) && (n < 8))
      return RELATIVE_DIR[n];
    return "unexpectedly";
}
