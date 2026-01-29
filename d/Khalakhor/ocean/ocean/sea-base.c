/*
 * Khalakhor sea base room using Sparkle sea base room using
 * Ansalon's Mapserver 
 * created by Tapakah October 2021
 *
 */
#pragma no_clone
#pragma strict_types

#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <ss_types.h>

#include "defs.h"

inherit SAILING_BASE;
inherit "/d/Khalakhor/lib/logger";

#define DEBUG(x)  find_player("tapakah")->catch_msg("[Khalsea] " + x + "\n")

#define CREATE "create_sea_room"
#define RESET "reset_sea_room"

#define OFFSET		 "_map_serv_off"
#define IS_LOST		 "_map_serv_lost"
#define ALLOW_MOVE_OFF	 "_allow_move_off"

string gExtra_night_long, gSpecial_short;
string *herbs = 0;

// Don't forget to add new sailing room types here!
// Easily forgotten, and annoying when debugging why rooms don't load!
mixed *points = ({
  ({ 22,13,"Nexus of Khalakhor" }),
  ({ 22,3, "North Speir of Khalakhor" }),
  ({ 13,18,"Southwestern Speir of Khalakhor" }),
  ({ 28,17,"Southeastern Speir of Khalakhor" }),
  ({ 24,17,"Port Macdunn", 0 }),
  ({ 29,19,"Tabor Sogh", 0 }),
  ({ 14,22,"Sa Morgan", 0 }),
  ({ 25,28,"Baile Ashlagh" }),
  ({ 5,25, "Nyreese" }),
  ({ 7,30, "Carisca" }),
  ({ 4,12, "Eil Galaith" }),
  ({ 6,3,  "Lucky Island" }),
});

static string *sailing_rooms =
  ({ "C", "O", "L", "M", "T", "S", "E", "F", "D",
     "n", "w", "e", "b", "g", "l", "c", "r", "s"});

static string area_handler;

string query_area_handler();

/*** Global variables ***/
static string *_std_dir = ({"north","northeast","east","southeast",
                            "south","southwest","west","northwest"});

static string _map, _name, _path, Zz;
static int Xx, Yy, _check, *_map_exit_mask, _bug;

varargs mixed *
get_distance_direction (int x, int y, string _point=0)
{
  mixed *nearest_point, *_points;
  float distance = 50.0, this_distance, angle;
  string direction;
  
  _points = _point ? filter(points, &operator(==)(_point)) : points;
  foreach (mixed point: points) {
    if (! _point && sizeof(point) > 3)
      continue;
    this_distance = sqrt(itof(
                              (x-point[0])*(x-point[0])+
                              (y-point[1])*(y-point[1])
                              ));
    if (distance > this_distance) {
      distance = this_distance;
      nearest_point = point;
    }
  }
  if (x == nearest_point[0]) 
    return ({
      distance, y > nearest_point[1] ? "north" : "south", nearest_point[2]
    });
  angle = atan2(
                itof(y-nearest_point[1]), itof(x-nearest_point[0])
                )/3.1416*180.0;
  if (angle < 157.5 && angle >= 112.5)
    direction = "northeast";
  else if (angle < 112.5 && angle >= 67.5)
    direction = "north";
  else if (angle < 67.5 && angle >= 22.5)
    direction = "northwest";
  else if (angle < 22.5 && angle >= -22.5)
    direction = "west";
  else if (angle < -22.5 && angle >= -67.5)
    direction = "southwest";
  else if (angle < -67.5 && angle >= -112.5)
    direction = "south";
  else if (angle < -112.5 && angle >= -157.5)
    direction = "southeast";
  else
    direction = "east";
  return ({distance, direction, nearest_point[2]});
}

/* Function name: query_file_with_map
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return path to the file containing map
 */
nomask string
query_file_with_map ()
{
  return KHALAKHOR_SEA + "sea-map";
}

/* Function name: query_base_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where base-files are located
 */
string
query_base_dir ()
{
  return KHALAKHOR_SEA;
}

/* Function name: query_room_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where room-files are located
 */
string
query_room_dir ()
{
  return ROOM;
}

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
int
is_room (string arg)
{
  return member_array(arg, sailing_rooms) != -1 ? 1 : 0;
}

/* Function name: add_std_exits
 * Description:	  adds standard exits to the room. You do not have to call it.
 *		  It is always called after execution of create_map_room().
 */
nomask void
add_std_exits();


/*		MOVEMENT		*/

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for TP
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
int
query_map_fatigue()
{
  return 1;
}

/* Function name: block_enter
 * Description:	  Decide if TP can enter this room.
 *		  Redefine it in ROOM base file or in room file.
 * Returns:	  0 - can enter, 1 - block
 * Note:	  If player is blocked, display appropriate message.
 */
