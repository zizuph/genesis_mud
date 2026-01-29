/*
 * Sparkle sea base room using Ansalon's Mapserver 
 * created by Arman April 2021
 *
 * When adding rooms to magic map, you need to go to each sailing room
 * and, for example:
 *    execr "/secure/map_central"->add_maplink("/d/Sparkle/area/sea/room/sparkle_sea-2-4-d",
 *        "/d/Sparkle/open/MAP_FILES/sparkle_sea.txt");
 *    Call here init_map_data
 *
 */
#pragma save_binary
#pragma strict_types

#include "local.h"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <ss_types.h>

inherit SAIL_ROOM_BASE;

#define DEBUG(x)  find_player("arman")->catch_msg("[Spark] " + x + "\n")
#define CREATE "create_sea_room"
#define RESET "reset_sea_room"

#define OFFSET		 "_map_serv_off"
#define IS_LOST		 "_map_serv_lost"
#define ALLOW_MOVE_OFF	 "_allow_move_off"

string gExtra_night_long, gSpecial_short;
string *herbs = 0;

// Don't forget to add new sailing room types here!
// Easily forgotten, and annoying when debugging why rooms don't load!
static string *sailing_rooms = ({ "c", "s", "d", "m", "x", "j", "t",
                                  "k", "n", "e", "b" });

static string area_handler;

string query_area_handler();

/*** Global variables ***/
public static string *Rel_dir = ({"forward",  "rightforward",
				  "right",    "rightbackwards",
				  "backwards","leftbackwards",
				  "left",     "leftforward"});
public static string *Std_dir = ({"north","northeast","east","southeast",
				   "south","southwest","west","northwest"});

public static string Map, Name, Path, Zz;
public static int Xx, Yy, Check, Relative, *Map_exit_mask, Bug;



/* Function name: query_file_with_map
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return path to the file containing map
 */
public nomask string
query_file_with_map()
{
    return SPARKLE_SEA + "sparkle_sea_map";
}

/* Function name: query_base_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where base-files are located
 */
public string
query_base_dir()
{
    return SPARKLE_SEA;
}

/* Function name: query_room_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where room-files are located
 */
public string
query_room_dir()
{
    return ROOM;
}

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
public int
is_room(string arg)
{
    if (member_array(arg, sailing_rooms) != -1)
    {
	return 1;
    }

    return 0;
}

/* Function name: exit_not_obvious
 * Description:	  Test if exit from one room to another should be not obvious
 * Argument:	  from - letter corresponding to from room
 *		  dest - letter corresponding to dest room
 * Returns:	  1 if not obvious    else 0 - exit will be obvious
 */
public int
exit_not_obvious(string from, string dest)
{
    // This probably isn't necessary
    return 1;

    string *paths = ({ "c", "s", "d", "j", "m", "x", "b" });
    if (member_array(from, paths) != -1 && member_array(dest, paths) != -1) // path is obvious
	return 0;
    return 1; // all other are not obvious
}

/*		EXITS			*/

/* Function name: add_std_exits
 * Description:	  adds standard exits to the room. You do not have to call it.
 *		  It is always called after execution of create_map_room().
 *		  If add_rel_exits() was called before then it does nothing.
 */
public nomask void
add_std_exits();

/* Function name: add_rel_exits
 * Description:	  adds relative exits to the room. If you want relative exits
 *		  you have to call it directly in your create_map_room().
 *		  If add_std_exits() was called before then it does nothing.
 *		  Call it in create_map_room() in ROOM base file.
 */
public nomask void
add_rel_exits();


/*		MOVEMENT		*/

/* Function name: is_lost
 * Description:	  Test if this_player() lost directions when leaving
 *		  this room.
 *		  Redefine it in ROOM base file.
 * Returns:	  FALSE (0) - player is not lost.
 *                TRUE      - player is lost
 *                            if it returns string, it is displayed to player
 *                            othervise standard message is used
 */
public mixed
is_lost()
{
    if (random(36) > this_player()->query_skill(SS_LOC_SENSE))
	return 1;
    return 0;
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 1;
}

