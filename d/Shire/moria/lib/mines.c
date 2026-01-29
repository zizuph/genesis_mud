
#include <stdproperties.h>
#include <macros.h>
#include <filepath.h>
#include "defs.h"
#include <filter_funs.h>

inherit ROGON_ROOM;

string this_dir;

int
add_item(mixed what, string text)
{
    return ::add_item(what, text+"\n");
}

int
add_cmd_item(mixed what, mixed cmds, mixed res)
{
    int i;
    if (pointerp(res)) {
	for (i=0;i<sizeof(res);i++) 
	    res[i] += "\n";
	return ::add_cmd_item(what, cmds, res);
    }
    if (stringp(res))
	return ::add_cmd_item(what, cmds, res+"\n");
    else
	return ::add_cmd_item(what, cmds, res);
}

public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired)
{
    int deep;

    if (!efunc)
	return ::add_exit(place, cmd, efunc, tired);

    deep = CONTROL->query_where(TO);

    if (!tired) {
	if (cmd == "up")
	    tired = 3;
	else if (cmd != "down")
	    tired = 1;
	else
	    tired = 0;
	if (deep < 0)
	    tired += 2;
    }

    /* Heh! We're fooling folx! This allows add_exit("aroom", ...); */
    if (!strlen(this_dir)) 
	this_dir = FPATH(MASTER, "..");

    return ::add_exit(FPATH(this_dir, place), cmd, efunc, tired);
}

create_rogon_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    this_object()->CreateMines();
    add_item(({"openings","exits"}), "@@exa_mines_openings@@");
    add_item("floor", "@@exa_mines_floor@@");
    add_item(({"ceiling", "floor"}),
      "You see nothing interesting.");
    add_item(({ "room","cave","here","place","hall","cavern","hollow",
	"passage", "corridor"
      }), "@@long@@");
    add_item(({"wall","walls"}),"@@exa_walls@@");

    my_exit_desc_mode = 1;
    enable_reset();
}

reset_rogon_room() {
    this_object()->ResetMines();
}

string
exa_mines_openings()
{
    string *exits=query_exit();
    string ret;
    object to_room;
    int i;

    if (!exits)
	ret = "There are no exits out of this room.";
    else
	ret = exits_description();

    if (TP->query_name() != "Rogon" || !exits)
	return ret;

    ret += "\n";

    for (i=0;i<sizeof(exits);i+=3)
    {
	if (LOAD_ERR(exits[i]))
	    continue;

	to_room = find_object(exits[i]);

	ret +=
	"The " + exits[i+1] + " exit leads to: " + exits[i] + "\n"
	+ "Distance : " + CONTROL->dist(TO, to_room) + "\t"
	+ "Direction: " + CONTROL->direction_plane(TO, to_room) + " "
	+ " (" + CONTROL->direction_string(TO, to_room) + ")\t"
	+ "Rize : " + CONTROL->rize(TO, to_room) + "%\n"
	+ "--------------------------------------------------------\n";
    }
    return ret;
}

string
exa_mines_floor()
{
    return "The floor is dirty.";
}

string
exa_walls()
{
    return "The walls are of granite.\n";
}

init()
{
    ::init();
    add_action("do_deep", "deep");
    add_action("do_pos",  "pos");
}

int
do_deep(string str)
{
    int deep = CONTROL->query_where(TO);

    if(str!="here")
	return 0;
    str = "You are in the ";

    if (deep > 0)
	str += LANG_WORD(deep) + " level";
    else
	str += LANG_WORD(-deep+1) + " deep";
    str += " of the Mines of Moria.\n";

    write(str);
    return 1;
}

int 
name_to_random(string str, int seed, int range)
{
    int il, sum, len;

    len = strlen(str);
    if (len > 40) 
	il = len - 40;
    sum = 0;

    while (il < len) 
	sum += str[il++];

    return random(range, seed * sum);
}


varargs string
position_description(object tp = TP)
{
    int *pos;
    string str;
    string name, room;
    int n, e, u, skill, ran;

    pos = CONTROL->room_position(TO);

    if (pos[0] == -1 && pos[1] == -1 && pos[2] == -1)
	return ("You simply can not quess your current position.\n");
    else if (pos[0] == -2 && pos[1] == -2 && pos[2] == -2)
	return ("You can not quess your current position.\n");
    else {
	if (!tp->query_wiz_level() || tp->query_name() == "Rogon") {
	    skill = tp->query_skill(SS_LOC_SENSE);
	    name = tp->query_name();
	    ran = name_to_random(name, pos[0]+pos[1]+pos[2], 1000/(skill+1));
	    ran -= 500/(skill + 1);
	}

	n = pos[0] + ran;
	e = pos[1] - ran;
	u = pos[2] + 200 + ran;

	str = "You would estimate that you are ";
	if (n > 0)
	    str += n + " yards north, ";
	else if (n < 0)
	    str += -n + " yards south, ";

	if (e > 0)
	    str += e + " yards east, ";
	else
	    str += -e + " yards west, ";

	if (u > 0)
	    str += "and " + u + " yards above the Western gate of Moria.\n";
	else if (u < 0)
	    str += "and " + -u + " yards below the Western gate of Moria.\n";
	else
	    str += "and on the same level as the Western gate of Moria.\n";
    }
    return str;
}

static int
do_pos(string arg)
{
    if (!strlen(arg))
	return notify_fail("Eh.. Pos here perhaps?\n");
    say(QCTNAME(TP) + " tries to estimate his position within the Mines of Moria.\n");
    write(position_description(TP));
    return 1;
}

static int 
is_wiz_in_moria(object p)
{
    return p && living(p) && p->query_wiz_level() && 
    ((IS_IN_MORIA(p) && p->query_prop("moria_i_wiz_message")) ||
      p->query_name()=="Rogon" && p->query_prop("moria_i_wiz_message"));
}

void
message(string what)
{
    object *pl = filter(users(), "is_wiz_in_moria", TO);
    int i;

    for (i=0;i<sizeof(pl);i++)
	pl[i]->catch_msg("MORIA> " + what);

#ifdef MORIA_LOGGING_ENABLED
    write_file(MORIA_DIR + "log/message", ctime(time())+ " : " + what);
#endif
}