int
block_enter()
{
  return 0;
}

/*		MISC			*/

/* Function name: do_not_remove
 * Description:	  Decide if file with this room should be kept
 *		  (for security it is sometime usefull to keep the file)
 *		  Redefine it in ROOM base file or in room file.
 * Returns:	  0 - file can be removed, 1 - keep the file
 */
int
do_not_remove()
{
  return 0;
}

/* Function name: get_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      s - letter corresponding to required room
 * Returns:       array of integers
 * Note:          This function should be called for every argument at most
 *                once. Store result in var and use if necessary (save CPU)
 *                Translate into string with desc_map_dirs(int *dir)
 */
nomask int *
get_map_dirs(string s);

/* Function name: desc_map_dirs
 * Description:   Gives description of set of directions
 * Argumant:      array of integers corresponding to directions
 * Returns:       string - composited directions
 */
nomask string
desc_map_dirs(int *dir);

/* Function name: update_map_rooms
 * Description:   Updates all map rooms.
 * Note:	  Since most room files do not exists it is impossible
 *		  to do it with update command
 */
nomask void
update_map_rooms();

/*********************************************************************/
/*	   End of functions you may find useful (I think ;)	     */
/*********************************************************************/

/* Function name: get_local_map
 * Description:	  Local map contains room + attached rooms
 * Argument:	  x,y - coordinates of room on global map
 */
private nomask void
get_local_map(int x, int y)
{
  string file = query_file_with_map();
  if (!file || !(_map = file->query_local_map(x, y)))
    _map = "12345678 ";
}

string
wizinfo()
{
  string s = "WIZINFO:\n";

  if (!_check)
    return s+"This is not a map room. "+
	    "It is probably one of the base rooms. No mortals here.\n";
  if (_bug) {
    s += "Problem was detected.\n";
    if (_bug % 2)
      s += "_check redefinition of query_room_dir() in your area base file.\n";
    if ((_bug / 2) % 2)
      s += "This room has manually created file and last char in its name ("+Zz+
        ") does not correspond to the char ("+_map[8..8]+
        ") on map on given coordinates ("+Xx+", "+Yy+").\n";
    if ((_bug / 4) % 2)
      s += "_check redefinition of is_room() in your area base file. "+
        "It returns 0 for '"+_map[8..8]+"'.\n";
  }
  s += "\nThis is a mapserver room. Special support:\n"+
    "   updating: 'Call here update_map_rooms' updates all rooms in area.\n"+
    "                           Should be used only when developing area.\n"+
    "If you have any ideas/needs for more special support please contact me.\n"+
    "\n          Milan^H^H^H^H^HTapakah\n";
  return s;
}

/* Function name: find_room_file
 * Description:	  find file of room in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  file with room
 */
nomask string
find_room_file (int off)
{
  int x, y;

  if (!_check)
    return 0;

  x = Xx;
  y = Yy;
  if (off >= 1 && off <= 3)
    x = Xx + 1;
  else if (off >= 5)
    x = Xx - 1;
  if (off >= 3 && off <= 5)
    y = Yy + 1;
  if (off >= 7 || off <= 1)
    y = Yy - 1;

  string room_file = sprintf("%s%s-%d-%d-%s",
                             _path, _name, x, y, _map[off..off]);
  return room_file;
}

private nomask object
load_map_room_file (string file, string p)
{
  int is_tmp;
  string err, code;

  setuid();
  seteuid(getuid());
  code = "inherit \""+query_base_dir()+_name+"-"+p+"\";\n";

  if (file_size(file + ".c") < 0) {
    is_tmp = 1;
    write_file(file + ".c", code);
  }
  if (err = LOAD_ERR(file)) {
    SECURITY->log_loaderr(file,
                          environment(this_object()),
                          query_verb(),
                          this_object(), err);
    log_me(sprintf("Sailing room %s failed to load: %s", file, err),
           "error",
           environment(TO));
    write("err in load:" + err + " <" + file + ">\n");
    return 0;
  }
  if (is_tmp && !(file->do_not_remove()))
    rm(file + ".c");
  return find_object(file);
}

/* Function name: load_map_room
 * Description:	  loads room in given direction
 * Arguments:	    offset - number of direction
 * Returns:	      room object
 */
private nomask object
load_map_room (int off)
{
  object room;
  string file;

  if (!_check)
    return 0;

  if (room = find_object(file = find_room_file(off)))
    return room;
  return load_map_room_file(file, _map[off..off]);
}

/* Function name: block_map_room
 * Description:	  decides if player can move in given direction
 * Arguments:	    offset - (string) number of direction
 * Returns:	      0 - can move, 1 - blocked out
 */