/* Function name: block_enter
 * Description:	  Decide if this_player() can enter this room.
 *		  Redefine it in ROOM base file or in room file.
 * Returns:	  0 - can enter, 1 - block
 * Note:	  If player is blocked, display appropriate message.
 */
public int
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
public int
do_not_remove()
{
    return 0;
}

/* Function name: query_relative
 * Returns:	   1 if there are relative exits,
 *		  -1 if there are standard exits,
 *		   0 no map exits set up
 */
public nomask int
query_relative()
{
    return Relative;
}

/* Function name: get_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      s - letter corresponding to required room
 * Returns:       array of integers
 * Note:          This function should be called for every argument at most
 *                once. Store result in var and use if necessary (save CPU)
 *                Translate into string with desc_map_dirs(int *dir)
 */
public nomask int *
get_map_dirs(string s);

/* Function name: desc_map_dirs
 * Description:   Gives description of set of directions
 * Argumant:      array of integers corresponding to directions
 * Returns:       string - composited directions
 */
public nomask string
desc_map_dirs(int *dir);

/* Function name: update_map_rooms
 * Description:   Updates all map rooms.
 * Note:	  Since most room files do not exists it is impossible
 *		  to do it with update command
 */
public nomask void
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
    if (!file || !(Map = file->query_local_map(x, y)))
	Map = "12345678 ";
}

public string
wizinfo()
{
    string s = "WIZINFO:\n";

    if (!Check)
    	return s+"This is not a map room. "+
	    "It is probably one of the base rooms. No mortals here.\n";
    if (Bug)
    {
	s += "Problem was detected.\n";
	if (Bug % 2)
	    s += "Check redefinition of query_room_dir() in your area base file.\n";
	if ((Bug / 2) % 2)
	    s += "This room has manually created file and last char in its name ("+Zz+
		") does not correspond to the char ("+Map[8..8]+
		") on map on given coordinates ("+Xx+", "+Yy+").\n";
	if ((Bug / 4) % 2)
	    s += "Check redefinition of is_room() in your area base file. "+
		"It returns 0 for '"+Map[8..8]+"'.\n";
    }
    s += "\nThis is a mapserver room. Special support:\n"+
	 "   updating: 'Call here update_map_rooms' updates all rooms in area.\n"+
	 "                           Should be used only when developing area.\n"+
	 "If you have any ideas/needs for more special support please contact me.\n"+
	 "\n          Milan\n";
    return s;
}

/* Function name: find_room_file
 * Description:	  find file of room in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  file with room
 */
private nomask string
find_room_file(int off)
{
    int x, y;

    if (!Check)
	return 0;

    x = Xx;
    y = Yy;
    if (off > 0 && off < 4)
	x = Xx + 1;
    if (off > 4)
	x = Xx - 1;
    if (off > 2 && off < 6)
	y = Yy + 1;
    if (off > 6 || off < 2)
	y = Yy - 1;

    return Path+Name+"-"+x+"-"+y+"-"+Map[off..off];
}

private nomask object
load_map_room_file(string file, string p)
{
    int is_tmp;
    string err, code;

    setuid();
    seteuid(getuid());
    code = "inherit \""+query_base_dir()+Name+"-"+p+"\";\n";

    if (file_size(file + ".c") < 0)
    {
	is_tmp = 1;
	write_file(file + ".c", code);
    }
    if (err = LOAD_ERR(file))
    {
	SECURITY->log_loaderr(file,
			      environment(this_object()),
			      query_verb(),
			      this_object(), err);
	write("err in load:" + err + " <" + file + ">\n");
	return 0;
    }
    if (is_tmp && !(file->do_not_remove()))
	rm(file + ".c");
    return find_object(file);
}

/* Function name: load_map_room
 * Description:	  loads room in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  room object
 */
private nomask object
load_map_room(int off)
{
    object room;
    string file;

    if (!Check)
	return 0;

    if (room = find_object(file = find_room_file(off)))
	return room;
    return load_map_room_file(file, Map[off..off]);
}

