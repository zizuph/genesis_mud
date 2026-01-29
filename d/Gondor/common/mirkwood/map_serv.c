/*
 *  /d/Gondor/common/mirkwood/map_serv.c
 *  by Milan
 */
#pragma save_binary
#pragma strict_types
#pragma no_clone

#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <composite.h>

inherit "/std/room";

#define OFFSET		 "_map_serv_off"
#define ALLOW_MOVE_OFF	 "_allow_move_off"

/*** Global variables ***/
public static string *Rel_dir = ({"forward",  "rightforward",
				  "right",    "rightbackwards",
				  "backwards","leftbackwards",
				  "left",     "leftforward"});
public static string *Std_dir = ({"north","northeast","east","southeast",
				   "south","southwest","west","northwest"});

public static string Name, Path, Zz;
public static mixed *Map;
public static int Xx, Yy, Check, Relative, Fatigue, *Map_exit_mask;

/*********************************************************************/
/*	      Some functions you may find useful		     */
/*********************************************************************/

/* Function name: query_file_with_map
 * Note:	  This function is _NECESSARY_ to redefine
 * Returns:	  Should return path to the file containing map
 */
public string
query_file_with_map()
{
    return 0;
}

/* Function name: create_map_room
 * Description:	  This function should be masked for room specific
 *		  initializations.
 */
public void
create_map_room()
{}

/* Function name: add_std_exits
 * Description:	  adds standard exits to the room
 *		  This is prototype - see code below...
 */
public nomask void
add_std_exits();

/* Function name: add_rel_exits
 * Description:	  adds relative exits to the room
 *		  This is prototype - see code below...
 */
public nomask void
add_rel_exits();

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
public int
is_room(string arg)
{
    if (arg != " ") return 1;
    return 0;
}

/* Function name: is_lost
 * Description:	  Test if this_player() lost directions when leaving
 *		  this room.
 * Returns:	  1 if lost,  0 if knows directions
 */
public int
is_lost()
{
    return 0;
}

/* Function name: block_enter
 * Description:	  Decide if this_player() can enter this room.
 * Returns:	  0 - can enter, 1 - block
 */
public int
block_enter()
{
    return 0;
}

/* Function name: do_not_remove
 * Description:	  Decide if file with this room should be kept
 *		  (for security it is sometime usefull to keep the file)
 * Returns:	  0 - can be removed, 1 - keep the file
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
 * Description:   Gives direction numbers to the rooms of required type.
 * Argumant:      array of integers corresponding to directions
 * Returns:       string - composited directions
 */
public nomask string
desc_map_dirs(int *dir);

/*********************************************************************/
/*	   End of functions you may find useful (I think ;)	     */
/*********************************************************************/

/* Function name: on_map
 * Description:	  Test if this room is on map
 * Argument:	  x,y - coordinates of room on local map
 * Returns:	  1 if it is on map    else 0
 */
public nomask int
on_map(int x, int y)
{
    return is_room(Map[x][y]);
}

/* Function name: get_local_map
 * Description:	  Local map contains room + attached rooms
 * Argument:	  x,y - coordinates of room on global map
 */
private nomask void
get_local_map(int x, int y)
{
    string file = query_file_with_map();

    if (!file)
    {
	Map = ({({" "," "," "}),({" "," "," "}),({" "," "," "})});
	return;
    }
    Map = file->query_local_map(x, y);
    if (!Map) Map = ({({" "," "," "}),({" "," "," "}),({" "," "," "})});
}

/* Function name: create_room
 * Description:	  creates room (calls create_map_room())
 *		  exits should be added by calling
 *		    add_std_exit() - standard exits or
 *		    add_rel_exit() - relative exits
 */
