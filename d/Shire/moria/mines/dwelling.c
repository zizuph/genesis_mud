/*
 * Removed traces of ogress as it's not in theme with ME.
 * There is a hole that leads down to a troll treasure room which can be
 * used as part of a quest later on.
 * -- Finwe, June 2004
 */
#include "defs.h"


object witch;
int op;

CONSTRUCT_ROOM {
    op = 0;
    set_short("Abandoned cave");
    set_long("@@my_long@@");
    add_prop(ROOM_I_LIGHT, 1);
    add_item(({"cave","room"}),
	     "This was once a nice dwelling, but now has been abandoned. There little of value remaining.");
    add_item(({"fire-place","fire place"}),
	     "It is cold and dirty.");
    add_item(({"carpets","carpet"}),
	     "They are soft, but thread bare and have holes in them.");
    add_item("hole","@@hole@@");
    add_exit(THIS_DIR+"rattrap","north", "@@chk_north@@");
    reset();
}

RESET_ROOM {
    op = 0;
//    if (!witch || !present(witch)) {
      //witch = clone_object(MORIA_NPC+"ogress");
      //witch->move(this_object());
//    }
}

object
query_witch()
{
    return witch;
}


init() {
    ::init();
//    add_action("my_say","say");
//    add_action("my_say","'",1);
//    add_action("my_say","rsay");
//    add_action("my_say","shout");
//    add_action("my_nod","nod");
//    add_action("my_nod","agree");
    add_action("enter","enter");
    add_action("down","down");
    add_action("my_climb","climb");
}

string
my_long() {
    string desc;
    desc ="This is an abandoned cave. It was once nice but is no longer in use. A fire place sits in a corner. The walls are covered with soft carpets, and the only exit is to the north, where you came from. ";
    if (op)
	desc += "There is also a hole in the floor here.";
    return desc;
}

string
hole() {
    if (op)
	return "A hole in the floor.\n"+
	       "You can probably go down there.\n";
    else
	return "What hole?\n";
}
    
chk_north() {
  if (witch && !witch->query_allowed(this_player())) {
    write("The ogress wont let you pass.\n");
    return 1;
  }
}

int
down() {
    if (!op)
	return 0;
    this_player()->move_living("down",THIS_DIR+"deep/ringroom");
    return 1;
}

int
my_say(string what)
{
    string vrb = query_verb();
    if (vrb[0]=='\'')
	what = extract(vrb,1)+" "+what;
    if (witch && present(witch, TO))
	witch->recieve_say(TP, what);
    return 0;
}

int
my_nod(string how)
{
    if (witch && present(witch, TO) && witch)
	witch->recieve_say(TP, "yes");
    return 0;
}

int
my_climb(string str) {
  if (!op) {
    notify_fail("Climb where?\n");
    return 0;
  }
  if (str =="down" || str == "hole")
    return down();
  return 0;
}

int
enter(string str) {
  if (!op){
    notify_fail("Enter what?\n");
    return 0;
  }
  if (str == "hole")
    return down();
  return 0;
}

void
open_hole() {
    op = 1;
}