/* Function name: block_map_room
 * Description:	  decides if player can move in given direction
 * Arguments:	  offset - (string) number of direction
 * Returns:	  0 - can move, 1 - blocked out
 */
public nomask int
block_map_room(int off)
{
    object room = load_map_room(off);
    mixed msg;

    if (room && !room->block_enter())
    {
	this_player()->add_prop(OFFSET, off+1);
	// player can get lost only if relative dirs. NPCs don't get lost
	if (Relative == 1 && !this_player()->query_npc() &&
	    (room->query_relative() == 1) && (msg = is_lost()))
	{
	    this_player()->add_prop(IS_LOST, 1);
	    // player may have turn left or right
	    this_player()->add_prop(OFFSET, ((off + 6 + (2 * random(3))) % 8) + 1);
	    if (stringp(msg))
	    {
	        write(msg);
	    }
	    else
		write("You are disoriented...\n");
	}
	return 0;
    }
    return 1;
}

/* Function name: exit_map_cmd
 * Description:	  gives exit command for given direction
 * Arguments:	  off - (string) number of direction
 * Returns:	  direction command/description
 */
public nomask string
exit_map_cmd(int off)
{
    if (!this_player()->query_prop(IS_LOST))
    	return Std_dir[off];
    return Rel_dir[(8 + off + 1 - this_player()->query_prop(OFFSET)) % 8];
}

public varargs void
add_row_exits(string place, string cmd, mixed efunc, mixed tired)
{
    if (member_array(cmd, Std_dir) != -1)
    {
    	if (Relative == 1)
	    return 0;
	remove_row_exit(cmd); // we do not want two exits to same direction
    }
    else if (member_array(cmd, Rel_dir) != -1)
	return 0;

    add_row_exit(place, cmd, efunc, tired);

    return;
}

private nomask void
add_map_exits()
{
    int i, j;
    string d,v,h;
    Map_exit_mask = ({ 0,0,0,0,0,0,0,0 });
    for (i = 0; i < 8; i++)
    {
	d = Map[i..i];
	j = (i + 7) % 8;
	v = Map[j..j];
	j = (i + 1) % 8;
	h = Map[j..j];
	if (is_room(d) &&
		// room must be on map and satisfy one of following conditions
	    ((i % 2 == 0) ||	// n,e,s,w direction
				// room connected only diagonally
	     (!is_room(v) && !is_room(h)) ||
				// obvious exit only diagonaly
	     (!exit_not_obvious(Zz, d) &&
	      (!is_room(v) || exit_not_obvious(Zz, v) || exit_not_obvious(v, d)) &&
	      (!is_room(h) || exit_not_obvious(Zz, h) || exit_not_obvious(h, d)))))
	{
	    add_row_exits(find_room_file(i), Std_dir[i], &block_map_room(i), 1);
	    Map_exit_mask[i] = 1;
	}
	else if (Relative == 1)
        {
	    add_row_exits(0, Std_dir[i], &block_map_room(i), 0);
        }
    }
}
	
/* Function name: add_std_exits
 * Description:	  adds standard exits to the room
 */
public nomask void
add_std_exits()
{
    if (!Check || Relative)
	return;
    Relative = -1; /*** room has standard exits ***/

    add_map_exits();
}

/* Function name: add_rel_exits
 * Description:	  adds relative exits to the room
 */
public nomask void
add_rel_exits()
{
    if (!Check || Relative)
	return;
    Relative = 1; /*** room has relative exits ***/
    add_map_exits();
}

/* Function name: point
 * Description:	  executes when player does 'point direction'
 * Arguments:	  str - pointing direction
 * Returns:	  1 - success, 0 - failed
 */