nomask int
block_map_room (int off)
{
  object room = load_map_room(off);
  mixed msg;

  if (room && !room->block_enter()) {
    TP->add_prop(OFFSET, off+1);
    return 0;
  }
  return 1;
}

/* Function name: exit_map_cmd
 * Description:	  gives exit command for given direction
 * Arguments:	    off - (string) number of direction
 * Returns:	      direction command/description
 */
nomask string
exit_map_cmd (int off)
{
  return _std_dir[off];
}

varargs void
add_row_exits (string place, string cmd, mixed efunc, mixed tired)
{
  if (member_array(cmd, _std_dir) != -1)
    remove_row_exit(cmd); // we do not want two exits to same direction

  add_row_exit(place, cmd, efunc, tired);

  return;
}

nomask void
add_map_exits ()
{
  int i;
  string d;
  _map_exit_mask = ({ 0,0,0,0,0,0,0,0 });
  for (i = 0; i < 8; i++) {
    d = _map[i..i];
    if (! is_room(d)) // exit is not a room
      continue;
    if (i % 2 == 0) { // n, e, s, w
      add_row_exits(find_room_file(i), _std_dir[i], &block_map_room(i), 1);
	    _map_exit_mask[i] = 1;
    }
  }
}
	
/* Function name: add_std_exits
 * Description:	  adds standard exits to the room
 */
nomask void
add_std_exits ()
{
  if (!_check)
    return;
  add_map_exits();
}

/* Function name: point
 * Description:	  executes when player does 'point direction'
 * Arguments:	  str - pointing direction
 * Returns:	  1 - success, 0 - failed
 */

int
point (string str)
{
  object *pl, tp = TP;
  int off, s, i;

  if ((off = member_array(str, _std_dir)) != -1) {
    if (tp->query_prop(IS_LOST)) {
	    write("And where do you think " + str + " is?\n");
	    return 1;
    }
  }
  else
    off = (off + tp->query_prop(OFFSET) + 7) % 8;

  write("You point "+str+".\n");

  pl = all_inventory(this_object()) - ({ tp });
  for (i = 0, s = sizeof(pl); i < s; i++)
    if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp)) {
      set_this_player(pl[i]);
      pl[i]->catch_tell(tp->query_The_name(pl[i]) + " points " +
                        exit_map_cmd(off) + ".\n");
    }
  set_this_player(tp);
  return 1;
}

/* Function name: query_exit_cmds
 * Description:	  gives array of exit commands
 * Returns:	  array of strings
 * Note:	  We need to mask it so that 'sneak' works right
 */
string *
query_exit_cmds()
{
  string *exits = ::query_exit_cmds();
  return exits;
}

int
add_prop_room_s_dir (mixed val)
{
  int off;

  return 0;
}

/* Function name: get_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      s - letter corresponding to required room
 * Returns:       array of integers
 * Note:          This function should be called for every argument at most
 *                once. Store result in var and use if necessary (save CPU)
 *                Translate into string with desc_map_dirs(int *dir)
 */
nomask int *
get_map_dirs (string s)
{
  int i, *dir = ({ });

  for (i=0; i<8; i++)
    if (s == _map[i..i])
	    dir += ({ i });
  return dir;
}

/* Function name: desc_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      array of integers corresponding to directions
 * Returns:       string - composited directions
 */
nomask string
desc_map_dirs (int *dir)
{
  string *tmp = ({ });
  int i, s;

  for(i=0, s=sizeof(dir); i<s; i++)
    tmp += ({ _std_dir[dir[i]] });

  return COMPOSITE_WORDS(tmp);
}

nomask int
is_player (object ob)
{
  return interactive(ob);
}

nomask void
do_update_map_room (object tp, int y, int x, string nnn)
{
  string file, line, s;
  object ob, *obs;
  int i, error;

  if (_check) // this function is not to be called in map rooms
    return;

  if (y < 0) {
    tp->catch_tell("...done updating map rooms.\n");
    return;
  }

  line = query_file_with_map()->query_map_line(y);
  while (x >= 0) {
    s = line[x..x];
    if (is_room(s))
	    break;
    x--;
  }

  if (x < 0) {
    y--;
    x = strlen(query_file_with_map()->query_map_line(y)) - 1;
    set_alarm(0.0, 0.0, &do_update_map_room(tp, y, x, nnn));
    return;
  }

  file = query_room_dir() + nnn + "-" + x + "-" + y + "-" + s;

  ob = find_object(file);
  if (ob && ob != this_object()) {
    obs = filter(all_inventory(ob), is_player);
    error = 0;
    for (i = 0; i < sizeof(obs); i++)
	    if (obs[i]->query_default_start_location() == file) {
        error = 1;	
        tp->catch_tell("Cannot update the start location of "
                       + obs[i]->query_name() + ".\n");
	    }


    if (error == 1)
	    tp->catch_tell("Failed to update '"+file+"'.\n");
    else {
	    /* Move all objects out of the room */
	    for (i = 0; i<sizeof(obs); i++) {
        obs[i]->catch_tell(tp->query_The_name(obs[i]) + " updates the room.\n");
        obs[i]->move(obs[i]->query_default_start_location());
	    }
	    SECURITY->do_debug("destroy", ob);
	    if (sizeof(obs)) {
	    	ob = load_map_room_file(file, s);
	    	if (ob)
          for (i = 0; i < sizeof(obs); i++)
            obs[i]->move(ob);
	    }
	    tp->catch_tell("Updated room '"+file+"'\n");
    }
    set_alarm(0.0, 0.0, &do_update_map_room(tp, y, x-1, nnn));
    return;
  }
  set_alarm(0.0, 0.0, &do_update_map_room(tp, y, x-1, nnn));
}

