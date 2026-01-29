/*
 *  /d/Rhovanion/lib/mapserver.c
 *
 *  by Milan improving great idea of Hazelnut
 *
 *  This is tool for creating large areas using some sort of maps
 *  You should write your own server.c which inherits this one and 
 *  redefines functions below for your special purpose and taste.
 *  
 *  Vital function that you MUST redefine is query_file_with_map()
 *  It should return path to object or object that defines function
 *  string *map()  - this contains actual map of the area.
 *  Below look at functions that you may redefine.
 */


#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define RELATIVE_DIR    ({"forward","rightforward", \
                          "right","rightbackwards", \
                          "backwards","leftbackwards", \
                          "left","leftforward"})
#define SHORT_RELATIVE_DIR  ({"ff","rf","rr","rb","bb","lb","ll","lf"})
#define STD_DIR     ({"north","northeast","east","southeast", \
                      "south","southwest","west","northwest"})
#define SHORT_STD_DIR     ({"n","ne","e","se","s","sw","w","nw"})

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
nomask string
exist_room(int offset);

nomask int *
delta(int offset);


/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*            Some functions you may find useful                     */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/

/*
 * Function: add_exits
 *
 * This function must be called if you want to have standard exits.
 * Otherwise you will have relative exits.
 * 
 * Note: If you have defined any of standard exits (n,ne,e,se,s,sw,w,nw)
 *       in room relative exits will NOT be added.
 */
nomask void
add_exits();

/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*          Beginning of functions you should redefine               */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/

/*
 * Function name: on_map
 * Description:	  Test if this room is on map
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if it is on map    else 0
 * Note:          ALWAYS make " " return 0
 */
int
this_is_room(string arg)
{
  if(arg != " ") return 1;
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

/*
 * Function name: neighbour_desc_start
 * Description:	  Gives additional text depending on adjacent rooms.
 *                Whole text showing paths:  neighbour_desc_start() +
 *                + directions + neighbour_desc_end() + "."
 * Argument:	  from - letter from the map corresponding to this room
 *                to - letter from the map corresponding to adjacent
 *                        rooms
 */
string
neighbour_desc_start(string from, string to)
{
  return "You see something to the ";
}

/*
 * Function name: neighbour_desc_end
 * Description:	  Gives additional text depending on adjacent rooms.
 *                Whole text showing paths:  neighbour_desc_start() +
 *                + directions + neighbour_desc_end() + "."
 * Argument:	  from - letter from the map corresponding to this room
 *                to - letter from the map corresponding to adjacent
 *                        rooms
 */
string
neighbour_desc_end(string from, string to)
{
  return "";
}

/*
 * Function name: player_see_surrounding
 * Description:	  Test if player can see surrounding rooms
 * Argument:	  who - pointer to living
 * 	 	  from - letter from the map corresponding to this room
 *                to - letter from the map corresponding to adjacent
 *                        rooms
 */
int
player_see_surrounding(object who, string from, string to)
{
  if(from == to) return 0;
  return 1;
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
 *                These letters determine if there is extra description
 *                for surrounding rooms
 */
string *
query_show()
{
  return ({  });
}

/*
 * Function name: query_map_fatigue
 * Arguments:     here - string, character corresponding to room on map
 * Returns:	  How much tiring it is to move from here
 */
int
query_map_fatigue(string here)
{
  return 1;
}

/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*            End of functions you should redefine                   */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/

/*
 * Function name: on_map
 * Description:	  Test if this room is on map
 * Argument:	  x,y - coordinates of room
 * Returns:	  1 if it is on map    else 0
 */
nomask int
on_map(int x, int y)
{
  if(this_is_room(map[y][x..x])) return 1;
  return 0;
}

/*
 * Function name: query_room_letter
 * Returns:	  Gives letter corresponding with this room
 */ 
nomask string
query_room_letter()
{
  return map[1][1..1];
}

/*
 * Function name: query_next_room_letter
 * Arguments:	  who - object living to whom dirrection apply
 *                      (directions may be relative)
 *                direction - string with direction
 * Returns:	  Gives letter corresponding with this room
 */ 
nomask string
query_next_room_letter(object who, string direction)
{
  int i, relative, dir = -1;

  if(!check)
    return " ";

  if(member_array(direction, query_exit_cmds()) != -1)
  {
    dir = member_array(direction, STD_DIR);
    if(dir == -1)
      dir = member_array(direction, SHORT_STD_DIR);
  }
  else
  {
    relative = 1;
    dir = member_array(direction, RELATIVE_DIR);
    if(dir == -1)
      dir = member_array(direction, SHORT_RELATIVE_DIR);
  }
  if(dir == -1)
    return " ";

  if(relative)
  {
    dir += who->query_prop(MAPSERVER_OFFSET);
    dir %= 8;
  }
  return map[1+delta(dir)[1]][1+delta(dir)[0]..1+delta(dir)[0]];
}

/*********************************************************************/
/*********************************************************************/
/*                                                                   */
/*         End of functions you may find useful (I think ;)          */
/*                                                                   */
/*********************************************************************/
/*********************************************************************/

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
      set_long("BUG! This room is not on the map! Please call wizard for help.\n");
      return;
    }
  }
  else
  {
    set_short("BUG");
    set_long("BUG! This room is not on the map! Please call wizard for help.\n");
    return;
  }
  create_map_room();
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