public int
point(string str)
{
    object *pl, tp = this_player();
    int off, s, i;

    if ((off = member_array(str, Std_dir)) != -1)
    {
	if (tp->query_prop(IS_LOST))
	{
	    write("And where do you think " + str + " is?\n");
	    return 1;
	}
    }
    else if ((off = member_array(str, Rel_dir)) < 0)
    {
	return 0;
    }
    else
    {
	off = (off + tp->query_prop(OFFSET) + 7) % 8;
    }

    write("You point "+str+".\n");

    pl = all_inventory(this_object()) - ({ tp });
    for (i = 0, s = sizeof(pl); i < s; i++)
        if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp))
        {
            set_this_player(pl[i]);
            pl[i]->catch_tell(tp->query_The_name(pl[i]) + " points " +
					exit_map_cmd(off) + ".\n");
        }
    set_this_player(tp);
    return 1;
}

/* Function name: init
 * Description:	  gives commands to player
 *		  - exit commands (for relative exits)
 *		  - 'point' in relative direction
 */
public void
init()
{
    int i;

    ::init();
    if (!Check || (Relative != 1))
	return;

    for (i=0; i<8; i++)
	add_action(unq_move, Rel_dir[i]);

    add_action(point, "point");
}

/* Function name: query_exit_cmds
 * Description:	  gives array of exit commands
 * Returns:	  array of strings
 * Note:	  We need to mask it so that 'sneak' works right
 */
public string *
query_exit_cmds()
{
    string *exits = ::query_exit_cmds();
    if ((Relative != 1) || this_player()->query_npc())
	return exits;
    return exits + Rel_dir;
}

/* Function name: unq_move
 * Description:	  makes player actually move after given command
 * Argument:	  str - the rest of command
 * Returns:	  0 - failed, 1 - success
 */
public int
unq_move(string str)
{
    int i, s, tired, tmp, off;
    object d, *pl, tp = this_player();
    string msg_in, msg_out;

    if (Relative != 1) // we mask this function only for relative exits
	return ::unq_move(str);

    if (!(off = query_prop(ALLOW_MOVE_OFF)))
    {
	if ((off = member_array(query_verb(), Std_dir)) != -1)
	{
	    if (tp->query_prop(IS_LOST))
	    {
		str = COMPOSITE_WORDS(sort_array(Rel_dir + ({})));
		str = implode(explode(str, " and "), " or ");
		write("You are disoriented and do not know where " +
			query_verb() + " is. Try " + str + " direction.\n");
		return 1;
	    }
	}
	else if ((off = member_array(query_verb(), Rel_dir)) != -1)
	{
	    off = (off + tp->query_prop(OFFSET) + 7) % 8;
	}
	else // some other exit is used
	    return ::unq_move(str);

	if (str)
	{
	    notify_fail(capitalize(query_verb()) + " what?\n");
	    return 0;
	}

	if (!Map_exit_mask[off]) // no exit in this direction
	    return unq_no_move(str);

	off++;
	add_prop(ALLOW_MOVE_OFF, off);
	set_alarm(0.0, 0.0, &remove_prop(ALLOW_MOVE_OFF));
    }

    off--;
    if (!(d = load_map_room(off)))
	return 1;
    if (block_map_room(off))
	return 1;

    /* Players younger than 4 hours don't get tired from sailing around in
     * the world.
     */
    if (tp->query_age() > 14400)
    {
        tired = query_map_fatigue();
        tmp = tp->query_encumberance_weight();

        /* Compute the fatigue bonus. Sneaking gives double fatigue and
         * so does walking with 80% encumberance, while 20% or less gives
         * only half the fatigue.
         */
        tired = (tp->query_prop(LIVE_I_SNEAK) ?
            (tired * 2) : tired);
        tired = ((tmp > 80) ? (tired * 2) :
            ((tmp < 20) ? (tired / 2) : tired));

        /* Player is too tired to move. */
        if (tp->query_fatigue() < tired)
        {
            notify_fail("You are too tired to move in that direction.\n");
            return 0;
        }
    }

    if (tp->query_prop(LIVE_I_SNEAK))
    {
	msg_in = explode(tp->query_m_in(), ".")[0]+" sneaking";
	msg_out = "sneaks ";
    }
    else
    {
	msg_in = tp->query_m_in();
	msg_out = tp->query_m_out() + " ";
    }

    // leaving messages
    pl = all_inventory(this_object()) - ({ tp });
    for (i = 0, s = sizeof(pl); i < s; i++)
	if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp))
	{
	    set_this_player(pl[i]);
	    pl[i]->catch_tell(tp->query_The_name(pl[i])+" "+
				msg_out+exit_map_cmd(off)+".\n");
	}

    // arriving messages
    pl = all_inventory(d) - ({ tp });
    for (i = 0, s = sizeof(pl); i < s; i++)
	if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp))
	{
	    set_this_player(pl[i]);
	    pl[i]->catch_tell(tp->query_Art_name(pl[i])+" "+msg_in+
		" from "+exit_map_cmd((off+4)%8)+".\n");
	}

    set_this_player(tp);

    tp->move_living("M", d);

    if (d->query_relative() != 1 && tp->query_prop(IS_LOST))
    {
	tp->remove_prop(IS_LOST);
	tp->catch_tell("You regain the orientation.\n");
    }

    return 1;
}