/* Function name: update_map_rooms
 * Description:   Updates all map rooms.
 * Note:	  Since most room files do not exists it is impossible
 *		  to do it with update command
 */
nomask void
update_map_rooms ()
{
  object base;
  string file = query_file_with_map();
  int s = file->query_map_size();
  int l = strlen(file->query_map_line(s-1));

  if (!_check || this_object() != environment(TP)) {
    TP->catch_tell("Go to map room and 'Call here update_map_rooms'\n");
    return;
  }

  file = query_base_dir()+_name+"-"+Zz;

  if (file->is_player(TP)) {
    TP->catch_tell("Updating map rooms...\n");
    file->do_update_map_room(TP, s-1, l-1, _name);
  }
  else
    TP->catch_tell("Updating failed :-(\n");
}

/*
 * Function _name: set_area_handler
 * Description  : Sets the object that should be notified of resets
 *                etc. for this area.
 *
 */
void
set_area_handler (string file)
{
  area_handler = file;
}

/*
 * Function name: query_area_handler
 * Description  : Returns the object handlign this area.
 */
string
query_area_handler()
{
  return area_handler;
}

nomask void
create_map_room ()
{
  int a,b,c,s,i;

  if (!_check)
    // DEBUG("No _check in create_map_room");
    return;

  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);

  if (s = sizeof(herbs)) {
    i = (Xx+1)*(Yy+1);
    a = random(s, i);
    b = random(s, i + a + random(i + a, i + a + (a * i)));
    c = random(s, i + a + b + random(i + a + b, i + a + b + (b * i)));
  }

  set_area_handler(KHALAKHOR_SEA + "sea-placer");
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this room
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if (is_player(ob) && !ob->query_prop(OFFSET))
    ob->add_prop(OFFSET, 1 + member_array(query_verb(), _std_dir));

  if (ob->query_prop(IS_LOST)) {
    ob->remove_prop(IS_LOST);
    ob->catch_tell("You regain the orientation.\n");
  }
}

string
coords ()
{
  if (TP->query_wiz_level() || wildmatch("*jr", TP->query_name()))
    return sprintf("%d, %d, %s\n", Xx, Yy, Zz);
  return "Curious, aren't we?\n";
}

void
init ()
{
  int i;

  ::init();
  if (!_check)
    return;

  add_action(point, "point");
  add_action(coords, "coords");
}

void
reset_sea_room ()
{
  if (!_check)
    return;

  set_searched(random(3));
}

void
create_sea_room ()
{
  string *list, master, str = "";
  if (_check)
    return;

  add_prop(OBJ_S_WIZINFO, "Do 'Call here wizinfo'.\n");
  set_short("BUG");
  master = MASTER;
  list = explode(master, "/");

  _name = explode(list[sizeof(list)-1], "-")[0];
  if (sscanf(master, "%s"+_name+"-%d-%d-%s", _path, Xx, Yy, Zz) == 4)  {
    _check = 1;
    get_local_map(Xx, Yy);
    set_long("Room is not properly created.\n");

    create_map_room();
    add_std_exits();

    if (_path != query_room_dir()) {
	    _bug += 1;
	    str = "File location is different than result of query_room_dir().\n";
    }
    if (Zz != _map[8..8]) {
	    _bug += 2;
	    str += "Filename does not match letter on the map.\n";
    }
    if (!is_room(_map[8..8])) {
	    _bug += 4;
	    str += "Letter on the map is not a room.\n";
    }
    if (_bug) {
	    set_short("BUG");
	    set_long(str + "Please make 'bug' report.\n");
    }
  }
  else
    set_long("BUG! Wrong format of filename. This room is not on the map! Call wizard for help.\n");

  reset_sea_room();  
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */

int
query_standard_water_room ()
{
  return 0; 
}