public nomask void
create_room()
{
    string *list, master = MASTER;

    Relative = 0;
    set_short("BUG");
    list = explode(master, "/");
    Name = explode(list[sizeof(list)-1], "-")[0];
    if (sscanf(master, "%s"+Name+"-%d-%d-%s", Path, Xx, Yy, Zz) == 4)
    {
	get_local_map(Xx, Yy);
	if (on_map(1,1))
	{
	    Check = 1;
	    set_long("Room is not properly created.\n");
	    create_map_room();
	    if (Zz != Map[1][1])
	    {
		set_short("BUG");
		set_long("Filename does not match letter on the map.\n"+
			 "Please make 'bug' report.\n");
	    }
	    return;
	}
    }
    set_long("BUG! This room is not on the map! Call wizard for help.\n");
}

/* Function name: delta_map
 * Description:	  gives coordinates difference in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  ({ dif-x, dif-y })
 */
private nomask int *
delta_map(int offset)
{
    switch (offset)
    {
	case 0:	 return ({  0, -1 });
	case 1:	 return ({  1, -1 });
	case 2:	 return ({  1,	0 });
	case 3:	 return ({  1,	1 });
	case 4:	 return ({  0,	1 });
	case 5:	 return ({ -1,	1 });
	case 6:	 return ({ -1,	0 });
	case 7:	 return ({ -1, -1 });
    }
}

/* Function name: find_room_file
 * Description:	  find file of room in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  file with room
 */
private nomask string
find_room_file(int offset)
{
    int *d, x, y;

    if (!Check) return 0;
    d = delta_map(offset);
    x = Xx + d[0];
    y = Yy + d[1];
    return Path+Name+"-"+x+"-"+y+"-"+Map[1+d[0]][1+d[1]];
}

/* Function name: load_map_room
 * Description:	  loads room in given direction
 * Arguments:	  offset - number of direction
 * Returns:	  room object
 */