/* Function name: add_prop_room_s_dir
 * Description:	  sets VBFC value so 'track' works properly
 * Argument:	  val - the value someone tried to set
 * Returns:	  0 - allow set prop, 1 - do not allow (we set it)
 */
public int
add_prop_room_s_dir(mixed val)
{
    int off;

    if ((Relative != 1) || (sizeof(val) != 2))
	return 0;
    if (!(off = query_prop(ALLOW_MOVE_OFF)))
	return 0;
    obj_props["_room_s_dir"] = ({ &exit_map_cmd(off-1), val[1] });
    return 1;
}

/* Function name: get_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      s - letter corresponding to required room
 * Returns:       array of integers
 * Note:          This function should be called for every argument at most
 *                once. Store result in var and use if necessary (save CPU)
 *                Translate into string with desc_map_dirs(int *dir)
 */
public nomask int *
get_map_dirs(string s)
{
    int i, *dir = ({ });

    for (i=0; i<8; i++)
        if (s == Map[i..i])
	    dir += ({ i });
    return dir;
}

/* Function name: desc_map_dirs
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      array of integers corresponding to directions
 * Returns:       string - composited directions
 */
public nomask string
desc_map_dirs(int *dir)
{
    string *tmp = ({ });
    int i, s;

    if (Relative != 1)
        for(i=0, s=sizeof(dir); i<s; i++)
            tmp += ({ Std_dir[dir[i]] });
    else
        for(i=0, s=sizeof(dir); i<s; i++)
            tmp += ({ exit_map_cmd(dir[i]) });

    return COMPOSITE_WORDS(tmp);
}

public nomask int
is_player(object ob)
{
    return (living(ob) && !(ob->query_npc()));
}