nomask void
reset_room()
{
  int i, clean_up_is_set;
  mixed *calls = get_all_alarms();

    reset_map_room(map[1][1..1]);

  for (i = 0; i < sizeof(calls); i++)
    if(calls[i][1] == "clean_up")
      clean_up_is_set = 1;
  if (!clean_up_is_set)
    set_alarm(5.0, 0.0, "clean_up");
}

void
enter_inv(object ob, object from)
{
    int offset;
    int oldx, oldy;
    string dummy;

    ::enter_inv(ob, from);

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
      add_exit(VBFC_ME_P("exit_room",i), STD_DIR[i],0,
                                      query_map_fatigue(map[1][1..1]));

  for(i=1; i < 8; i += 2)
    if( on_map(1+delta(i)[0],1+delta(i)[1]) &&
       !on_map(1,1+delta(i)[1]) && !on_map(1+delta(i)[0],1) )
      add_exit(VBFC_ME_P("exit_room",i), STD_DIR[i],0,
                                      query_map_fatigue(map[1][1..1]));
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

string
full_neighbour_desc(int relative)
{
  string *neighbours, *neigh_exits, ex = "";
  int i,j,k,poff;

  poff = this_player()->query_prop(MAPSERVER_OFFSET);

  neighbours = ({ });
  for(i=0; i < 8; i++)
    if(relative)
      neighbours += ({ exist_room(i) });
    else
      neighbours += ({ exist_room(i+8-poff) });

  for(i=0; i<sizeof(show); i++)
    if((member_array(show[i], neighbours) != -1) &&
       player_see_surrounding(this_player(), map[1][1..1], show[i]))
    {
      neigh_exits = ({ });
      for(j=0; j<8; j++)
      {
        if(neighbours[j] == show[i])
	  if((j % 2) == 0)
            if(relative)
              neigh_exits += ({ RELATIVE_DIR[j] });
            else
              neigh_exits += ({ STD_DIR[j] });
	  else if((neighbours[(j+1)%8] != show[i]) &&
	          (neighbours[(j+7)%8] != show[i]))
            if(relative)
              neigh_exits += ({ RELATIVE_DIR[j] });
            else
              neigh_exits += ({ STD_DIR[j] });
      }
      if (sizeof(neigh_exits)) 
      {
	ex += neighbour_desc_start(map[1][1..1],show[i]) + 
              neigh_exits[0];
	if (sizeof(neigh_exits) > 1)
	{
	  for (j = 1; j < sizeof(neigh_exits) - 1; j++ )
	    ex += ", " + neigh_exits[j];
	  ex += " and " + neigh_exits[j];
	}
        ex += neighbour_desc_end(map[1][1..1],show[i]) + ".\n";
      }
    }
  return ex;
}

public string
exits_description()
{
  string fix_show, ex = "";
  mixed *exits, *neigh_exits, *neighbours = ({ });
  int i, j, poff;

    if(check)
    {
      exits = query_exit_cmds();
      if (!pointerp(exits))
        exits = ({ });

      if(sizeof(exits & STD_DIR))
        ex = full_neighbour_desc(0);
      else
        ex = full_neighbour_desc(1);

      poff = this_player()->query_prop(MAPSERVER_OFFSET);
      if(member_array(map[1][1..1], paths) != -1)
      {

        if(sizeof(exits & STD_DIR))
	{
          exits = ({ });
	  for(i=0; i < 8; i++)
	  {
	    if(member_array(exist_room(i+8-poff), paths) != -1)
	      if((i % 2) == 0)
	        exits += ({ STD_DIR[i] });
	      else if(!this_is_room(exist_room(i+9-poff)) &&
	              !this_is_room(exist_room(i+7-poff)))
	        exits += ({ STD_DIR[i] });
	  }
	  if (sizeof(exits)) 
	  {
	    ex += path_desc_start(map[1][1..1]) + exits[0];
	    if (sizeof(exits) > 1)
	    {
	      for (i = 1; i < sizeof(exits) - 1; i++ )
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
	    else if(!this_is_room(exist_room(i+1)) &&
	            !this_is_room(exist_room(i+7)))
	      exits += ({ RELATIVE_DIR[i] });
	}
	if (sizeof(exits)) 
	{
	  ex += path_desc_start(map[1][1..1]) + exits[0];
	  if (sizeof(exits) > 1)
	  {
	    for (i = 1; i < sizeof(exits) - 1; i++ )
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
        for(i=0; i < 8; i++)
        {
          if(this_is_room(exist_room(i)))
            if(((poff + i) % 2) == 0)
              exits += ({ RELATIVE_DIR[i] });
            else if(!this_is_room(exist_room(i+1)) &&
                    !this_is_room(exist_room(i+7)))
              exits += ({ RELATIVE_DIR[i] });
        }
        if (!sizeof(exits))
	  return ex;

        if (sizeof(exits) == 1)
	  return ex + "There is one obvious exit: " + exits[0] + ".\n";

        ex += "There are " + LANG_WNUM(sizeof(exits)) +
	      " obvious exits: " + exits[0];
        for (i = 1; i < sizeof(exits); i++ )
	  ex += ", " + exits[i];

        return ex + ".\n";
      }
      return ex + ::exits_description();
    }
    return "";
}

void
init()
{
  ::init();
  set_alarm(0.0, 0.0, "init_more");
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
        if(this_is_room(exist_room(i)))
          if(((poff + i) % 2) == 0)
          {
            add_action("normal_exit", RELATIVE_DIR[i] );
            add_action("normal_exit", SHORT_RELATIVE_DIR[i] );
          }
          else if(!this_is_room(exist_room(i+1)) &&
                  !this_is_room(exist_room(i+7)))
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
    int i, dir, err;

    vb = query_verb();
    notify_fail(capitalize(query_verb()) + " what?\n");
    if (arg)  return 0;
    ob = find_room(vb);
    notify_fail("You cannot move in that direction after all.\n");
    if (!ob)  return 0;
    notify_fail("You are too tired to walk in that direction.\n");
    if(this_player()->query_fatigue() < query_map_fatigue(map[1][1..1]))
      return 0;

    dir = standard_offset(vb);

    dir += this_player()->query_prop(MAPSERVER_OFFSET);
    dir %= 8;
    team = this_player()->query_team();
    if (sizeof(team))
    {
	team = filter(team, "check_team", this_player());
        this_player()->add_prop(TEMP_DRAGGED_ENEMIES, ({ }));
    }
    for(i=0; i<sizeof(team); i++)
    {
      if(team[i]->query_fatigue() < query_map_fatigue(map[1][1..1]))
        team[i]->catch_msg("You are too tired to walk in that direction.\n");
      else
      {
	this_player()->add_prop(TEMP_DRAGGED_ENEMIES,
	       this_player()->query_prop(TEMP_DRAGGED_ENEMIES)+({team[i]}));
        team[i]->set_fatigue(team[i]->query_fatigue() - 
                                          query_map_fatigue(map[1][1..1]));
      }
    }
    this_player()->set_fatigue(this_player()->query_fatigue() - 
                                          query_map_fatigue(map[1][1..1]));

    tell_room(ob, QCTNAME(this_player()) + " arrives.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " leaves " +
                             VBFC_ME_P("from_dir",dir) + ".\n",this_player());
    err = this_player()->move_living("M", ob, 1);
    if(err)
    {
      tell_room(ob, QCTNAME(this_player()) + " leaves again.\n");
      tell_room(this_object(), QCTNAME(this_player()) + " arrives again.\n",
                               this_player());
    }
    if(err > 3)
    {
      write("There is some strange problem. Please call wizard and ask "+
            "him to do 'update "+MASTER_OB(ob)+"'. Thank you.\n");
      write_file("/d/Rhovanion/log/mapserver", 
                 MASTER_OB(ob)+" stuck in memory.  "+ctime(time())+"\n");
    }
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