private nomask object
load_map_room(int offset)
{
    object room;
    string file, err;
    int *d, is_tmp;

    if (!Check) return 0;
    room = find_object(file = find_room_file(offset));
    if (room) return room;
    setuid(); seteuid(getuid());
    if (file_size(file + ".c") < 0)
    {
	is_tmp = 1;
	d = delta_map(offset);
	write_file(file + ".c",
		   "inherit \""+Path+Name+"-"+Map[1+d[0]][1+d[1]]+"\";\n");
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
    if (is_tmp && !(file->do_not_remove())) rm(file + ".c");
    return find_object(file);
}

/* Function name: block_map_room
 * Description:	  decides if player can move in given direction
 * Arguments:	  offset - (string) number of direction
 * Returns:	  0 - can move, 1 - blocked out
 */
public nomask int
block_map_room(string offset)
{
    int off = atoi(offset);
    object room = load_map_room(off);

    if (room && !room->block_enter())
    {
	if (interactive(this_player())) /*** NPCs don't get lost ***/
	{
	    if (is_lost())
	    {
		this_player()->add_prop(OFFSET, 2 * random(4));
		if (room->query_relative() == 1) write("You feel lost...\n");
	    }
	    else this_player()->add_prop(OFFSET, off);
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
exit_map_cmd(string off)
{
    return Rel_dir[(8 + atoi(off) - this_player()->query_prop(OFFSET)) % 8];
}

/* Function name: add_std_exits
 * Description:	  adds standard exits to the room
 */
public nomask void
add_std_exits()
{
    int i, *d;

    if (!Check || Relative) return;
    Relative = -1; /*** room has standard exits ***/
    for (i = 0; i < 8; i++)
    {
	d = delta_map(i);
	if (on_map(1+d[0],1+d[1]) &&
	    ((i % 2 == 0) || (!on_map(1,1+d[1]) && !on_map(1+d[0],1))))
	    add_exit(find_room_file(i), Std_dir[i],
		     "@@block_map_room|"+i+"@@", Fatigue);
    }
}

/* Function name: add_rel_exits
 * Description:	  adds relative exits to the room
 */
public nomask void
add_rel_exits()
{
    int i, *d;

    if (!Check || Relative) return;
    Relative = 1; /*** room has relative exits ***/
    Map_exit_mask = ({ });
    for (i = 0; i < 8; i++)
    {
	d = delta_map(i);
	if (on_map(1+d[0],1+d[1]) &&
	    ((i % 2 == 0) || (!on_map(1,1+d[1]) && !on_map(1+d[0],1))))
	{
	    add_exit(find_room_file(i), Rel_dir[i],
		     "@@block_map_room|"+i+"@@", Fatigue);
	    Map_exit_mask += ({ i });
	}
    }
}

/* Function name: exit_description
 * Description:	  describe the exits - modified from the original to
 *		  masked exits.
 */
public string
exits_description()
{
    string *exits, *m_exits;
    int i, s;

    if (Relative != 1) return ::exits_description();
    m_exits = ({ });
    exits = ::query_exit_cmds() - Rel_dir;
    s = sizeof(Map_exit_mask);
    for (i = 0 ; i < s ; i++)
	m_exits += ({ exit_map_cmd(""+Map_exit_mask[i]) });
    exits += sort_array(m_exits);
    if (!(i = sizeof(exits))) return "";
    if (i == 1) return "There is one obvious exit: " + exits[0] + ".\n";
    return "There are " + LANG_WNUM(i) + " obvious exits: " +
	   implode(exits,", ") + ".\n";
}

/* Function name: map_unq_move
 * Description:	  executes when relative direction command is given
 * Arguments:	  off - number of actuall direction
 *		  is_exit - is this actual exit?
 *		  str - rest of command
 * Returns:	  1 - success, 0 - failed
 */
public nomask int
map_unq_move(int off, int is_exit, string str)
{
    int allow = query_prop(ALLOW_MOVE_OFF);

    if (!is_exit && !allow)
    {
	notify_fail("There is no obvious exit " + query_verb() + ".\n");
	return 0;
    }
    if (str)
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }
    if (!allow)
    {
	add_prop(ALLOW_MOVE_OFF, off+1);
	set_alarm(0.0, 0.0, &remove_prop(ALLOW_MOVE_OFF));
    }
    return unq_move(str);
}

/* Function name: point
 * Description:	  executes when player does 'point direction'
 * Arguments:	  str - pointing direction
 * Returns:	  1 - success, 0 - failed
 */
public int
point(string str)
{
    int off, s, i;
    object *pl, tp = this_player();

    if (member_array(str, Std_dir) != -1)
    {
	write("And where do you think " + str + " is?\n");
	return 1;
    }
    if ((off = member_array(str, Rel_dir)) == -1) return 0;
    off += tp->query_prop(OFFSET);
    write("You point "+str+".\n");

    pl = all_inventory(this_object()) - ({ tp });
    for (i = 0, s = sizeof(pl); i < s; i++)
        if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp))
        {
            set_this_player(pl[i]);
            pl[i]->catch_msg(QCTNAME(tp) + " points @@exit_map_cmd:" +
                             MASTER + "|" + off + "@@.\n");
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
    int i, off;

    ::init();
    if (!Check || (Relative != 1)) return;
    off = this_player()->query_prop(OFFSET);
    for (i=0; i < 8; i++)
	if (member_array(i, Map_exit_mask) != -1)
	    add_action(&map_unq_move(i,1), Rel_dir[(8+i-off) % 8]);
	else add_action(&map_unq_move(i,0), Rel_dir[(8+i-off) % 8]);
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
    int j, i, off, s;
    string *exits = ::query_exit_cmds(), *rexits = ({ });

    if ((Relative != 1) || !interactive(this_player())) return exits;
    off = this_player()->query_prop(OFFSET);
    for (i=0, s=sizeof(exits); i < s; i++)
	if ((j = member_array(exits[i], Rel_dir)) != -1)
	    rexits += ({ Rel_dir[(8+j-off) % 8] });
	else rexits += ({ exits[i] });
    return rexits;
}

/* Function name: out_in_msg
 * Description:	  generates messages to be used when leaving/entering room
 * Argument:	  off - number of direction taken
 * Returns:	  ({ leaving_msg, entering_msg })
 */
private nomask string *
out_in_msg(int off)
{
    string msg_in, msg_out;

    if (this_player()->query_prop(LIVE_I_SNEAK))
    {
	msg_in = explode(this_player()->query_m_in(), ".")[0]+" sneaking.\n";
	msg_out = "sneaks ";
    }
    else
    {
	msg_in = this_player()->query_m_in() + "\n";
	msg_out = this_player()->query_m_out() + " ";
    }
    return ({ msg_out+"@@exit_map_cmd:"+MASTER+"|"+off+"@@.\n", msg_in });
}

/* Function name: map_tell_room
 * Description:	  displays messages when leaving/entering room
 * Argument:	  room - object we want to display message in
 *		  str - message (without players desc)
 *		  in - 0 == leaving message, 1 == entering (articles)
 */
private nomask void
map_tell_room(object room, string str, int in)
{
    object *pl, tp = this_player();
    string pname = tp->query_name();
    int i, s, invis = tp->query_prop(OBJ_I_INVIS);

    pl = all_inventory(room) - ({ tp });
    for (i = 0, s = sizeof(pl); i < s; i++)
	if (living(pl[i]) && CAN_SEE_IN_ROOM(pl[i]) && CAN_SEE(pl[i], tp))
	{
	    set_this_player(pl[i]);
	    if (invis) pl[i]->catch_msg("("+pname+") "+str, tp);
	    else if (in) pl[i]->catch_msg(QCNAME(tp)+" "+str, tp);
	    else pl[i]->catch_msg(QCTNAME(tp)+" "+str, tp);
	}
    set_this_player(tp);
}

/* Function name: unq_move
 * Description:	  makes player actually move after given command
 * Argument:	  str - the rest of command
 * Returns:	  0 - failed, 1 - success
 */
public int
unq_move(string str)
{
    int tmp, off = query_prop(ALLOW_MOVE_OFF);
    object d;
    string *msg;

    if (!off)
    {
	if (member_array(query_verb(), Rel_dir) == -1)
	    return ::unq_move(str);
	return 0; /*** should go through map_unq_move() ***/
    }
    off -= 1;
    if (!(d = load_map_room(off))) return 1;
    if (block_map_room(""+off)) return 1;

    // Players younger than 2 hours or carrying less than 20 % of their
    // capability doesn't get tired from walking around in the world...
    if (this_player()->query_age() > 3600 &&
	(tmp = this_player()->query_encumberance_weight()) > 20)
	if (this_player()->query_fatigue() >= Fatigue)
	    this_player()->add_fatigue(tmp > 80 ? -Fatigue * 2 : -Fatigue);
	else
	{
	    notify_fail("You are too tired to walk in that direction.\n");
	    return 0;
	}
    msg = out_in_msg(off);
    map_tell_room(this_object(), msg[0], 0);
    map_tell_room(d, msg[1], 1);
    this_player()->move_living("M", d);
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

    if ((Relative != 1) || (sizeof(val) != 2)) return 0;
    if (!(off = query_prop(ALLOW_MOVE_OFF))) return 0;
    obj_props["_room_s_dir"] = ({"@@exit_map_cmd:"+MASTER+"|"+(off-1)+"@@",
				 val[1] });
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
    int i, *d, *dir = ({ });

    for (i=0; i < 8; i++)
    {
        d = delta_map(i);
        if (s == Map[1+d[0]][1+d[1]]) dir += ({ i });
    }
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
        for(i=0, s=sizeof(dir); i < s; i++)
            tmp += ({ Std_dir[dir[i]] });
    else
        for(i=0, s=sizeof(dir); i < s; i++)
            tmp += ({ exit_map_cmd(""+dir[i]) });

    return COMPOSITE_WORDS(tmp);
}

