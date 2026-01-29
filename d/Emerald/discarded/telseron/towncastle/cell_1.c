inherit "/std/room";
 
#include <tasks.h>
#include <filter_funs.h>
#include "/d/Emerald/defs.h"
 
int pushed;

int do_push(string arg);
int do_pull(string str);
int do_enter(string arg);

void
reset_room()
{
    object *obs;
 
    obs = FILTER_PLAYERS(all_inventory());
    if (sizeof(obs))
	return;
    pushed = 0;
    remove_item("hole");
    seteuid(getuid());
    call_other(TCASTLE_DIR + "passage_e", "remove_exit", "south");
}
 
void
create_room()
{
    set_short("Dark cell");
    set_long( "The cell is quite small, about 6 by 4 feet. It is also dark " +
              "and musty, there being no windows to allow fresh air. The " +
              "floor is quite dusty and on the wall someone has tried to " +
              "engrave something.\n" );
 
    add_item("floor", "It looks like some of the dirt might be mortar?\n");
    add_item(({ "wall", "north wall" }),
	     "@@wall_desc@@");
    add_item("words", "L..se st..e .n .he n..th w..l.\n");
    add_cmd_item("words", "read", "L..se st..e .n .he n..th w..l.\n");
    add_item(({ "stone", "loose stone" }),
	     "@@stone_desc@@");
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(OBJ_S_SEARCH_FUN, "search_it");
 
    clone_object(TCASTLE_DIR + "doors/cdoor1_b")->move(this_object());
}
 
string
search_it(object who, string what)
{
    int success;
 
    if (what != "north wall")
	return 0;
    success = who->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_AWARENESS }) );
    if (success > 0) {
	return "One of the stones in the wall seems to be loose!\n";
    }
    return 0;
}
 
string
wall_desc()
{
    if (pushed)
	return "There is a hole in the north wall that you might be able to "+
	       "enter.\n";
    return "Someone has tried to engrave some words on it.\n";
}
 
string
stone_desc()
{
    if (pushed)
	return "You might be able to pull it into the hole, covering it.\n";
    return "Which stone? The whole cell is built up with stones!\n";
}
 
void
init()
{
    ::init();
    add_action(do_push, "push");
    add_action(do_pull, "pull");
    add_action(do_enter, "enter");
}
 
int
do_push(string arg)
{
    notify_fail("Push what?\n");
    if (pushed || (arg != "stone" && arg != "loose stone"))
	return 0;
    write( "You put your weight on the stone and slowly push it "+
	  "into the wall, leaving a hole into a passage.\n" );
    say(QCTNAME(this_player()) + " pushes a stone into the wall.\n");
    pushed = 1;
    add_item("hole",
	     "It looks like there is a lighted passage on the other side.\n");
    seteuid(getuid());
    call_other(TCASTLE_DIR + "passage_e", "add_exit", MASTER, "south", 0);
    return 1;
}
 
int
do_pull(string arg)
{
    notify_fail("Pull what?\n");
    if (!pushed || (arg != "stone" && arg != "loose stone"))
	return 0;
    write("You pull the stone back into the hole, making it flush with the "+
	  "wall.\n");
    say(QCTNAME(this_player()) + " pulls a stone into the hole, covering it.\n");
    pushed = 0;
    remove_item("hole");
    seteuid(getuid());
    call_other(TCASTLE_DIR + "passage", "remove_exit", "south");
    return 1;
}
 
int
do_enter(string arg)
{
    notify_fail("Enter what?\n");
    if (!pushed || arg != "hole")
	return 0;
    set_dircmd(arg);
    this_player()->move_living("into a hole", TCASTLE_DIR + "passage_e");
    return 1;
}