public nomask void
do_update_map_room(object tp, int y, int x, string nnn)
{
    string file, line, s;
    object ob, *obs;
    int i, error;

    if (Check) // this function is not to be called in map rooms
	return;

    if (y < 0)
    {
	tp->catch_tell("...done updating map rooms.\n");
	return;
    }

    line = query_file_with_map()->query_map_line(y);
    while (x >= 0)
    {
	s = line[x..x];
	if (is_room(s))
	    break;
	x--;
    }

    if (x < 0)
    {
	y--;
	x = strlen(query_file_with_map()->query_map_line(y)) - 1;
	set_alarm(0.0, 0.0, &do_update_map_room(tp, y, x, nnn));
	return;
    }

    file = query_room_dir() + nnn + "-" + x + "-" + y + "-" + s;

    ob = find_object(file);
    if (ob && ob != this_object())
    {
	obs = filter(all_inventory(ob), is_player);
	error = 0;
	for (i = 0; i < sizeof(obs); i++)
	{
	    if (obs[i]->query_default_start_location() == file)
	    {
		error = 1;	
		tp->catch_tell("Cannot update the start location of "
		    + obs[i]->query_name() + ".\n");
	    }
	}

	if (error == 1)
	{
	    tp->catch_tell("Failed to update '"+file+"'.\n");
	}
	else
	{
	    /* Move all objects out of the room */
	    for (i = 0; i<sizeof(obs); i++)
	    {
		obs[i]->catch_tell(tp->query_The_name(obs[i]) + " updates the room.\n");
		obs[i]->move(obs[i]->query_default_start_location());
	    }
	    SECURITY->do_debug("destroy", ob);
	    if (sizeof(obs))
	    {
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
public nomask void
update_map_rooms()
{
    object base;
    string file = query_file_with_map();
    int s = file->query_map_size();
    int l = strlen(file->query_map_line(s-1));

    if (!Check || this_object() != environment(this_player()))
    {
	this_player()->catch_tell("Go to map room and 'Call here update_map_rooms'\n");
	return;
    }

    file = query_base_dir()+Name+"-"+Zz;

    if (file->is_player(this_player()))
    {
	this_player()->catch_tell("Updating map rooms...\n");
	file->do_update_map_room(this_player(), s-1, l-1, Name);
    }
    else
	this_player()->catch_tell("Updating failed :-(\n");
}

/*
 * Function Name: set_area_handler
 * Description  : Sets the object that should be notified of resets
 *                etc. for this area.
 *
 */
void
set_area_handler(string file)
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

nomask public void
create_map_room()
{
    int a,b,c,s,i;

    if (!Check)
    {
        // DEBUG("No Check in create_map_room");
	return;
    }

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    if (s = sizeof(herbs))
    {
    	i = (Xx+1)*(Yy+1);
	a = random(s, i);
	b = random(s, i + a + random(i + a, i + a + (a * i)));
	c = random(s, i + a + b + random(i + a + b, i + a + b + (b * i)));
    }

    set_area_handler(SPARKLE_SEA + "sparkle_sea_placer");
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this room
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (is_player(ob) && !ob->query_prop(OFFSET))
	ob->add_prop(OFFSET, 1 + member_array(query_verb(), Std_dir));

    if (Relative != 1 && ob->query_prop(IS_LOST))
    {
	ob->remove_prop(IS_LOST);
	ob->catch_tell("You regain the orientation.\n");
    }
}

void
reset_sea_room()
{
    if (!Check)
	return;

    set_searched(random(3));
}

void
create_sea_room()
{
    string *list, master, str = "";

    if (Check)
	return;

    add_prop(OBJ_S_WIZINFO, "Do 'Call here wizinfo'.\n");
    set_short("BUG");
    master = MASTER;
    list = explode(master, "/");

    Name = explode(list[sizeof(list)-1], "-")[0];
 
    if (sscanf(master, "%s"+Name+"-%d-%d-%s", Path, Xx, Yy, Zz) == 4)
    {
	Check = 1;
	get_local_map(Xx, Yy);
	set_long("Room is not properly created.\n");

	create_map_room();

	add_std_exits();

	if (Path != query_room_dir())
	{
	    Bug += 1;
	    str = "File location is different than result of query_room_dir().\n";
	}
	if (Zz != Map[8..8])
	{
	    Bug += 2;
	    str += "Filename does not match letter on the map.\n";
	}
	if (!is_room(Map[8..8]))
	{
	    Bug += 4;
	    str += "Letter on the map is not a room.\n";
	}
	if (Bug)
	{
	    set_short("BUG");
	    set_long(str + "Please make 'bug' report.\n");
	}
    }
    else
        set_long("BUG! Wrong format of filename. This room is not on the map! Call wizard for help.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    // Set the sailing skill required to sail to this room.
    set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The open waters of the high seas are highly " +
        "rough, with only master navigators capable of sailing!\n");
    set_sailing_difficulty_message("You navigate skillfully through the rough " +
        "open waters of the high seas!\n");

    set_sink_path(ROOM + "sink_path");

    reset_sea_room();
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */

int
query_standard_water_room()
{
    return 0; 
}

